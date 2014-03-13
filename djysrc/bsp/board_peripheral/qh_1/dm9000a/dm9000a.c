//----------------------------------------------------
//Copyright (C), 2012-, Merlin
//��Ȩ���� (C)��2012-��Merlin
//����ģ�飺����ģ��
//���ߣ�Merlin
//�汾��V0.1.0
//�ļ�������dm9000�������ļ������ϲ��ṩ�����д���ĺ���
//����˵����
//�޶���ʷ��
//2. ���ڣ�
//   ���ߣ�
//   �°汾�ţ�
//   �޸�˵����
//1. ����: 2012-02-27
//   ���ߣ�Merlin
//   �°汾�ţ�V0.1.0
//   �޸�˵����ԭʼ�汾
//------------------------------------------------------

#include "os_inc.h"

#if (cfg_djyip == 1)
#include "stm32f10x.h"
#include "nicxx.h"

#define cn_int_line_enet (cn_int_line_EXTI9_5)	// dm9000a�ĵ�STM32������ж�

#define ADDRW8(r)	(*(volatile u8 *)DM9000A_INDEX = r)
#define DATAR8()	(*(volatile u8 *)DM9000A_DATA)
#define DATAW8(d)	(*(volatile u8 *)DM9000A_DATA = d)

#define ADDRW16(r)	(*(volatile u16 *)DM9000A_INDEX = r)
#define DATAR16()	(*(volatile u16 *)DM9000A_DATA)
#define DATAW16(d)	(*(volatile u16 *)DM9000A_DATA = d)

enum DM9000A_PHY_mode { DM9000A_10MHD = 0, DM9000A_100MHD = 1,
	DM9000A_10MFD = 4, DM9000A_100MFD = 5, DM9000A_AUTO = 8,
	DM9000A_1M_HPNA = 0x10
};
enum DM9000A_NIC_TYPE { FASTETHER_NIC = 0, HOMERUN_NIC = 1, LONGRUN_NIC = 2
};

struct _eth_hw_info {
	u8	io; // IO mode 0:16-bit; 1:32-bit; 2:8-bit
	u8	base; // BASE mode 1:10MHalfDuplex; 2:10MFullDuplex; 4:100MHD; 8:100MFD
};

struct _eth_hw_info ehi;	// ethernet hardware connect information

static int media_mode = DM9000A_AUTO;
// DM9000A���ź�������һ���߳�Ҫʹ��DM9000A�������ݻ��߽�������ʱ������Ӧȡ�ø��ź���
static struct semaphore_LCB* semp_dm9000;

static u8 ior(u8 reg)
{
	ADDRW8(reg);
	return (u8)DATAR8();
}

static void iow(u8 reg, u8 value)
{
	ADDRW8(reg);
	DATAW8(value);
}

//----дPHY�����֣�--------------------------------------------------------------
//���ܣ���PHY��д��16λ������
//������reg���Ĵ���ƫ�Ƶ�ַ
//      value��Ҫд���ֵ
//���أ���
//-----------------------------------------------------------------------------
static void phyw_h(u8 reg, u16 value)
{
	iow(DM9000A_EPAR, reg|0x40);// ʹ���ڲ�PHYʱbit[7:6]ҪΪ01b
	iow(DM9000A_EPDRL, value&0xFF);
	iow(DM9000A_EPDRH, (value&0xFF00)>>8);
	iow(DM9000A_EPCR, 0x0A);		// ѡ��PHY���ܣ�д����
	while (ior(DM9000A_EPCR) & 0x01)
	{
		djy_delay_10us(1);
	}
	djy_delay_10us(15);
	iow(DM9000A_EPCR, 0x00);		// �ɳ�������
}

