//----------------------------------------------------
//Copyright (C), 2004-2009,  lst.
//版权所有 (C), 2004-2009,   lst.
//所属模块: 调度器
//作者：lst
//版本：V1.0.1
//文件描述: 调度器中与CPU直接相关的代码。
//其他说明:
//修订历史:
//2. 日期: 2009-04-24
//   作者: lst
//   新版本号: V1.0.1
//   修改说明: 删除了一些为dlsp版本准备的东西
//1. 日期: 2009-01-04
//   作者: lst
//   新版本号: V1.0.0
//   修改说明: 原始版本
//------------------------------------------------------
#include "os_inc.h"

#include <windows.h>
#include <tchar.h>
#include <process.h>
#pragma comment(lib,"Winmm.lib")

u8 *sys_heap_top_cnt;
u8 *sys_heap_bottom_cnt; 

extern ufast_t ufg_int_number;

extern u32  u32g_os_ticks;             //操作系统运行ticks数
volatile u32    u32g_delay_10uS = 40;
static u32 u32g_ns_of_u32for; //for(i=j;i>0;i--);语句，i和j都是u32型，每循环纳秒数
static u32 u32g_ns_of_u16for; //for(i=j;i>0;i--);语句，i和j都是u16型，每循环纳秒数
static u32 u32g_ns_of_u8for;  //for(i=j;i>0;i--);语句，i和j都是u8型，每循环纳秒数
s64 s64g_freq;
extern struct  event_ECB  *pg_event_ready;      //就绪队列头
extern struct  event_ECB  *pg_event_running;    //当前正在执行的事件
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

    sys_heap_bottom_cnt = (u8*)malloc(0x1000000);   //16M内存
    sys_heap_top_cnt = sys_heap_bottom_cnt + 0x1000000;
//	a = CreateDirectory(_TEXT("djyfs"),NULL);
//	a = CreateDirectory(_TEXT("djyfs\\sys"),NULL);
    int_init();
    int_isr_connect(cn_int_line_switch_context,switch_context);
    int_setto_asyn_signal(cn_int_line_switch_context); //tick中断被设为异步信号
    int_restore_asyn_line(cn_int_line_switch_context);
    printf("VC 编译器版本：%d\n\r >",_MSC_VER);
    start_sys(); 
//    Sleep(INFINITE);                 
// 主消息循环:
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



//----创建线程-----------------------------------------------------------------
//功能：为事件类型创建伪虚拟机，初始化上下文环境，安装执行函数，构成完整线程
//参数：evtt_id，待创建的线程所服务的事件类型id
//返回：新创建的线程的虚拟机指针
//注: 移植敏感函数
//-----------------------------------------------------------------------------
struct  thread_vm *__create_thread(struct  event_type *evtt)
{
    struct  thread_vm  *result;
    //看实际分配了多少内存，djyos内存分配使用块相联策略，如果分配的内存量大于
    //申请量，可以保证其实际尺寸是对齐的。之所以注释掉，是因为当len大于申请量时，
    //对齐只是实际结果，而不是内存管理的规定动作，如果不注释掉，就要求内存管理
    //模块必须提供对齐的结果，对模块独立性是不利的。
	result=(struct  thread_vm  *)malloc(sizeof(struct  thread_vm)); //申请内存，移植敏感
	memset(result,0,sizeof(struct thread_vm));
	result->stack_top = CreateThread( NULL, 0, win_engine, evtt->thread_routine,
                                        CREATE_SUSPENDED, NULL );
//    SetThreadAffinityMask( result->stack_top, 1 );

	result->stack = 0;
	result->next = NULL;
    result->stack_size = 0; //保存栈深度
    result->host_vm = NULL;
    //复位虚拟机并重置线程
    __asm_reset_thread(evtt->thread_routine,result);
    return result;
}

//----重置线程-----------------------------------------------------------------
//功能:  初始化线程的栈，并挂上线程执行函数，新创建线程时将会调用本函数
//参数:  thread_routine，被重置的线程函数
//		vm，线程虚拟机指针
//返回:  初始化结束后的当前栈指针
//函数原型:void * __asm_reset_thread(void (*thread_routine)(void),
//                                   struct  thread_vm  *vm);
//-----------------------------------------------------------------------------
void * __asm_reset_thread(void (*thread_routine)(void),struct  thread_vm  *vm)
{
	return NULL;
}

