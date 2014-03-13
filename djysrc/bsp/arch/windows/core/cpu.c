//----------------------------------------------------
//Copyright (C), 2004-2009,  lst.
//��Ȩ���� (C), 2004-2009,   lst.
//����ģ��: ������
//���ߣ�lst
//�汾��V1.0.1
//�ļ�����: ����������CPUֱ����صĴ��롣
//����˵��:
//�޶���ʷ:
//2. ����: 2009-04-24
//   ����: lst
//   �°汾��: V1.0.1
//   �޸�˵��: ɾ����һЩΪdlsp�汾׼���Ķ���
//1. ����: 2009-01-04
//   ����: lst
//   �°汾��: V1.0.0
//   �޸�˵��: ԭʼ�汾
//------------------------------------------------------
#include "os_inc.h"

#include <windows.h>
#include <tchar.h>
#include <process.h>
#pragma comment(lib,"Winmm.lib")

u8 *sys_heap_top_cnt;
u8 *sys_heap_bottom_cnt; 

extern ufast_t ufg_int_number;

extern u32  u32g_os_ticks;             //����ϵͳ����ticks��
volatile u32    u32g_delay_10uS = 40;
static u32 u32g_ns_of_u32for; //for(i=j;i>0;i--);��䣬i��j����u32�ͣ�ÿѭ��������
static u32 u32g_ns_of_u16for; //for(i=j;i>0;i--);��䣬i��j����u16�ͣ�ÿѭ��������
static u32 u32g_ns_of_u8for;  //for(i=j;i>0;i--);��䣬i��j����u8�ͣ�ÿѭ��������
s64 s64g_freq;
extern struct  event_ECB  *pg_event_ready;      //��������ͷ
extern struct  event_ECB  *pg_event_running;    //��ǰ����ִ�е��¼�
u32 WINAPI win_engine( LPVOID lpParameter );

u32 WINAPI win32_switch( LPVOID lpParameter );

HINSTANCE hInstance = NULL;

extern HANDLE win32_int_event;
extern HANDLE win32_int_engine;
HANDLE old_id,new_id;

u32 switch_context(ufast_t line)
{
	SuspendThread(old_id);
	ResumeThread(new_id);
    int_contact_asyn_signal();
	return 0;
}

void main(int argc, char *argv[])
{ 
    MSG msg;
 	SetProcessAffinityMask(GetCurrentProcess(), 1);
    hInstance = GetModuleHandle(NULL);

    sys_heap_bottom_cnt = (u8*)malloc(0x1000000);   //16M�ڴ�
    sys_heap_top_cnt = sys_heap_bottom_cnt + 0x1000000;
//	a = CreateDirectory(_TEXT("djyfs"),NULL);
//	a = CreateDirectory(_TEXT("djyfs\\sys"),NULL);
    int_init();
    int_isr_connect(cn_int_line_switch_context,switch_context);
    int_setto_asyn_signal(cn_int_line_switch_context); //tick�жϱ���Ϊ�첽�ź�
    int_restore_asyn_line(cn_int_line_switch_context);
    printf("VC �������汾��%d\n\r >",_MSC_VER);
    start_sys(); 
//    Sleep(INFINITE);                 
// ����Ϣѭ��:
    while (GetMessage(&msg, NULL, 0, 0)) 
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return ;
}


ATOM RegisterWinClass(HINSTANCE hInstance,WNDPROC *func,TCHAR *title)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX); 
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = (WNDPROC)func;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = NULL;
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = title;
    wcex.hIconSm        = NULL;

    return RegisterClassEx(&wcex);

    
}



//----�����߳�-----------------------------------------------------------------
//���ܣ�Ϊ�¼����ʹ���α���������ʼ�������Ļ�������װִ�к��������������߳�
//������evtt_id�����������߳���������¼�����id
//���أ��´������̵߳������ָ��
//ע: ��ֲ���к���
//-----------------------------------------------------------------------------
struct  thread_vm *__create_thread(struct  event_type *evtt)
{
    struct  thread_vm  *result;
    //��ʵ�ʷ����˶����ڴ棬djyos�ڴ����ʹ�ÿ��������ԣ����������ڴ�������
    //�����������Ա�֤��ʵ�ʳߴ��Ƕ���ġ�֮����ע�͵�������Ϊ��len����������ʱ��
    //����ֻ��ʵ�ʽ�����������ڴ����Ĺ涨�����������ע�͵�����Ҫ���ڴ����
    //ģ������ṩ����Ľ������ģ��������ǲ����ġ�
	result=(struct  thread_vm  *)malloc(sizeof(struct  thread_vm)); //�����ڴ棬��ֲ����
	memset(result,0,sizeof(struct thread_vm));
	result->stack_top = CreateThread( NULL, 0, win_engine, evtt->thread_routine,
                                        CREATE_SUSPENDED, NULL );
//    SetThreadAffinityMask( result->stack_top, 1 );