//----��PHY�����֣�--------------------------------------------------------------
//���ܣ���PHY�ж�ȡ16λ������
//������reg���Ĵ���ƫ�Ƶ�ַ
//���أ����õļĴ���ֵ
//-----------------------------------------------------------------------------
static u16 phyr_h(u8 reg)
{
	u16 tmp;

	iow(DM9000A_EPAR, reg|0x40);	// ʹ���ڲ�PHYʱbit[7:6]ҪΪ01b
	iow(DM9000A_EPCR, 0x0C);		// ѡ��PHY���ܣ���ȡ����
	while (ior(DM9000A_EPCR) & 0x01)
	{
		djy_delay_10us(1);
	}
	djy_delay_10us(15);
	iow(DM9000A_EPCR, 0x00);		// �ɳ�������
	tmp = ior(DM9000A_EPDRL);
	tmp |= ior(DM9000A_EPDRH)<<8;

	return tmp;
}

//----��������ж�---------------------------------------------------------------
//���ܣ���������ж�
//��������
//���أ���
//-----------------------------------------------------------------------------
void __hw_enet_clear_int_tx(void)
{
	iow(DM9000A_ISR, 0x02);
}

//----��������ж�---------------------------------------------------------------
//���ܣ���������ж�
//��������
//���أ���
//-----------------------------------------------------------------------------
void __hw_enet_clear_int_rx(void)
{
	iow(DM9000A_ISR, 0x01);
}

//----����һ֡����---------------------------------------------------------------
//���ܣ�����һ�����ݰ�����̫����
//������upsec���ϲ����ݰ���һ������ṹ����ͷָ��
//���أ�����ʱΪ���͵��ֽ���������ʱΪ-1
//-----------------------------------------------------------------------------
int __hw_enet_start_transmit(struct enet_send_section* upsec)
{
	u16 dat;
	u32 i, len, times, totlen;
	struct enet_send_section* pt_ssec;

	// ����DM9000AӲ���������ź������ȴ�10S�����û�з���ȥ���򷵻�
	if (semp_pend(semp_dm9000, 10000*mS) == true)
	{
		int_save_asyn_line(cn_int_line_enet);	// �ر�DM9000A���ⲿ�ж�
		totlen = 0;
		pt_ssec = upsec;

		ADDRW8(DM9000A_MWCMD);
		if (ehi.io == 0)	// 16-bit
		{
			u8* pt_data;	// �����ֽ�Ϊ8λ�ģ��������ǿ��ת��
			while (pt_ssec != NULL)
			{
				pt_data = (u8*)pt_ssec->data;
				len = pt_ssec->count;
				totlen += len;
				if ((ptu32_t)pt_data & 0x01)	//�ж�ָ���Ƿ�˫�ֽڶ���
				{
					for (i=0; i<len; i+=2)
					{
						dat = pt_data[i] + (pt_data[i+1]<<8);
						DATAW16(dat);
					}
				}
				else
				{
					times = (len+1)/2;
					for (i=0; i<times; i++)
						DATAW16(((u16*)pt_data)[i]);
				}

				pt_ssec = pt_ssec->next_data_ssection;
			}
		}
		else if (ehi.io == 1) // 32-bit
		{
		}
		else if (ehi.io == 2) // 8-bit
		{
		}

		if (totlen > 0)
		{
			iow(DM9000A_TXPLH, (totlen>>8) & 0xff);
			iow(DM9000A_TXPLL, totlen & 0xff);
			iow(DM9000A_NSR, 0x2c);		// ���״̬�Ĵ���
			iow(DM9000A_TCR, ior(DM9000A_TCR) | 0x01);		//�������ݵ���̫����

			// �ȴ��������
			// NSR��TX1END��TX2END��������ɣ�
			// ISR��PTM��������ɣ�
			times = 100000;	// �൱�ȴ���3S
			while (!(ior(DM9000A_NSR) & 0x0C) || !(ior(DM9000A_ISR) & 0x02))
			{
				if (times == 0)
				{
					dm9000a_reset_to_new();
					break ;
				}
				times--;
				djy_delay_10us(1);
			}
		}

		int_restore_asyn_line(cn_int_line_enet);	// ��DM9000A���ⲿ�ж�
		semp_post(semp_dm9000);
	}

	if (times == 0)
		return -1;

    return totlen;
}

