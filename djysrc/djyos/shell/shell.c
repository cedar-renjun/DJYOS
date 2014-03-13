//----------------------------------------------------
//Copyright (C), 2011.9,wjz.
//��Ȩ���� (C), 2011.9,wjz
//����ģ��: djyshģ��
//���ߣ�wjz
//�汾��V0.1.0
//�ļ�����: djyos��shell��ģ�飬�ṩshell��ʵ�ֹ����Լ���������
//�޶���ʷ:
// 1. ����:2010-09-10֮ǰ
//   ����:lst
//   �°汾�ţ�djysh0.0.1
//     �޸�˵����shellʵ�ֵ���ơ�
// 2. ����:2011-06-15
//   ����:wjz
//   �°汾�ţ�djysh0.0.2
//   �޸�˵��: ����ļ�ϵͳ�����Լ�ע���ļ�ϵͳshellģ�顣
// 2. ����:2011-09-24
//   ����:wjz
//   �°汾�ţ�djysh1.0.0
//   �޸�˵��: ����¼����¼����͡��жϡ��ڴ桢���������
//               djysh1.0.0��������Ϊһ����������shell�ˡ�
//------------------------------------------------------

#include "os_inc.h"

#if (cfg_shell == 1)

#include "char_term.h"
#include <string.h>
#include "shell_fs.h"
#include "shell.h"

bool_t (*sh_ext_command)(char *buf);

//----����ģ���ʼ������-------------------------------------------------------
//����: ��ʼ������ģ��
//����: ��
//����: 1
//-----------------------------------------------------------------------------
ptu32_t module_init_shell(ptu32_t para)
{
    uint16_t shell_evtt;
    shell_evtt = djy_evtt_regist(enum_correlative,              //�������¼�
                                cn_prio_real,       //Ĭ�����ȼ�
                                0,                  //�̱߳���������������Ч
                                0,                  //�߳����ޣ���������Ч
                                1,                  //�������г�������
                                sh_service,         //��ں���
                                0x3000,             //ջ�ߴ�
                                "shell"             //�¼�������
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

//----��ȡĿ¼---------------------------------------------------------------
//����: ��buf����ȡһ����'\\'���н����������ĵ��ʣ�next���ڷ�����һ�������׵�ַ��
//      ���û����һ�����ʣ���next=NULL��
//����: buf�����������ַ���
//      next��������һ������ָ��
//����: ��ȡ�ĵ���ָ�룬�ѽ����ʺ���ķָ������ɴ�������'\0'
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


//----��ȡ����---------------------------------------------------------------
//����: ��buf����ȡһ���ɿո���н����������ĵ��ʣ�next���ڷ�����һ�������׵�ַ��
//      ���û����һ�����ʣ���next=NULL��
//����: buf�����������ַ���
//      next��������һ������ָ��
//����: ��ȡ�ĵ���ָ�룬�ѽ����ʺ���ķָ������ɴ�������'\0'
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

//----��ʾforѭ��ʱ��----------------------------------------------------------
//����: ��ʾһ��for(;;)ѭ����ִ��ʱ�䣬ѭ�������ֱ���8λ��16λ��32λ��
//����: ��
//����: ��
//-----------------------------------------------------------------------------
bool_t sh_show_for_cycle(char *param)
{
    djy_printf("32λѭ������ %dnS\r\n", djy_get_for_time(4));
    djy_printf("16λѭ������ %dnS\r\n", djy_get_for_time(2));
    djy_printf("8λѭ������ %dnS\r\n", djy_get_for_time(1));

    return true;
}

//----��ʾ��Դ����----------------------------------------------------------
//����: ������Ҫ����ʾ��Դ��������Դ�����֣�������Դ����Ϊ�գ�����ʾ"������Դ"
//����: �����ַ���������:
//          all����ʾȫ����Դ����
//          flash chip����ʾ�ļ�ϵͳ���ص�flashоƬ
//          semaphore����ʾϵͳ�е������ź���
//          mutex����ʾϵͳ�е����л�����
//          device����ʾϵͳ�е����з��豸
//          opened files����ʾ�򿪵��ļ���·��
//          pool����ʾ�����ڴ��
//����: true
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
            djy_printf("û�ҵ� %s ��Դ��\r\n",param);
        }
        else
            __sh_show_branche(rsc_tree);
    }
    return true;
}

