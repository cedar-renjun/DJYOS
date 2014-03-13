//----------------------------------------------------
//Copyright (C), 2011.9,wjz.
//版权所有 (C), 2011.9,wjz
//所属模块: djysh模块
//作者：wjz
//版本：V0.1.0
//文件描述: djyos的shell主模块，提供shell的实现过程以及内置命令
//修订历史:
// 1. 日期:2010-09-10之前
//   作者:lst
//   新版本号：djysh0.0.1
//     修改说明：shell实现的设计。
// 2. 日期:2011-06-15
//   作者:wjz
//   新版本号：djysh0.0.2
//   修改说明: 添加文件系统命令以及注册文件系统shell模块。
// 2. 日期:2011-09-24
//   作者:wjz
//   新版本号：djysh1.0.0
//   修改说明: 添加事件、事件类型、中断、内存、帮助等命令，
//               djysh1.0.0，可以作为一个简单完整的shell了。
//------------------------------------------------------

#include "os_inc.h"

#if (cfg_shell == 1)

#include "char_term.h"
#include <string.h>
#include "shell_fs.h"
#include "shell.h"

bool_t (*sh_ext_command)(char *buf);

//----调试模块初始化函数-------------------------------------------------------
//功能: 初始化调试模块
//参数: 无
//返回: 1
//-----------------------------------------------------------------------------
ptu32_t module_init_shell(ptu32_t para)
{
    uint16_t shell_evtt;
    shell_evtt = djy_evtt_regist(enum_correlative,              //关联型事件
                                cn_prio_real,       //默认优先级
                                0,                  //线程保留数，关联型无效
                                0,                  //线程上限，关联型无效
                                1,                  //参数队列长度上限
                                sh_service,         //入口函数
                                0x3000,             //栈尺寸
                                "shell"             //事件类型名
                                );
    if(shell_evtt == cn_invalid_evtt_id)
        return false;
    if(djy_event_pop(shell_evtt,NULL,0,NULL,0,0,0)
                        == cn_invalid_event_id)
    {
        djy_evtt_unregist(shell_evtt);
    }
    
    return 1;
}

void sh_install_sh_ext(bool_t (*sh_user_ext)(char *buf))
{
    if(sh_user_ext != NULL)
        sh_ext_command = sh_user_ext;
}

//----提取目录---------------------------------------------------------------
//功能: 从buf中提取一个由'\\'或行结束符隔开的单词，next用于返回下一个单词首地址，
//      如果没有下一个单词，则next=NULL。
//参数: buf，待分析的字符串
//      next，返回下一个单词指针
//返回: 提取的单词指针，已将单词后面的分隔符换成串结束符'\0'
//-----------------------------------------------------------------------------
char *sh_get_item(char *buf,char **next)
{
    uint32_t i=0;
    *next = NULL;
    while(1)
    {
        if((buf[i] == '\\') || (buf[i] == 0))
        {
            if(buf[i] == 0)
                return buf;
            else
            {
                buf[i] = '\0';
                break;
            }
        }
        i++;
    }
    i++;
    while(buf[i] != 0)
    {
        if((buf[i]!='\\') && (buf[i] != '\n') && (buf[i] != '\r'))
        {
            *next = &buf[i];
            break;
        }
        i++;
    }
    return buf;
}


//----提取单词---------------------------------------------------------------
//功能: 从buf中提取一个由空格或行结束符隔开的单词，next用于返回下一个单词首地址，
//      如果没有下一个单词，则next=NULL。
//参数: buf，待分析的字符串
//      next，返回下一个单词指针
//返回: 提取的单词指针，已将单词后面的分隔符换成串结束符'\0'
//-----------------------------------------------------------------------------
char *sh_get_word(char *buf,char **next)
{
    uint32_t i=0;
    *next = NULL;
    if(buf == NULL)
        return NULL;
    while(1)
    {
        if((buf[i] == ' ') || (buf[i] == 0))
        {
            if(buf[i] == 0)
                return buf;
            else
            {
                buf[i] = '\0';
                break;
            }
        }
        i++;
    }
    i++;
    while(buf[i] != 0)
    {
        if(buf[i]!=' ')
        {
            if((buf[i] == '\n') || (buf[i] == '\r'))
                *next = NULL;
            else
                *next = &buf[i];
            break;
        }
        i++;
    }
    return buf;
}

//----显示for循环时间----------------------------------------------------------
//功能: 显示一个for(;;)循环的执行时间，循环变量分别是8位、16位、32位。
//参数: 无
//返回: 无
//-----------------------------------------------------------------------------
bool_t sh_show_for_cycle(char *param)
{
    djy_printf("32位循环变量 %dnS\r\n", djy_get_for_time(4));
    djy_printf("16位循环变量 %dnS\r\n", djy_get_for_time(2));
    djy_printf("8位循环变量 %dnS\r\n", djy_get_for_time(1));

    return true;
}