//----ʹ�ܷ����ж�---------------------------------------------------------------
//���ܣ�ʹ�ܷ����ж�
//��������
//���أ���
//-----------------------------------------------------------------------------
void __hw_enet_en_int_tx(void)
{
	u8 flag;

	flag = ior(DM9000A_IMR);
	iow(DM9000A_IMR, flag | 0x02);
}

//----��ֹ�����ж�---------------------------------------------------------------
//���ܣ���ֹ�����ж�
//��������
//���أ���
//-----------------------------------------------------------------------------
void __hw_enet_disen_int_tx(void)
{
	u8 flag;

	flag = ior(DM9000A_IMR);
	iow(DM9000A_IMR, flag & ~0x02);
}

//----ʹ�ܽ����ж�---------------------------------------------------------------
//���ܣ�ʹ�ܽ����ж�
//��������
//���أ���
//-----------------------------------------------------------------------------
void __hw_enet_en_int_rx(void)
{
	u8 flag;

	flag = ior(DM9000A_IMR);
	iow(DM9000A_IMR, flag | 0x01);
}

//----��ֹ�����ж�---------------------------------------------------------------
//���ܣ���ֹ�����ж�
//��������
//���أ���
//-----------------------------------------------------------------------------
void __hw_enet_disen_int_rx(void)
{
	u8 flag;

	flag = ior(DM9000A_IMR);
	iow(DM9000A_IMR, flag & ~0x01);
}

//----����PHY����ģʽ------------------------------------------------------------
//���ܣ�����PHY����ģʽ
//��������
//���أ���
//-----------------------------------------------------------------------------
static void set_phy_mode(void)
{
	u16 phy_reg4 = 0x01e1, phy_reg0 = 0x3100;

	// reset PHY
	phyw_h(0, 0x8000);
	do {
		djy_delay_10us(5);
	} while (phyr_h(0) & 0x8000);

	switch (media_mode) {
	case DM9000A_10MHD:
		phy_reg4 = 0x21;
		phy_reg0 = 0x0000;
		break;
	case DM9000A_10MFD:
		phy_reg4 = 0x41;
		phy_reg0 = 0x1100;
		break;
	case DM9000A_100MHD:
		phy_reg4 = 0x81;
		phy_reg0 = 0x2000;
		break;
	case DM9000A_100MFD:
		phy_reg4 = 0x101;
		phy_reg0 = 0x3100;
		break;
	}
	phyw_h(4, phy_reg4);	// Set PHY media mode
	phyw_h(0, phy_reg0);	// Tmp
}

//----̽��оƬ��ID�Ƿ�ΪDM9000A--------------------------------------------------
//���ܣ�̽��оƬ��ID�Ƿ�ΪDM9000A
//��������
//���أ���ȡ��ȷʱΪ1������ʱΪ0
//-----------------------------------------------------------------------------
static u8 dm9000a_probe(void)
{
	u32 id;

	// ��ȡ����ID�Ͳ�ƷID��
	id = ior(DM9000A_PIDL);
	id |= ior(DM9000A_PIDH)<<8;
	id |= ior(DM9000A_VIDL)<<16;
	id |= ior(DM9000A_VIDH)<<24;
	if (id != DM9000A_VID_PID) // ������IDӦ��Ϊ0x0A469000
	{
		return 0;
	}
	return 1;
}

//----����MAC��ַ---------------------------------------------------------------
//���ܣ�����MAC��ַ
//������mac����̫���ĵ�ַ���飨6���ֽڣ�
//���أ���
//-----------------------------------------------------------------------------
void dm9000a_set_macaddr(u8 mac[])
{
	for (int i=0; i<6; i++)
		iow(DM9000A_PAR0+i, mac[i]);
}

