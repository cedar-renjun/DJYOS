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

//----��ֵת�����ַ���---------------------------------------------------------
//����: ����ֵdת����Ϊָ�����������ַ���
//����: d��Ҫת������ֵ
//      buf�����ת���õ��ַ����Ļ�����
//      scale��ת���Ľ��ƣ���Ϊ-10,10,-16,16
//			scaleΪ��ֵ��ʱ���ʾdΪ�з�����������Ϊ�޷�������
//����: 1
//������d=5628, scale=10 �������Ϊ buf="5628"
//-----------------------------------------------------------------------------
char * djy_itoa(int d, char *buf, int scale)
{
	unsigned char str_inv[16];	// ���������
	unsigned int ud;	// d���޷��ű�ʾ
	char *str = buf;
	u8 i, j, k;

	i = 0;
	// ������ȥ��
	if (scale < 0)
	{
		scale = -scale;
		if (d < 0)
		{
			ud = (unsigned int)(-d);
			str_inv[i++] = '-';
		}
		else
		{
			ud = (unsigned int)d;
		}
	}
	else
	{
		ud = (unsigned int)d;
	}

	// 16������ת��
	if (scale == 16)
	{
		do	// ���4λ�Ƿ���ֵ
		{
			str_inv[i] = ud & 0x0F;	// ��ĩ4λ��ֵ
			ud >>= 4;	// ����4λ

			if ((str_inv[i] >= 0) && (str_inv[i] <= 9))
			{
				str_inv[i] += '0';
			}
			else if ((str_inv[i] >= 0x0A) && (str_inv[i] <= 0x0F))
			{
				str_inv[i] += ('a'-0x0A);
			}

			i++;
		} while (ud);
		i--;	// �˸�����λ��

		// �������
		if (str_inv[0] == '-')
		{
			*str++ = '-';
			j = 1;
		}
		else
		{
			j = 0;
		}

		k = i-j;	// ����λ��
		k += 1;		// ѭ����ȡ����
		for (; k; k--)
		{
			*str++ = str_inv[i--];
		}
		*str = '\0';	// ������
	}
	else if (scale == 10)
	{
		// ����ת��
		do
		{
			str_inv[i++] = (ud % 10) + '0';
			ud /= 10;
		} while (ud);
		i--;	// �˸�����λ��

		// �������
		if (str_inv[0] == '-')
		{
			*str++ = '-';
			j = 1;
		}
		else
		{
			j = 0;
		}

		k = i-j;	// ����λ��
		k += 1;		// ѭ����ȡ����
		for (; k; k--)
		{
			*str++ = str_inv[i--];
		}
		*str = '\0';	// ������
	}
    return buf;
}

//----���ַ���ת���ɳ�����---------------------------------------------------------
//����: ���ַ���ת���ɳ����ͣ�δ׼����ctype����������ʹ��atol��isdigit֮��ĺ���
//����:
//����:
//-----------------------------------------------------------------------------
u32 djy_atol(char *s)
{
    ufast_t offset;
    u32 result = 0;
    if((s[0] == '0') && ((s[1] == 'x') || (s[1] == 'X')))   //16����
    {
        offset = 2;
        while(s[offset] == '0')
            offset++;
        while(s[offset] != '\0')
        {
            if((s[offset]>='0')&&(s[offset]<= '9'))         //0~9��Χ
                result = (result<<4) + s[offset] - 0x30;
            else if((s[offset]>='A')&&(s[offset]<= 'F'))    //A~F��Χ
                result = (result<<4) + s[offset] - 0x37;
            else if((s[offset]>='a')&&(s[offset]<= 'f'))    //a~f��Χ
                result = (result<<4) + s[offset] - 0x57;
            else                       //�Ƿ��ַ�
                return result;
            offset++;
        }
    }else       //10����
    {
        offset = 0;
        while(s[offset] == '0')
            offset++;
        while(s[offset] != '\0')
        {
            if((s[offset]>='0')&&(s[offset]<= '9'))         //0~9��Χ
                result = result*10 + s[offset] - 0x30;
            else                       //�Ƿ��ַ�
                return result;
            offset++;
        }
    }
    return result;
}

//----��ȡ�ַ���--------------------------------------------------------------
//����: ����������unix���ҵ� stringp �ַ�����һ������delim���е���һ���ַ�������
//      ��Ϊ\0 ���ţ�Ȼ�� stringp ����ָ�� \0 ���ŵ���һ��λ�ã�����ԭָ��
//����: stringp��ԭ��ָ��
//      delim���������ַ�ָ��
//����: ԭ��ָ��
//-----------------------------------------------------------------------------
#if 1		//���port����gcc���������߱���ѡ��û�д�gnu��չ����Ҫ������δ���
char * strsep(char **stringp, char *delim)
{
	char *s;
	const char *spanp;
	int c, sc;
	char *tok;

	if ((s = *stringp)== NULL)
	{
		return (NULL);
	}

	for (tok = s;;)
	{
		c = *s++;
		spanp = delim;
		do
		{
			if ((sc =*spanp++) == c)
			{
				if (c == 0)
				    s = NULL;
				else
				    s[-1] = 0;
				*stringp = s;

				return (tok);
			}
		} while (sc != 0);
	}

	return *stringp;
}
#endif
#if (cfg_shell == 1)