	result->stack = 0;
	result->next = NULL;
    result->stack_size = 0; //����ջ���
    result->host_vm = NULL;
    //��λ������������߳�
    __asm_reset_thread(evtt->thread_routine,result);
    return result;
}

//----�����߳�-----------------------------------------------------------------
//����:  ��ʼ���̵߳�ջ���������߳�ִ�к������´����߳�ʱ������ñ�����
//����:  thread_routine�������õ��̺߳���
//		vm���߳������ָ��
//����:  ��ʼ��������ĵ�ǰջָ��
//����ԭ��:void * __asm_reset_thread(void (*thread_routine)(void),
//                                   struct  thread_vm  *vm);
//-----------------------------------------------------------------------------
void * __asm_reset_thread(void (*thread_routine)(void),struct  thread_vm  *vm)
{
	return NULL;
}

//----��λ���̣߳��л������߳�-------------------------------------------------
//����:  ��old_vm�����������³�ʼ�����´�����״̬��Ȼ���л������̵߳�
//		�������м���ִ�С�
//��һ���ڳ�פ�ڴ��������д�����¼���ɺ󣬲���ɾ��������������븴λ
//		���������Ȼ���л������������̣߳���ʱ�����Ҫ���ñ���������˱�������
//		����λ���߳�����������ִ�С�
//����:  thread_routine�������õ��̺߳���
//		new_vm��Ŀ���߳�
//		old_vm������λ�߳�
//����:  ��
//����ԭ��:void __asm_reset_switch(void (*thread_routine)(void),
//                           struct  thread_vm *new_vm,struct  thread_vm *old_vm);
//-----------------------------------------------------------------------------
void __asm_reset_switch(void (*thread_routine)(void),
                           struct  thread_vm *new_vm,struct  thread_vm *old_vm)
{
	int_half_enable_asyn_signal();
	old_vm->stack_top = CreateThread( NULL, 0, win_engine, thread_routine,
                                        CREATE_SUSPENDED, NULL );
	old_vm->stack = 0;
	old_vm->next = NULL;
    old_vm->stack_size = 0; //����ջ���
    old_vm->host_vm = NULL;
    
	ResumeThread((HANDLE )new_vm->stack_top);
}   //��Ȼ���غ���windows�����̻߳��չ���


void __asm_start_thread(struct  thread_vm  *new_vm)
{
    ResumeThread(win32_int_engine);
    __asm_turnto_context(new_vm);
}

//----����������---------------------------------------------------------------
//����:  ������ԭ�����ģ�ֱ�������µ�������ִ��
//����:  new_sp���������ĵ�ջָ��
//����:  ��
//����ԭ��: void __asm_turnto_context(struct  thread_vm  *new_vm);
//˵��:  ���¼����,��û�б�Ҫ������¼���������,ֱ���л������¼�����.
//-----------------------------------------------------------------------------
void __asm_turnto_context(struct  thread_vm  *new_vm)
{
	int_half_enable_asyn_signal();
	ResumeThread((HANDLE )new_vm->stack_top);
    int_contact_asyn_signal();
}

//----�������л�---------------------------------------------------------------
//����:  ���浱ǰ�̵߳������ģ��л������̵߳��������м���ִ�С�
//����:  new_sp���������ĵ�ջָ��
//����:  old_sp���������ĵ�ջָ���ָ�룬��&vm->stack�������ṩ��������ջָ�룬
//               sp�Ĵ����ĵ�ǰֵ����
//����:  ��
//����ԭ��: void __asm_switch_context(struct  thread_vm *new_vm,struct  thread_vm *old_vm);
//-----------------------------------------------------------------------------
void __asm_switch_context(struct  thread_vm *new_vm,struct  thread_vm *old_vm)
{
	old_id = (HANDLE )old_vm->stack_top;
	new_id = (HANDLE )new_vm->stack_top;
    ufg_int_number = cn_int_line_switch_context;
    SetEvent(win32_int_event);

}