//----���öಥ��ַ---------------------------------------------------------------
//���ܣ����öಥ��ַ
//������mulicast���ಥ��ַ���飨8���ֽڣ�
//���أ���
//-----------------------------------------------------------------------------
void dm9000a_set_multicastaddr(void) //u8 mulicast[])
{
	// ���öಥ��ַ
	for (int i=0; i<8; i++)
		iow(DM9000A_MAR0+i, 0xFF);
}

//----DM9000A��RST����δ����-----------------------------------------------------
//���ܣ�Ӳ����RST���Ų������ã���δ��RST״̬�¡�
//��������
//���أ���
//-----------------------------------------------------------------------------
void dm9000a_rstpin_deassert(void)
{
	GPIO_SetBits(GPIOG, GPIO_Pin_7);
}

//----DM9000A��RST����������-----------------------------------------------------
//���ܣ�Ӳ����RST�������������У�����ǰ�������ڸ�λ�����мĴ�����ΪĬ��ֵ��
//��������
//���أ���
//-----------------------------------------------------------------------------
void dm9000a_rstpin_assert(void)
{
	GPIO_ResetBits(GPIOG, GPIO_Pin_7);
}

//----DM9000A��λ---------------------------------------------------------------
//���ܣ������λDM9000A��ĳЩ�Ĵ�����ֵ���������λ��Ӱ�졣
//��������
//���أ���
//-----------------------------------------------------------------------------
void dm9000a_reset(void)
{
	iow(DM9000A_NCR, 0x01);	// RESET
	do {
		djy_delay_10us(3);	// ��ʱ30us��Ӧ���ֲ���˵����20us
	} while (ior(DM9000A_NCR) & 0x01);
	iow(DM9000A_NCR, 0x00);
}

//----��λDM9000A��ĳһ�ض���ԭʼ״̬---------------------------------------------
//���ܣ���DM9000A�ص�����һ��״̬�������ж�δ��֮�⣬�����й���DM9000A�����г�ʼ������
//      ������ɵĵز���DM9000AоƬ�ڴ��ڲ�RAM�ж�����ʱ����������ı�־λ����1Ҳ����0
//      ʱ������ñ���������������Ҫ���RAM�е����ݼ�ʹ��дָ�븴λ��
//��������
//���أ���
//-----------------------------------------------------------------------------
void dm9000a_reset_to_new(void)
{
	__hw_enet_disen_int_tx();
	__hw_enet_disen_int_rx();
	ior(DM9000A_ISR);	// ��������ж�״̬
	iow(DM9000A_IMR, 0x80);	// ����ַ��λ��0xC000��д��ַ��λ��0x0000

//	__hw_enet_en_int_tx();	// �򿪷�������ж�
	__hw_enet_en_int_rx();	// �򿪽����ж�
	iow(DM9000A_TCR, 0);
	iow(DM9000A_RCR, 0x3d);	// ʹ�ܽ��գ��㲥��Runt������ʹ�û���ģʽ��
}

//----DM9000A��ʼ��-------------------------------------------------------------
//���ܣ���ʼ��DM9000A
//��������
//���أ���
//-----------------------------------------------------------------------------
u8 nicxx_init(void)
{
	u16 i;

	dm9000a_reset();	// �����λ

	if (!dm9000a_probe())	// ̽�鵱ǰ������оƬ�Ƿ�ΪDM9000A������ID���жԱȣ�
		return 0;
	iow(DM9000A_GPR, 0x00);	// PHYPD=0ʱʹ��PHY��Ĭ��Ϊ1��ʾ��ʹ���ڲ�PHY
	djy_delay_10us(2*mS);

	iow(DM9000A_NCR, 0x03);	// ѡ���ڲ�PHY
	djy_delay_10us(2);
	iow(DM9000A_NCR, 0x03);	// ѡ���ڲ�PHY
	djy_delay_10us(2);

	ior(DM9000A_NSR);	// �������״̬����ȡ���������

	dm9000a_set_macaddr(MyMAC);	// ����MAC��ַ
	dm9000a_set_multicastaddr();	// ���öಥ��ַ

	set_phy_mode();	// �Զ�Э��

	while (!(phyr_h(1) & 0x20)) 	// �Զ�Э����ɱ�־λ
	{
		djy_event_delay(5*mS);	// 50mS
	}

	// ����IO��Baseģʽ
	ehi.io = (ior(DM9000A_ISR)>>6) & 0x3;
	ehi.base = (phyr_h(17)>>12) & 0xF;

	semp_dm9000 = semp_create(1, 1, NULL);
	if (semp_dm9000 == NULL)
	{
		return -1;
	}

	dm9000a_reset_to_new();
	// TODO DM9000A����IP��UDP��TCP�ļ�����Զ����㹦��
	//...

	i = ior(DM9000A_NSR);		// xxx del ��Ҫ����0x40�ű�ʾ���ӳɹ�

	return 1;
}