#include "cpu_peri.h"
#include "char_term.h"
#include "shell_fs.h"

#include <string.h>
#include <stdarg.h>

static s32 s32g_char_term_id;
djy_handle_t pg_char_term_lhdl;
struct semaphore_LCB *semp_char_term_hdl;

void term_scan(void)
{
    struct char_termineral_msg msg;
    while(1)
    {
        do
        {
            //���ն��豸
            msg.num = dev_read_left(pg_char_term_lhdl,0,
                                    (ptu32_t)msg.input_char,cn_char_buf_limit);
            if(msg.num != 0)
            {
                msg.time = djy_get_time_tick();
                stdin_input_msg(s32g_char_term_id,(u8*)&msg,sizeof(msg));
            }
        } while (msg.num ==16); //ֱ�����е����ݶ�������
        //ִ�б�����¼��������������ڱ�ͬ�����¼����;��Ǳ��¼����¼����ͣ�
        //����ͬ���������ǣ��ٴη����������¼���
        //���� ��1����ʾֻҪ����һ���¼��Ϳ�����
        //����cn_timeout_forever��ʾ���һֱ�������������õȴ�
        //�����¼����͵���ͬ�����μ��������߲���ϵͳ��Ƕ��ʽϵͳ��ơ��ĵ�5.3��
        djy_wait_evtt_pop(djy_my_evtt_id(),1,cn_timeout_forever);
    }
}

//----�ն�ģ���ʼ������-------------------------------------------------------
//����: ��ʼ������ģ��
//����: para,�������ʹ�õ��豸������紮��
//����: �ն��豸��id(ע:�ⲻ�Ƿ��豸),�����򷵻�-1
//-----------------------------------------------------------------------------
ptu32_t module_init_char_term(ptu32_t para)
{
    u16 term_scan_evtt;

    if(para == 0)
        return -1;
    s32g_char_term_id = stdin_install_device("char_term", enum_char_termineral,NULL);
    if(s32g_char_term_id == -1)
        goto exit_install_device;
    semp_char_term_hdl = semp_create(1, 1, NULL);
    if (semp_char_term_hdl == NULL)
    	goto exit_create_semp;
    term_scan_evtt = djy_evtt_regist(enum_correlative,          //�������¼�
                                cn_prio_real,       //Ĭ�����ȼ�
                                0,                  //�̱߳���������������Ч
                                0,                  //�߳����ޣ���������Ч
                                1,                  //�������г�������
                                term_scan,          //��ں���
                                1024,               //ջ�ߴ�
                                "term_scan"         //�¼�������
                                );
    if(term_scan_evtt == cn_invalid_evtt_id)
    {
        goto exit_install_evtt;
    }
    if(djy_event_pop(term_scan_evtt,NULL,0,&para,sizeof(ptu32_t),0,0)
                        == (uint16_t)cn_invalid_event_id)
    {
        goto exit_pop_event;
    }
    pg_char_term_lhdl = (djy_handle_t)para;

    djy_printf("\r\n��ӭʹ�ö����߲���ϵͳ\r\n");
    djy_printf("  �汾����ʱ�䣺%s %s\r\n", __DATE__, __TIME__);
    djy_printf(">");
    return s32g_char_term_id;

exit_pop_event:
    djy_evtt_unregist(term_scan_evtt);
exit_install_evtt:
    stdin_uninstall_device("char_term");
exit_create_semp:
	semp_delete(semp_char_term_hdl);
exit_install_device:
    return -1;
}

s32 djy_getchar(void)
{
    struct input_device_msg *input_msg;
    struct char_termineral_msg *char_msg;
    static u32 offset=0;
	s32 ch;
    input_msg = (struct input_device_msg *)djy_get_event_para(NULL);
    if(input_msg == NULL)
    {
        while (1)
        {
            djy_wait_evtt_pop(djy_my_evtt_id(),1,20*mS);
            input_msg = (struct input_device_msg *)djy_get_event_para(NULL);
            if (input_msg)
            {
				break;
            }
//			djy_echo_para(0);
        }
    }
    char_msg = &(input_msg->input_data.char_termineral);
    ch = char_msg->input_char[offset++]; 
    if(offset == char_msg->num)
    {
        offset = 0;
    	djy_echo_para(0);
    }
    return ch;
}