//----显示资源队列----------------------------------------------------------
//功能: 按参数要求显示资源队列中资源的名字，若该资源名字为空，则显示"无名资源"
//参数: 参数字符串，含义:
//          all，显示全部资源队列
//          flash chip，显示文件系统加载的flash芯片
//          semaphore，显示系统中的所有信号量
//          mutex，显示系统中的所有互斥量
//          device，显示系统中的所有泛设备
//          opened files，显示打开的文件和路径
//          pool，显示所有内存池
//返回: true
//-----------------------------------------------------------------------------
bool_t sh_list_rsc(char *param)
{
    struct rsc_node *rsc_tree;
    if(param == NULL)
        sh_list_rsc_all();
    else
    {
        rsc_tree = rsc_search_tree(param);
        if(rsc_tree == NULL)
        {
            djy_printf("没找到 %s 资源树\r\n",param);
        }
        else
            __sh_show_branche(rsc_tree);
    }
    return true;
}

//----显示全部资源----------------------------------------------------------
//功能: 由sh_list_rsc函数调用，显示全部资源
//参数: 无
//返回: 无
//-----------------------------------------------------------------------------
void sh_list_rsc_all(void)
{
    struct rsc_node *rsc_root;
    rsc_root = rsc_get_root();
    __sh_show_branche(rsc_root);
}

//----显示资源树---------------------------------------------------------------
//功能: 显示某资源结点起始的一个资源分支，不包含该资源自身
//参数: 无
//返回: 无
//-----------------------------------------------------------------------------
void __sh_show_branche(struct rsc_node *branche)
{
    struct rsc_node *current_node = branche;
    ucpu_t len;
    char neg[20];
    for(len = 0; len<20; len++)
        neg[len] = '-';
    while(1)
    {
        current_node = rsc_trave_scion(branche,current_node);
        if(current_node == NULL)
        {
            djy_printf("\r\n");
            break;
        }
        len = rsc_get_class(current_node);
        neg[len] = '\0';
        djy_printf("%s", neg);
        neg[len] = '-';
        if(current_node->name != NULL)
        {
            djy_printf("%s\r\n", current_node->name);
        }else
        {
            djy_printf("无名资源\r\n");
        }
    }
}