u8 nicxx_init_debug(void)
{
	u16 i;

	dm9000a_reset();	// �����λ

	if (!dm9000a_probe())	// ̽�鵱ǰ������оƬ�Ƿ�ΪDM9000A������ID���жԱȣ�
		return 0;
	iow(DM9000A_GPR, 0x00);	// PHYPD=0ʱʹ��PHY��Ĭ��Ϊ1��ʾ��ʹ���ڲ�PHY
	djy_delay_10us(2*mS);

	iow(DM9000A_NCR, 0x03);	// ѡ���ڲ�PHY
	djy_delay_10us(2);
	iow(DM9000A_NCR, 0x03);	// ѡ���ڲ�PHY
	djy_delay_10us(2);

	ior(DM9000A_NSR);	// �������״̬����ȡ���������

	dm9000a_set_macaddr(MyMAC);	// ����MAC��ַ
	dm9000a_set_multicastaddr();	// ���öಥ��ַ

	set_phy_mode();	// �Զ�Э��

	while (!(phyr_h(1) & 0x20)) 	// �Զ�Э����ɱ�־λ
	{
		djy_event_delay(5*mS);	// 50mS
	}

	// ����IO��Baseģʽ
	ehi.io = (ior(DM9000A_ISR)>>6) & 0x3;
	ehi.base = (phyr_h(17)>>12) & 0xF;

	dm9000a_reset_to_new();
	// TODO DM9000A����IP��UDP��TCP�ļ�����Զ����㹦��
	//...

	i = ior(DM9000A_NSR);		// xxx del ��Ҫ����0x40�ű�ʾ���ӳɹ�

	return 1;
}

//----��DM9000A���ڲ��������ж�һ������--------------------------------------------
//���ܣ���DM9000A���ڲ��������ж�һ������
//������data_ptr�����ջ�����ͷָ��
//      count����ȡ���ֽ���
//���أ���
//-----------------------------------------------------------------------------
static void dm9000a_inblk_16bit(void *data_ptr, int count)
{
	int i;
	u32 tmplen = (count + 1) / 2;

	for (i = 0; i < tmplen; i++) {
		((u16 *) data_ptr)[i] = DATAR16();
	}
}

//----��DM9000A�ж�ȡһ������----------------------------------------------------
//���ܣ�����һ���㹻��С���ڴ棬Ȼ��DM9000A�еĵ�һ�����ݿ�����ȥ������µ����ݰ�������
//      pg_enet_rcvp_list.process�����У��ȴ������Ĵ���
//��������
//���أ�����ʱΪ��ȡ���ֽ�����������ĳ��ȴ�����̫����󳤶ȣ�����ֵΪ-1
//-----------------------------------------------------------------------------
static int dump_data16(void)
{
	u16 status, len;
	u32 align_len;	// ���϶��������յĴ�С
	struct enet_rcv_packet* pt_rcv_packet;

	ADDRW8(DM9000A_MRCMD);
	status = DATAR16();	// ״̬����õ�0x4001����8λΪ״̬����8λΪ0x01��־
	len = DATAR16();	// ��֡���ݰ��ĳ���
	if (len > DM9000A_PKT_MAX)	// ������̫������
	{
		return -1;
	}

	// ������ڴ棬���϶���
	align_len = sizeof(struct enet_rcv_packet) + len;
	pt_rcv_packet = enet_malloc_rcv_packet(align_len);
	if (pt_rcv_packet)
	{
		dm9000a_inblk_16bit((u16*)pt_rcv_packet->section, len);
		pg_enet_rcvp_list.process = enet_add_to_rcv_packet_list(
				pt_rcv_packet, pg_enet_rcvp_list.process);
	}

	return len;
}