//----复位老线程，切换到新线程-------------------------------------------------
//功能:  把old_vm的上下文重新初始化到新创建的状态，然后切换到新线程的
//		上下文中继续执行。
//当一个在常驻内存的虚拟机中处理的事件完成后，不能删除该虚拟机，必须复位
//		该虚拟机，然后切换到其他就绪线程，这时候就需要调用本函数。因此本函数在
//		被复位的线程上下文里面执行。
//参数:  thread_routine，被重置的线程函数
//		new_vm，目标线程
//		old_vm，被复位线程
//返回:  无
//函数原型:void __asm_reset_switch(void (*thread_routine)(void),
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
    old_vm->stack_size = 0; //保存栈深度
    old_vm->host_vm = NULL;
    
	ResumeThread((HANDLE )new_vm->stack_top);
}   //自然返回后，由windows负责线程回收工作


void __asm_start_thread(struct  thread_vm  *new_vm)
{
    ResumeThread(win32_int_engine);
    __asm_turnto_context(new_vm);
}

//----切入上下文---------------------------------------------------------------
//功能:  不保存原上下文，直接切入新的上下文执行
//参数:  new_sp，新上下文的栈指针
//返回:  无
//函数原型: void __asm_turnto_context(struct  thread_vm  *new_vm);
//说明:  当事件完成,就没有必要保存旧事件的上下文,直接切换到新事件即可.
//-----------------------------------------------------------------------------
void __asm_turnto_context(struct  thread_vm  *new_vm)
{
	int_half_enable_asyn_signal();
	ResumeThread((HANDLE )new_vm->stack_top);
    int_contact_asyn_signal();
}

//----上下文切换---------------------------------------------------------------
//功能:  保存当前线程的上下文，切换到新线程的上下文中继续执行。
//参数:  new_sp，新上下文的栈指针
//参数:  old_sp，旧上下文的栈指针的指针，即&vm->stack。无需提供旧上下文栈指针，
//               sp寄存器的当前值就是
//返回:  无
//函数原型: void __asm_switch_context(struct  thread_vm *new_vm,struct  thread_vm *old_vm);
//-----------------------------------------------------------------------------
void __asm_switch_context(struct  thread_vm *new_vm,struct  thread_vm *old_vm)
{
	old_id = (HANDLE )old_vm->stack_top;
	new_id = (HANDLE )new_vm->stack_top;
    ufg_int_number = cn_int_line_switch_context;
    SetEvent(win32_int_event);

}

//----中断中的上下文切换-------------------------------------------------------
//功能:  保存被中断线程的上下文，切换到新线程的上下文中继续执行。本函数虽然在中
//		断服务函数(非用户用int_isr_connect函数连接的中断服务函数)中，但在ARM
//		中，却运行在svc态
//参数:  new_sp，切换目标虚拟机
//参数:  old_sp，被中断线程虚拟机
//返回:  无
//函数原型: void __asm_switch_context_int(struct thread_vm *new_vm,struct thread_vm *old_vm);
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

