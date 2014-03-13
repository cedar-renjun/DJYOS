//----------------------------------------------------
//Copyright (C), 2011.9,wjz.
//��Ȩ���� (C), 2011.9,wjz
//����ģ��: djyshģ��
//���ߣ�wjz
//�汾��djysh1.0.0
//�ļ�����: djysh���ļ�ϵͳshell���
//�޶���ʷ:
// 1. ����:2010-6-15
//   ����:wjz
//   �°汾�ţ�djysh1.0.0
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

//----���ͨ���-----------------------------------------------
//����: ����ַ�����·�������Ƿ����ǺŻ����ʺ�,���ҳ�������������󳤶�Ϊ�ޡ�
//����: str,�����ַ���
//����: true=·��������'*'����'?'��false=û'*'����'?'
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

//----���ͨ���-----------------------------------------------
//����: ����ַ������ļ��������Ƿ����ǺŻ����ʺ�,���ҳ�������������󳤶�Ϊ�ޡ�
//����: str,�����ַ���
//����: true=�ļ���������'*'����'?'��false=û'*'����'?'
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

//----���ͨ���-----------------------------------------------
//����: ����ַ����Ƿ����ǺŻ����ʺ�,���ҳ�������������󳤶�Ϊ�ޡ�
//����: str,�����ַ���
//����: true=�ļ���������'*'����'?'��false=û'*'����'?'
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

