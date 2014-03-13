//----------------------------------------------------
//Copyright (C), 2004-2011,  ������.
//��Ȩ���� (C), 2004-2011,   ������.
//����ģ��:ʱ��ģ��
//����:  ������
//�汾��V1.0.0
//�ļ�����: Ϊϵͳ�ṩʱ������
//����˵��:
//�޶���ʷ:
// 1. ����: 2012-5-1
//   ����:  ������
//   �°汾��: V1.1.0
//   �޸�˵��: ������޸�
// 1. ����: 2011-10-28
//   ����:  ������
//   �°汾��: V1.0.0
//   �޸�˵��: ԭʼ�汾
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
char tm_wdays[][8] = {"������", "����һ", "���ڶ�", "������", "������", "������", "������"};
static bool_t (*ck_set_rtc_hard)(struct djy_tm *DateTime) = NULL;

//----����Ӳ��rtc--------------------------------------------------------------
//����: ����Ӳ��rtc����������timeϵͳ
//����: set_rtc_hard����ʱ��д��Ӳ��rtc�ĺ���
//����: ��
//-----------------------------------------------------------------------------
void time_connect_rtc(bool_t (*set_rtc_hard)(struct djy_tm *DateTime))
{
    ck_set_rtc_hard = set_rtc_hard;
}

//----�Ѹ�������ʱ��ת������ʱ��----------------------------------------------
//����: �Ѹ�������ʱ�䣨������ʱ���룩ת��������ʱ��(1970������������),
//����: dt��������ʱ������ʽ��ʱ��
//����: �ֽ�ʱ��
//----------------------------------------------------------------------------
s64 __date_to_binary(struct djy_tm *dt)
{
    u32 iday;
    s64 val;

    iday = 365  * (dt->tm_year - 1970)+ DaysToMonth[dt->tm_mon-1]+ (dt->tm_mday - 1);
    iday += (dt->tm_year - 1969) >> 2;	// ���������������Ϊ���ܻ�û��2�·ݣ�

    if ((dt->tm_mon > 2) && ((dt->tm_year % 4) == 0))
	{
		iday++;
	}

    iday -= dt->tm_year/100 - 1970/100;	// ����ж��ٸ�100�������
    iday += dt->tm_year/400 - 1970/400;	// ����ж��ٸ�400�������

    val = dt->tm_sec + 60 * dt->tm_min + 3600 * (dt->tm_hour + 24 * iday);

    return val;
}

//----������ʱ��ת�ɸ�������ʱ��----------------------------------------------
//����: ������ʱ��(1970������������)ת����������ʱ����,
//����: time,1970����������
//����: �ֽ�ʱ��
//----------------------------------------------------------------------------
struct djy_tm gmtime(s64 time)
{
	return localtime(time - cn_time_zone_offset);
}

//----������ʱ��ת�ɱ���ʱ��---------------------------------------------------
//����: ������ʱ��(1970������������)ת����������ʱ����,
//����: time,1970����������
//����: �ֽ�ʱ��
//-----------------------------------------------------------------------------
struct djy_tm localtime(s64 time)
{
	struct djy_tm datetime;
	u32 second, minute, hour;
	u32 day, month, year;

	u32 days;
	u32 years;
	u32 leap_years;
	u32 dayth;	// ����ĵ�x�죨1��1��0ʱ0��0�뼴Ϊ��1���ˣ�
	u32 day_of_week;
	u32 tmp_month_days;

	second = time % 60;
	minute = time/60 %60;
	hour = time/3600 %24;
	days = (u32)(time/86400);

	years = days / 365;
	leap_years = (years + 1) >> 2; // ��������ȵ���
	leap_years -= (years+1970)/100 - 1970/100;
	leap_years += (years+1970)/400 - 1970/400;
	dayth = days % 365 - leap_years + 1;	// ����ȵ�x�죨��1��1��0ʱΪ��1�죩

	year = 1970 + years;

	month_days[1] = 28;
	if (year%4 == 0)	// ������������꣬��ô����2�·����һ��
	{
		if ((year%100 == 0) && (year%400 != 0))
		{
			// ���겻���İ�����
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

//----����ϵͳʱ��-------------------------------------------------------------
//����: �ø�ʽΪ"2011/10/28,22:37:50"���ַ�����ʾ��ʱ����������ʱ�䣬�ֹ�����ʱ
//      ��󣬿ɵ��ñ���������ϵͳ����ʱ��
//����: buf������ʱ��ֵ
//����: 1=�ɹ�������ֵ:��Ӧ�Ĵ������
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

//----����ϵͳʱ��-------------------------------------------------------------
//����: �÷ֽ�ʱ�����ϵͳʱ�䣬��rtcӲ����ϵͳ�У���Ӳ���������ñ�������
//����: tm,��ǰʱ�䣬��������ʱ����ֽ�
//����: ��
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

//----����ϵͳʱ��-------------------------------------------------------------
//����: �÷ֽ�ʱ�����ϵͳʱ�䣬��rtcӲ����ϵͳ�У���Ӳ���������ñ�������
//����: tm,��ǰʱ�䣬��������ʱ����ֽ�
//����: ��
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

//----�ѷֽ�ʱ��ת���ַ���-----------------------------------------------------
//����: ��һ���ֽ�ʱ��ת���ַ�������ʽ"2011/10/28,22:37:50"
//����: time,1970����������
//����: �ֽ�ʱ��
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

//----timeģ���ʼ��-----------------------------------------------------------
//����: ��ʼ������ʱ��ģ��
//����: para����ʹ��
//����: ��ʹ��
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

//----ȡϵͳʱ��---------------------------------------------------------------
//����: ȡ��1970��1��1��0:0:0�����ڵ�ʱ��������
//����: time,�ǿ��򷵻�ϵͳʱ�䡣
//����: ϵͳʱ��
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