//----设置指令延时常数---------------------------------------------------------
//功能: 设置指令延时常数,使y_delay_10us函数的延时常数=10uS，不管用何种编译器和
//      编译优化选项
//参数：无
//返回: 无
//备注: 本函数移植敏感
//-----------------------------------------------------------------------------
void __djy_set_delay(void)
{
//x86 用QueryPerformanceFrequency函数和QueryPerformanceCounter函数测量10000个for
//循环时间，然后计算。这两函数的使用范例：
#if 0
在进行定时之前，先调用QueryPerformanceFrequency()函数获得机器内部定时器的时钟频率， 
然后在需要严格定时的事件发生之前和发生之后分别调用QueryPerformanceCounter()函数，
利用两次获得的计数之差及时钟频率，计算出事件经 历的精确时间。下列代码实现1ms的
精确定时：
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

//----初始化tick---------------------------------------------------------------
//功能: 初始化定时器,并连接tick中断函数,启动定时器.
//参数: 无
//返回: 无
//备注: 本函数是移植敏感函数.
//-----------------------------------------------------------------------------
void __djy_init_tick(void)
{
    LARGE_INTEGER litmp;

    int_isr_connect(cn_int_line_timer_event,__djy_isr_tick);
    int_setto_asyn_signal(cn_int_line_timer_event); //tick中断被设为异步信号
    int_restore_asyn_line(cn_int_line_timer_event);
    timeSetEvent(cfg_tick_us/mS,cfg_tick_us/mS,&TimerCallBack,0,TIME_PERIODIC);
    QueryPerformanceFrequency(&litmp);
    s64g_freq = litmp.QuadPart;
}


//----读取当前ticks-------------------------------------------------------------
//功能：读取操作系统时钟
//      u32g_os_ticks 为32位无符号变量，ARM是32位机，可以直接读取，非32位系统中
//      读取 u32g_os_ticks 需要超过1个周期,因此访问SysTimer时需要关中断。
//参数：无
//返回：当前时钟
//-----------------------------------------------------------------------------
u32 djy_get_time_tick(void)
{
    u32 time;
#if (32 > cn_cpu_bits)
    //若处理器字长不是32位,需要多个周期才能读取os_ticks,该过程不能被时钟中断打断.
    int_save_asyn_line(cn_int_line_timer3);
#endif

    time = u32g_os_ticks;

#if (32 > cn_cpu_bits)
    //若处理器字长不是32位,需要多个周期才能读取os_ticks,该过程不能被时钟中断打断.
    int_restore_asyn_line(cn_int_line_timer3);
#endif
    return time;
}

//----读取当前时间(uS)---------------------------------------------------------
//功能：读取操作系统时钟
//      u32g_os_ticks 为32位无符号变量，ARM是32位机，可以直接读取，非32位系统中
//      读取 u32g_os_ticks 需要超过1个周期,因此访问SysTimer时需要关中断。
//参数：无
//返回：当前时钟
//-----------------------------------------------------------------------------
u32 djy_get_time(void)
{
    u32 time;
#if (32 > cn_cpu_bits)
    //若处理器字长不是32位,需要多个周期才能读取os_ticks,该过程不能被时钟中断打断.
    int_save_asyn_line(cn_int_line_timer3);
#endif

    time = u32g_os_ticks*cfg_tick_us;

#if (32 > cn_cpu_bits)
    //若处理器字长不是32位,需要多个周期才能读取os_ticks,该过程不能被时钟中断打断.
    int_restore_asyn_line(cn_int_line_timer3);
#endif
    return time;
}

//----读取精密时间-----------------------------------------------------------
//功能：读取精密时钟,单位uS，从系统启动开始计时，达4294.967296秒回绕到0.
//参数：无
//返回：时间值
//备注: 本函数是移植敏感函数.
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

//----10微秒级延时-------------------------------------------------------------
//功能：利用循环实现的微秒分辨率延时，调用__djy_set_delay函数后才能使用本函数，
//      否则在不同优化级别和不同编译器下,延时数不同.
//参数：time，延时时间，单位为10微秒,最多655毫秒。
//返回：无
//注意：不建议使用此函数做太长延时，长延时请使用函数 djy_timer_sync,
//-----------------------------------------------------------------------------
void djy_delay_10us(volatile u16 time)
{
    volatile u32 i;
    for(; time > 0; time--)
        for(i = u32g_delay_10uS; i >0 ; i--);
}

//----取for循环延时常数--------------------------------------------------------
//功能: 当代码使用for(i=j;i>0;i--);循环来实现短时间延时时，可通过本函数获取单个
//      循环的执行时间。根据循环变量i的类型，使用:
//          i = djy_get_for_time(sizeof(i));
//      返回使用i做循环变量是for循环的执行时间。用下列代码实现延时x纳秒
//          i= x/i;
//          for( ; i > 0; i--);
//      注意:有些编译器会把空for循环当作无用代码删掉，故循环变量须volatile修饰。
//参数: var_len，变量长度(字节数)
//返回: 根据var_len值，返回u32g_ns_of_u32/16/8for中的一个。
u32 djy_get_for_time(ufast_t var_len)
{
    if(var_len == 1)
        return u32g_ns_of_u8for;
    else if(var_len == 2)
        return u32g_ns_of_u16for;
    else 
        return u32g_ns_of_u32for;
}