//----显示内存-----------------------------------------------------------------
//功能: 显示某地址开始的一段内存，每行显示16个单元，只显示，不能修改
//参数: param，参数串，本命令需要三个参数，用空格隔开
//          参数1:起始地址，10进制或16进制(0x开头)
//          参数2:显示的单元数
//          参数3:每单元字节数，合法值是1、2、4、8，其他数值将返回错误
//返回: true=正常显示，false=错误
//-----------------------------------------------------------------------------
bool_t sh_show_memory(char *param)
{
    ptu32_t addr;
    uint32_t unit_num,unit_bytes,len;
    char *word_addr,*word_un,*word_ub,*word_trail;

    //提取3个参数
    word_addr = strsep(&param," ");
    word_un = strsep(&param," ");
    word_ub = strsep(&param," ");
    word_trail = strsep(&param," ");
    if((word_addr == NULL)||(word_un == NULL)
            ||(word_ub == NULL)||(word_trail != NULL))
    {
        djy_printf("\r\n格式错误，正确格式是：\r\n>d 地址 单元数 每单元字节数\r\n");
        return false;
    }
    addr = djy_atol(word_addr);
    unit_num = djy_atol(word_un);
    unit_bytes = djy_atol(word_ub);
#if (cn_byte_bits == 8)  //字节位宽=8，最常见的情况
    switch(unit_bytes)
    {
        case 1:
        	djy_printf("0x%8x:", addr);
            for(len = 0; len < unit_num; len++)
            {
            	djy_printf("%2x ", *(uint8_t*)addr);
                addr ++;
                if(addr %8 == 0)
                {
                    djy_printf("\r\n");
                    if(len != unit_num)
                    {
                    	djy_printf("0x%8x:", addr);
                    }
                }
            }
            break;
        case 2:
            addr &= ~(ptu32_t)1;//只能从偶数开始
        	djy_printf("0x%8x:", addr);
            for(len = 0; len < unit_num; len++)
            {
            	djy_printf("%4x ", *(uint16_t*)addr);
                addr +=2;
                if(addr %16 == 0)
                {
                    djy_printf("\r\n");
                    if(len != unit_num)
                    {
                    	djy_printf("0x%8x:", addr);
                    }
                }
            }
            break;
        case 4:
            addr &= ~(ptu32_t)3;//只能从偶数开始
        	djy_printf("0x%8x:", addr);
            for(len = 0; len < unit_num; len++)
            {
            	djy_printf("%8x ", *(uint32_t*)addr);
                addr +=4;
                if(addr %32 == 0)
                {
                    djy_printf("\r\n");
                    if(len != unit_num)
                    {
                    	djy_printf("0x%8x:", addr);
                    }
                }
            }
            break;
        case 8:
            addr &= ~(ptu32_t)7;//只能从偶数开始
        	djy_printf("0x%8x:", addr);
            for(len = 0; len < unit_num; len++)
            {
            	djy_printf("%8x", *(uint32_t*)addr);
                addr +=4;
            	djy_printf("%8x ", *(uint32_t*)addr);
                addr +=4;
                if(addr %64 == 0)
                {
                    djy_printf("\r\n");
                    if(len != unit_num)
                    {
                    	djy_printf("0x%8x:", addr);
                    }
                }
            }
            break;
        default :
            djy_printf("\r\n参数错误\r\n");
            return false;
        	break;
    }
#elif (cn_byte_bits == 16)  //字节位宽=16
    switch(unit_bytes)
    {
        case 1:
        {
        	djy_printf("0x%8x:", addr);
            for(len = 0; len < unit_num; len++)
            {
            	djy_printf("%4x ", *(uint16_t*)addr);
                addr ++;
                if(addr %8 == 0)
                {
                    djy_printf("\r\n");
                    if(len != unit_num)
                    {
                    	djy_printf("0x%8x:", addr);
                    }
                }
            }
        } break;
        case 2:
        {
            addr &= ~(ptu32_t)1;
        	djy_printf("0x%8x:", addr);
            for(len = 0; len < unit_num; len++)
            {
            	djy_printf("%8x ", *(uint32_t*)addr);
                addr +=2;
                if(addr %16 == 0)
                {
                    djy_printf("\r\n");
                    if(len != unit_num)
                    {
                    	djy_printf("0x%8x:", addr);
                    }
                }
            }
        } break;
        case 4:
        {
            addr &= ~(ptu32_t)3;
        	djy_printf("0x%8x:", addr);
            for(len = 0; len < unit_num; len++)
            {
            	djy_printf("%8x ", *(uint32_t*)addr);
                addr +=2;
            	djy_printf("%8x ", *(uint32_t*)addr);
                djy_putchar(' ');
                addr +=2;
                if(addr %32 == 0)
                {
                    djy_printf("\r\n");
                    if(len != unit_num)
                    {
                    	djy_printf("0x%8x:", addr);
                    }
                }
            }
        } break;
        default :
        {
            djy_printf("\r\n参数错误\r\n");
            return false;
        } break;
    }
#elif (cn_byte_bits == 32)  //字节位宽=32
    switch(unit_bytes)
    {
        case 1:
        {
        	djy_printf("0x%8x:", addr);
            for(len = 0; len < unit_num; len++)
            {
            	djy_printf("%8x ", *(uint32_t*)addr);
                addr ++;
                if(addr %8 == 0)
                {
                    djy_printf("\r\n");
                    if(len != unit_num)
                    {
                    	djy_printf("0x%8x:", addr);
                    }
                }
            }
        } break;
        case 2:
        {
            addr &= ~(ptu32_t)1;
        	djy_printf("0x%8x:", addr);
            for(len = 0; len < unit_num; len++)
            {
            	djy_printf("%8x ", *(uint32_t*)addr);
                addr +=2;
            	djy_printf("%8x ", *(uint32_t*)addr);
                printf_char(' ');
                addr +=2;
                if(addr %16 == 0)
                {
                    djy_printf("\r\n");
                    if(len != unit_num)
                    {
                    	djy_printf("0x%8x:", addr);
                    }
                }
            }
        } break;
        default :
        {
            djy_printf("\r\n参数错误\r\n");
            return false;
        } break;
    }
#endif
    djy_printf("\r\n");
    return true;
}

//----写入内存-----------------------------------------------------------------
//功能: 写入某地址开始的一段内存
//参数: param，参数串，本命令需要三个参数，用空格隔开
//          参数1:起始地址，10进制或16进制(0x开头)
//          参数2:显示的单元数
//          参数3:每单元字节数，合法值是1、2、4，其他数值将返回错误
//          参数4:待填充的内容
//返回: true=正常显示，false=错误
//-----------------------------------------------------------------------------
bool_t sh_fill_memory(char *param)
{
    ptu32_t addr;
    uint32_t unit_num,unit_bytes,len,data;
    char *word;

    word = strsep(&param," ");
    addr = djy_atol(word);
    word = strsep(&param," ");
    unit_num = djy_atol(word);
    word = strsep(&param," ");
    unit_bytes = djy_atol(word);
    word = strsep(&param," ");
    data = djy_atol(word);
#if (cn_byte_bits == 8)  //字节位宽=8，最常见的情况
    switch(unit_bytes)
    {
        case 1:
        	djy_printf("0x%8x:", addr);
            for(len = 0; len < unit_num; len++)
            {
                *(uint8_t*)addr = (u8)data;
                addr ++;
            }
            break;
        case 2:
            addr &= ~(ptu32_t)1;
        	djy_printf("0x%8x:", addr);
            for(len = 0; len < unit_num; len++)
            {
                *(u16*)addr = (u16)data;
                addr +=2;
            }
            break;
        case 4:
            addr &= ~(ptu32_t)3;
        	djy_printf("0x%8x:", addr);
            for(len = 0; len < unit_num; len++)
            {
                *(u32*)addr = (u32)data;
                addr +=4;
            }
            break;
        default :
            djy_printf("\r\n参数错误\r\n");
            return false;
            break;
    }
#elif (cn_byte_bits == 16)  //字节位宽=16
    switch(unit_bytes)
    {
        case 1:
        {
        	djy_printf("0x%8x:", addr);
            for(len = 0; len < unit_num; len++)
            {
                *(u16*)addr = (u16)data;
                addr ++;
            }
        } break;
        case 2:
        {
            addr &= ~(ptu32_t)1;
        	djy_printf("0x%8x:", addr);
            for(len = 0; len < unit_num; len++)
            {
                *(u32*)addr = (u32)data;
                addr +=2;
            }
        } break;
        default :
        {
            djy_printf("\r\n参数错误\r\n");
            return false;
        } break;
    }
#elif (cn_byte_bits == 32)  //字节位宽=32
    switch(unit_bytes)
    {
        case 1:
        {
        	djy_printf("0x%8x:", addr);
            for(len = 0; len < unit_num; len++)
            {
                *(u32*)addr = (u32)data;
                addr ++;
            }
        } break;
        default :
        {
            djy_printf("\r\n参数错误\r\n");
            return false;
        } break;
    }
#endif
    return true;
}

