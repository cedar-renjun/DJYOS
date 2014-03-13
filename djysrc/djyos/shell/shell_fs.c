//----------------------------------------------------
//Copyright (C), 2011.9,wjz.
//版权所有 (C), 2011.9,wjz
//所属模块: djysh模块
//作者：wjz
//版本：djysh1.0.0
//文件描述: djysh的文件系统shell命令。
//修订历史:
// 1. 日期:2010-6-15
//   作者:wjz
//   新版本号：djysh1.0.0
//------------------------------------------------------

#include "os_inc.h"

#if ((cfg_djyfs == 1) && (cfg_run_mode != cn_mode_tiny) && (cfg_shell == 1))

#include <string.h>
#include "char_term.h"
#include "shell.h"
#include "shell_fs.h"
#include "file.h"
#include "flashfile.h"
#include "mdr.h"

extern struct file_rsc *pg_work_path;

//----检查通配符-----------------------------------------------
//功能: 检查字符串的路径部分是否有星号或者问号,查找长度以命令行最大长度为限。
//参数: str,被测字符串
//返回: true=路径部分有'*'或者'?'，false=没'*'或者'?'
//----------------------------------------------------------------------------
bool_t __check_wildcard_path(char *str)
{
    u32 loop,name_len;
    
    if(str == NULL)
        return false;
    name_len = strlen(str);
    for(loop = 0; loop <= name_len; loop++)
    {
        if((str[loop]=='*')||(str[loop]=='?'))
        {
            break;
        }
    }
    for( ; loop <= name_len; loop++)
    {
        if(str[loop]=='\\')
        {
            return true;
        }
    }
    return false;
}

//----检查通配符-----------------------------------------------
//功能: 检查字符串的文件名部分是否有星号或者问号,查找长度以命令行最大长度为限。
//参数: str,被测字符串
//返回: true=文件名部分有'*'或者'?'，false=没'*'或者'?'
//----------------------------------------------------------------------------
bool_t __check_wildcard_name(char *str)
{
    s32 loop,name_len;
    
    if(str == NULL)
        return false;
    name_len = strlen(str);
    if((str[name_len-1] == '\\') || (str[name_len-1] == ':'))
        return false;
    for(loop = name_len-1 ; loop >= 0; loop--)
    {
        if((str[loop]=='*')||(str[loop]=='?'))
        {
            return true;
        }
        if(str[loop]=='\\')
        {
            return false;
        }
    }
    return false;
}

//----检查通配符-----------------------------------------------
//功能: 检查字符串是否有星号或者问号,查找长度以命令行最大长度为限。
//参数: str,被测字符串
//返回: true=文件名部分有'*'或者'?'，false=没'*'或者'?'
//----------------------------------------------------------------------------
bool_t __check_wildcard(char *str)
{
    u32 loop,name_len;
    
    if(str == NULL)
        return false;
    name_len = strlen(str);
    for( loop = 0; loop <= name_len; loop++)
    {
        if((str[loop]=='*')||(str[loop]=='?'))
        {
            return true;
        }
    }
    return false;
}