//----��ʾȫ����Դ----------------------------------------------------------
//����: ��sh_list_rsc�������ã���ʾȫ����Դ
//����: ��
//����: ��
//-----------------------------------------------------------------------------
void sh_list_rsc_all(void)
{
    struct rsc_node *rsc_root;
    rsc_root = rsc_get_root();
    __sh_show_branche(rsc_root);
}

//----��ʾ��Դ��---------------------------------------------------------------
//����: ��ʾĳ��Դ�����ʼ��һ����Դ��֧������������Դ����
//����: ��
//����: ��
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
            djy_printf("������Դ\r\n");
        }
    }
}

//----��ʾ�ڴ�-----------------------------------------------------------------
//����: ��ʾĳ��ַ��ʼ��һ���ڴ棬ÿ����ʾ16����Ԫ��ֻ��ʾ�������޸�
//����: param������������������Ҫ�����������ÿո����
//          ����1:��ʼ��ַ��10���ƻ�16����(0x��ͷ)
//          ����2:��ʾ�ĵ�Ԫ��
//          ����3:ÿ��Ԫ�ֽ������Ϸ�ֵ��1��2��4��8��������ֵ�����ش���
//����: true=������ʾ��false=����
//-----------------------------------------------------------------------------
bool_t sh_show_memory(char *param)
{
    ptu32_t addr;
    uint32_t unit_num,unit_bytes,len;
    char *word_addr,*word_un,*word_ub,*word_trail;

    //��ȡ3������
    word_addr = strsep(&param," ");
    word_un = strsep(&param," ");
    word_ub = strsep(&param," ");
    word_trail = strsep(&param," ");
    if((word_addr == NULL)||(word_un == NULL)
            ||(word_ub == NULL)||(word_trail != NULL))
    {
        djy_printf("\r\n��ʽ������ȷ��ʽ�ǣ�\r\n>d ��ַ ��Ԫ�� ÿ��Ԫ�ֽ���\r\n");
        return false;
    }
    addr = djy_atol(word_addr);
    unit_num = djy_atol(word_un);
    unit_bytes = djy_atol(word_ub);
#if (cn_byte_bits == 8)  //�ֽ�λ��=8����������
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
            addr &= ~(ptu32_t)1;//ֻ�ܴ�ż����ʼ
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
            addr &= ~(ptu32_t)3;//ֻ�ܴ�ż����ʼ
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
            addr &= ~(ptu32_t)7;//ֻ�ܴ�ż����ʼ
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
            djy_printf("\r\n��������\r\n");
            return false;
        	break;
    }
#elif (cn_byte_bits == 16)  //�ֽ�λ��=16
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
            djy_printf("\r\n��������\r\n");
            return false;
        } break;
    }
#elif (cn_byte_bits == 32)  //�ֽ�λ��=32
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
            djy_printf("\r\n��������\r\n");
            return false;
        } break;
    }
#endif
    djy_printf("\r\n");
    return true;
}

//----д���ڴ�-----------------------------------------------------------------
//����: д��ĳ��ַ��ʼ��һ���ڴ�
//����: param������������������Ҫ�����������ÿո����
//          ����1:��ʼ��ַ��10���ƻ�16����(0x��ͷ)
//          ����2:��ʾ�ĵ�Ԫ��
//          ����3:ÿ��Ԫ�ֽ������Ϸ�ֵ��1��2��4��������ֵ�����ش���
//          ����4:����������
//����: true=������ʾ��false=����
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
#if (cn_byte_bits == 8)  //�ֽ�λ��=8����������
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
            djy_printf("\r\n��������\r\n");
            return false;
            break;
    }
#elif (cn_byte_bits == 16)  //�ֽ�λ��=16
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
            djy_printf("\r\n��������\r\n");
            return false;
        } break;
    }
#elif (cn_byte_bits == 32)  //�ֽ�λ��=32
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
            djy_printf("\r\n��������\r\n");
            return false;
        } break;
    }
#endif
    return true;
}