//----命令串分析---------------------------------------------------------------
//功能: 分析buf包含的字符串第一个单词是否keyword命令。并且在param中返回keyword
//      后第一个非零且非回车换行的字符的指针，该指针实际包含第一个命令行参数的
//      地址。如果没有参数，则param=NULL。
//参数: buf，待分析的字符串
//      keyword，待匹配的命令
//      param，返回命令行参数指针
//返回: true = 命令匹配，false=命令不匹配
//-----------------------------------------------------------------------------
bool_t sh_cmd_parser(const char *buf,const char *keyword,char **param)
{
    uint32_t i=0;
    char buf2[255];

    if(buf == NULL)
    	return false;
    *param = NULL;
    //获取不带参数的命令的停止符号或者后面空格的下标号i
    for(i=0;i<255;i++)
    {    
        if((buf[i]==' ')||(buf[i] == '\0'))
            break;
    }
    memcpy(buf2,buf,i);
    buf2[i] = '\0';
    //比较没有带参数的命令
    if(strcmp(buf2,keyword)!=0)
        return false;

    while(buf[i] != 0)
    {
        if(buf[i]!=' ')
        {
            if((buf[i] == '\n') || (buf[i] == '\r'))
                *param = NULL;
            else
                *param = (char*)&buf[i];
            break;
        }
        i++;
    }
    return true;
}

