#include "os_inc.h"
#include "cpu_peri.h"

void djy_main(void);

void __djy_main(void)
{
    djy_main();
}

//----�����ʼ��2-----------------------------------------------------------
//���ܣ���ѡ�����ʼ����������3��:
//      1��sys_module_init����sys_init.c�У��μ��ú���ע��
//      2��prj_module_init���������ʼ����ģ�飬��Ҫ���ø����幤����صĴ��룬��
//         �����ģ�飬���˵���module_init_keyboard�����⣬��Ҫ���ø�Ӳ����ص�
//         module_init_keyboard_hard������
//      ǰ������ʼ��ʱ�����������䷽ʽ��û�г�ʼ��������������õ���̬���䣬ʹ��
//      ����׼��̬���䣬����׼��̬�����˵�����μ�mems.c�ļ���
//      3��run_module_init���μ��ú���ע�͡�
//��������
//���أ���
//-----------------------------------------------------------------------------
void prj_module_init(void)
{
    uint16_t evtt_main;
    
#if cfg_keyboard == 1
    module_init_keyboard(0);
#endif

#if cfg_djyfs == 1
    module_init_djyfs(0);
#if cfg_djyfs_flash == 1
    module_init_DFFSD();
#endif
#endif

#if(cfg_uart0_used == 1)
    module_init_uart0(0);
#endif
#if(cfg_uart1_used == 1)
    module_init_uart1(0);
#endif
#if(cfg_uart2_used == 1)
    module_init_uart2(0);
#endif
#if(cfg_uart3_used == 1)
    module_init_uart3(0);
#endif
    evtt_main = djy_evtt_regist(enum_correlative,cn_prio_RRS,0,0,2, 
                                __djy_main,cn_main_stack,"main function");
    //�¼���������������Ϊ0�������shell�������������ɼ�shell�����в���
    djy_event_pop(evtt_main,NULL,0,NULL,0,0,0);
    return ;
}

//----�����ʼ��3-----------------------------------------------------------
//���ܣ���ѡ�����ʼ����������3��:
//      1��sys_module_init����sys_init.c�У��μ��ú���ע��
//      2��prj_module_init���μ��ú���ע�͡�
//      3��run_module_init����������djy_main������ʼ�����ã���Ҫ����ϵͳ���¼�
//          ���ȿ�ʼ�󣬻�����Ҫ�������ڴ�����ʼ������ܳ�ʼ����ģ�顣
//��������
//���أ���
//-----------------------------------------------------------------------------
void run_module_init(void)
{

}