//----��DM9000A�ж�����������----------------------------------------------------
//���ܣ���DM9000A�е��������ݶ���ȡ��������Щ���ݰ�����֯��pg_enet_rcvp_list.process��
//      ����
//��������
//���أ�����ʱ�������ֽ���
//-----------------------------------------------------------------------------
int __hw_raw_to_rcv_packet_list(void)
{
	u32 tmp;
	u32 len;
	u32 totlen = 0;

	// ����DM9000AӲ���������ź������ȴ�5S�����û�з���ȥ���򷵻�
	if (semp_pend(semp_dm9000, 5000*mS) == true)
	{
		// ���չ�����������жϷ������ж���Ӧ������ дDM9000�������Ĵ������Ͻ��չ��̡�
		int_save_asyn_line(cn_int_line_enet);	// �ر�DM9000A���ⲿ�ж�
		ior(DM9000A_MRCMDX);	// dummy read
		tmp = (u8)DATAR16();
		if (tmp == 0x01)	// ��һ���ֽڶ���Ϊ01h
		{
			switch (ehi.io)
			{
			case ENUM_DM9000A_IO_16BIT:	// 16-bit
				while (tmp == 0x01)
				{
					len = dump_data16();
					if (len == -1)
					{
						dm9000a_reset_to_new();
						totlen = 0;
					}
					else
					{
						totlen += len;
						// �Զ���һ֡���ݣ���Ϊ01h�������������Ϊ0���ʾû����Ч����
						ADDRW8(DM9000A_MRCMDX);
						tmp = (u8)DATAR16();
					}
				}
				__hw_enet_clear_int_rx();	// ��������ж�
				break;
			case ENUM_DM9000A_IO_32BIT:	// 32-bit
				break;
			case ENUM_DM9000A_IO_8BIT:	// 8-bit
				break;
			default:
				break;
			}
		}
		else if (tmp != 0)
		{
			dm9000a_reset_to_new();
			totlen = 0;
		}

		int_restore_asyn_line(cn_int_line_enet);	// ��DM9000A���ⲿ�ж�
		semp_post(semp_dm9000);
	}

	return totlen;
}

//----�����ж���Ӧ����-----------------------------------------------------------
//���ܣ�Ŀǰ��ʹ�õ�DM9000A����δʹ�÷����ж�
//��������
//���أ���
//-----------------------------------------------------------------------------
void dm9000a_txint_handler(void)
{
//	semp_post(enet_semp_transmit_int);
	__hw_enet_clear_int_tx();
    __hw_enet_en_int_tx();
}

//----�����жϺ���---------------------------------------------------------------
//���ܣ���ֹ�����жϣ����ͷ�һ�������ź���
//��������
//���أ�����Ϊ1
//-----------------------------------------------------------------------------
u32 dm9000a_rxint_handler(void)
{
	__hw_enet_disen_int_rx();
	semp_post(enet_semp_receive_int);	// �ͷſ������ݵ��ź���

	return 1;
}