//----显示cd的帮助-------------------------------------------------------------
//功能: 由sh_list_fscmd_help函数调用，cd的帮助
//参数: 无
//返回: 无
//-----------------------------------------------------------------------------
void sh_list_cd_help(void)
{
    djy_printf("DBX_name[:]         进入指定文件柜名根目录\r\n");
    djy_printf("                    例如：D： 进入D文件柜根目录\r\n");
    djy_printf("cd/chdir[文件柜：]路径 显示当前目录的名称或改变当前目录\r\n");
    djy_printf("                    例如: 1)cd C:\\folder 进入folder目录\r\n");
    djy_printf("                          2)cd folder 进入folder目录\r\n");
    djy_printf("cd/chdir[](空字符) 显示当前目录名称\r\n");
    djy_printf("cd/chdir[\\]        更换到根目录\r\n");
	djy_printf("cd/chdir[..]       更换到上一级目录\r\n");
	djy_printf("                   例如: 1)cd ..\\.. 进入上两级的目录 \r\n");
	djy_printf("                         2)cd ..\\folder 进入上一级目录中含有folder的目录 \r\n");
}
//----显示dir的帮助------------------------------------------------------------
//功能: 由sh_list_fscmd_help函数调用，dir的帮助
//参数: 无
//返回: 无
//-----------------------------------------------------------------------------
void sh_list_dir_help(void)
{

	djy_printf("dir	[文件柜：]路径  [文件柜：]路径... ...\r\n");
	djy_printf("            显示指定目录下的文件和子目录列表\r\n");
	djy_printf("dir	[文件柜：][含有通配符路径][文件柜：][含有通配符路径]... ...\r\n");
	djy_printf("            显示指定目录下匹配的文件和子目录列表\r\n");
	djy_printf("dir	[\\][\\]... ...	显示根目录下一级的文件和子目录列表\r\n");
	djy_printf("dir	[..][..]... ...	显示当前目录上一级的文件和子目录列表\r\n");
	djy_printf("dir	[](空字符)      显示当前目录下的文件和子目录列表\r\n");
}
//----显示rd的帮助----------------------------------------------------------
//功能: 由sh_list_fscmd_help函数调用，rd的帮助
//参数: 无
//返回: 无
//-----------------------------------------------------------------------------
void sh_list_rd_help(void)
{
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
}
//----显示ren的帮助----------------------------------------------------------
//功能: 由sh_list_fscmd_help函数调用，ren的帮助
//参数: 无
//返回: 无
//-----------------------------------------------------------------------------
void sh_list_ren_help(void)
{
	djy_printf("Ren/rename [文件柜:][路径]文件名1 文件名2\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
}
//----显示信号量----------------------------------------------------------
//功能: 由sh_list_fscmd_help函数调用，chkdsk的帮助
//参数: 无
//返回: 无
//-----------------------------------------------------------------------------
void sh_list_md_help(void)
{
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
}
//----显示deltree的帮助----------------------------------------------------------
//功能: 由sh_list_fscmd_help函数调用，deltree的帮助
//参数: 无
//返回: 无
//-----------------------------------------------------------------------------
void sh_list_deltree_help(void)
{
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
}
//----显示del的帮助----------------------------------------------------------
//功能: 由sh_list_fscmd_help函数调用，del的帮助
//参数: 无
//返回: 无
//-----------------------------------------------------------------------------
void sh_list_del_help(void)
{
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
}
//----显示copy的帮助----------------------------------------------------------
//功能: 由sh_list_fscmd_help函数调用，copy的帮助
//参数: 无
//返回: 无
//-----------------------------------------------------------------------------
void sh_list_copy_help(void)
{
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
}
//----显示move的帮助----------------------------------------------------------
//功能: 由sh_list_fscmd_help函数调用，move的帮助
//参数: 无
//返回: 无
//-----------------------------------------------------------------------------
void sh_list_move_help(void)
{
 	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
}
//----显示chkdsk的帮助----------------------------------------------------------
//功能: 由sh_list_fscmd_help函数调用，chkdsk的帮助
//参数: 无
//返回: 无
//-----------------------------------------------------------------------------
void sh_list_chkdbx_help(void)
{
	djy_printf("chkdbx 文件名 显示该文件柜下的文件柜属性\r\n");

}
//----显示ver的帮助----------------------------------------------------------
//功能: 由sh_list_fscmd_help函数调用，ver的帮助
//参数: 无
//返回: 无
//-----------------------------------------------------------------------------
void sh_list_ver_help(void)
{
 	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
}
//----显示chcp的帮助----------------------------------------------------------
//功能: 由sh_list_fscmd_help函数调用，chcp的帮助
//参数: 无
//返回: 无
//-----------------------------------------------------------------------------
void sh_list_chcp_help(void)
{
 	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
}

//----显示format的帮助----------------------------------------------------------
//功能: 由sh_list_fscmd_help函数调用，format的帮助
//参数: 无
//返回: 无
//-----------------------------------------------------------------------------
void sh_list_format_help(void)
{
 	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
}

//----显示time的帮助----------------------------------------------------------
//功能: 由sh_list_fscmd_help函数调用，time的帮助
//参数: 无
//返回: 无
//-----------------------------------------------------------------------------
void sh_list_time_help(void)
{
 	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
}

//----显示date的帮助----------------------------------------------------------
//功能: 由sh_list_fscmd_help函数调用，date的帮助
//参数: 无
//返回: 无
//-----------------------------------------------------------------------------
void sh_list_date_help(void)
{
 	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
}
//----显示cls的帮助----------------------------------------------------------
//功能: 由sh_list_fscmd_help函数调用，cls的帮助
//参数: 无
//返回: 无
//-----------------------------------------------------------------------------
void sh_list_cls_help(void)
{
 	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
}
//----显示list-rsc的帮助----------------------------------------------------------
//功能: 由sh_list_fscmd_help函数调用，cls的帮助
//参数: 无
//返回: 无
//-----------------------------------------------------------------------------
void sh_list_listrsc_help(void)
{
 	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
}
//----显示get-evtt的帮助----------------------------------------------------------
//功能: 由sh_list_fscmd_help函数调用，cls的帮助
//参数: 无
//返回: 无
//-----------------------------------------------------------------------------
void sh_list_getevtt_help(void)
{
 	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
}
//----显示get-envent的帮助----------------------------------------------------------
//功能: 由sh_list_cmd_help函数调用，cls的帮助
//参数: 无
//返回: 无
//-----------------------------------------------------------------------------
void sh_list_getevent_help(void)
{
 	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
}
//----显示get-int的帮助----------------------------------------------------------
//功能: 由sh_list_cmd_help函数调用，cls的帮助
//参数: 无
//返回: 无
//-----------------------------------------------------------------------------
void sh_list_getint_help(void)
{
 	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
}

void shell_cmd_help()
{
	djy_printf("\r\n有关某个命令的详细信息，请输入help [某个命令]\r\n");
	djy_printf("\r\n");

	djy_printf("list-rsc        列出系统中的资源名字和层次关系\r\n");
	djy_printf("speed           测量循环运行速度\r\n");
    djy_printf("event           显示事件表\r\n");
    djy_printf("evtt            显示事件类型表\r\n");
    djy_printf("heap            显示系统堆使用情况\r\n");
    djy_printf("stack           显示系统中所有已经分配线程的事件的栈信息\r\n");
    djy_printf("lock            显示系统中所有信号量和互斥量的信息\r\n");
    djy_printf("d               读取内存里的数据\r\n");
    djy_printf("f               写数据到内存\r\n");
    djy_printf("help            DJYOS的命令帮助信息\r\n");
	djy_printf("ver             显示djyos的版本\r\n");
	djy_printf("date            显示或者设置日期\r\n");
	djy_printf("time            显示当前时间或者设置输入新时间\r\n");
	djy_printf("\r\n");

	djy_printf("cd              显示当前目录的名称或将其更改\r\n");
	djy_printf("md              创建一个目录\r\n");
	djy_printf("mkdir           创建一个目录\r\n");
	djy_printf("rd              删除一个目录\r\n");
	djy_printf("rmdir           删除一个目录\r\n");
	djy_printf("copy            复制一个文件\r\n");
	djy_printf("move            将一个或多个文件移动到指定目录下\r\n");
	djy_printf("ren             重命名一个文件\r\n");
	djy_printf("rename          重命名一个文件\r\n");
	djy_printf("del             删除至少一个文件\r\n");
	djy_printf("dir             显示指定目录下的文件和子目录列表\r\n");
	djy_printf("\r\n");

	djy_printf("文件系统擦除与重建命令（慎用！）\r\n");
	djy_printf("chip-erase      擦除NANDFLASH芯片中所有内容\r\n");
	djy_printf("create-dbx      创建文件柜\r\n");
	djy_printf("format          格式化文件系统\r\n");
	djy_printf("chkdbx          显示文件柜空间的参数\r\n");
    
}


//----显示文件系统命令帮助----------------------------------------------------------
//功能: 按参数要求显示资源队列中资源的名字，若该资源名字为空，则显示"无名资源"
//参数: 参数字符串，含义:
//返回: true
//-----------------------------------------------------------------------------
bool_t sh_list_cmd_help(char *param)
{
    char *next_para;

   	if(sh_cmd_parser(param,"cd",&next_para) == true)
        sh_list_cd_help();
    else if(sh_cmd_parser(param,"dir",&next_para) == true)
        sh_list_dir_help();
    else if(sh_cmd_parser(param,"rd",&next_para) == true)
        sh_list_rd_help();
    else if(sh_cmd_parser(param,"ren",&next_para) == true)
        sh_list_rd_help();
    else if(sh_cmd_parser(param,"md",&next_para) == true)
        sh_list_md_help();
    else if(sh_cmd_parser(param,"deltree",&next_para) == true)
        sh_list_deltree_help();
    else if(sh_cmd_parser(param,"del",&next_para) == true)
        sh_list_del_help();
    else if(sh_cmd_parser(param,"copy",&next_para) == true)
        sh_list_copy_help();
	else if(sh_cmd_parser(param,"move",&next_para) == true)
        sh_list_move_help();
  	else if(sh_cmd_parser(param,"chkdbx",&next_para) == true)
        sh_list_chkdbx_help();
   	else if(sh_cmd_parser(param,"ver",&next_para) == true)
        sh_list_ver_help();
   	else if(sh_cmd_parser(param,"time",&next_para) == true)
        sh_list_time_help();
	else if(sh_cmd_parser(param,"date",&next_para) == true)
        sh_list_date_help();
  	else if(sh_cmd_parser(param,"chcp",&next_para) == true)
        sh_list_chcp_help();
   	else if(sh_cmd_parser(param,"format",&next_para) == true)
        sh_list_format_help();
   	else if(sh_cmd_parser(param,"cls",&next_para) == true)
        sh_list_cls_help();
   	else if(param == NULL)
        shell_cmd_help();
    else
        djy_printf("参数错误\r\n");
    return true;
}
bool_t sh_ver(char *param)
{
	djy_printf("\r\n%s\r\n", djyos_kernel_version);

	return true;
}

bool_t sh_date(char *param)
{
	s64 nowtime;
	struct djy_tm dtm;
    char command[256];
    char buf[8];
    int cmdlen;
    int res;

    nowtime = djy_time(NULL);
	dtm = localtime(nowtime);

	djy_printf("\r\n当前日期：%d/%02d/%02d %s",
			dtm.tm_year, dtm.tm_mon, dtm.tm_mday, tm_wdays[dtm.tm_wday]);
	djy_printf("\r\n输入新日期：");

    cmdlen = djy_scanf(NULL, command);
	if ((8<=cmdlen) && (cmdlen<=10))
	{
		//日期为“2012/02/12”形式，在它背后加入时间
		strcat(command, ",");	// 逗号用于分开日期和时间
		djy_itoa(dtm.tm_hour, buf, 10);
		strcat(command, buf);
		strcat(command, ":");
		djy_itoa(dtm.tm_min, buf, 10);
		strcat(command, buf);
		strcat(command, ":");
		djy_itoa(dtm.tm_sec, buf, 10);
		strcat(command, buf);

		res = time_set_datetime_str(command);
		switch (res)
		{
		case cn_ck_error_code_year:
			djy_printf("年份错误。");
			break;
		case cn_ck_error_code_month:
			djy_printf("月份错误。");
			break;
		case cn_ck_error_code_day:
			djy_printf("日期错误。");
			break;
		default:
			break;
		}
	}

	djy_printf("\r\n");
    return true;
}

bool_t sh_time(char *param)
{
	s64 nowtime;
	struct djy_tm dtm;
    char command[256];
    char time[16];
    char buf[8];
    int cmdlen;
    int res;

    nowtime = djy_time(NULL);
	dtm = localtime(nowtime);

	djy_printf("\r\n当前时间：%02d:%02d:%02d", dtm.tm_hour, dtm.tm_min, dtm.tm_sec);
	djy_printf("\r\n输入新时间：");

    cmdlen = djy_scanf(NULL, command);
	if ((5<=cmdlen) && (cmdlen<=8))
	{
		time[0] = '\0';
		strcpy(time, command);	// 将获得的时间字符串复制到buf中
		//时间为“03:32:1”形式，在它前面加日期
		command[0] = '\0';
		djy_itoa(dtm.tm_year, buf, 10);
		strcat(command, buf);
		strcat(command, "/");
		djy_itoa(dtm.tm_mon, buf, 10);
		strcat(command, buf);
		strcat(command, "/");
		djy_itoa(dtm.tm_mday, buf, 10);
		strcat(command, buf);
		strcat(command, ",");	// 逗号用于分开日期和时间
		strcat(command, time);

		res = time_set_datetime_str(command);
		switch (res)
		{
		case cn_ck_error_code_hour:
			djy_printf("小时错误。");
			break;
		case cn_ck_error_code_minute:
			djy_printf("分钟错误。");
			break;
		case cn_ck_error_code_second:
			djy_printf("秒钟错误。");
			break;
		default:
			break;
		}
	}

	djy_printf("\r\n");
    return true;
}

//----转换输入命令的大写字母为小写----------------------------------------------
//功能: 转换shell下输入的命令"buf"中空格前的大写字母为小写。
//参数: cmd，shell下输入的命令命令"buf"(cmd)
//返回: 0
//-----------------------------------------------------------------------------
void capital_convert_lowercase(char *cmd)
{

	while(*cmd!='\0')
    {
           if(*cmd>='A'&&*cmd<='Z')
            *cmd=*cmd+('a'-'A');
            cmd++; //下一个字符
         //遇到空格
         if(*cmd==' ')
         	break;
    }
	return ;
}

//----显示事件表---------------------------------------------------------------
//功能: 显示事件列表
//参数: 无
//返回: true
//-----------------------------------------------------------------------------
bool_t sh_show_event(char *param)
{
    u32 cmd;
    u16 evtt;
    cmd = cn_db_info_event;
#if(cfg_debug_info == 1)
    evtt = djy_get_evtt_id("debug_info");
    djy_event_pop(evtt,NULL,cn_timeout_forever,&cmd,4,0,0);
#else
    djy_printf("没有包含调试信息模块\r\n");
#endif

    return true;
}

//----显示事件类型表-----------------------------------------------------------
//功能: 显示事件类型列表
//参数: 无
//返回: true
//-----------------------------------------------------------------------------
bool_t sh_show_evtt(char *param)
{
    u32 cmd;
    u16 evtt;
    cmd = cn_db_info_evtt;
#if(cfg_debug_info == 1)
    evtt = djy_get_evtt_id("debug_info");
    djy_event_pop(evtt,NULL,cn_timeout_forever,&cmd,4,0,0);
#else
    djy_printf("没有包含调试信息模块\r\n");
#endif

    return true;
}

//----显示系统堆使用情况-------------------------------------------------------
//功能: 显示系统堆使用情况
//参数: 无
//返回: true
//-----------------------------------------------------------------------------
bool_t sh_show_heap(char *param)
{
    u32 cmd;
    u16 evtt;
    cmd = cn_db_info_heap;
#if(cfg_debug_info == 1)
    evtt = djy_get_evtt_id("debug_info");
    djy_event_pop(evtt,NULL,cn_timeout_forever,&cmd,4,0,0);
#else
    djy_printf("没有包含调试信息模块\r\n");
#endif
    return true;
}


//----显示栈使用情况-----------------------------------------------------------
//功能: 显示系统中所有已经分配线程的事件的栈信息
//参数: 无
//返回: true
//-----------------------------------------------------------------------------
bool_t sh_show_stack(char *param)
{
    u32 cmd;
    u16 evtt;
    cmd = cn_db_info_stack;
#if(cfg_debug_info == 1)
    evtt = djy_get_evtt_id("debug_info");
    djy_event_pop(evtt,NULL,cn_timeout_forever,&cmd,4,0,0);
#else
    djy_printf("没有包含调试信息模块\r\n");
#endif
    return true;
}

//----显示全部锁-----------------------------------------------------------
//功能: 显示系统中所有信号量和互斥量的信息
//参数: 无
//返回: true
//-----------------------------------------------------------------------------
bool_t sh_show_lock(char *param)
{
    u32 cmd;
    u16 evtt;
    cmd = cn_db_info_lock;
#if(cfg_debug_info == 1)
    evtt = djy_get_evtt_id("debug_info");
    djy_event_pop(evtt,NULL,cn_timeout_forever,&cmd,4,0,0);
#else
    djy_printf("没有包含调试信息模块\r\n");
#endif
    return true;
}

extern bool_t __erase_all_nand(char *param);

//内置命令表
struct cmd_table shell_cmd_table[] =
{
    {"list-rsc", sh_list_rsc},
    {"speed", sh_show_for_cycle},
    {"event", sh_show_event},
    {"evtt", sh_show_evtt},
    {"heap", sh_show_heap},
    {"stack", sh_show_stack},
    {"lock", sh_show_lock},
    {"d", sh_show_memory},
    {"f", sh_fill_memory},
    {"help", sh_list_cmd_help},
    {"ver", sh_ver},
	{"date", sh_date},
	{"time", sh_time},


#if ((cfg_djyfs == 1) && (cfg_run_mode != cn_mode_tiny))
    {"rmdir", sh_rd},
    {"rd", sh_rd},
    {"dir", sh_dir},
    {"rename", sh_ren},
    {"ren", sh_ren},
    {"del", sh_del},
    {"copy", sh_copy},
    {"move", sh_move},
    {"chdir", sh_cd},
    {"cd", sh_cd},
    {"mkdir", sh_md},
    {"md", sh_md},
#if(cfg_djyfs_flash == 1)
    {"chip-erase", __erase_all_nand},
    {"create-dbx", sh_create_dbx},
#endif
    {"format", sh_format},
    {"chkdbx", sh_chkdbx},
#endif

    {NULL,NULL}
};

//----判断':'后面是否有数据-----------------------------------------------------
//功能: 从一个可能包含多级路径名和文件名的字符串中判断第一次遇到'\'之后是否还有
//      数据
//参数: path，被测路径，格式如"C:\aaaa\bbbb\cccc"
//返回: true=成功, 说明':'之后有数据,或者没有':'
//      false=失败，说明':'之后没有数据
//备注: path应该是经过合法性检查的字符串，不会出现word超长的问题
//-----------------------------------------------------------------------------
bool_t __judge_colon_is_data(char *path)
{
    uint32_t index;
    uint32_t  name_len;

	name_len = strlen(path);
    for(index = 0; index< name_len; index++)
    {
        if(path[index] == ':')    //遇到字符'\'
        {
            if(path[index+1] != '\0')
            	return true;
        	else
            	return false;
        }
    }
    //字符串里没有冒号
	if(index == name_len)
    	return true;
	return false;        
}

//----执行控制台命令---------------------------------------------------
//功能: 分析并执行控制台命令
//参数: 无
//返回: 无
//备注: 到时候用哈希表等，进行更加快速的比较。如果这样的比较，命令多了。
//      那还不无奈死了。
//---------------------------------------------------------------------
bool_t sh_exec_command(char *buf)
{
    bool_t result = false;
    char *param;
    uint32_t i=0;
    //串口限制读取255字符，在这里提示超长就行。命令里，就不用操作，提示
    //太长了
	if(strnlen(buf, cn_shell_cmd_limit+1) > cn_shell_cmd_limit)
	{
        djy_printf("输入字符串太长\r\n");
	}
    //转换buf中的大写字母为小写
	capital_convert_lowercase(buf);
    
    if(!__judge_colon_is_data(buf))
    {
#if ((cfg_djyfs == 1) && (cfg_run_mode != cn_mode_tiny))
        if(cd_dbx(buf))
        {
            return true;
        }
#else
        djy_printf("not file system");
        return true;
#endif
    }
    do
    {
        if(sh_cmd_parser(buf,shell_cmd_table[i].cmd,&param)==true)
        {
            result = shell_cmd_table[i].shell_cmd_func(param);
            break;
        }
        i++;
    }while(shell_cmd_table[i].cmd != NULL);
    if(shell_cmd_table[i].cmd == NULL)
    {
        if(sh_ext_command == NULL)
        {
            djy_printf("\r\n无此命令\r\n");
            result = false;
        }else
        {
            if(!sh_ext_command(buf))
            {
                
                djy_printf("\r\n无此命令\r\n");
                result = false;
            }else
                result = true;
        }
    }    
    return result;
}
//----控制台服务函数-----------------------------------------------------------
//功能: 返回console输入的字符，带console输入回车符时，执行命令。一次命令不得超过
//      255字符。
//参数: 无
//返回: 无
//-----------------------------------------------------------------------------
void sh_service(void)
{
    char command[cn_shell_cmd_limit+1];
    while(1)
    {
        djy_scanf(NULL,command);
        if(strlen(command) != 0)
            sh_exec_command(command);  //执行命令
#if ((cfg_djyfs == 1) && (cfg_run_mode != cn_mode_tiny))
        print_work_path( );
#endif
        djy_putchar('>');
    }
}

#endif  //#if (cfg_shell == 1)
