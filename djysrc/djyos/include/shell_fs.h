#ifndef __shell_fs_h__
#define __shell_fs_h__

#ifdef __cplusplus
extern "C" {
#endif

#if ((cfg_djyfs == 1) && (cfg_run_mode != cn_mode_tiny))

#define cn_item_is_folder   0
#define cn_item_is_file     1
#define cn_item_no_exist    2

bool_t __check_wildcard(char *str);
bool_t __wildcard_match( char* src, char* wildcard);
bool_t __judge_backslash_is_data(char *path);
bool_t __cut_path_end_item(char *path);
bool_t __pick_path_end_item(char *path,char *name);
bool_t __path_is_absolute_path(char *path);
char *get_folder_wildcard_str(char *wildcard_param,char *get_merge_str);
bool_t del_wildcard_files(char *wildcard_param);
bool_t deltree_wildcard_files(char *wildcard_param);
bool_t str_end_increase_backslash(char *str);
bool_t str_end_wipe_backslash(char *str);
bool_t dir_item_son(struct file_rsc *parent_fp);
bool_t dir_wildcard_files(char *wildcard_param);
bool_t judge_is_folder(char *fullname);
bool_t del_items_of_folder_or_loop(char *work_path);
bool_t del_files_of_folder(char *work_path);
bool_t fs_mkdir(char *md_param);
bool_t fs_remove_tree(char *tree_param);
bool_t fs_remove_folder(char *rd_param);
bool_t cd_parent(char *next_param);
bool_t cd_dbx(char *dbx);
bool_t sh_chkdbx(char *DBX_name);
bool_t sh_copy(char *param);
bool_t sh_move(char *param);
bool_t sh_ren(char *param);
bool_t sh_md(char *param);
bool_t sh_deltree(char *param);
bool_t sh_rd(char *param);
bool_t sh_del(char *param);
bool_t sh_cd(char *chdir_param);
bool_t sh_dir(char *param);
bool_t write(char *param);
bool_t sh_create_dbx(char *param);
bool_t sh_format(char *param);

#endif


#ifdef __cplusplus
}
#endif

#endif //__shell_fs_h__