//-------带通配符的字符匹配-----------------------------------------------------
//功能: 带通配符的字符匹配最常见的通配符是'?'和'*'。其中,'?'可以代表一个字符
//        (不能没有),'*'可以代表任意多个字符(可以为空)。首先是'?'， 根据'?'
//    	的功能,'?'表示任意字符,也就是说在匹配过程中,'?'永远匹配成功 。
//    	本质上,'?'并没有修改算法，而仅仅修改了匹配规则 -- 遇到'?'则一定匹配 。
//    	然而'*'与此不同,'*'的作用是匹配任意多个字符，显然我们不能简单的修改匹配
//    	过程而满足要求。
//参数: src - 待匹配的字符串,不能含有'?'或'*'
//    	wildcard - 通配符字符串
//返回: true=匹配成功,
//      false=匹配失败,
//-----------------------------------------------------------------------------
bool_t __wildcard_match(char *src, char *wildcard)
{
	u32 i = 0;
	u32 j = 0;

    if(wildcard == NULL)
        return true;

	while (wildcard[j] || src[i])
	{
		if (wildcard[j] == '*')
		{
			while (wildcard[j] == '*')	// 找到一连串*号的最后一个*号
			{
				j++;
				if (wildcard[j] == '\0')
				{
					return true;	// 匹配
				}
			}
			while (src[i] != wildcard[j])	// 匹配src中与*后第一个字符
			{
				if (src[i])
				{
					i++;
				}
				else
				{
					return false;	// 不匹配
				}
			}
		}
		else
		{
			if ((src[i] == wildcard[j]) || (wildcard[j] == '?'))
			{
				i++;
				j++;
			}
			else
			{
				return false;
			}
		}
	}

	if ((src[i] == '\0') && (wildcard[j] == '\0'))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//----判断'\'后面是否有数据-----------------------------------------------------
//功能: 从一个可能包含多级路径名和文件名的字符串中判断第一次遇到'\'之后是否还有
//      数据
//参数: path，被测路径，格式如"C:\aaaa\bbbb\cccc"
//返回: true=成功, 说明'\'之后有数据,或者没有'\'
//      false=失败，说明'\'之后没有数据
//备注: path应该是经过合法性检查的字符串，不会出现word超长的问题
//-----------------------------------------------------------------------------
bool_t __judge_backslash_is_data(char *path)
{
    uint32_t index;
    uint32_t name_len;

	name_len = strlen(path);
    for(index = 0; index< name_len; index++)
    {
        if(path[index] == '\\')    //遇到字符'\'
        {
            if(path[index+1] != '\0')
            	return true;
        	else
            	return false;
        }
    }
    //字符串里没有反斜杠
	if(index == name_len)
    	return true;
	else
    	return false;            
}

//----删除路径后的文件或者目录-------------------------------------------------
//功能: 从一个可能包含多级路径名和文件名的字符串中删除最后一项，如果path是一个根
//      目录名，则不操作
//参数: path，被测路径，格式如"C:\aaaa\bbbb\cccc"
//返回: true=成功删除，或无须删除
//      false=失败
//-----------------------------------------------------------------------------
bool_t __cut_path_end_item(char *path)
{
	uint16_t name_len,loop;
    
	name_len = strlen(path);
	loop=name_len;
	if(path[name_len-1]=='\\')//有反斜杠说明是去除文件夹
    {
    	if(path[name_len-2]==':')
        	return true;//说明是根目录，不用操作
    	else
        {
        	for(loop=name_len-2;loop>0;loop--)
            {
            	if(path[loop] == '\\')
                {
                	path[loop+1] = '\0';
                	break;
                }
            }
        }
    	return true;
    }
	else//没有反斜杠，说明去除的是文件
    {
    	for(loop=name_len-1;loop>0;loop--)
        {
        	if(path[loop] == '\\')
            {                    
            	path[loop+1] = '\0';
            	break;
            }
        }
    }
	return true;
}

//----提取路径后的文件或者目录--------------------------------------------------
//功能: 从一个可能包含多级路径名和文件名的字符串中提取最后一项。如果path是根目录
//      则不操作。path串保持不变。
//参数: path，被测路径，格式如"C:\aaaa\bbbb\cccc"
//    	name,保存提取的文件或者目录
//返回: true=成功, 提取成功
//      false=失败，提取失败
//-----------------------------------------------------------------------------
bool_t __pick_path_end_item(char *path,char *name)
{
	uint16_t name_len,loop;
	char *str;
    
	name_len = strlen(path);
	loop=name_len;
	if(path[name_len-1]=='\\')//有反斜杠，说明提取的是文件夹名
    {
    	if(path[name_len-2]==':')
        	return false;   //说明是根目录，不用操作
    	else
        {
        	for(loop=name_len-2;loop>0;loop--)
            {
            	if(path[loop] == '\\')
                {
                	str=&path[loop+1];
                    strcpy(name,str);
                    return true;
                }            
            }
        }
    }
	else//没有反斜杠，说明提取的是文件名
    {
    	for(loop=name_len-1;loop>0;loop--)
        {
        	if(path[loop] == '\\')
            {                    
            	str=&path[loop+1];
                strcpy(name,str);
            	return true;
            }
        }

    }
    //执行到这步，说明只是一个文件或者目录，直接拷贝就ok
    strcpy(name,path);    
	return true;
}

//----分离文件名---------------------------------------------------------------
//功能: 如果字符串包含文件名，则把最后一个'\\'后的第一个字符改成'\0'，并返回文件
//      名指针
//参数: path，被测试的串
//      filename，返回文件名地址,但首字符已经被作为返回值返回，串中被替换为'\0'
//      pathname，若path串中存在目录名，则返回路径名地址，否则返回NULL;
//返回: 被'\0'替换的字符，'\0'=不含文件名
//-----------------------------------------------------------------------------
char __separate_filename(char *path,char **filename,char **pathname)
{
    u32 name_len,loop;
    char ch;
    name_len = strlen(path);
    if(name_len == 0)
        return 0;
    for(loop = 0; loop < name_len; loop++)
    {
        if((path[loop-1] == ':') || (path[loop-1] == '\\'))
            break;
    }
    if(loop == name_len)        //整个串是一个文件名
    {
        *pathname = NULL;
        *filename = path;
        return path[0];
    }
    else if(loop == name_len -1)    //不含文件名
    {
        *filename = NULL;
        *pathname = path;
        return 0;
    }
    else
    {
        *filename = path + loop;
        *pathname = path;
        ch = path[loop];
        path[loop] = '\0';
        return ch;
    }
}

//----判断字符串是绝对路径还是相对路径-----------------------------------------
//功能: 检查一个可能包含多级路径名和文件名的字符串是否包含文件柜名的绝对路径
//参数: path，被测路径，格式如"C:\aaaa\bbbb\cccc"
//返回: true=是绝对路径
//      false=不是绝对路径
//备注: path应该是经过合法性检查的字符串，不会出现word超长的问题
//-----------------------------------------------------------------------------
bool_t __path_is_absolute_path(char *path)
{
    uint32_t index;
    //synname是已经经过字符串长度合法性检查的指针
    uint32_t name_len;

	name_len = strlen(path);
    if(path[0] == '\\')
        return true;
    for(index = 0; index< name_len; index++)
    {
        if(path[index] == ':')
        {
        	return true;
        }
    }
    	return false;
}

//----判断路径是否包含文件柜---------------------------------------------------
//功能: 判断一个可能包含多级路径名和文件名的字符串是否包含文件柜名
//参数: path，被测路径，格式如"C:\aaaa\bbbb\cccc"
//返回: true=含文件柜名
//      false=不含文件柜名
//-----------------------------------------------------------------------------
bool_t __path_include_dbxname(char *path)
{
    uint32_t index;
    //synname是已经经过字符串长度合法性检查的指针
    uint32_t name_len;

    name_len = strlen(path);
    for(index = 0; index< name_len; index++)
    {
        if(path[index] == ':')
        {
            return true;
        }
    }
        return false;
}

//----目录下匹配的文件提取到一个字符串--------------------------------------
//功能: 在一个目录下扫描存在的文件，然后每个文件通过匹配函数和wildcard_param进行
//    	一一匹配，把匹配的文件名提到到一个字符串里。
//参数: wildcard_param，含有通配符的参数
//    	get_merge_str ，最后符合要求的文件名合并而成的字符串
//返回: true=成功, 提取成功
//      false=失败，提取失败
//-----------------------------------------------------------------------------
char *get_folder_wildcard_str(char *wildcard_param,char *get_merge_str)
{
	struct file_rsc *fp = NULL,*current_fp = NULL;
	char work_path[256];
    u32 fat_block_no;

 
    if(__djyfs_is_contain_DBX_name(wildcard_param) ==0)
        fp = pg_work_path;//相对路径，直接使用工作路径
    else
    {    
    	strcpy(work_path,wildcard_param);
    	__pick_filename_word(work_path,wildcard_param);
        __cut_path_end_item(work_path);
        fp = djyfs_fopen(work_path, "r");    
    }
    //是文件，没意义（同时fp2是非根目录,根目录下，文件属性不确定）
    if(fp->attr.bits.archive&&(fp->file_medium_tag!=0))
        return NULL;
	current_fp =(struct file_rsc *)djyfs_folder_traversal_son(fp,current_fp);
	if(current_fp == NULL)
    {    
    	djyfs_fclose(fp);
    	djy_printf("该目录为空!\r\n");
    	return NULL;
    }
	fat_block_no = current_fp->file_medium_tag;
        //全部置0，这样就可以准确知道本来merge_str已经没有数据了
    memset(get_merge_str,0,sizeof(get_merge_str));
	do//循环读目录表，直到读完
    {
    	if(__wildcard_match(current_fp->name,wildcard_param))
        {//把匹配成功的目录串成一个新字符串
        	strcat(get_merge_str,current_fp->name);
        	strcat(get_merge_str," ");
        }    
        //当fp下所有的文件都被删除了，就没文件，返回false
        current_fp = (struct file_rsc *)djyfs_folder_traversal_son(fp,current_fp);
        if(current_fp == NULL)
            break;
    }while(current_fp != NULL);
	djyfs_fclose(fp);

	return get_merge_str;
}

//----带通配符删除文件---------------------------------------------------------
//功能: 带通配符删除文件，路径部分不能带通配符。空目录也一并删除。
//参数: 
//返回: true=成功, 提取成功
//      false=失败，提取失败
//-----------------------------------------------------------------------------
bool_t del_wildcard_files(char *wildcard_param)
{
	char *filename,*pathname;
    char ch;
    struct file_rsc *current=NULL,*parent;

	if(wildcard_param == NULL)
    {
		djy_printf("文件名不正确!\r\n");
    	return false;
    }
    ch = __separate_filename(wildcard_param,&filename,&pathname);
    if(filename == NULL)     //不含文件名
    {
		djy_printf("文件名不正确!\r\n");
        return false;
    }

    if(pathname != NULL)
    {
        if(djyfs_fsearch(pathname,NULL))
        {
            parent = djyfs_fopen(pathname,"r");
        }
        else
        {
            djy_printf("路径不存在\n\r");
            return false;
        }
    }
    else
    {
        parent = pg_work_path;
    }
    if(filename != NULL)
        filename[0] = ch;       //恢复文件名的第一个字符
	while(1)                //循环读目录表，直到读完
    {
        current =(struct file_rsc *)djyfs_folder_traversal_son(parent,current);
        if(current == NULL)
            break;
    	if(__wildcard_match(current->name,filename))
        {
            djyfs_remove(current->name);
        }    
    }
    
	djyfs_fclose(parent);
	return true;    
}

//----在字符串末尾无反斜杠加上反斜杠--------------------------------------------------------------
//功能：在字符串末尾无反斜杠加上反斜杠,有反斜杠就不要加了
//参数：str 字符串，任何形式
//返回：true 成功
//    	false 遇到".."了
//------------------------------------------------------------------------------
bool_t str_end_increase_backslash(char *str)
{
	uint16_t name_len;

	if(strcmp(str,"..") ==0)//如果是"..",那么不要操作
    	return false;
	name_len = strnlen(str,cn_shell_cmd_limit +1);
    if(name_len >cn_shell_cmd_limit)
        return false;
    //如果字符串最后一位不是'\\'，那么加反斜杠
	if(str[name_len-1] != '\\')
    {
    	str[name_len] = '\\';
        //如果str不是规定好的空间，很容易泄露，必须防止
       	str[name_len+1] = '\0';    
    }
	return true;
}

//----在字符串末尾有反斜杠去掉反斜杠--------------------------------------------
//功能：在字符串末尾无反斜杠加上反斜杠，没有反斜杠就不处理
//参数：str 字符串，任何形式
//返回：true 成功
//    	false 字符串没有反斜杠
//------------------------------------------------------------------------------
bool_t str_end_wipe_backslash(char *str)
{
	uint16_t name_len;

	name_len = strnlen(str,cn_shell_cmd_limit +1);
    if(name_len >cn_shell_cmd_limit)
        return false;
	if(str[name_len-1] == '\\')
    {
    	str[name_len-1] = '\0';
    	return true;
    }
	else
	return false;
    
}

//----显示目录下的文件和文件夹------------------------------------------------
//功能: 扫描根目录下的文件和文件夹，然后按照一定个格式，全部打印出来
//参数: ancestor_fp，被显示的文件夹
//返回: true=成功, 列出成功
//      false=失败，列出失败
//-----------------------------------------------------------------------------
bool_t dir_item_son(struct file_rsc *parent_fp)
{
    struct file_rsc *current_fp;
    s64 files_size=0;
    u32 index=0;
    uint32_t files_items=0,folder_items=0;
    s64 available_dbx_size=0;
    char *buf;

    if(parent_fp == NULL)
        return false;//可能是文件柜未建立

    index = djyfs_getpath_len(parent_fp);
    buf = m_malloc(index,0);
    if(buf == NULL)
    {
        djy_printf("内存不足，不能执行dir");
        return false;
    }
    buf[0] = '\0';
    djyfs_getpath(parent_fp,buf,index+1);
    djy_printf("%s 的目录\r\n\r\n",buf);
    djyfs_dbx_stat_fp(parent_fp,NULL,NULL,&available_dbx_size);

	current_fp = NULL;
    current_fp = (struct file_rsc*)djyfs_folder_traversal_son(parent_fp,current_fp);
    if(current_fp == NULL)
    {
        djy_printf("该目录为空!\r\n");
        return false;
    }

    do //循环读目录表，直到读完
    {
        djy_printf("%d/%02d/%02d %02d:%02d",
                (current_fp->year_high_modify<<8) + current_fp->year_low_modify,
                current_fp->month_modify,
                current_fp->date_modify,
                current_fp->hour_modify,
                current_fp->minute_modify);

        if(current_fp->attr.bits.folder)
        {
            djy_printf(" <DIR> ");//代表是目录，可以继续dir
            folder_items++;
        }
        else
        {
            djy_printf("       ");
            files_items++;
        }
		djy_printf("%9d %s\r\n",
				(s32)current_fp->file_size, current_fp->name);
        files_size+=current_fp->file_size;
        current_fp = (struct file_rsc*)djyfs_folder_traversal_son(parent_fp,current_fp);
    }while(current_fp != NULL);

    djy_printf("%d个文件 %d字节\r\n", files_items, (s32)files_size);
    djy_printf("%d个目录 %d可用字节\r\n", folder_items, (s32)available_dbx_size);
    return true;
}

//----显示含有通配符的文件或者文件夹------------------------------------------------
//功能: dir命令下，显示含有通配符的文件或者文件夹。扫描当前工作路径或者指定路径下
//    	的文件或者目录。然后用匹配函数一一匹配。符合要求的，显示出来。
//参数: wildcard_param，含有通配符的字符串
//返回: true=成功, 列出成功
//      false=失败，列出失败
//-----------------------------------------------------------------------------
bool_t dir_wildcard_files(char *wildcard_param)
{
	char *filename,*pathname;
	uint32_t files_items=0,folder_items=0;
    s64 files_size=0,available_dbx_size=0;
    char ch;
    struct file_rsc *current=NULL,*parent;
//    struct file_rsc *bak_work_path = pg_work_path;

	if(wildcard_param == NULL)
    {
		djy_printf("文件名不正确!\r\n");
    	return false;
    }
    ch = __separate_filename(wildcard_param,&filename,&pathname);

    if(pathname != NULL)
    {
        if(djyfs_fsearch(pathname,NULL))
        {
            parent = djyfs_fopen(pathname,"r");
        }
        else
        {
            djy_printf("路径不存在\n\r");
            return false;
        }
    }
    else
    {
        parent = pg_work_path;
    }
    if(filename != NULL)
        filename[0] = ch;       //恢复文件名的第一个字符

	while(1)                //循环读目录表，直到读完
    {
        current =(struct file_rsc *)djyfs_folder_traversal_son(parent,current);
        if(current == NULL)
            break;
    	if(__wildcard_match(current->name,filename))
        {
            djy_printf("%d/%02d/%02d %02d:%02d",
                    (current->year_high_modify<<8) + current->year_low_modify,
                    current->month_modify,
                    current->date_modify,
                    current->hour_modify,
                    current->minute_modify);
            
            if(current->attr.bits.folder)
            {
                djy_printf(" <DIR> ");
                folder_items++;
            }
            else
            {
                djy_printf("       ");
                files_items++;
            }
            djy_printf("%9dB %s\r\n", (s32)current->file_size, current->name);
            files_size += current->file_size;
        }    
    }
    
    djyfs_dbx_stat_fp(parent,NULL,NULL,&available_dbx_size);
	djyfs_fclose(parent);
    djy_printf("%d个文件 %d字节\r\n", files_items, (s32)files_size);
    djy_printf("%d个目录 %d可用字节\r\n", folder_items, (s32)available_dbx_size);
	return true;    
}



//----判断一个目录是否是文件夹------------------------------------------------
//功能: 通过访问fp的属性，判断是否是文件夹
//参数: fullname,路径 格式:"C:\aa\bb\cc"
//返回: cn_item_is_folder=是文件夹, 
//      cn_item_is_file=是文件，
//      cn_item_no_exist=不存在这样的文件或文件夹
//注:   调用时须确保fullname是合法的字符串
//-----------------------------------------------------------------------------
u32 __judge_item_attr(char *fullname)
{
	struct file_rsc fp;
	bool_t result;
	result = djyfs_fsearch(fullname,&fp);
	if(result == true)
    {
       	if(fp.attr.bits.folder)
        {
            return cn_item_is_folder; 
        }
        else
        {
            return cn_item_is_file;
        }
    }
    else
        return cn_item_no_exist;
}

//----建立一个文件夹------------------------------------------------
//功能: 指定建立一个文件夹
//参数: md_param，输入字符
//返回: true=成功, 
//      false=失败，
//-----------------------------------------------------------------------------
bool_t fs_mkdir(char *md_param)
{  
	struct file_rsc *fp;

	if(md_param == NULL)
    {
    	djy_printf("命令语法不正确!\r\n");
    	return false;
    }
    //在创建的末尾加了'\'，无论如何，都是目录
    //这里不怕内存泄漏，因为md函数里，规定了长度
	str_end_increase_backslash(md_param);
	if(!__check_fullname(md_param))
     	return false; 
    //如果有存在文件或者目录，那么就不需要创建了
    if(!djyfs_fsearch(md_param,NULL))
    {
        fp = djyfs_fopen(md_param,"w+");
        if(fp == NULL)
            return false;
        djyfs_fclose(fp);
    }
    else
    {
        djy_printf("\r\n子目录或者文件%d已经存在\r\n", md_param);

        return false;
    }
    return true;    
}
//----删除文件夹--------------------------------------------------------------
//功能: 把指定的文件夹删除掉
//参数: rd_param，输入字符
//返回: true=成功, 
//      false=失败，
//-----------------------------------------------------------------------------
bool_t fs_remove_folder(char *rd_param)
{    
	struct file_rsc *fp;

	if(rd_param == NULL)
    {
    	djy_printf("命令语法不正确!\r\n");
    	return false;
    }
	if(!__check_fullname(rd_param))
     	return false; 
	fp = djyfs_fopen(rd_param,"r");
	if(fp == NULL)
    {    
    	djy_printf("系统找不到指定的文件\r\n");
    	return false; 
    }
	if(fp->attr.bits.folder)
    {
    	djyfs_fclose(fp);
    	if(djyfs_remove(rd_param) == enum_fs_folder_unblank)
        {
            djy_printf("目录%s不是空！\r\n", rd_param);
        }
    	return true;
    }
	else
    {
    	djyfs_fclose(fp);
    	djy_printf("目录名称无效!\r\n");
    	return false;
    }
    
}

//----显示指定目录下的文件和子目录列表-------------------------------------------------------
//功能：显示指定目录下的文件和子目录列表	
//参数：dir_param，dir输入的参数，可以是文件，路径或者不输入
//返回：true，显示成功
//    	false,显示失败
//-----------------------------------------------------------------------------
bool_t dir_parent(char *next_param)
{
    char *foldername=NULL;
    struct file_rsc *fp;
    uint32_t lenth=0;
    char work_path[cn_shell_cmd_limit+1];

    //这里，必须使用get_work_path了。下面，dir ..\folder，需要                                                        ->private_tag);
    get_work_path_name(work_path,cn_shell_cmd_limit);
    do   
    {
        foldername = (char *)sh_get_item(next_param,&next_param);
    	if(foldername == NULL&&lenth==0)
        	return false;
        //执行 如: cd ..\foder
        if(strcmp(foldername,"..") != 0)
        {
            str_end_increase_backslash(work_path);
            strcat(work_path,foldername);
            fp = djyfs_fopen(work_path,"r");
            if(fp == NULL)
            {
                djy_printf("系统找不到指定的路径!\r\n");
                return false;
            }
            dir_item_son(fp);
            djyfs_fclose(fp);
            break;
        }
        __cut_path_end_item(work_path);
        if(next_param == NULL)
        {
            fp = djyfs_fopen(work_path,"r");
            dir_item_son(fp);
            djyfs_fclose(fp);
            break;
        }
        //路径深度大于cn_path_depth_limit，会跳出循环。在这里，
        //就为了防止死循环，多一个保护吧
        lenth++;
     }while((lenth!=cn_path_depth_limit)&&(foldername != NULL));    
    return true;
}

//----更改当前工作路径到父目录-------------------------------------------------------
//功能：更改当前工作路径到原来当前工作路径的父目录
//参数：next_param，输入的参数
//返回：true，显示成功
//    	false,显示失败
//-----------------------------------------------------------------------------

bool_t cd_parent(char *next_param)
{
    char *foldername=NULL;
    struct file_rsc *fp;
    struct file_rsc *root,*temp;
    uint32_t lenth=0;

    root = (struct file_rsc*)rsc_get_tree(&pg_work_path->file_node);
    do   
    {
        foldername = sh_get_item(next_param,&next_param);
        //执行 如: cd ..\foder
        if(strcmp(foldername,"..") != 0)
        {
            //是目录才能打开，不用考虑根目录的情况。
            //假如"cd ..\foder",在根目录下执行，就没意义。
            //以只读方式打开，如果不存在，就返回NULL，
            //就不用去专门搜索该目录下这个目录是否存在。
        	if(__judge_item_attr(foldername) == cn_item_is_folder)
            {
            	fp = pg_work_path;
            	pg_work_path = djyfs_fopen(foldername,"r");
            	djyfs_fclose(fp);
            	return true;
            }
        	else
            {
                djy_printf("系统找不到指定路径\r\n");
                return false;
            } 
            lenth++;
        }
        temp = (struct file_rsc*)rsc_get_parent(&pg_work_path->file_node);
    	if(temp != root)
        {    
        	fp=pg_work_path;        //当前工作路径不能关闭,故转移
            pg_work_path = temp;
            djyfs_fclose(fp);
        }
        else
            break;
        //路径深度大于cn_path_depth_limit，会跳出循环。在这里，
        //就为了防止死循环，多一个保护吧
     }while((lenth <= cn_path_depth_limit)&&(next_param != NULL));    
    return true;
}


//----显示指定目录下的文件和子目录列表-------------------------------------------------------
//功能：显示指定目录下的文件和子目录列表	
//参数：dir_param，dir输入的参数，可以是文件，路径或者不输入
//返回：true，显示成功
//    	false,显示失败
//-----------------------------------------------------------------------------

bool_t cd_dbx(char *dbx)
{
    char work_path[cn_shell_cmd_limit+1]; 
    struct file_rsc *fp;
    
    strcpy(work_path,dbx);
    strcat(work_path,"\\");
    if(djyfs_fsearch(work_path,NULL))
    {
        fp = djyfs_fopen(work_path,"r");
        if(fp != NULL)
        {
            pg_work_path = fp;
            return true;
        }
        else
            return false;
    }
    else
    { 
    	djy_printf("该文件柜不存在\r\n");
        return false;
    }
}

//复制次数太多，出的问题吧!可能是磨损平衡吧!总之，这算是一个大bug。

//----复制一个文件到目标------------------------------------------------
//功能: 把一个文件复制到需要被复制的地方
//参数:  src，当前的工作路径，不过区别work_path，因为work_patch是全局变量，
//    	尽量少修改。
//    	dest，这个工作路径是复制到目标的路径
//返回: true=成功, 
//      false=失败，
//-----------------------------------------------------------------------------
bool_t copy_file_to_dest(char *src,char *dest)
{
	uint32_t file_size,loop,loop_times,buf_size;
	uint32_t buf_size_offset,size;
	struct file_rsc *src_fp;
	struct file_rsc *dest_fp;
	char* buf;
    
	src_fp = djyfs_fopen(src,"r");
	if(src_fp == NULL)
    	return false;
	file_size = src_fp->file_size;
	djyfs_fclose(src_fp);
    ////申请16k内存,防止内存不足
    //申请的内存不能太小，否则文件大，操作次数多，影响copy的速度
    //太大，申请不了就完蛋了，暂时定为16k，大概一个flash块的大小
    //待频繁测试之后，再确定
	buf_size = 16384;
	loop_times =(file_size+buf_size-1)/buf_size;
    if(loop_times==0)
    {//loop_times==0时候，说明文件大小为0.只需要建立，就ok
        dest_fp = djyfs_fopen(dest,"a+");
        djyfs_fclose(dest_fp);
        return true;
    }
    buf = (char *)m_malloc(file_size,0);
    if(buf == NULL)
        return false;
	buf_size_offset = file_size%buf_size;
    if(buf_size_offset == 0)
        buf_size_offset = buf_size;
    src_fp = djyfs_fopen(src,"r");
    dest_fp = djyfs_fopen(dest,"a+");
	for(loop=0;loop<loop_times;loop++)
    {
    	if(loop!=loop_times-1)
        	size = buf_size;
    	else//写入的数据小于申请的内存，不应该写入buf_size的大小
        	size = buf_size_offset;
    	djyfs_fseek(src_fp, (sint64_t)(size*loop), SEEK_SET);
       	djyfs_fread(buf, (size_t)size, 1,src_fp);
    	djyfs_fwrite((void *)buf,(size_t)size,1,dest_fp);    
    }
    djyfs_fclose(src_fp);
    djyfs_fclose(dest_fp);
	m_free(buf);
	return true;
}
//----移动一个目录下的文件到目标------------------------------------------------
//功能: 把一个目录的文件移动到需要被移动的地方
//参数: src，当前的工作路径，不过区别work_path，因为work_patch是全局变量，
//    	尽量少修改。
//    	dest，这个工作路径是复制到目标的路径
//返回: true=成功, 
//      false=失败，
//-----------------------------------------------------------------------------
bool_t copy_files_of_folder_to_dest(char *src,char *dest)
{

	uint32_t file_nunmber=0,fat_block_no;
	struct file_rsc *dest_fp,*src_fp,*current_fp=NULL;
    if(!djyfs_fsearch(dest,NULL))
    {
    	djy_printf("djyos不支持此操作,详情请看help!\r\n");
    	return false;
    }    
	dest_fp = djyfs_fopen(dest,"r");
    if(dest_fp == NULL)
        return false;
    //djyfs不支持多个文件合并写入到一个文件里
	if(dest_fp->attr.bits.archive)
    {
    	djy_printf("djyos不支持此操作,详情请看help!\r\n");
    	djyfs_fclose(dest_fp);
    	return false;
    }
	djyfs_fclose(dest_fp);
    
	src_fp = djyfs_fopen(src,"r");
    if(src_fp == NULL)
    {    
    	djyfs_fclose(dest_fp);
    	return false;
    }                             
	current_fp = (struct file_rsc *)djyfs_folder_traversal_son(src_fp,current_fp);
    //必须循环一次就关闭，否则数据不准确，有些文件可能被删除
   	djyfs_fclose(src_fp);
    if(current_fp == NULL)
    {
        djy_printf("%s*\r\n", src);
        djy_printf("系统找不到指定的文件\r\n");
        djy_printf("已经复制了	    	0个文件\r\n");//暂时这样
        return false;  //parent是一个空目录
    }    
    fat_block_no = current_fp->file_medium_tag;
    do
    {

        if(current_fp->attr.bits.archive)
        {
            strcat(src,current_fp->name);
            strcat(dest,current_fp->name);
            copy_file_to_dest(src,dest);
            djy_printf("%s\r\n", src);
            __cut_path_end_item(src);
            __cut_path_end_item(dest);
            file_nunmber++;
        }
        src_fp = djyfs_fopen(src,"r");
    	if(src_fp == NULL)
        {    
        	djyfs_fclose(dest_fp);
        	return false;
        }                             
        //必须循环一次就关闭一次，否则数据不准确，有些文件可能被删除
       	djyfs_fclose(src_fp);
        current_fp = (struct file_rsc *)djyfs_folder_traversal_son(src_fp,current_fp);
    } while(current_fp != NULL);   
    	djy_printf("已经复制了	    	%d个文件\r\n", file_nunmber);
    	return true;                   
}

//复制次数太多，出的问题吧!可能是磨损平衡吧!总之，这算是一个大bug。

//----移动一个文件到目标------------------------------------------------
//功能: 把一个文件移动到需要被移动的地方
//参数:  src，当前的工作路径，不过区别work_path，因为work_patch是全局变量，
//    	尽量少修改。
//    	dest，这个工作路径是复制到目标的路径
//返回: true=成功, 
//      false=失败，
//-----------------------------------------------------------------------------
bool_t move_file_to_dest(char *src,char *dest)
{
	uint32_t file_size,loop,loop_times,buf_size;
	uint32_t buf_size_offset,size;
	struct file_rsc *src_fp;
	struct file_rsc *dest_fp;
	char* buf;

	src_fp = djyfs_fopen(src,"r");
	if(src_fp == NULL)
    	return false;
	file_size = src_fp->file_size;
	djyfs_fclose(src_fp);
    ////申请16k内存,防止内存不足
    //申请的内存不能太小，否则文件大，操作次数多，影响copy的速度
    //太大，申请不了就完蛋了，暂时定为16k，大概一个flash块的大小
    //待频繁测试之后，再确定
	buf_size = 16384;
	loop_times =(file_size+buf_size-1)/buf_size;
    if(loop_times == 0)
    {
    	dest_fp = djyfs_fopen(dest,"a+");
    	djyfs_fclose(dest_fp);  
        djyfs_remove(src);
    }
    buf = (char *)m_malloc(file_size,0);
    if(buf == NULL)
        return false;
	buf_size_offset = file_size%buf_size;
    if(buf_size_offset == 0)
        buf_size_offset = buf_size;
    src_fp = djyfs_fopen(src,"r");
    dest_fp = djyfs_fopen(dest,"a+");
	for(loop=0;loop<loop_times;loop++)
    {
    	if(loop!=loop_times-1)
        	size = buf_size;
    	else//写入的数据小于申请的内存，不应该写入buf_size的大小
        	size = buf_size_offset;
    	djyfs_fseek(src_fp, (sint64_t)(size*loop), SEEK_SET);
       	djyfs_fread(buf, (size_t)size, 1,src_fp);
    	djyfs_fwrite((void *)buf,(size_t)size,1,dest_fp);
    }
    djyfs_fclose(src_fp);
    djyfs_fclose(dest_fp);
    djyfs_remove(src);
	m_free(buf);

	return true;
}

//----移动一个目录下的文件到目标------------------------------------------------
//功能: 把一个目录的文件移动到需要被移动的地方
//参数: src，当前的工作路径，不过区别work_path，因为work_patch是全局变量，
//    	尽量少修改。
//    	dest，这个工作路径是复制到目标的路径
//返回: true=成功, 
//      false=失败，
//-----------------------------------------------------------------------------
bool_t move_files_of_folder_to_dest(char *src,char *dest)
{

	uint32_t file_nunmber=0,fat_block_no=0xffffffff;
	struct file_rsc *dest_fp,*src_fp,*current_fp=NULL;
    if(!djyfs_fsearch(dest,NULL))
    {
    	djy_printf("djyos不支持此操作,详情请看help!\r\n");
    	return false;
    }    
	dest_fp = djyfs_fopen(dest,"r");
    if(dest_fp == NULL)
        return false;
    //djyfs不支持多个文件合并写入到一个文件里
	if(dest_fp->attr.bits.archive)
    {
    	djy_printf("djyos不支持此操作,详情请看help!\r\n");
    	djyfs_fclose(dest_fp);
    	return false;
    }
	djyfs_fclose(dest_fp);
    
	src_fp = djyfs_fopen(src,"r");
    if(src_fp == NULL)
    {    
    	djyfs_fclose(dest_fp);
    	return false;
    }                             
	current_fp =(struct file_rsc *) djyfs_folder_traversal_son(src_fp,current_fp);
    //必须循环一次就关闭，否则数据不准确，有些文件可能被删除
   	djyfs_fclose(src_fp);
    if(current_fp == NULL)
    {
        djy_printf("%s*\r\n", src);
        djy_printf("系统找不到指定的文件\r\n");
        djy_printf("已经移动了	    	0个文件\r\n");//暂时这样
        return false;  //parent是一个空目录
    }    
    //strcpy(name,current_fp->name);
    do
    {

        if(current_fp->attr.bits.archive)
        {
            strcat(src,current_fp->name);
            strcat(dest,current_fp->name);
            move_file_to_dest(src,dest);
            djy_printf("%s\r\n", src);
            __cut_path_end_item(src);
            __cut_path_end_item(dest);
            file_nunmber++;
        }
        else if(!current_fp->attr.bits.archive)
        {
            if(fat_block_no==0xffffffff)//第一个的话，变成了child
                fat_block_no = current_fp->file_medium_tag;
        }
        src_fp = djyfs_fopen(src,"r");
    	if(src_fp == NULL)
        {    
        	djyfs_fclose(dest_fp);
        	return false;
        }                             
        //必须循环一次就关闭一次，否则数据不准确，有些文件可能被删除
       	djyfs_fclose(src_fp);
        current_fp = (struct file_rsc *)djyfs_folder_traversal_son(src_fp,current_fp);
        if(current_fp ==NULL)
            break;
        if(current_fp->attr.bits.archive)
        {
           continue;
        }
    	if(fat_block_no==current_fp->file_medium_tag)
        	break;
    } while(current_fp !=NULL);   
    	djy_printf("已经移动了	    	%d个文件\r\n", file_nunmber);
    	return true;                   
}

//----显示指定目录下的文件和子目录列表-----------------------------------------
//功能：显示指定目录下的文件和子目录列表	
//参数：dir_param，dir输入的参数，可以是文件
//返回：true，显示成功
//    	false,显示失败
//-----------------------------------------------------------------------------

bool_t fs_dir(char *dir_param)
{
	struct file_rsc *fp;
    s64 size;
    if(dir_param == NULL)
        return false;
    if(__check_wildcard_path(dir_param))     //路径部分不允许带通配符
    {
        djy_printf("%s 文件名不正确!\r\n",dir_param);
        return true;
    }
    else if(__check_wildcard_name(dir_param))   //文件名带通配符
    {
        dir_wildcard_files(dir_param);
        return true;
    }

    if(strcmp(dir_param,"\\")==0)//执行 dir [\]
    {
        fp = djyfs_get_rootfolder(pg_work_path);
        dir_item_son(fp);
        return true;
    }
    if(dir_param[0]=='.' && dir_param[1]=='.')//执行dir	[..]
    {    
        if(dir_parent(dir_param))
            return true;
        else
            return false;
    }
	if((dir_param[0] == '.') && (dir_param[1] == '\0'))
    {
    	dir_item_son(pg_work_path);
    	return true;
    }

    if(!__check_fullname(dir_param))
    {
        djy_printf("路径格式不正确!\r\n");
            return false;
    }
    if(__judge_item_attr(dir_param) != cn_item_is_folder)
    {
        djy_printf("系统找不到指定的路径\r\n");
        return false; 
    }
    if(djyfs_fsearch(dir_param,NULL))
    {
        fp = djyfs_fopen(dir_param,"r");
        if(fp->attr.bits.folder)
            dir_item_son(fp);
        else
        {
            djyfs_dbx_stat_fp(fp,NULL,NULL,&size);
            djy_printf("%s 的目录\r\n\r\n",dir_param);
            djy_printf("%d/%02d/%02d %02d:%02d",
                    (fp->year_high_modify<<8) + fp->year_low_modify,
                    fp->month_modify,
                    fp->date_modify,
                    fp->hour_modify,
                    fp->minute_modify);
            djy_printf("       ");
            djy_printf("%9dB %s\r\n", (s32)fp->file_size, fp->name);
            djy_printf("1个文件 %d字节\r\n", (s32)fp->file_size);
            djy_printf("0个目录 %d可用字节\r\n", (s32)size);
        }
        djyfs_fclose(fp);
        return true;
    }
    else
    {
        djy_printf("找不到文件\r\n");
        return false;
    }
}
//----列出文件柜内的空间参数--------------------------------------------------
//功能：把文件柜的大小，有效空间，空闲大小都列出来
//参数：DBX_name 文件柜名
//返回：true 成功
//-----------------------------------------------------------------------------
bool_t sh_chkdbx(char *DBX_name)
{
	s64 sum_size;
	s64 valid_size;
	s64 free_size;
    
    if(DBX_name == NULL)
    {
    	djy_printf("命令语法不正确!\r\n");
    	return false;
    }
	if(djyfs_dbx_stat(DBX_name,&sum_size,&valid_size,&free_size))
	{
    	djy_printf("文件柜%s占用总空间：%dB\r\n", DBX_name, (s32)sum_size);
    	djy_printf("文件柜%s有效空间：%dB\r\n", DBX_name, (s32)valid_size);
    	djy_printf("文件柜%s空闲空间：%dB\r\n", DBX_name, (s32)free_size);
	}
    else
    {
    	djy_printf("文件柜名不正确或未格式化!\r\n");
    }
 	return true;
}


//----将至少一个文件复制到另外一个位置--------------------------------------------------
//功能：将至少一个文件复制到另外一个位置
//参数：DBX_name 文件柜名
//返回：true 成功
//-----------------------------------------------------------------------------
bool_t sh_copy(char *param)
{
    char *next_param,source[255],destination[255];
    struct file_rsc *fp,*second_fp;
    char s[255];      
	if(param == NULL)
    {
    	djy_printf("命令语法不正确!\r\n");
    	return false;
    }
    strcpy(source,sh_get_word(param,&next_param));

	if(NULL == next_param)
    {
    	djy_printf("djyfs不支持此操作，详情请看help\r\n");
    	return false;
    }    
    strcpy(destination,sh_get_word(next_param,&next_param));
    if((!__check_fullname(source))||(!__check_fullname(destination)))
        return false; 
    if(!djyfs_fsearch(source,NULL))
    {
        djy_printf("系统找不到指定的文件\r\n");
        return false; 
    }
    //如果操作的文件一样，返回，不操作，因为效果一样
    if(strcmp(source,destination)==0)
        return true;
    if(djyfs_fsearch(destination,NULL))
    {
        second_fp = djyfs_fopen(destination,"r");
        if(second_fp == NULL)
        {
            return false;
        }
        if(second_fp->attr.bits.archive)
        {
            djy_printf("是否覆盖%s？ <yes/no>", destination);
            djyfs_fclose(second_fp); 
            while(1)
            {
                djy_scanf(NULL,s);
                if(s[0] == 'y'||s[0] == 'Y')
                {
                	djy_putchar(s[0]);
                    djy_printf("\r\n");
                    djyfs_remove(destination);//为覆盖做准备
                    break;
                }
                else if(s[0] == 'n'||s[0] == 'N')
                {
                	djy_putchar(s[0]);
                    djy_printf("\r\n");
                    return false;        
                }
            }   
        }
        else
        {   
            //是目录，需要增加反斜杠，以便下面拷贝路径使用   
            str_end_increase_backslash(destination);
            fp = djyfs_fopen(source,"r");
            if(fp == NULL)
            {
                djyfs_fclose(second_fp);
                return false;
            }
            if(fp->attr.bits.archive)
            {//如果source_file是文件，把文件名插入到second_work_path末尾
            //使用这个函数，还得提供准确的路径。
                str_end_wipe_backslash(source);
                __pick_filename_word(source,s);
                strcat(destination,s);      
             }
                djyfs_fclose(second_fp);
                djyfs_fclose(fp);
        }
    }
    else//如果destination不存在，那么全部按照文件处理
        str_end_wipe_backslash(source);//可以不用加反斜杠吧?
    fp = djyfs_fopen(source,"r");
    if(fp == NULL)
        return 0;
    if(!fp->attr.bits.folder)//source是一个文件
    {   
        djyfs_fclose(fp);
        copy_file_to_dest(source,destination);
        djy_printf("已经复制了      1个文件\r\n");
    }
    else//source是一个目录
    {
        djyfs_fclose(fp);
        str_end_increase_backslash(source);
        copy_files_of_folder_to_dest(source,destination);
    }
    return true;    
}


//----将至少一个文件移动到另外一个位置--------------------------------------------------
//功能：将至少一个文件移动到另外一个位置
//参数：DBX_name 文件柜名
//返回：true 成功
//-----------------------------------------------------------------------------
bool_t sh_move(char *param)
{
    char *next_param,source[255],destination[255];
    struct file_rsc *fp,*second_fp;
    char s[255];      
	if(param == NULL)
    {
    	djy_printf("命令语法不正确!\r\n");
    	return false;
    }
    strcpy(source,sh_get_word(param,&next_param));

	if(NULL == next_param)
    {
    	djy_printf("djyfs不支持此操作，详情请看help\r\n");
    	return false;
    }    
    strcpy(destination,sh_get_word(next_param,&next_param));
    if((!__check_fullname(source))||(!__check_fullname(destination)))
        return false; 
    if(!djyfs_fsearch(source,NULL))
    {
        djy_printf("系统找不到指定的文件\r\n");
        return false; 
    }
    //如果操作的文件一样，返回，不操作，因为效果一样
    if(strcmp(source,destination)==0)
        return true;
    if(djyfs_fsearch(destination,NULL))
    {
        second_fp = djyfs_fopen(destination,"r");
        if(second_fp == NULL)
        {
            return false;
        }
        if(second_fp->attr.bits.archive)
        {
            djy_printf("是否覆盖%s？ <yes/no>", destination);
            djyfs_fclose(second_fp); 
            while(1)
            {
                djy_scanf(NULL,s);
                if(s[0] == 'y')
                {
                	djy_putchar(s[0]);
                    djy_printf("\r\n");
                    djyfs_remove(destination);//为覆盖做准备
                    break;
                }
                else if(s[0] == 'n')
                {
                	djy_putchar(s[0]);
                    djy_printf("\r\n");
                    return false;        
                }
            }   
        }
        else
        {   
            //是目录，需要增加反斜杠，以便下面拷贝路径使用   
            str_end_increase_backslash(destination);
            fp = djyfs_fopen(source,"r");
            if(fp == NULL)
            {
                djyfs_fclose(second_fp);
                return false;
            }
            if(fp->attr.bits.archive)
            {//如果source_file是文件，把文件名插入到second_work_path末尾
            //使用这个函数，还得提供准确的路径。
                str_end_wipe_backslash(source);
                __pick_filename_word(source,s);
                strcat(destination,s);      
             }
                djyfs_fclose(second_fp);
                djyfs_fclose(fp);
        }
    }
    else//如果destination不存在，那么全部按照文件处理
        str_end_wipe_backslash(source);
    fp = djyfs_fopen(source,"r");
    if(fp == NULL)
        return 0;
    if(!fp->attr.bits.folder)//source是一个文件
    {   
        djyfs_fclose(fp);
        move_file_to_dest(source,destination);
        djy_printf("已经移动了      1个文件\r\n");
    }
    else//source是一个目录
    {
        djyfs_fclose(fp);
        str_end_increase_backslash(source);
        move_files_of_folder_to_dest(source,destination);
    }
    return true;    
}

//----修改指定文件或者文件夹的名字------------------------------------------------
//功能: 这是命令ren，修改指定的文件或者文件夹
//参数: param，输入参数
//返回: true=成功, 
//      false=失败，
//-----------------------------------------------------------------------------
bool_t sh_ren(char *param)
{
	char *next_param;
	char *fullname;//指定被修改的文件
	char *filename;//修改后的名字

	if(param == NULL)
    {
    	djy_printf("命令语法不正确!\r\n");
    	return false;
    }
    fullname = sh_get_word(param,&next_param);
    filename = sh_get_word(next_param,&next_param);
	if(!__check_fullname(fullname))
    	return false; 
	if(!djyfs_fsearch(fullname,NULL))
    {
    	djy_printf("系统找不到指定的文件\r\n");
     	return false; 
    }        
	djyfs_rename(fullname,filename);
	return true;

}    
//----创建一个或者多个目录------------------------------------------------
//功能: 这是命令md，创建一个或者多个目录
//参数: param，输入参数
//返回: true=成功, 
//      false=失败，
//-----------------------------------------------------------------------------
bool_t sh_md(char *param)
{
	char *next_param;
	char *del_param;
    //限制255字符，因为fs_mkdir的参数，要进行增加字符串
    //如果不限制，会内存泄漏。造成不可控
	char str[cn_shell_cmd_limit+1];
    
	del_param = sh_get_word(param,&next_param);
	if(del_param == NULL)
    {
    	djy_printf("命令语法不正确!\r\n");
    	return false;
    }
	strcpy(str,del_param);
	do
    {    
    	fs_mkdir(str);
    	del_param = sh_get_word(next_param,&next_param);
    	strcpy(str,del_param);    
    }while(del_param!=NULL);
	return true;
}


//----删除一个或者多个文件夹里的文件-------------------------------------------
//功能: 把指定的一个或者多个文件夹删除掉，只能删空目录
//参数: rd_param，输入字符
//返回: true=成功, 
//      false=失败，
//-----------------------------------------------------------------------------
bool_t sh_rd(char *param)
{
	char *next_param = param;
	char *del_param;

	if(param == NULL)
    {
    	djy_printf("命令语法不正确!\r\n");
    	return false;
    }
    
    
	while(1)
    {
        del_param = sh_get_word(next_param,&next_param);
        if(del_param == NULL)
            break;
        if(__check_wildcard(del_param))     //不允许带通配符删除文件夹
        {
            djy_printf("命令语法不正确!\r\n");
        }
        else
            fs_remove_folder(del_param);   
    }
    
	return true;
}

//----删除一个或者多个文件-----------------------------------------------------
//功能: 删除一个或者多个文件
//参数: param，输入字符
//返回: true=成功, 
//      false=失败，
//-----------------------------------------------------------------------------
bool_t sh_del(char *param)
{
	char *next_param;
	char *del_param;

    //参数不能为空字符
	if(param == NULL)
    {
    	djy_printf("命令语法不正确!\r\n");
    	return false;
    }
    next_param = param;
	while(1)
    {
        del_param = strsep(&next_param," ");
        if(del_param == NULL)
            break;
        if(del_param[0] == ' ')     //遇到连续空格
            break;
        if( ! __judge_backslash_is_data(del_param))     //路径不包含文件名
        {
            djy_printf("%s 文件名不正确!\r\n",del_param);
            break;
        }
        if(__check_wildcard_path(del_param))     //路径部分不允许带通配符
        {
            djy_printf("%s 文件名不正确!\r\n",del_param);
        }
        else if(__check_wildcard_name(del_param))   //文件名带通配符
        {
            del_wildcard_files(del_param);
        }
        else
        {
            if(__judge_item_attr(del_param) == cn_item_is_file) //不删除目录
            {
                if(djyfs_remove(del_param) == 0)
                    djy_printf("已删除 %s \r\n",del_param);
                else
                    djy_printf("删除 %s 错误\r\n",del_param);
            }
        }
    }

	return true;
}

//----显示当前目录的名称或改变当前目录-----------------------------------------
//功能: 显示当前目录的名称或改变当前目录
//参数: chdir_param，输入字符
//返回: true=成功, 
//      false=失败，
//-----------------------------------------------------------------------------
bool_t sh_cd(char *chdir_param)
{        
	bool_t result;
	struct file_rsc *fp;
	char work_path[cn_shell_cmd_limit+1];
    
    //执行cd/chdir[](空字符) 显示当前目录名称
	if(chdir_param == NULL)
    {
    	print_work_path();
    	djy_printf("\r\n");
    	return true;
    }
    //方便用户输入目录的时候不用输入反斜杠
    //如"cd folder\"变成"cd folder"
    //执行cd/chdir[\] 更换到根目录
	if(strcmp(chdir_param,"\\") ==0)
    {
        if(!get_DBX_name(work_path,cn_shell_cmd_limit))
            return false;
    	strcat(work_path,":\\");
    	fp=pg_work_path;
    	pg_work_path = djyfs_fopen(work_path,"r");
    	djyfs_fclose(fp);
    	return true;
    }
    //执行cd/chdir[..] 更换到上一级目录
	else if(chdir_param[0]=='.' && chdir_param[1]=='.')//执行 "cd .."
    {
        if(cd_parent(chdir_param))
            return true;
        else
            return false;
    }
	else
    {
    	if(!__check_fullname(chdir_param))
         	return false; 
    	result = djyfs_fsearch(chdir_param,NULL);
        //执行 cd/chdir[文件柜：]路径 显示当前目录的名称或改变当前目录
    	if(result == true)
        {
            //是目录才能打开            
        	if(__judge_item_attr(chdir_param) == cn_item_is_folder)
            {
            	fp = pg_work_path;
            	pg_work_path = djyfs_fopen(chdir_param,"r");
            	djyfs_fclose(fp);
            	return true;
            }
        	else if(!__judge_backslash_is_data(chdir_param))
            {//如C:\,在judge_is_folder里无法成功判断
            	fp = pg_work_path;
            	pg_work_path = djyfs_fopen(chdir_param,"r");
            	djyfs_fclose(fp);
            	return true;    
            }
        	else
            {
                djy_printf("系统找不到指定的路径\r\n");
                return false;
            }
        }
    	else
            	djy_printf("系统找不到指定的路径\r\n");
    }
 	return true;
}

//-------显示指定目录下的文件和子目录列表--------------------------------------
//功能: 显示指定目录下的文件和子目录列表
//参数: param，输入字符
//返回: true=成功, 
//      false=失败，
//-----------------------------------------------------------------------------
bool_t sh_dir(char *param)
{
	char *dir_param;
	char *next_param = param;
	if(param == NULL)
    {
    	dir_item_son(pg_work_path);
    	return true;
    }

	do
    {
        dir_param = strsep(&next_param," ");
        if(dir_param == NULL)
            break;
        if(dir_param[0] == ' ')     //遇到连续空格
            break;
        fs_dir(dir_param);
    }while(dir_param != NULL);
    
	return true;
}


bool_t sh_create_dbx(char *param)
{
#if 0
    struct flash_chip *chip;
    struct rsc_node *chip_tree;
    u64  dbx_size;
    u32 blocks;
    char *word,*next_param;

    chip_tree = rsc_search_tree("flash chip");
    chip = (struct flash_chip *)rsc_get_son(chip_tree);
    
    word = sh_get_word(param,&next_param);
    dbx_size = djy_atol(word);
    blocks = dbx_size / chip->block_size+1;
    if(blocks > chip->valid_sum)
    {
        djy_printf("尺寸太大\r\n");
        return true;
    }
    word = sh_get_word(next_param,&next_param);
    if(word == NULL)
    {
        djy_printf("文件柜名不能为空");
        return true;
    }
    
    if(DFFSD_create_DBX(chip,blocks,word) == true)
    {
        djy_printf("创建文件柜成功");
    }
    else
    {
        djy_printf("创建文件柜失败");
    }
    djy_printf("\r\n");
#endif
    return true;
}

bool_t sh_format(char *param)
{
    if(param == NULL)
    {
        djy_printf("文件柜名不能为空");
        return true;
    }
    
    if(djyfs_format(1,0,param) == 0)
    {
        djy_printf("格式化成功");
    }
    else
    {
        djy_printf("格式化失败");
    }
    djy_printf("\r\n");
    return true;
}
#endif //#if ((cfg_djyfs == 1) && (cfg_run_mode != cn_mode_tiny))

