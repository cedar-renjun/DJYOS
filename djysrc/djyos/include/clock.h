//----------------------------------------------------
//Copyright (C), 2004-2011,  �����߲���ϵͳ�з��Ŷ�
//��Ȩ���� (C), 2004-2011,   �����߲���ϵͳ�з��Ŷ�
//����ģ��:ʱ��ģ��
//����:  ������
//�汾��V1.0.0
//�ļ�����: Ϊϵͳ�ṩʱ��
//����˵��:
//�޶���ʷ:
// 1. ����: 2011-10-28
//   ����:  ������
//   �°汾��: V1.0.0
//   �޸�˵��: ԭʼ�汾
//------------------------------------------------------

#ifndef __clock_h__
#define __clock_h__

#ifdef __cplusplus
extern "C" {
#endif

#define cn_ck_error_code_year      (-1)
#define cn_ck_error_code_month     (-2)
#define cn_ck_error_code_day       (-3)
#define cn_ck_error_code_hour      (-4)
#define cn_ck_error_code_minute    (-5)
#define cn_ck_error_code_second    (-6)

struct djy_tm 
{
    s32 tm_sec;     // ��Cȡֵ����Ϊ[0,59] 
    s32 tm_min;     // �� - ȡֵ����Ϊ[0,59] 
    s32 tm_hour;    // ʱ - ȡֵ����Ϊ[0,23] 
    s32 tm_mday;    // һ�����е����� - ȡֵ����Ϊ[1,31] 
    s32 tm_mon;     // �·ݣ���һ�¿�ʼ��0����һ�£� - ȡֵ����Ϊ[0,11] 
    s32 tm_year;    // ��ݣ���ֵ��1900��ʼ 
    s32 tm_wday;    // ���ڨCȡֵ����Ϊ[0,6]������0���������죬1��������һ��
                    // �Դ����� 
    s32 tm_yday;    // ��ÿ���1��1�տ�ʼ�������Cȡֵ����Ϊ[0,365]������0����
                    //1��1�գ�1����1��2�գ��Դ����� 
    s32 tm_isdst;   // ����ʱ��ʶ����ʵ������ʱ��ʱ��tm_isdstΪ������ʵ��
                    //����ʱ�Ľ���tm_isdstΪ0�����˽����ʱ��tm_isdst()Ϊ����
};

extern char tm_wdays[][8];

ptu32_t module_init_datatime(ptu32_t para);
s64 djy_time(s64 *ret);
struct djy_tm localtime(s64 time);

s64 __date_to_binary(struct djy_tm *dt);
extern int time_set_datetime_str(char *buf);
void time_set_datatime_tm(struct djy_tm *tm);
struct djy_tm gmtime(s64 time);
void time_connect_rtc(bool_t (*set_rtc_hard)(struct djy_tm *DateTime));

#ifdef __cplusplus
}
#endif

#endif