//----�ж��е��������л�-------------------------------------------------------
//����:  ���汻�ж��̵߳������ģ��л������̵߳��������м���ִ�С���������Ȼ����
//		�Ϸ�����(���û���int_isr_connect�������ӵ��жϷ�����)�У�����ARM
//		�У�ȴ������svc̬
//����:  new_sp���л�Ŀ�������
//����:  old_sp�����ж��߳������
//����:  ��
//����ԭ��: void __asm_switch_context_int(struct thread_vm *new_vm,struct thread_vm *old_vm);
//-----------------------------------------------------------------------------
void __asm_switch_context_int(struct thread_vm *new_vm,struct thread_vm *old_vm)
{
	SuspendThread((HANDLE )old_vm->stack_top);
	ResumeThread((HANDLE )new_vm->stack_top);
}

u32 WINAPI win_engine( LPVOID lpParameter )
{
    void (*thread_routine)(void);

    thread_routine = (void (*)(void)) lpParameter;
    __djy_vm_engine(thread_routine);
    return 0;
}



static volatile ufast_t uf_delay_counter;
u32 set_delay_isr(ufast_t timer_int_line)
{
    uf_delay_counter++;
    return 0;
}

//----����ָ����ʱ����---------------------------------------------------------
//����: ����ָ����ʱ����,ʹy_delay_10us��������ʱ����=10uS�������ú��ֱ�������
//      �����Ż�ѡ��
//��������
//����: ��
//��ע: ��������ֲ����
//-----------------------------------------------------------------------------
void __djy_set_delay(void)
{
//x86 ��QueryPerformanceFrequency������QueryPerformanceCounter��������10000��for
//ѭ��ʱ�䣬Ȼ����㡣����������ʹ�÷�����
#if 0
�ڽ��ж�ʱ֮ǰ���ȵ���QueryPerformanceFrequency()������û����ڲ���ʱ����ʱ��Ƶ�ʣ� 
Ȼ������Ҫ�ϸ�ʱ���¼�����֮ǰ�ͷ���֮��ֱ����QueryPerformanceCounter()������
�������λ�õļ���֮�ʱ��Ƶ�ʣ�������¼��� ���ľ�ȷʱ�䡣���д���ʵ��1ms��
��ȷ��ʱ��
#endif

}

void CALLBACK TimerCallBack(UINT uTimerID, UINT uMsg, DWORD dwUser, 
                            DWORD dw1, DWORD dw2)
{
    int_tap_line(cn_int_line_timer_event);
}

u32 __djy_isr_tick(ufast_t line)
{
    djy_isr_tick();
    return 0;
}

//----��ʼ��tick---------------------------------------------------------------
//����: ��ʼ����ʱ��,������tick�жϺ���,������ʱ��.
//����: ��
//����: ��
//��ע: ����������ֲ���к���.
//-----------------------------------------------------------------------------
void __djy_init_tick(void)
{
    LARGE_INTEGER litmp;

    int_isr_connect(cn_int_line_timer_event,__djy_isr_tick);
    int_setto_asyn_signal(cn_int_line_timer_event); //tick�жϱ���Ϊ�첽�ź�
    int_restore_asyn_line(cn_int_line_timer_event);
    timeSetEvent(cfg_tick_us/mS,cfg_tick_us/mS,&TimerCallBack,0,TIME_PERIODIC);
    QueryPerformanceFrequency(&litmp);
    s64g_freq = litmp.QuadPart;
}


//----��ȡ��ǰticks-------------------------------------------------------------
//���ܣ���ȡ����ϵͳʱ��
//      u32g_os_ticks Ϊ32λ�޷��ű�����ARM��32λ��������ֱ�Ӷ�ȡ����32λϵͳ��
//      ��ȡ u32g_os_ticks ��Ҫ����1������,��˷���SysTimerʱ��Ҫ���жϡ�
//��������
//���أ���ǰʱ��
//-----------------------------------------------------------------------------
u32 djy_get_time_tick(void)
{
    u32 time;
#if (32 > cn_cpu_bits)
    //���������ֳ�����32λ,��Ҫ������ڲ��ܶ�ȡos_ticks,�ù��̲��ܱ�ʱ���жϴ��.
    int_save_asyn_line(cn_int_line_timer3);
#endif

    time = u32g_os_ticks;

#if (32 > cn_cpu_bits)
    //���������ֳ�����32λ,��Ҫ������ڲ��ܶ�ȡos_ticks,�ù��̲��ܱ�ʱ���жϴ��.
    int_restore_asyn_line(cn_int_line_timer3);
#endif
    return time;
}