s32 djy_gets(char buf[])
{
//    char ch;
//
//    buf[0] = '\0';
//	do
//	{
//		ch = (char)djy_getchar();
//		if ((ch != '\r') && (ch != '\n'))
//		{
//			buf++ = ch;
//		}
//		else
//		{
//			buf++ = '\0';
//			return 1;
//		}
//	} while (1);
//
	return 0;
}

//----��ʽ����---------------------------------------------------------
//����: ����ʽ�����ַ�������C�⺯�����ƣ���������������ࡣ
//����: const char *fmt, ...
//����:
//ע�⣺��ǰ�����ڻ�ȡ�ַ�������������ȫδʵ�֣�
//-----------------------------------------------------------------------------
s32 djy_scanf(const char *format, char *buf)
{
    char ch;
    u8 chars = 0;

    semp_pend(semp_char_term_hdl, cn_timeout_forever);
    stdin_set_focus("char_term",djy_my_evtt_id());
    while (1)
    {
    	ch = (char)djy_getchar();
    	if ((ch == '\r') || (ch == '\n'))
    	{
            buf[chars] = '\0';
            djy_printf("\r\n");
            break;
    	}
    	else
    	{
    		if (ch == 8)	// Backspace
    		{
                if(chars > 0)
                {
                    chars --;
                    djy_printf("\b \b");
                }
    		}
    		else
    		{
    			if(chars < 255)  //������32�ֽڣ������ı�����
				{
    			    djy_putchar(ch);
					buf[chars] = ch;
					chars++;
				}
    		}

    	}
    }
    semp_post(semp_char_term_hdl);
    return chars;
}

void djy_putchar(char c)
{
    dev_write_left(pg_char_term_lhdl,(ptu32_t)&c,0,1);
}

//----��ʽ��ӡ-----------------------------------------------------------------
//����: ����ʽ��ӡ�ַ�������C�⺯�����ƣ���������������ࡣ
//����: const char *fmt, ...
//����: 1
//-----------------------------------------------------------------------------
int djy_printf(const char *fmt, ...)
{
	const char *s;
	int d;
	u32 len, decbits = 0;
	char buf[16];
	char fillch = ' ';
	va_list argp;	// ��������
	va_start(argp, fmt);

	while (*fmt)
	{
		decbits = 0;
		fillch = ' ';
		if (*fmt != '%')
		{
			djy_putchar(*fmt++);
			continue ;
		}

		fmt++;
		// ����ַ�
		if ((*fmt == ' ') || (*fmt == '0'))
		{
			fillch = *fmt;
			fmt++;
		}
		// ָ����ӡ����
		while (('0' < *fmt) && (*fmt <= '9' ))
		{
			decbits = decbits*10 + (*fmt - '0');
			fmt++;
		}

		switch (*fmt)
		{
		case 's':
			s = va_arg(argp, const char *);
			len = strlen(s);
			if (len<decbits)
			{
				for (; len<decbits; decbits--)
				{
					djy_putchar(' ');
				}
			}
			for (; *s; s++)
			{
				djy_putchar(*s);
			}
			break;
		case 'u':	// �޷���10������
			d = va_arg(argp, int);
			djy_itoa(d, buf, 10);
			len = strlen(buf);
			if (len<decbits)
			{
				for (; len<decbits; decbits--)
				{
					djy_putchar(fillch);
				}
			}
			for (s=buf; *s; s++)
			{
				djy_putchar(*s);
			}
			break;
		case 'd':	// 10������
			d = va_arg(argp, int);
			djy_itoa(d, buf, -10);
			len = strlen(buf);
			if (len<decbits)
			{
				for (; len<decbits; decbits--)
				{
					djy_putchar(fillch);
				}
			}
			for (s=buf; *s; s++)
			{
				djy_putchar(*s);
			}
			break;
		case 'x':	// 16������
			d = va_arg(argp, int);
			djy_itoa(d, buf, 16);
			len = strlen(buf);
			if (len<decbits)
			{
				for (; len<decbits; decbits--)
				{
					djy_putchar('0');
				}
			}
			for (s=buf; *s; s++)
			{
				djy_putchar(*s);
			}
			break;
			//�����������
		default :
			djy_putchar(*fmt);
			break;
		}
		fmt++;
	}
	va_end(argp);

	return 1;	// ԭ��Ҫ����
}

#else       //for (cfg_shell == 1)

//����Щ�����ÿ�
s32 djy_getchar(void){return 0;}
s32 djy_gets(char buf[]){return 0;}
s32 djy_scanf(const char *format, char *buf){return 0;}
void djy_putchar(char c){}
int djy_printf(const char *fmt, ...){return 0;}
#endif      //for (cfg_shell == 1)