//----�������---------------------------------------------------------------
//����: ����buf�������ַ�����һ�������Ƿ�keyword���������param�з���keyword
//      ���һ�������ҷǻس����е��ַ���ָ�룬��ָ��ʵ�ʰ�����һ�������в�����
//      ��ַ�����û�в�������param=NULL��
//����: buf�����������ַ���
//      keyword����ƥ�������
//      param�����������в���ָ��
//����: true = ����ƥ�䣬false=���ƥ��
//-----------------------------------------------------------------------------
bool_t sh_cmd_parser(const char *buf,const char *keyword,char **param)
{
    uint32_t i=0;
    char buf2[255];

    if(buf == NULL)
    	return false;
    *param = NULL;
    //��ȡ���������������ֹͣ���Ż��ߺ���ո���±��i
    for(i=0;i<255;i++)
    {    
        if((buf[i]==' ')||(buf[i] == '\0'))
            break;
    }
    memcpy(buf2,buf,i);
    buf2[i] = '\0';
    //�Ƚ�û�д�����������
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

//----��ʾcd�İ���-------------------------------------------------------------
//����: ��sh_list_fscmd_help�������ã�cd�İ���
//����: ��
//����: ��
//-----------------------------------------------------------------------------
void sh_list_cd_help(void)
{
    djy_printf("DBX_name[:]         ����ָ���ļ�������Ŀ¼\r\n");
    djy_printf("                    ���磺D�� ����D�ļ����Ŀ¼\r\n");
    djy_printf("cd/chdir[�ļ���]·�� ��ʾ��ǰĿ¼�����ƻ�ı䵱ǰĿ¼\r\n");
    djy_printf("                    ����: 1)cd C:\\folder ����folderĿ¼\r\n");
    djy_printf("                          2)cd folder ����folderĿ¼\r\n");
    djy_printf("cd/chdir[](���ַ�) ��ʾ��ǰĿ¼����\r\n");
    djy_printf("cd/chdir[\\]        ��������Ŀ¼\r\n");
	djy_printf("cd/chdir[..]       ��������һ��Ŀ¼\r\n");
	djy_printf("                   ����: 1)cd ..\\.. ������������Ŀ¼ \r\n");
	djy_printf("                         2)cd ..\\folder ������һ��Ŀ¼�к���folder��Ŀ¼ \r\n");
}
//----��ʾdir�İ���------------------------------------------------------------
//����: ��sh_list_fscmd_help�������ã�dir�İ���
//����: ��
//����: ��
//-----------------------------------------------------------------------------
void sh_list_dir_help(void)
{

	djy_printf("dir	[�ļ���]·��  [�ļ���]·��... ...\r\n");
	djy_printf("            ��ʾָ��Ŀ¼�µ��ļ�����Ŀ¼�б�\r\n");
	djy_printf("dir	[�ļ���][����ͨ���·��][�ļ���][����ͨ���·��]... ...\r\n");
	djy_printf("            ��ʾָ��Ŀ¼��ƥ����ļ�����Ŀ¼�б�\r\n");
	djy_printf("dir	[\\][\\]... ...	��ʾ��Ŀ¼��һ�����ļ�����Ŀ¼�б�\r\n");
	djy_printf("dir	[..][..]... ...	��ʾ��ǰĿ¼��һ�����ļ�����Ŀ¼�б�\r\n");
	djy_printf("dir	[](���ַ�)      ��ʾ��ǰĿ¼�µ��ļ�����Ŀ¼�б�\r\n");
}
//----��ʾrd�İ���----------------------------------------------------------
//����: ��sh_list_fscmd_help�������ã�rd�İ���
//����: ��
//����: ��
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
//----��ʾren�İ���----------------------------------------------------------
//����: ��sh_list_fscmd_help�������ã�ren�İ���
//����: ��
//����: ��
//-----------------------------------------------------------------------------
void sh_list_ren_help(void)
{
	djy_printf("Ren/rename [�ļ���:][·��]�ļ���1 �ļ���2\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
	djy_printf("\r\n");
}
//----��ʾ�ź���----------------------------------------------------------
//����: ��sh_list_fscmd_help�������ã�chkdsk�İ���
//����: ��
//����: ��
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
//----��ʾdeltree�İ���----------------------------------------------------------
//����: ��sh_list_fscmd_help�������ã�deltree�İ���
//����: ��
//����: ��
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
//----��ʾdel�İ���----------------------------------------------------------
//����: ��sh_list_fscmd_help�������ã�del�İ���
//����: ��
//����: ��
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
//----��ʾcopy�İ���----------------------------------------------------------
//����: ��sh_list_fscmd_help�������ã�copy�İ���
//����: ��
//����: ��
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
//----��ʾmove�İ���----------------------------------------------------------
//����: ��sh_list_fscmd_help�������ã�move�İ���
//����: ��
//����: ��
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
//----��ʾchkdsk�İ���----------------------------------------------------------
//����: ��sh_list_fscmd_help�������ã�chkdsk�İ���
//����: ��
//����: ��
//-----------------------------------------------------------------------------
void sh_list_chkdbx_help(void)
{
	djy_printf("chkdbx �ļ��� ��ʾ���ļ����µ��ļ�������\r\n");

}
//----��ʾver�İ���----------------------------------------------------------
//����: ��sh_list_fscmd_help�������ã�ver�İ���
//����: ��
//����: ��
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
//----��ʾchcp�İ���----------------------------------------------------------
//����: ��sh_list_fscmd_help�������ã�chcp�İ���
//����: ��
//����: ��
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

//----��ʾformat�İ���----------------------------------------------------------
//����: ��sh_list_fscmd_help�������ã�format�İ���
//����: ��
//����: ��
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

//----��ʾtime�İ���----------------------------------------------------------
//����: ��sh_list_fscmd_help�������ã�time�İ���
//����: ��
//����: ��
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

//----��ʾdate�İ���----------------------------------------------------------
//����: ��sh_list_fscmd_help�������ã�date�İ���
//����: ��
//����: ��
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
//----��ʾcls�İ���----------------------------------------------------------
//����: ��sh_list_fscmd_help�������ã�cls�İ���
//����: ��
//����: ��
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
//----��ʾlist-rsc�İ���----------------------------------------------------------
//����: ��sh_list_fscmd_help�������ã�cls�İ���
//����: ��
//����: ��
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
//----��ʾget-evtt�İ���----------------------------------------------------------
//����: ��sh_list_fscmd_help�������ã�cls�İ���
//����: ��
//����: ��
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
//----��ʾget-envent�İ���----------------------------------------------------------
//����: ��sh_list_cmd_help�������ã�cls�İ���
//����: ��
//����: ��
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
//----��ʾget-int�İ���----------------------------------------------------------
//����: ��sh_list_cmd_help�������ã�cls�İ���
//����: ��
//����: ��
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
	djy_printf("\r\n�й�ĳ���������ϸ��Ϣ��������help [ĳ������]\r\n");
	djy_printf("\r\n");

	djy_printf("list-rsc        �г�ϵͳ�е���Դ���ֺͲ�ι�ϵ\r\n");
	djy_printf("speed           ����ѭ�������ٶ�\r\n");
    djy_printf("event           ��ʾ�¼���\r\n");
    djy_printf("evtt            ��ʾ�¼����ͱ�\r\n");
    djy_printf("heap            ��ʾϵͳ��ʹ�����\r\n");
    djy_printf("stack           ��ʾϵͳ�������Ѿ������̵߳��¼���ջ��Ϣ\r\n");
    djy_printf("lock            ��ʾϵͳ�������ź����ͻ���������Ϣ\r\n");
    djy_printf("d               ��ȡ�ڴ��������\r\n");
    djy_printf("f               д���ݵ��ڴ�\r\n");
    djy_printf("help            DJYOS�����������Ϣ\r\n");
	djy_printf("ver             ��ʾdjyos�İ汾\r\n");
	djy_printf("date            ��ʾ������������\r\n");
	djy_printf("time            ��ʾ��ǰʱ���������������ʱ��\r\n");
	djy_printf("\r\n");

	djy_printf("cd              ��ʾ��ǰĿ¼�����ƻ������\r\n");
	djy_printf("md              ����һ��Ŀ¼\r\n");
	djy_printf("mkdir           ����һ��Ŀ¼\r\n");
	djy_printf("rd              ɾ��һ��Ŀ¼\r\n");
	djy_printf("rmdir           ɾ��һ��Ŀ¼\r\n");
	djy_printf("copy            ����һ���ļ�\r\n");
	djy_printf("move            ��һ�������ļ��ƶ���ָ��Ŀ¼��\r\n");
	djy_printf("ren             ������һ���ļ�\r\n");
	djy_printf("rename          ������һ���ļ�\r\n");
	djy_printf("del             ɾ������һ���ļ�\r\n");
	djy_printf("dir             ��ʾָ��Ŀ¼�µ��ļ�����Ŀ¼�б�\r\n");
	djy_printf("\r\n");

	djy_printf("�ļ�ϵͳ�������ؽ�������ã���\r\n");
	djy_printf("chip-erase      ����NANDFLASHоƬ����������\r\n");
	djy_printf("create-dbx      �����ļ���\r\n");
	djy_printf("format          ��ʽ���ļ�ϵͳ\r\n");
	djy_printf("chkdbx          ��ʾ�ļ���ռ�Ĳ���\r\n");
    
}


//----��ʾ�ļ�ϵͳ�������----------------------------------------------------------
//����: ������Ҫ����ʾ��Դ��������Դ�����֣�������Դ����Ϊ�գ�����ʾ"������Դ"
//����: �����ַ���������:
//����: true
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
        djy_printf("��������\r\n");
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

	djy_printf("\r\n��ǰ���ڣ�%d/%02d/%02d %s",
			dtm.tm_year, dtm.tm_mon, dtm.tm_mday, tm_wdays[dtm.tm_wday]);
	djy_printf("\r\n���������ڣ�");

    cmdlen = djy_scanf(NULL, command);
	if ((8<=cmdlen) && (cmdlen<=10))
	{
		//����Ϊ��2012/02/12����ʽ�������������ʱ��
		strcat(command, ",");	// �������ڷֿ����ں�ʱ��
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
			djy_printf("��ݴ���");
			break;
		case cn_ck_error_code_month:
			djy_printf("�·ݴ���");
			break;
		case cn_ck_error_code_day:
			djy_printf("���ڴ���");
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

	djy_printf("\r\n��ǰʱ�䣺%02d:%02d:%02d", dtm.tm_hour, dtm.tm_min, dtm.tm_sec);
	djy_printf("\r\n������ʱ�䣺");

    cmdlen = djy_scanf(NULL, command);
	if ((5<=cmdlen) && (cmdlen<=8))
	{
		time[0] = '\0';
		strcpy(time, command);	// ����õ�ʱ���ַ������Ƶ�buf��
		//ʱ��Ϊ��03:32:1����ʽ������ǰ�������
		command[0] = '\0';
		djy_itoa(dtm.tm_year, buf, 10);
		strcat(command, buf);
		strcat(command, "/");
		djy_itoa(dtm.tm_mon, buf, 10);
		strcat(command, buf);
		strcat(command, "/");
		djy_itoa(dtm.tm_mday, buf, 10);
		strcat(command, buf);
		strcat(command, ",");	// �������ڷֿ����ں�ʱ��
		strcat(command, time);

		res = time_set_datetime_str(command);
		switch (res)
		{
		case cn_ck_error_code_hour:
			djy_printf("Сʱ����");
			break;
		case cn_ck_error_code_minute:
			djy_printf("���Ӵ���");
			break;
		case cn_ck_error_code_second:
			djy_printf("���Ӵ���");
			break;
		default:
			break;
		}
	}

	djy_printf("\r\n");
    return true;
}

//----ת����������Ĵ�д��ĸΪСд----------------------------------------------
//����: ת��shell�����������"buf"�пո�ǰ�Ĵ�д��ĸΪСд��
//����: cmd��shell���������������"buf"(cmd)
//����: 0
//-----------------------------------------------------------------------------
void capital_convert_lowercase(char *cmd)
{

	while(*cmd!='\0')
    {
           if(*cmd>='A'&&*cmd<='Z')
            *cmd=*cmd+('a'-'A');
            cmd++; //��һ���ַ�
         //�����ո�
         if(*cmd==' ')
         	break;
    }
	return ;
}

//----��ʾ�¼���---------------------------------------------------------------
//����: ��ʾ�¼��б�
//����: ��
//����: true
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
    djy_printf("û�а���������Ϣģ��\r\n");
#endif

    return true;
}