//-------��ͨ������ַ�ƥ��-----------------------------------------------------
//����: ��ͨ������ַ�ƥ�������ͨ�����'?'��'*'������,'?'���Դ���һ���ַ�
//        (����û��),'*'���Դ����������ַ�(����Ϊ��)��������'?'�� ����'?'
//    	�Ĺ���,'?'��ʾ�����ַ�,Ҳ����˵��ƥ�������,'?'��Զƥ��ɹ� ��
//    	������,'?'��û���޸��㷨���������޸���ƥ����� -- ����'?'��һ��ƥ�� ��
//    	Ȼ��'*'��˲�ͬ,'*'��������ƥ���������ַ�����Ȼ���ǲ��ܼ򵥵��޸�ƥ��
//    	���̶�����Ҫ��
//����: src - ��ƥ����ַ���,���ܺ���'?'��'*'
//    	wildcard - ͨ����ַ���
//����: true=ƥ��ɹ�,
//      false=ƥ��ʧ��,
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
			while (wildcard[j] == '*')	// �ҵ�һ����*�ŵ����һ��*��
			{
				j++;
				if (wildcard[j] == '\0')
				{
					return true;	// ƥ��
				}
			}
			while (src[i] != wildcard[j])	// ƥ��src����*���һ���ַ�
			{
				if (src[i])
				{
					i++;
				}
				else
				{
					return false;	// ��ƥ��
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

//----�ж�'\'�����Ƿ�������-----------------------------------------------------
//����: ��һ�����ܰ����༶·�������ļ������ַ������жϵ�һ������'\'֮���Ƿ���
//      ����
//����: path������·������ʽ��"C:\aaaa\bbbb\cccc"
//����: true=�ɹ�, ˵��'\'֮��������,����û��'\'
//      false=ʧ�ܣ�˵��'\'֮��û������
//��ע: pathӦ���Ǿ����Ϸ��Լ����ַ������������word����������
//-----------------------------------------------------------------------------
bool_t __judge_backslash_is_data(char *path)
{
    uint32_t index;
    uint32_t name_len;

	name_len = strlen(path);
    for(index = 0; index< name_len; index++)
    {
        if(path[index] == '\\')    //�����ַ�'\'
        {
            if(path[index+1] != '\0')
            	return true;
        	else
            	return false;
        }
    }
    //�ַ�����û�з�б��
	if(index == name_len)
    	return true;
	else
    	return false;            
}

//----ɾ��·������ļ�����Ŀ¼-------------------------------------------------
//����: ��һ�����ܰ����༶·�������ļ������ַ�����ɾ�����һ����path��һ����
//      Ŀ¼�����򲻲���
//����: path������·������ʽ��"C:\aaaa\bbbb\cccc"
//����: true=�ɹ�ɾ����������ɾ��
//      false=ʧ��
//-----------------------------------------------------------------------------
bool_t __cut_path_end_item(char *path)
{
	uint16_t name_len,loop;
    
	name_len = strlen(path);
	loop=name_len;
	if(path[name_len-1]=='\\')//�з�б��˵����ȥ���ļ���
    {
    	if(path[name_len-2]==':')
        	return true;//˵���Ǹ�Ŀ¼�����ò���
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
	else//û�з�б�ܣ�˵��ȥ�������ļ�
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

//----��ȡ·������ļ�����Ŀ¼--------------------------------------------------
//����: ��һ�����ܰ����༶·�������ļ������ַ�������ȡ���һ����path�Ǹ�Ŀ¼
//      �򲻲�����path�����ֲ��䡣
//����: path������·������ʽ��"C:\aaaa\bbbb\cccc"
//    	name,������ȡ���ļ�����Ŀ¼
//����: true=�ɹ�, ��ȡ�ɹ�
//      false=ʧ�ܣ���ȡʧ��
//-----------------------------------------------------------------------------
bool_t __pick_path_end_item(char *path,char *name)
{
	uint16_t name_len,loop;
	char *str;
    
	name_len = strlen(path);
	loop=name_len;
	if(path[name_len-1]=='\\')//�з�б�ܣ�˵����ȡ�����ļ�����
    {
    	if(path[name_len-2]==':')
        	return false;   //˵���Ǹ�Ŀ¼�����ò���
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
	else//û�з�б�ܣ�˵����ȡ�����ļ���
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
    //ִ�е��ⲽ��˵��ֻ��һ���ļ�����Ŀ¼��ֱ�ӿ�����ok
    strcpy(name,path);    
	return true;
}

//----�����ļ���---------------------------------------------------------------
//����: ����ַ��������ļ�����������һ��'\\'��ĵ�һ���ַ��ĳ�'\0'���������ļ�
//      ��ָ��
//����: path�������ԵĴ�
//      filename�������ļ�����ַ,�����ַ��Ѿ�����Ϊ����ֵ���أ����б��滻Ϊ'\0'
//      pathname����path���д���Ŀ¼�����򷵻�·������ַ�����򷵻�NULL;
//����: ��'\0'�滻���ַ���'\0'=�����ļ���
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
    if(loop == name_len)        //��������һ���ļ���
    {
        *pathname = NULL;
        *filename = path;
        return path[0];
    }
    else if(loop == name_len -1)    //�����ļ���
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

//----�ж��ַ����Ǿ���·���������·��-----------------------------------------
//����: ���һ�����ܰ����༶·�������ļ������ַ����Ƿ�����ļ������ľ���·��
//����: path������·������ʽ��"C:\aaaa\bbbb\cccc"
//����: true=�Ǿ���·��
//      false=���Ǿ���·��
//��ע: pathӦ���Ǿ����Ϸ��Լ����ַ������������word����������
//-----------------------------------------------------------------------------
bool_t __path_is_absolute_path(char *path)
{
    uint32_t index;
    //synname���Ѿ������ַ������ȺϷ��Լ���ָ��
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

//----�ж�·���Ƿ�����ļ���---------------------------------------------------
//����: �ж�һ�����ܰ����༶·�������ļ������ַ����Ƿ�����ļ�����
//����: path������·������ʽ��"C:\aaaa\bbbb\cccc"
//����: true=���ļ�����
//      false=�����ļ�����
//-----------------------------------------------------------------------------
bool_t __path_include_dbxname(char *path)
{
    uint32_t index;
    //synname���Ѿ������ַ������ȺϷ��Լ���ָ��
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

//----Ŀ¼��ƥ����ļ���ȡ��һ���ַ���--------------------------------------
//����: ��һ��Ŀ¼��ɨ����ڵ��ļ���Ȼ��ÿ���ļ�ͨ��ƥ�亯����wildcard_param����
//    	һһƥ�䣬��ƥ����ļ����ᵽ��һ���ַ����
//����: wildcard_param������ͨ����Ĳ���
//    	get_merge_str ��������Ҫ����ļ����ϲ����ɵ��ַ���
//����: true=�ɹ�, ��ȡ�ɹ�
//      false=ʧ�ܣ���ȡʧ��
//-----------------------------------------------------------------------------
char *get_folder_wildcard_str(char *wildcard_param,char *get_merge_str)
{
	struct file_rsc *fp = NULL,*current_fp = NULL;
	char work_path[256];
    u32 fat_block_no;

 
    if(__djyfs_is_contain_DBX_name(wildcard_param) ==0)
        fp = pg_work_path;//���·����ֱ��ʹ�ù���·��
    else
    {    
    	strcpy(work_path,wildcard_param);
    	__pick_filename_word(work_path,wildcard_param);
        __cut_path_end_item(work_path);
        fp = djyfs_fopen(work_path, "r");    
    }
    //���ļ���û���壨ͬʱfp2�ǷǸ�Ŀ¼,��Ŀ¼�£��ļ����Բ�ȷ����
    if(fp->attr.bits.archive&&(fp->file_medium_tag!=0))
        return NULL;
	current_fp =(struct file_rsc *)djyfs_folder_traversal_son(fp,current_fp);
	if(current_fp == NULL)
    {    
    	djyfs_fclose(fp);
    	djy_printf("��Ŀ¼Ϊ��!\r\n");
    	return NULL;
    }
	fat_block_no = current_fp->file_medium_tag;
        //ȫ����0�������Ϳ���׼ȷ֪������merge_str�Ѿ�û��������
    memset(get_merge_str,0,sizeof(get_merge_str));
	do//ѭ����Ŀ¼��ֱ������
    {
    	if(__wildcard_match(current_fp->name,wildcard_param))
        {//��ƥ��ɹ���Ŀ¼����һ�����ַ���
        	strcat(get_merge_str,current_fp->name);
        	strcat(get_merge_str," ");
        }    
        //��fp�����е��ļ�����ɾ���ˣ���û�ļ�������false
        current_fp = (struct file_rsc *)djyfs_folder_traversal_son(fp,current_fp);
        if(current_fp == NULL)
            break;
    }while(current_fp != NULL);
	djyfs_fclose(fp);

	return get_merge_str;
}

//----��ͨ���ɾ���ļ�---------------------------------------------------------
//����: ��ͨ���ɾ���ļ���·�����ֲ��ܴ�ͨ�������Ŀ¼Ҳһ��ɾ����
//����: 
//����: true=�ɹ�, ��ȡ�ɹ�
//      false=ʧ�ܣ���ȡʧ��
//-----------------------------------------------------------------------------
bool_t del_wildcard_files(char *wildcard_param)
{
	char *filename,*pathname;
    char ch;
    struct file_rsc *current=NULL,*parent;

	if(wildcard_param == NULL)
    {
		djy_printf("�ļ�������ȷ!\r\n");
    	return false;
    }
    ch = __separate_filename(wildcard_param,&filename,&pathname);
    if(filename == NULL)     //�����ļ���
    {
		djy_printf("�ļ�������ȷ!\r\n");
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
            djy_printf("·��������\n\r");
            return false;
        }
    }
    else
    {
        parent = pg_work_path;
    }
    if(filename != NULL)
        filename[0] = ch;       //�ָ��ļ����ĵ�һ���ַ�
	while(1)                //ѭ����Ŀ¼��ֱ������
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

//----���ַ���ĩβ�޷�б�ܼ��Ϸ�б��--------------------------------------------------------------
//���ܣ����ַ���ĩβ�޷�б�ܼ��Ϸ�б��,�з�б�ܾͲ�Ҫ����
//������str �ַ������κ���ʽ
//���أ�true �ɹ�
//    	false ����".."��
//------------------------------------------------------------------------------
bool_t str_end_increase_backslash(char *str)
{
	uint16_t name_len;

	if(strcmp(str,"..") ==0)//�����"..",��ô��Ҫ����
    	return false;
	name_len = strnlen(str,cn_shell_cmd_limit +1);
    if(name_len >cn_shell_cmd_limit)
        return false;
    //����ַ������һλ����'\\'����ô�ӷ�б��
	if(str[name_len-1] != '\\')
    {
    	str[name_len] = '\\';
        //���str���ǹ涨�õĿռ䣬������й¶�������ֹ
       	str[name_len+1] = '\0';    
    }
	return true;
}

//----���ַ���ĩβ�з�б��ȥ����б��--------------------------------------------
//���ܣ����ַ���ĩβ�޷�б�ܼ��Ϸ�б�ܣ�û�з�б�ܾͲ�����
//������str �ַ������κ���ʽ
//���أ�true �ɹ�
//    	false �ַ���û�з�б��
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

//----��ʾĿ¼�µ��ļ����ļ���------------------------------------------------
//����: ɨ���Ŀ¼�µ��ļ����ļ��У�Ȼ����һ������ʽ��ȫ����ӡ����
//����: ancestor_fp������ʾ���ļ���
//����: true=�ɹ�, �г��ɹ�
//      false=ʧ�ܣ��г�ʧ��
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
        return false;//�������ļ���δ����

    index = djyfs_getpath_len(parent_fp);
    buf = m_malloc(index,0);
    if(buf == NULL)
    {
        djy_printf("�ڴ治�㣬����ִ��dir");
        return false;
    }
    buf[0] = '\0';
    djyfs_getpath(parent_fp,buf,index+1);
    djy_printf("%s ��Ŀ¼\r\n\r\n",buf);
    djyfs_dbx_stat_fp(parent_fp,NULL,NULL,&available_dbx_size);

	current_fp = NULL;
    current_fp = (struct file_rsc*)djyfs_folder_traversal_son(parent_fp,current_fp);
    if(current_fp == NULL)
    {
        djy_printf("��Ŀ¼Ϊ��!\r\n");
        return false;
    }

    do //ѭ����Ŀ¼��ֱ������
    {
        djy_printf("%d/%02d/%02d %02d:%02d",
                (current_fp->year_high_modify<<8) + current_fp->year_low_modify,
                current_fp->month_modify,
                current_fp->date_modify,
                current_fp->hour_modify,
                current_fp->minute_modify);

        if(current_fp->attr.bits.folder)
        {
            djy_printf(" <DIR> ");//������Ŀ¼�����Լ���dir
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

    djy_printf("%d���ļ� %d�ֽ�\r\n", files_items, (s32)files_size);
    djy_printf("%d��Ŀ¼ %d�����ֽ�\r\n", folder_items, (s32)available_dbx_size);
    return true;
}

//----��ʾ����ͨ������ļ������ļ���------------------------------------------------
//����: dir�����£���ʾ����ͨ������ļ������ļ��С�ɨ�赱ǰ����·������ָ��·����
//    	���ļ�����Ŀ¼��Ȼ����ƥ�亯��һһƥ�䡣����Ҫ��ģ���ʾ������
//����: wildcard_param������ͨ������ַ���
//����: true=�ɹ�, �г��ɹ�
//      false=ʧ�ܣ��г�ʧ��
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
		djy_printf("�ļ�������ȷ!\r\n");
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
            djy_printf("·��������\n\r");
            return false;
        }
    }
    else
    {
        parent = pg_work_path;
    }
    if(filename != NULL)
        filename[0] = ch;       //�ָ��ļ����ĵ�һ���ַ�

	while(1)                //ѭ����Ŀ¼��ֱ������
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
    djy_printf("%d���ļ� %d�ֽ�\r\n", files_items, (s32)files_size);
    djy_printf("%d��Ŀ¼ %d�����ֽ�\r\n", folder_items, (s32)available_dbx_size);
	return true;    
}



//----�ж�һ��Ŀ¼�Ƿ����ļ���------------------------------------------------
//����: ͨ������fp�����ԣ��ж��Ƿ����ļ���
//����: fullname,·�� ��ʽ:"C:\aa\bb\cc"
//����: cn_item_is_folder=���ļ���, 
//      cn_item_is_file=���ļ���
//      cn_item_no_exist=�������������ļ����ļ���
//ע:   ����ʱ��ȷ��fullname�ǺϷ����ַ���
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

//----����һ���ļ���------------------------------------------------
//����: ָ������һ���ļ���
//����: md_param�������ַ�
//����: true=�ɹ�, 
//      false=ʧ�ܣ�
//-----------------------------------------------------------------------------
bool_t fs_mkdir(char *md_param)
{  
	struct file_rsc *fp;

	if(md_param == NULL)
    {
    	djy_printf("�����﷨����ȷ!\r\n");
    	return false;
    }
    //�ڴ�����ĩβ����'\'��������Σ�����Ŀ¼
    //���ﲻ���ڴ�й©����Ϊmd������涨�˳���
	str_end_increase_backslash(md_param);
	if(!__check_fullname(md_param))
     	return false; 
    //����д����ļ�����Ŀ¼����ô�Ͳ���Ҫ������
    if(!djyfs_fsearch(md_param,NULL))
    {
        fp = djyfs_fopen(md_param,"w+");
        if(fp == NULL)
            return false;
        djyfs_fclose(fp);
    }
    else
    {
        djy_printf("\r\n��Ŀ¼�����ļ�%d�Ѿ�����\r\n", md_param);

        return false;
    }
    return true;    
}
//----ɾ���ļ���--------------------------------------------------------------
//����: ��ָ�����ļ���ɾ����
//����: rd_param�������ַ�
//����: true=�ɹ�, 
//      false=ʧ�ܣ�
//-----------------------------------------------------------------------------
bool_t fs_remove_folder(char *rd_param)
{    
	struct file_rsc *fp;

	if(rd_param == NULL)
    {
    	djy_printf("�����﷨����ȷ!\r\n");
    	return false;
    }
	if(!__check_fullname(rd_param))
     	return false; 
	fp = djyfs_fopen(rd_param,"r");
	if(fp == NULL)
    {    
    	djy_printf("ϵͳ�Ҳ���ָ�����ļ�\r\n");
    	return false; 
    }
	if(fp->attr.bits.folder)
    {
    	djyfs_fclose(fp);
    	if(djyfs_remove(rd_param) == enum_fs_folder_unblank)
        {
            djy_printf("Ŀ¼%s���ǿգ�\r\n", rd_param);
        }
    	return true;
    }
	else
    {
    	djyfs_fclose(fp);
    	djy_printf("Ŀ¼������Ч!\r\n");
    	return false;
    }
    
}

//----��ʾָ��Ŀ¼�µ��ļ�����Ŀ¼�б�-------------------------------------------------------
//���ܣ���ʾָ��Ŀ¼�µ��ļ�����Ŀ¼�б�	
//������dir_param��dir����Ĳ������������ļ���·�����߲�����
//���أ�true����ʾ�ɹ�
//    	false,��ʾʧ��
//-----------------------------------------------------------------------------
bool_t dir_parent(char *next_param)
{
    char *foldername=NULL;
    struct file_rsc *fp;
    uint32_t lenth=0;
    char work_path[cn_shell_cmd_limit+1];

    //�������ʹ��get_work_path�ˡ����棬dir ..\folder����Ҫ                                                        ->private_tag);
    get_work_path_name(work_path,cn_shell_cmd_limit);
    do   
    {
        foldername = (char *)sh_get_item(next_param,&next_param);
    	if(foldername == NULL&&lenth==0)
        	return false;
        //ִ�� ��: cd ..\foder
        if(strcmp(foldername,"..") != 0)
        {
            str_end_increase_backslash(work_path);
            strcat(work_path,foldername);
            fp = djyfs_fopen(work_path,"r");
            if(fp == NULL)
            {
                djy_printf("ϵͳ�Ҳ���ָ����·��!\r\n");
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
        //·����ȴ���cn_path_depth_limit��������ѭ���������
        //��Ϊ�˷�ֹ��ѭ������һ��������
        lenth++;
     }while((lenth!=cn_path_depth_limit)&&(foldername != NULL));    
    return true;
}

//----���ĵ�ǰ����·������Ŀ¼-------------------------------------------------------
//���ܣ����ĵ�ǰ����·����ԭ����ǰ����·���ĸ�Ŀ¼
//������next_param������Ĳ���
//���أ�true����ʾ�ɹ�
//    	false,��ʾʧ��
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
        //ִ�� ��: cd ..\foder
        if(strcmp(foldername,"..") != 0)
        {
            //��Ŀ¼���ܴ򿪣����ÿ��Ǹ�Ŀ¼�������
            //����"cd ..\foder",�ڸ�Ŀ¼��ִ�У���û���塣
            //��ֻ����ʽ�򿪣���������ڣ��ͷ���NULL��
            //�Ͳ���ȥר��������Ŀ¼�����Ŀ¼�Ƿ���ڡ�
        	if(__judge_item_attr(foldername) == cn_item_is_folder)
            {
            	fp = pg_work_path;
            	pg_work_path = djyfs_fopen(foldername,"r");
            	djyfs_fclose(fp);
            	return true;
            }
        	else
            {
                djy_printf("ϵͳ�Ҳ���ָ��·��\r\n");
                return false;
            } 
            lenth++;
        }
        temp = (struct file_rsc*)rsc_get_parent(&pg_work_path->file_node);
    	if(temp != root)
        {    
        	fp=pg_work_path;        //��ǰ����·�����ܹر�,��ת��
            pg_work_path = temp;
            djyfs_fclose(fp);
        }
        else
            break;
        //·����ȴ���cn_path_depth_limit��������ѭ���������
        //��Ϊ�˷�ֹ��ѭ������һ��������
     }while((lenth <= cn_path_depth_limit)&&(next_param != NULL));    
    return true;
}


//----��ʾָ��Ŀ¼�µ��ļ�����Ŀ¼�б�-------------------------------------------------------
//���ܣ���ʾָ��Ŀ¼�µ��ļ�����Ŀ¼�б�	
//������dir_param��dir����Ĳ������������ļ���·�����߲�����
//���أ�true����ʾ�ɹ�
//    	false,��ʾʧ��
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
    	djy_printf("���ļ��񲻴���\r\n");
        return false;
    }
}

//���ƴ���̫�࣬���������!������ĥ��ƽ���!��֮��������һ����bug��

//----����һ���ļ���Ŀ��------------------------------------------------
//����: ��һ���ļ����Ƶ���Ҫ�����Ƶĵط�
//����:  src����ǰ�Ĺ���·������������work_path����Ϊwork_patch��ȫ�ֱ�����
//    	�������޸ġ�
//    	dest���������·���Ǹ��Ƶ�Ŀ���·��
//����: true=�ɹ�, 
//      false=ʧ�ܣ�
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
    ////����16k�ڴ�,��ֹ�ڴ治��
    //������ڴ治��̫С�������ļ��󣬲��������࣬Ӱ��copy���ٶ�
    //̫�����벻�˾��군�ˣ���ʱ��Ϊ16k�����һ��flash��Ĵ�С
    //��Ƶ������֮����ȷ��
	buf_size = 16384;
	loop_times =(file_size+buf_size-1)/buf_size;
    if(loop_times==0)
    {//loop_times==0ʱ��˵���ļ���СΪ0.ֻ��Ҫ��������ok
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
    	else//д�������С��������ڴ棬��Ӧ��д��buf_size�Ĵ�С
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
//----�ƶ�һ��Ŀ¼�µ��ļ���Ŀ��------------------------------------------------
//����: ��һ��Ŀ¼���ļ��ƶ�����Ҫ���ƶ��ĵط�
//����: src����ǰ�Ĺ���·������������work_path����Ϊwork_patch��ȫ�ֱ�����
//    	�������޸ġ�
//    	dest���������·���Ǹ��Ƶ�Ŀ���·��
//����: true=�ɹ�, 
//      false=ʧ�ܣ�
//-----------------------------------------------------------------------------
bool_t copy_files_of_folder_to_dest(char *src,char *dest)
{

	uint32_t file_nunmber=0,fat_block_no;
	struct file_rsc *dest_fp,*src_fp,*current_fp=NULL;
    if(!djyfs_fsearch(dest,NULL))
    {
    	djy_printf("djyos��֧�ִ˲���,�����뿴help!\r\n");
    	return false;
    }    
	dest_fp = djyfs_fopen(dest,"r");
    if(dest_fp == NULL)
        return false;
    //djyfs��֧�ֶ���ļ��ϲ�д�뵽һ���ļ���
	if(dest_fp->attr.bits.archive)
    {
    	djy_printf("djyos��֧�ִ˲���,�����뿴help!\r\n");
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
    //����ѭ��һ�ξ͹رգ��������ݲ�׼ȷ����Щ�ļ����ܱ�ɾ��
   	djyfs_fclose(src_fp);
    if(current_fp == NULL)
    {
        djy_printf("%s*\r\n", src);
        djy_printf("ϵͳ�Ҳ���ָ�����ļ�\r\n");
        djy_printf("�Ѿ�������	    	0���ļ�\r\n");//��ʱ����
        return false;  //parent��һ����Ŀ¼
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
        //����ѭ��һ�ξ͹ر�һ�Σ��������ݲ�׼ȷ����Щ�ļ����ܱ�ɾ��
       	djyfs_fclose(src_fp);
        current_fp = (struct file_rsc *)djyfs_folder_traversal_son(src_fp,current_fp);
    } while(current_fp != NULL);   
    	djy_printf("�Ѿ�������	    	%d���ļ�\r\n", file_nunmber);
    	return true;                   
}

//���ƴ���̫�࣬���������!������ĥ��ƽ���!��֮��������һ����bug��

//----�ƶ�һ���ļ���Ŀ��------------------------------------------------
//����: ��һ���ļ��ƶ�����Ҫ���ƶ��ĵط�
//����:  src����ǰ�Ĺ���·������������work_path����Ϊwork_patch��ȫ�ֱ�����
//    	�������޸ġ�
//    	dest���������·���Ǹ��Ƶ�Ŀ���·��
//����: true=�ɹ�, 
//      false=ʧ�ܣ�
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
    ////����16k�ڴ�,��ֹ�ڴ治��
    //������ڴ治��̫С�������ļ��󣬲��������࣬Ӱ��copy���ٶ�
    //̫�����벻�˾��군�ˣ���ʱ��Ϊ16k�����һ��flash��Ĵ�С
    //��Ƶ������֮����ȷ��
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
    	else//д�������С��������ڴ棬��Ӧ��д��buf_size�Ĵ�С
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

//----�ƶ�һ��Ŀ¼�µ��ļ���Ŀ��------------------------------------------------
//����: ��һ��Ŀ¼���ļ��ƶ�����Ҫ���ƶ��ĵط�
//����: src����ǰ�Ĺ���·������������work_path����Ϊwork_patch��ȫ�ֱ�����
//    	�������޸ġ�
//    	dest���������·���Ǹ��Ƶ�Ŀ���·��
//����: true=�ɹ�, 
//      false=ʧ�ܣ�
//-----------------------------------------------------------------------------
bool_t move_files_of_folder_to_dest(char *src,char *dest)
{

	uint32_t file_nunmber=0,fat_block_no=0xffffffff;
	struct file_rsc *dest_fp,*src_fp,*current_fp=NULL;
    if(!djyfs_fsearch(dest,NULL))
    {
    	djy_printf("djyos��֧�ִ˲���,�����뿴help!\r\n");
    	return false;
    }    
	dest_fp = djyfs_fopen(dest,"r");
    if(dest_fp == NULL)
        return false;
    //djyfs��֧�ֶ���ļ��ϲ�д�뵽һ���ļ���
	if(dest_fp->attr.bits.archive)
    {
    	djy_printf("djyos��֧�ִ˲���,�����뿴help!\r\n");
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
    //����ѭ��һ�ξ͹رգ��������ݲ�׼ȷ����Щ�ļ����ܱ�ɾ��
   	djyfs_fclose(src_fp);
    if(current_fp == NULL)
    {
        djy_printf("%s*\r\n", src);
        djy_printf("ϵͳ�Ҳ���ָ�����ļ�\r\n");
        djy_printf("�Ѿ��ƶ���	    	0���ļ�\r\n");//��ʱ����
        return false;  //parent��һ����Ŀ¼
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
            if(fat_block_no==0xffffffff)//��һ���Ļ��������child
                fat_block_no = current_fp->file_medium_tag;
        }
        src_fp = djyfs_fopen(src,"r");
    	if(src_fp == NULL)
        {    
        	djyfs_fclose(dest_fp);
        	return false;
        }                             
        //����ѭ��һ�ξ͹ر�һ�Σ��������ݲ�׼ȷ����Щ�ļ����ܱ�ɾ��
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
    	djy_printf("�Ѿ��ƶ���	    	%d���ļ�\r\n", file_nunmber);
    	return true;                   
}

//----��ʾָ��Ŀ¼�µ��ļ�����Ŀ¼�б�-----------------------------------------
//���ܣ���ʾָ��Ŀ¼�µ��ļ�����Ŀ¼�б�	
//������dir_param��dir����Ĳ������������ļ�
//���أ�true����ʾ�ɹ�
//    	false,��ʾʧ��
//-----------------------------------------------------------------------------

bool_t fs_dir(char *dir_param)
{
	struct file_rsc *fp;
    s64 size;
    if(dir_param == NULL)
        return false;
    if(__check_wildcard_path(dir_param))     //·�����ֲ������ͨ���
    {
        djy_printf("%s �ļ�������ȷ!\r\n",dir_param);
        return true;
    }
    else if(__check_wildcard_name(dir_param))   //�ļ�����ͨ���
    {
        dir_wildcard_files(dir_param);
        return true;
    }

    if(strcmp(dir_param,"\\")==0)//ִ�� dir [\]
    {
        fp = djyfs_get_rootfolder(pg_work_path);
        dir_item_son(fp);
        return true;
    }
    if(dir_param[0]=='.' && dir_param[1]=='.')//ִ��dir	[..]
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
        djy_printf("·����ʽ����ȷ!\r\n");
            return false;
    }
    if(__judge_item_attr(dir_param) != cn_item_is_folder)
    {
        djy_printf("ϵͳ�Ҳ���ָ����·��\r\n");
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
            djy_printf("%s ��Ŀ¼\r\n\r\n",dir_param);
            djy_printf("%d/%02d/%02d %02d:%02d",
                    (fp->year_high_modify<<8) + fp->year_low_modify,
                    fp->month_modify,
                    fp->date_modify,
                    fp->hour_modify,
                    fp->minute_modify);
            djy_printf("       ");
            djy_printf("%9dB %s\r\n", (s32)fp->file_size, fp->name);
            djy_printf("1���ļ� %d�ֽ�\r\n", (s32)fp->file_size);
            djy_printf("0��Ŀ¼ %d�����ֽ�\r\n", (s32)size);
        }
        djyfs_fclose(fp);
        return true;
    }
    else
    {
        djy_printf("�Ҳ����ļ�\r\n");
        return false;
    }
}
//----�г��ļ����ڵĿռ����--------------------------------------------------
//���ܣ����ļ���Ĵ�С����Ч�ռ䣬���д�С���г���
//������DBX_name �ļ�����
//���أ�true �ɹ�
//-----------------------------------------------------------------------------
bool_t sh_chkdbx(char *DBX_name)
{
	s64 sum_size;
	s64 valid_size;
	s64 free_size;
    
    if(DBX_name == NULL)
    {
    	djy_printf("�����﷨����ȷ!\r\n");
    	return false;
    }
	if(djyfs_dbx_stat(DBX_name,&sum_size,&valid_size,&free_size))
	{
    	djy_printf("�ļ���%sռ���ܿռ䣺%dB\r\n", DBX_name, (s32)sum_size);
    	djy_printf("�ļ���%s��Ч�ռ䣺%dB\r\n", DBX_name, (s32)valid_size);
    	djy_printf("�ļ���%s���пռ䣺%dB\r\n", DBX_name, (s32)free_size);
	}
    else
    {
    	djy_printf("�ļ���������ȷ��δ��ʽ��!\r\n");
    }
 	return true;
}


//----������һ���ļ����Ƶ�����һ��λ��--------------------------------------------------
//���ܣ�������һ���ļ����Ƶ�����һ��λ��
//������DBX_name �ļ�����
//���أ�true �ɹ�
//-----------------------------------------------------------------------------
bool_t sh_copy(char *param)
{
    char *next_param,source[255],destination[255];
    struct file_rsc *fp,*second_fp;
    char s[255];      
	if(param == NULL)
    {
    	djy_printf("�����﷨����ȷ!\r\n");
    	return false;
    }
    strcpy(source,sh_get_word(param,&next_param));

	if(NULL == next_param)
    {
    	djy_printf("djyfs��֧�ִ˲����������뿴help\r\n");
    	return false;
    }    
    strcpy(destination,sh_get_word(next_param,&next_param));
    if((!__check_fullname(source))||(!__check_fullname(destination)))
        return false; 
    if(!djyfs_fsearch(source,NULL))
    {
        djy_printf("ϵͳ�Ҳ���ָ�����ļ�\r\n");
        return false; 
    }
    //����������ļ�һ�������أ�����������ΪЧ��һ��
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
            djy_printf("�Ƿ񸲸�%s�� <yes/no>", destination);
            djyfs_fclose(second_fp); 
            while(1)
            {
                djy_scanf(NULL,s);
                if(s[0] == 'y'||s[0] == 'Y')
                {
                	djy_putchar(s[0]);
                    djy_printf("\r\n");
                    djyfs_remove(destination);//Ϊ������׼��
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
            //��Ŀ¼����Ҫ���ӷ�б�ܣ��Ա����濽��·��ʹ��   
            str_end_increase_backslash(destination);
            fp = djyfs_fopen(source,"r");
            if(fp == NULL)
            {
                djyfs_fclose(second_fp);
                return false;
            }
            if(fp->attr.bits.archive)
            {//���source_file���ļ������ļ������뵽second_work_pathĩβ
            //ʹ����������������ṩ׼ȷ��·����
                str_end_wipe_backslash(source);
                __pick_filename_word(source,s);
                strcat(destination,s);      
             }
                djyfs_fclose(second_fp);
                djyfs_fclose(fp);
        }
    }
    else//���destination�����ڣ���ôȫ�������ļ�����
        str_end_wipe_backslash(source);//���Բ��üӷ�б�ܰ�?
    fp = djyfs_fopen(source,"r");
    if(fp == NULL)
        return 0;
    if(!fp->attr.bits.folder)//source��һ���ļ�
    {   
        djyfs_fclose(fp);
        copy_file_to_dest(source,destination);
        djy_printf("�Ѿ�������      1���ļ�\r\n");
    }
    else//source��һ��Ŀ¼
    {
        djyfs_fclose(fp);
        str_end_increase_backslash(source);
        copy_files_of_folder_to_dest(source,destination);
    }
    return true;    
}


//----������һ���ļ��ƶ�������һ��λ��--------------------------------------------------
//���ܣ�������һ���ļ��ƶ�������һ��λ��
//������DBX_name �ļ�����
//���أ�true �ɹ�
//-----------------------------------------------------------------------------
bool_t sh_move(char *param)
{
    char *next_param,source[255],destination[255];
    struct file_rsc *fp,*second_fp;
    char s[255];      
	if(param == NULL)
    {
    	djy_printf("�����﷨����ȷ!\r\n");
    	return false;
    }
    strcpy(source,sh_get_word(param,&next_param));

	if(NULL == next_param)
    {
    	djy_printf("djyfs��֧�ִ˲����������뿴help\r\n");
    	return false;
    }    
    strcpy(destination,sh_get_word(next_param,&next_param));
    if((!__check_fullname(source))||(!__check_fullname(destination)))
        return false; 
    if(!djyfs_fsearch(source,NULL))
    {
        djy_printf("ϵͳ�Ҳ���ָ�����ļ�\r\n");
        return false; 
    }
    //����������ļ�һ�������أ�����������ΪЧ��һ��
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
            djy_printf("�Ƿ񸲸�%s�� <yes/no>", destination);
            djyfs_fclose(second_fp); 
            while(1)
            {
                djy_scanf(NULL,s);
                if(s[0] == 'y')
                {
                	djy_putchar(s[0]);
                    djy_printf("\r\n");
                    djyfs_remove(destination);//Ϊ������׼��
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
            //��Ŀ¼����Ҫ���ӷ�б�ܣ��Ա����濽��·��ʹ��   
            str_end_increase_backslash(destination);
            fp = djyfs_fopen(source,"r");
            if(fp == NULL)
            {
                djyfs_fclose(second_fp);
                return false;
            }
            if(fp->attr.bits.archive)
            {//���source_file���ļ������ļ������뵽second_work_pathĩβ
            //ʹ����������������ṩ׼ȷ��·����
                str_end_wipe_backslash(source);
                __pick_filename_word(source,s);
                strcat(destination,s);      
             }
                djyfs_fclose(second_fp);
                djyfs_fclose(fp);
        }
    }
    else//���destination�����ڣ���ôȫ�������ļ�����
        str_end_wipe_backslash(source);
    fp = djyfs_fopen(source,"r");
    if(fp == NULL)
        return 0;
    if(!fp->attr.bits.folder)//source��һ���ļ�
    {   
        djyfs_fclose(fp);
        move_file_to_dest(source,destination);
        djy_printf("�Ѿ��ƶ���      1���ļ�\r\n");
    }
    else//source��һ��Ŀ¼
    {
        djyfs_fclose(fp);
        str_end_increase_backslash(source);
        move_files_of_folder_to_dest(source,destination);
    }
    return true;    
}

//----�޸�ָ���ļ������ļ��е�����------------------------------------------------
//����: ��������ren���޸�ָ�����ļ������ļ���
//����: param���������
//����: true=�ɹ�, 
//      false=ʧ�ܣ�
//-----------------------------------------------------------------------------
bool_t sh_ren(char *param)
{
	char *next_param;
	char *fullname;//ָ�����޸ĵ��ļ�
	char *filename;//�޸ĺ������

	if(param == NULL)
    {
    	djy_printf("�����﷨����ȷ!\r\n");
    	return false;
    }
    fullname = sh_get_word(param,&next_param);
    filename = sh_get_word(next_param,&next_param);
	if(!__check_fullname(fullname))
    	return false; 
	if(!djyfs_fsearch(fullname,NULL))
    {
    	djy_printf("ϵͳ�Ҳ���ָ�����ļ�\r\n");
     	return false; 
    }        
	djyfs_rename(fullname,filename);
	return true;

}    
//----����һ�����߶��Ŀ¼------------------------------------------------
//����: ��������md������һ�����߶��Ŀ¼
//����: param���������
//����: true=�ɹ�, 
//      false=ʧ�ܣ�
//-----------------------------------------------------------------------------
bool_t sh_md(char *param)
{
	char *next_param;
	char *del_param;
    //����255�ַ�����Ϊfs_mkdir�Ĳ�����Ҫ���������ַ���
    //��������ƣ����ڴ�й©����ɲ��ɿ�
	char str[cn_shell_cmd_limit+1];
    
	del_param = sh_get_word(param,&next_param);
	if(del_param == NULL)
    {
    	djy_printf("�����﷨����ȷ!\r\n");
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


//----ɾ��һ�����߶���ļ�������ļ�-------------------------------------------
//����: ��ָ����һ�����߶���ļ���ɾ������ֻ��ɾ��Ŀ¼
//����: rd_param�������ַ�
//����: true=�ɹ�, 
//      false=ʧ�ܣ�
//-----------------------------------------------------------------------------
bool_t sh_rd(char *param)
{
	char *next_param = param;
	char *del_param;

	if(param == NULL)
    {
    	djy_printf("�����﷨����ȷ!\r\n");
    	return false;
    }
    
    
	while(1)
    {
        del_param = sh_get_word(next_param,&next_param);
        if(del_param == NULL)
            break;
        if(__check_wildcard(del_param))     //�������ͨ���ɾ���ļ���
        {
            djy_printf("�����﷨����ȷ!\r\n");
        }
        else
            fs_remove_folder(del_param);   
    }
    
	return true;
}

//----ɾ��һ�����߶���ļ�-----------------------------------------------------
//����: ɾ��һ�����߶���ļ�
//����: param�������ַ�
//����: true=�ɹ�, 
//      false=ʧ�ܣ�
//-----------------------------------------------------------------------------
bool_t sh_del(char *param)
{
	char *next_param;
	char *del_param;

    //��������Ϊ���ַ�
	if(param == NULL)
    {
    	djy_printf("�����﷨����ȷ!\r\n");
    	return false;
    }
    next_param = param;
	while(1)
    {
        del_param = strsep(&next_param," ");
        if(del_param == NULL)
            break;
        if(del_param[0] == ' ')     //���������ո�
            break;
        if( ! __judge_backslash_is_data(del_param))     //·���������ļ���
        {
            djy_printf("%s �ļ�������ȷ!\r\n",del_param);
            break;
        }
        if(__check_wildcard_path(del_param))     //·�����ֲ������ͨ���
        {
            djy_printf("%s �ļ�������ȷ!\r\n",del_param);
        }
        else if(__check_wildcard_name(del_param))   //�ļ�����ͨ���
        {
            del_wildcard_files(del_param);
        }
        else
        {
            if(__judge_item_attr(del_param) == cn_item_is_file) //��ɾ��Ŀ¼
            {
                if(djyfs_remove(del_param) == 0)
                    djy_printf("��ɾ�� %s \r\n",del_param);
                else
                    djy_printf("ɾ�� %s ����\r\n",del_param);
            }
        }
    }

	return true;
}

//----��ʾ��ǰĿ¼�����ƻ�ı䵱ǰĿ¼-----------------------------------------
//����: ��ʾ��ǰĿ¼�����ƻ�ı䵱ǰĿ¼
//����: chdir_param�������ַ�
//����: true=�ɹ�, 
//      false=ʧ�ܣ�
//-----------------------------------------------------------------------------
bool_t sh_cd(char *chdir_param)
{        
	bool_t result;
	struct file_rsc *fp;
	char work_path[cn_shell_cmd_limit+1];
    
    //ִ��cd/chdir[](���ַ�) ��ʾ��ǰĿ¼����
	if(chdir_param == NULL)
    {
    	print_work_path();
    	djy_printf("\r\n");
    	return true;
    }
    //�����û�����Ŀ¼��ʱ�������뷴б��
    //��"cd folder\"���"cd folder"
    //ִ��cd/chdir[\] ��������Ŀ¼
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
    //ִ��cd/chdir[..] ��������һ��Ŀ¼
	else if(chdir_param[0]=='.' && chdir_param[1]=='.')//ִ�� "cd .."
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
        //ִ�� cd/chdir[�ļ���]·�� ��ʾ��ǰĿ¼�����ƻ�ı䵱ǰĿ¼
    	if(result == true)
        {
            //��Ŀ¼���ܴ�            
        	if(__judge_item_attr(chdir_param) == cn_item_is_folder)
            {
            	fp = pg_work_path;
            	pg_work_path = djyfs_fopen(chdir_param,"r");
            	djyfs_fclose(fp);
            	return true;
            }
        	else if(!__judge_backslash_is_data(chdir_param))
            {//��C:\,��judge_is_folder���޷��ɹ��ж�
            	fp = pg_work_path;
            	pg_work_path = djyfs_fopen(chdir_param,"r");
            	djyfs_fclose(fp);
            	return true;    
            }
        	else
            {
                djy_printf("ϵͳ�Ҳ���ָ����·��\r\n");
                return false;
            }
        }
    	else
            	djy_printf("ϵͳ�Ҳ���ָ����·��\r\n");
    }
 	return true;
}

//-------��ʾָ��Ŀ¼�µ��ļ�����Ŀ¼�б�--------------------------------------
//����: ��ʾָ��Ŀ¼�µ��ļ�����Ŀ¼�б�
//����: param�������ַ�
//����: true=�ɹ�, 
//      false=ʧ�ܣ�
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
        if(dir_param[0] == ' ')     //���������ո�
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
        djy_printf("�ߴ�̫��\r\n");
        return true;
    }
    word = sh_get_word(next_param,&next_param);
    if(word == NULL)
    {
        djy_printf("�ļ���������Ϊ��");
        return true;
    }
    
    if(DFFSD_create_DBX(chip,blocks,word) == true)
    {
        djy_printf("�����ļ���ɹ�");
    }
    else
    {
        djy_printf("�����ļ���ʧ��");
    }
    djy_printf("\r\n");
#endif
    return true;
}

bool_t sh_format(char *param)
{
    if(param == NULL)
    {
        djy_printf("�ļ���������Ϊ��");
        return true;
    }
    
    if(djyfs_format(1,0,param) == 0)
    {
        djy_printf("��ʽ���ɹ�");
    }
    else
    {
        djy_printf("��ʽ��ʧ��");
    }
    djy_printf("\r\n");
    return true;
}
#endif //#if ((cfg_djyfs == 1) && (cfg_run_mode != cn_mode_tiny))