//----��ȡ��ǰʱ��(uS)---------------------------------------------------------
//���ܣ���ȡ����ϵͳʱ��
//      u32g_os_ticks Ϊ32λ�޷��ű�����ARM��32λ��������ֱ�Ӷ�ȡ����32λϵͳ��
//      ��ȡ u32g_os_ticks ��Ҫ����1������,��˷���SysTimerʱ��Ҫ���жϡ�
//��������
//���أ���ǰʱ��
//-----------------------------------------------------------------------------
u32 djy_get_time(void)
{
    u32 time;
#if (32 > cn_cpu_bits)
    //���������ֳ�����32λ,��Ҫ������ڲ��ܶ�ȡos_ticks,�ù��̲��ܱ�ʱ���жϴ��.
    int_save_asyn_line(cn_int_line_timer3);
#endif

    time = u32g_os_ticks*cfg_tick_us;

#if (32 > cn_cpu_bits)
    //���������ֳ�����32λ,��Ҫ������ڲ��ܶ�ȡos_ticks,�ù��̲��ܱ�ʱ���жϴ��.
    int_restore_asyn_line(cn_int_line_timer3);
#endif
    return time;
}

//----��ȡ����ʱ��-----------------------------------------------------------
//���ܣ���ȡ����ʱ��,��λuS����ϵͳ������ʼ��ʱ����4294.967296����Ƶ�0.
//��������
//���أ�ʱ��ֵ
//��ע: ����������ֲ���к���.
//-----------------------------------------------------------------------------
u32 djy_get_fine_time(void)
{
    LARGE_INTEGER litmp;
    s64 cnt;
    u32 time;
    atom_low_t atom_low;
    atom_low = int_low_atom_start();

    QueryPerformanceCounter(&litmp);
    cnt = litmp.QuadPart;
    time = (u32)(cnt*1000000/s64g_freq);
    int_low_atom_end(atom_low);
    return time;// (((u32)cn_tick_us*1000/cn_fine_ns)-pg_timer_reg->TCNTO3) *cn_fine_ns;
}

//----10΢�뼶��ʱ-------------------------------------------------------------
//���ܣ�����ѭ��ʵ�ֵ�΢��ֱ�����ʱ������__djy_set_delay���������ʹ�ñ�������
//      �����ڲ�ͬ�Ż�����Ͳ�ͬ��������,��ʱ����ͬ.
//������time����ʱʱ�䣬��λΪ10΢��,���655���롣
//���أ���
//ע�⣺������ʹ�ô˺�����̫����ʱ������ʱ��ʹ�ú��� djy_timer_sync,
//-----------------------------------------------------------------------------
void djy_delay_10us(volatile u16 time)
{
    volatile u32 i;
    for(; time > 0; time--)
        for(i = u32g_delay_10uS; i >0 ; i--);
}

//----ȡforѭ����ʱ����--------------------------------------------------------
//����: ������ʹ��for(i=j;i>0;i--);ѭ����ʵ�ֶ�ʱ����ʱʱ����ͨ����������ȡ����
//      ѭ����ִ��ʱ�䡣����ѭ������i�����ͣ�ʹ��:
//          i = djy_get_for_time(sizeof(i));
//      ����ʹ��i��ѭ��������forѭ����ִ��ʱ�䡣�����д���ʵ����ʱx����
//          i= x/i;
//          for( ; i > 0; i--);
//      ע��:��Щ��������ѿ�forѭ���������ô���ɾ������ѭ��������volatile���Ρ�
//����: var_len����������(�ֽ���)
//����: ����var_lenֵ������u32g_ns_of_u32/16/8for�е�һ����
u32 djy_get_for_time(ufast_t var_len)
{
    if(var_len == 1)
        return u32g_ns_of_u8for;
    else if(var_len == 2)
        return u32g_ns_of_u16for;
    else 
        return u32g_ns_of_u32for;
}