//----��ʾ�¼����ͱ�-----------------------------------------------------------
//����: ��ʾ�¼������б�
//����: ��
//����: true
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
    djy_printf("û�а���������Ϣģ��\r\n");
#endif

    return true;
}

//----��ʾϵͳ��ʹ�����-------------------------------------------------------
//����: ��ʾϵͳ��ʹ�����
//����: ��
//����: true
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
    djy_printf("û�а���������Ϣģ��\r\n");
#endif
    return true;
}


//----��ʾջʹ�����-----------------------------------------------------------
//����: ��ʾϵͳ�������Ѿ������̵߳��¼���ջ��Ϣ
//����: ��
//����: true
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
    djy_printf("û�а���������Ϣģ��\r\n");
#endif
    return true;
}

//----��ʾȫ����-----------------------------------------------------------
//����: ��ʾϵͳ�������ź����ͻ���������Ϣ
//����: ��
//����: true
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
    djy_printf("û�а���������Ϣģ��\r\n");
#endif
    return true;
}

extern bool_t __erase_all_nand(char *param);

//���������
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

//----�ж�':'�����Ƿ�������-----------------------------------------------------
//����: ��һ�����ܰ����༶·�������ļ������ַ������жϵ�һ������'\'֮���Ƿ���
//      ����
//����: path������·������ʽ��"C:\aaaa\bbbb\cccc"
//����: true=�ɹ�, ˵��':'֮��������,����û��':'
//      false=ʧ�ܣ�˵��':'֮��û������
//��ע: pathӦ���Ǿ����Ϸ��Լ����ַ������������word����������
//-----------------------------------------------------------------------------
bool_t __judge_colon_is_data(char *path)
{
    uint32_t index;
    uint32_t  name_len;

	name_len = strlen(path);
    for(index = 0; index< name_len; index++)
    {
        if(path[index] == ':')    //�����ַ�'\'
        {
            if(path[index+1] != '\0')
            	return true;
        	else
            	return false;
        }
    }
    //�ַ�����û��ð��
	if(index == name_len)
    	return true;
	return false;        
}