//----DM9000A�����ж���Ӧ����----------------------------------------------------
//���ܣ�����IO���������жϵ���Ӧ������ͨ����ȡDM9000A���ж�״̬λ���з�֧
//��������
//���أ�����ʱΪ1
//-----------------------------------------------------------------------------
u32 dm9000a_int(void)
{
	u32 flag;

	// �ж��в���������ȣ����ڶ���дDM9000A�ĺ����ж��Ѿ���ֹ���ж�
	// ��˼����˵�����뱾������ʱ�������ڶ���д��������
	// ��֮���ڶ�дDM9000AʱҲ�����ܲ����ж�
	// �����DM9000A_ISR�Ķ�д�Ͳ��ؽ����ź���������
	flag = ior(DM9000A_ISR);

	// Packet Received
	if (flag & 0x01)
	{
		dm9000a_rxint_handler();
	}

	// Packet Transmitted
	if (flag & 0x02)
	{
		//dm9000a_txint_handler();
	}

	// Rx Overflow
	if (flag & 0x04)
	{
		iow(DM9000A_ISR, flag|0x04);
	}

	// Rx Overflow Counter Overflow
	if (flag & 0x08)
	{
		iow(DM9000A_ISR, flag|0x08);
	}

	return 1;
}

u32 enet_int_line_handler(ufast_t ufl_line)
{
    EXTI_ClearITPendingBit(EXTI_Line6);

	dm9000a_int();

	return 1;
}

void nicxx_exti_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

    // EXTI6�ж�ΪDM9000A���жϣ�EXTI6�ж���EXTI5-9�ǹ��õģ�
	// ʹ��GPIOG��ͨ�����ù���ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG | RCC_APB2Periph_AFIO, ENABLE);

	// IRQ������GPIOʱΪ���룬����������Ϊ�ж���������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//ѡ���ж�ͨ��2
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	//��ռʽ�ж����ȼ�����Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	//��Ӧʽ�ж����ȼ�����Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                                   //ʹ���ж�
	NVIC_Init(&NVIC_InitStructure);

	// ��GPIOG6��������Ϊ�ⲿ�жϴ�������
	EXTI_ClearITPendingBit(EXTI_Line6);	// ����ⲿ�ж���6
	// ѡ��GPIOG6�ܽ�Ϊ�ж���
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOG, GPIO_PinSource6);
	EXTI_InitStructure.EXTI_Line = EXTI_Line6; //ѡ���ж���·1
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //����Ϊ�ж����󣬷��¼�����
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�����жϴ�����ʽΪ���½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;	//�ⲿ�ж�ʹ��
	EXTI_Init(&EXTI_InitStructure);

	int_isr_connect(cn_int_line_enet, enet_int_line_handler);
	int_setto_asyn_signal(cn_int_line_enet);
    int_echo_line(cn_int_line_enet);
	int_restore_asyn_line(cn_int_line_enet);
}

static void dm9000a_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// ʹ��GPIOG��ͨ�����ù���ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG | RCC_APB2Periph_AFIO, ENABLE);

	// RST
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOG, &GPIO_InitStructure);

    nicxx_exti_init();
}

//----����оƬ��IO�ڳ�ʼ��-------------------------------------------------------
//���ܣ���ʼ��������оƬ��ص����߷��ʽӿڡ��ж��ߡ�IO�ڵȣ��ú���Ӧ�ôﵽ������Ŀ�ģ�
//      1. ʹ����оƬ����ͨ��iow��ior��д�Ĵ�����
//      2. ʹ����ģ����Խ��յ��жϣ�������оƬ�����Ѿ��������жϣ���
//      3. ������ģ�鲿�ֻ�ʹ��������IO�˿ڻ�Ӳ��ģ�飬��ô�ڴ˺�����ҲҪ��Ӧ�س�ʼ����
//��������
//���أ�����ʱΪ1
//-----------------------------------------------------------------------------
u8 nicxx_io_init(void)
{
	dm9000a_gpio_init();	// GPIO��ʼ��
//	dm9000_fsmc_init();	// FSMC�ĳ�ʼ����DM9000A���Դ������Ͻ��з���

	dm9000a_rstpin_assert();
	djy_delay_10us(5*mS);
	dm9000a_rstpin_deassert();
	djy_delay_10us(5*mS);	// RSTδ�����5uS��DM9000A��ʼ���Բ���

	return 1;
}
#endif
