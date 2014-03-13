//----------------------------------------------------
//Copyright (C), 2004-2011,  罗侍田.
//版权所有 (C), 2004-2011,   罗侍田.
//所属模块:时钟模块
//作者:  王建忠
//版本：V1.0.0
//文件描述: 为系统提供时钟日历
//其他说明:
//修订历史:
// 1. 日期: 2012-5-1
//   作者:  罗侍田
//   新版本号: V1.1.0
//   修改说明: 大幅度修改
// 1. 日期: 2011-10-28
//   作者:  王建忠
//   新版本号: V1.0.0
//   修改说明: 原始版本
//------------------------------------------------------
#include "os_inc.h"

#if (cfg_time_module == 1)

#include "cpu_peri.h"
#include <stdio.h>
#include <string.h>

#define cn_time_zone                (+8)
#define cn_time_zone_offset         (cn_time_zone*3600)

s64 s64g_nowtime;
u32 temp_time;
u32 DaysToMonth[13] = {0,31,59,90,120,151,181,212,243,273,304,334,365};
u32 month_days[]={31,28,31,30,31,30,31,31,30,31,30,31,};
char tm_wdays[][8] = {"星期天", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六"};
static bool_t (*ck_set_rtc_hard)(struct djy_tm *DateTime) = NULL;

//----连接硬件rtc--------------------------------------------------------------
//功能: 连接硬件rtc操作函数到time系统
//参数: set_rtc_hard，把时间写入硬件rtc的函数
//返回: 无
//-----------------------------------------------------------------------------
void time_connect_rtc(bool_t (*set_rtc_hard)(struct djy_tm *DateTime))
{
    ck_set_rtc_hard = set_rtc_hard;
}

//----把格林威治时间转成日历时间----------------------------------------------
//功能: 把格林威治时间（年月日时分秒）转换成日历时间(1970年以来的秒数),
//参数: dt，年月日时分秒形式的时间
//返回: 分解时间
//----------------------------------------------------------------------------
s64 __date_to_binary(struct djy_tm *dt)
{
    u32 iday;
    s64 val;

    iday = 365  * (dt->tm_year - 1970)+ DaysToMonth[dt->tm_mon-1]+ (dt->tm_mday - 1);
    iday += (dt->tm_year - 1969) >> 2;	// 不包括本年度闰（因为可能还没到2月份）

    if ((dt->tm_mon > 2) && ((dt->tm_year % 4) == 0))
	{
		iday++;
	}

    iday -= dt->tm_year/100 - 1970/100;	// 间隔有多少个100整的年份
    iday += dt->tm_year/400 - 1970/400;	// 间隔有多少个400整的年份

    val = dt->tm_sec + 60 * dt->tm_min + 3600 * (dt->tm_hour + 24 * iday);

    return val;
}

//----把日历时间转成格林威治时间----------------------------------------------
//功能: 把日历时间(1970年以来的秒数)转换成年月日时分秒,
//参数: time,1970年来的秒数
//返回: 分解时间
//----------------------------------------------------------------------------
struct djy_tm gmtime(s64 time)
{
	return localtime(time - cn_time_zone_offset);
}

//----把日历时间转成本地时间---------------------------------------------------
//功能: 把日历时间(1970年以来的秒数)转换成年月日时分秒,
//参数: time,1970年来的秒数
//返回: 分解时间
//-----------------------------------------------------------------------------
struct djy_tm localtime(s64 time)
{
	struct djy_tm datetime;
	u32 second, minute, hour;
	u32 day, month, year;

	u32 days;
	u32 years;
	u32 leap_years;
	u32 dayth;	// 本年的第x天（1月1日0时0分0秒即为第1天了）
	u32 day_of_week;
	u32 tmp_month_days;

	second = time % 60;
	minute = time/60 %60;
	hour = time/3600 %24;
	days = (u32)(time/86400);

	years = days / 365;
	leap_years = (years + 1) >> 2; // 不含本年度的闰
	leap_years -= (years+1970)/100 - 1970/100;
	leap_years += (years+1970)/400 - 1970/400;
	dayth = days % 365 - leap_years + 1;	// 本年度第x天（如1月1日0时为第1天）

	year = 1970 + years;

	month_days[1] = 28;
	if (year%4 == 0)	// 如果本年是闰年，那么先在2月份添加一天
	{
		if ((year%100 == 0) && (year%400 != 0))
		{
			// 百年不闰，四百年闰
		}
		else
		{
			month_days[1] = 29;
		}
	}

	month = 1;
	tmp_month_days = month_days[month-1];
	while (dayth > tmp_month_days)
	{
		dayth -= tmp_month_days;
		tmp_month_days = month_days[month];
		month++;
	}
	day = dayth;

	day_of_week = (days + 4) % 7;

	datetime.tm_yday = day;		// days since January 1 -[0,365]
	datetime.tm_sec  = second;        /* seconds after the minute - [0,59]  */
	datetime.tm_min  = minute;        /* minutes after the hour - [0,59]    */
	datetime.tm_hour = hour;          /* hours since midnight - [0,23]      */
	datetime.tm_wday = day_of_week;   /* days since Sunday - [0,6]          */
	datetime.tm_mday = day;           /* day of the month - [1,31]          */
	datetime.tm_mon  = month;         /* months since January - [0,11]      */
	datetime.tm_year = year;          /* years 1970-                   */

	return datetime;
}

//----更新系统时间-------------------------------------------------------------
//功能: 用格式为"2011/10/28,22:37:50"的字符串表示的时间设置日历时间，手工矫正时
//      间后，可调用本函数设置系统日历时间
//参数: buf，输入时间值
//返回: 1=成功，其他值:对应的错误代码
//-----------------------------------------------------------------------------
s32 time_set_datetime_str(char *buf)
{
    s64 nowtime;
    struct djy_tm ptDateTime;
    char *sepstr;
    char sepch[] = "/";
    u32 res;
    atom_low_t atom;

    sepch[0] = '/';
    sepstr = strsep(&buf, sepch);
    res = djy_atol(sepstr);
    if ((1900>res) || (res>2100))
    {
    	return cn_ck_error_code_year;
    }
    ptDateTime.tm_year = res;

    sepstr = strsep(&buf, sepch);
    res = djy_atol(sepstr);
    if ((1>res) || (res>12))
    {
    	return cn_ck_error_code_month;
    }
    ptDateTime.tm_mon = res;

    sepch[0] = ',';
    sepstr = strsep(&buf, sepch);
    res = djy_atol(sepstr);
    if ((1>res) || (res>31))
    {
    	return cn_ck_error_code_day;
    }
    if (res > month_days[ptDateTime.tm_mon-1])
    {
    	return cn_ck_error_code_day;
    }
    if (ptDateTime.tm_mon == 2)
    {
    	if (res > 29)
    	{
    		return cn_ck_error_code_day;
    	}

    	if (ptDateTime.tm_year%4 == 0)
    	{
    		if (ptDateTime.tm_year%100 == 0)
    		{
    			if (ptDateTime.tm_year%400)
    			{
    				if (res > 28)
    					return cn_ck_error_code_day;
    			}
    		}
    	}
    	else
    	{
			if (res > 28)
				return cn_ck_error_code_day;
    	}
    }
    ptDateTime.tm_mday = res;

    sepch[0] = ':';
    sepstr = strsep(&buf, sepch);
    res = djy_atol(sepstr);
    if (res>23)
    {
    	return cn_ck_error_code_hour;
    }
    ptDateTime.tm_hour = res;

    sepstr = strsep(&buf, sepch);
    res = djy_atol(sepstr);
    if (res>59)
    {
    	return cn_ck_error_code_minute;
    }
    ptDateTime.tm_min = res;

    sepstr = strsep(&buf, sepch);
    res = djy_atol(sepstr);
    if (res>59)
    {
    	return cn_ck_error_code_second;
    }
    ptDateTime.tm_sec = res;

    nowtime = __date_to_binary(&ptDateTime);
    
#if (64 > cn_cpu_bits)
    atom = int_low_atom_start();
    s64g_nowtime = nowtime;
    int_low_atom_end(atom);
#else
    s64g_nowtime = nowtime;
#endif

    if(ck_set_rtc_hard != NULL)
        ck_set_rtc_hard(&ptDateTime);

    return 1;
}

//----更新系统时间-------------------------------------------------------------
//功能: 用分解时间更新系统时间，有rtc硬件的系统中，由硬件驱动调用本函数。
//参数: tm,当前时间，按年月日时分秒分解
//返回: 无
//-----------------------------------------------------------------------------
void time_set_datatime_tm(struct djy_tm *tm)
{
    atom_low_t atom;
    s64 nowtime;
    
    nowtime = __date_to_binary(tm);
#if (64 > cn_cpu_bits)
    atom = int_low_atom_start();
    s64g_nowtime = nowtime;
    int_low_atom_end(atom);
#else
    s64g_nowtime = nowtime;
#endif
}

//----输入系统时间-------------------------------------------------------------
//功能: 用分解时间更新系统时间，有rtc硬件的系统中，由硬件驱动调用本函数。
//参数: tm,当前时间，按年月日时分秒分解
//返回: 无
//-----------------------------------------------------------------------------
void time_inc_second(void)
{
    atom_low_t atom;
#if (64 > cn_cpu_bits)
    atom = int_low_atom_start();
    s64g_nowtime++;
    int_low_atom_end(atom);
#else
    s64g_nowtime++;
#endif
}

//----把分解时间转成字符串-----------------------------------------------------
//功能: 把一个分解时间转成字符串，格式"2011/10/28,22:37:50"
//参数: time,1970年来的秒数
//返回: 分解时间
//----------------------------------------------------------------------------
void asctime(struct djy_tm *tm, char buf[])
{
	djy_itoa(tm->tm_year, &buf[0], 10);
    buf[4] = '/';
    djy_itoa(tm->tm_mon, &buf[5], 10);
    buf[7] = '/';
    djy_itoa(tm->tm_mday, &buf[8], 10);
    buf[10] = ',';
    djy_itoa(tm->tm_hour, &buf[11], 10);
    buf[13] = ':';
    djy_itoa(tm->tm_min, &buf[14], 10);
    buf[16] = ':';
    djy_itoa(tm->tm_sec, &buf[17], 10);
    buf[19] = '\0';

	return ;
}

void time_run(void)
{
    while(1)
    {
        djy_event_delay(1000*mS);
        time_inc_second();
    }
}

//----time模块初始化-----------------------------------------------------------
//功能: 初始化日期时间模块
//参数: para，不使用
//返回: 不使用
//-----------------------------------------------------------------------------
ptu32_t module_init_datatime(ptu32_t para)
{
#if(cfg_time_src == cfg_time_src_tick)
    u16 evtt_time;

    evtt_time = djy_evtt_regist(enum_correlative,cn_prio_RRS,0,0,1,
                                time_run,200,"clock");
    if(evtt_time != cn_invalid_evtt_id)
    {
        djy_event_pop(evtt_time,NULL,0,NULL,0,0,0);
    }
    else
    {
    	return false;
    }
#endif
    return true;
}

//----取系统时间---------------------------------------------------------------
//功能: 取从1970年1月1日0:0:0到现在的时间差，秒数。
//参数: time,非空则返回系统时间。
//返回: 系统时间
//-----------------------------------------------------------------------------
s64 djy_time(s64 *ret)
{
    atom_low_t atom;
    s64 nowtime;

#if (64 > cn_cpu_bits)
    atom = int_low_atom_start();
    nowtime = s64g_nowtime;
    int_low_atom_end(atom);
#else
    nowtime = s64g_nowtime;
#endif

    if(ret != NULL)
        *ret = nowtime;
    return nowtime;
}

#endif