//----ִ�п���̨����---------------------------------------------------
//����: ������ִ�п���̨����
//����: ��
//����: ��
//��ע: ��ʱ���ù�ϣ��ȣ����и��ӿ��ٵıȽϡ���������ıȽϣ�������ˡ�
//      �ǻ����������ˡ�
//---------------------------------------------------------------------
bool_t sh_exec_command(char *buf)
{
    bool_t result = false;
    char *param;
    uint32_t i=0;
    //�������ƶ�ȡ255�ַ�����������ʾ�������С�������Ͳ��ò�������ʾ
    //̫����
	if(strnlen(buf, cn_shell_cmd_limit+1) > cn_shell_cmd_limit)
	{
        djy_printf("�����ַ���̫��\r\n");
	}
    //ת��buf�еĴ�д��ĸΪСд
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
            djy_printf("\r\n�޴�����\r\n");
            result = false;
        }else
        {
            if(!sh_ext_command(buf))
            {
                
                djy_printf("\r\n�޴�����\r\n");
                result = false;
            }else
                result = true;
        }
    }    
    return result;
}
//----����̨������-----------------------------------------------------------
//����: ����console������ַ�����console����س���ʱ��ִ�����һ������ó���
//      255�ַ���
//����: ��
//����: ��
//-----------------------------------------------------------------------------
void sh_service(void)
{
    char command[cn_shell_cmd_limit+1];
    while(1)
    {
        djy_scanf(NULL,command);
        if(strlen(command) != 0)
            sh_exec_command(command);  //ִ������
#if ((cfg_djyfs == 1) && (cfg_run_mode != cn_mode_tiny))
        print_work_path( );
#endif
        djy_putchar('>');
    }
}

#endif  //#if (cfg_shell == 1)
