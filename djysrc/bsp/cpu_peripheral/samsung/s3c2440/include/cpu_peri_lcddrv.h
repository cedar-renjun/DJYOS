#ifndef __LCDDRV_H_
#define __LCDDRV_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"


/*
//=========== ɾ���˴�����==============
// ��ң��������
// 2012.09.04
#define cn_lcd_xsize        320
#define cn_lcd_ysize        240

//#define cn_lcd_line_size    (cn_lcd_xsize*2)


#define cn_frame_buffer_size    (cn_lcd_xsize*cn_lcd_ysize*2)

//hjj
//#define cn_lcd_frame_rate       60
#define cn_lcd_pf       cn_sys_pf_r5g6b5


#define LCDCON4_MVAL        (13)
#define LCDCON1_MMODE       (0)         //0=ÿ֡   1=��MVAL�����Ƶ��
#define LCDCON5_INVVDEN     (1)         //0=����       1=��ת
#define LCDCON5_BSWP        (0)         //�ֽڽ�������λ 
#define LCDCON5_HWSWP       (1)         //���ֽڽ�������λ 
#define LCDCON1_PNRMODE     (3)         // ����ΪTFT��
#define LCDCON1_BPPMODE     (12)        // ����Ϊ16bppģʽ

#define LCDCON2_VBPD        (12)        //��ֱͬ���źŵĺ��
#define LCDCON2_VFPD        (4)         //��ֱͬ���źŵ�ǰ��
#define LCDCON2_VSPW        (5)         //��ֱͬ���źŵ�����

#define LCDCON3_HBPD        (22)        //ˮƽͬ���źŵĺ��
#define LCDCON3_HFPD        (33)        //ˮƽͬ���źŵ�ǰ��
#define LCDCON4_HSPW        (44)        //ˮƽͬ���źŵ�����

#define LCDCON1_CLKVAL      (6) 

//hjj

#define HOZVAL_TFT          (cn_lcd_xsize-1)
#define LINEVAL_TFT         (cn_lcd_ysize-1)
//===========================================

*/
//=========== �����ӡ������޶��Ķ���==============
// ��ң��������
// 2012.09.04

#define cn_lcd_pf       cn_sys_pf_r5g6b5

// #define M5D(n)				((n) & 0x1fffff)  //��õ�21λ

#define LCDW35			1		// 3.5����(320X240)
#define LCDW43			2		// 4.3����(480X272)
#define LCDA70			3		// 7.0����(800X480)

#define LCD_Type		LCDW35 //LCDW35 		//�趨��������

#if (LCD_Type == LCDW35)				// ������

#define LCDCON4_MVAL		(13)
#define LCDCON1_MMODE 	(0)			//0=each frame   1=rate by MVAL
#define LCDCON5_INVVDEN		(1)			//0=normal       1=inverted
#define LCDCON5_BSWP		(0)			//Byte swap control
#define LCDCON5_HWSWP		(1)			//Half word swap control
#define LCDCON1_PNRMODE		(3)			// ����ΪTFT��
#define LCDCON1_BPPMODE		(12)			// ����Ϊ16bppģʽ

//TFT_SIZE
#define LCD_XSIZE_TFT 	(320)
#define LCD_YSIZE_TFT 	(240)

#define SCR_XSIZE_TFT 	(320)
#define SCR_YSIZE_TFT 	(240)

//Timing parameter for 3.5' LCD
#define LCDCON2_VBPD 		(12)			//��ֱͬ���źŵĺ��
#define LCDCON2_VFPD 		(4)			//��ֱͬ���źŵ�ǰ��
#define LCDCON2_VSPW 		(5)			//��ֱͬ���źŵ�����

#define LCDCON3_HBPD 		(22)			//ˮƽͬ���źŵĺ��
#define LCDCON3_HFPD 		(33)			//ˮƽͬ���źŵ�ǰ��
#define LCDCON4_HSPW 		(44)			//ˮƽͬ���źŵ�����

#define LCDCON1_CLKVAL  	(6)

#elif (LCD_Type == LCDW43)			// 4.3����

#define LCDCON4_MVAL		(13)
#define LCDCON1_MMODE 	(0)			//0=each frame   1=rate by MVAL
#define LCDCON5_INVVDEN		(1)			//0=normal       1=inverted
#define LCDCON5_BSWP		(0)			//Byte swap control
#define LCDCON5_HWSWP		(1)			//Half word swap control
#define LCDCON1_PNRMODE		(3)			// ����ΪTFT��
#define LCDCON1_BPPMODE		(12)			// ����Ϊ16bppģʽ

//TFT_SIZE
#define LCD_XSIZE_TFT 	(480)
#define LCD_YSIZE_TFT 	(272)

#define SCR_XSIZE_TFT 	(480)
#define SCR_YSIZE_TFT 	(272)

//Timing parameter for 4.3' LCD
#define LCDCON2_VBPD 		(2)			//��ֱͬ���źŵĺ��
#define LCDCON2_VFPD 		(4)			//��ֱͬ���źŵ�ǰ��
#define LCDCON2_VSPW 		(8)			//��ֱͬ���źŵ�����

#define LCDCON3_HBPD 		(10)			//ˮƽͬ���źŵĺ��
#define LCDCON3_HFPD 		(19)			//ˮƽͬ���źŵ�ǰ��
#define LCDCON4_HSPW 		(30)			//ˮƽͬ���źŵ�����

#define LCDCON1_CLKVAL 	(4)

#elif (LCD_Type == LCDA70)			// 7.0����

#define LCDCON4_MVAL		(13)
#define LCDCON1_MMODE 	(0)			//0=each frame   1=rate by MVAL
#define LCDCON5_INVVDEN		(1)			//0=normal       1=inverted
#define LCDCON5_BSWP		(0)			//Byte swap control
#define LCDCON5_HWSWP		(1)			//Half word swap control
#define LCDCON1_PNRMODE		(3)			// ����ΪTFT��
#define LCDCON1_BPPMODE		(12)			// ����Ϊ16bppģʽ

//TFT_SIZE
#define LCD_XSIZE_TFT 	(800)
#define LCD_YSIZE_TFT 	(480)

#define SCR_XSIZE_TFT 	(800)
#define SCR_YSIZE_TFT 	(480)

//Timing parameter for 7.0' LCD
#define LCDCON2_VBPD 		(3)			//��ֱͬ���źŵĺ��
#define LCDCON2_VFPD 		(5)			//��ֱͬ���źŵ�ǰ��
#define LCDCON2_VSPW 		(15)			//��ֱͬ���źŵ�����

#define LCDCON3_HBPD 		(5)			//ˮƽͬ���źŵĺ��
#define LCDCON3_HFPD 		(15)			//ˮƽͬ���źŵ�ǰ��
#define LCDCON4_HSPW 		(8)			//ˮƽͬ���źŵ�����

#define LCDCON1_CLKVAL  	(7)

#endif

#define cn_lcd_xsize        SCR_XSIZE_TFT
#define cn_lcd_ysize        SCR_YSIZE_TFT

#define HOZVAL_TFT          (cn_lcd_xsize-1)
#define LINEVAL_TFT         (cn_lcd_ysize-1)


#define cn_frame_buffer_size    (cn_lcd_xsize*cn_lcd_ysize*2)

//=====================================


#define PALETTE         0x4d000400            //0x400,��ɫ�忪ʼ��ַ

// LCD CONTROLLER
struct lcd_reg            //0x4d000000
{
    u32 LCDCON1;            //0x00,LCD����1�Ĵ��� 
    u32 LCDCON2;            //0x04,LCD����2�Ĵ��� 
    u32 LCDCON3;            //0x08,LCD����3�Ĵ���
    u32 LCDCON4;            //0x0c,LCD����4�Ĵ���
    u32 LCDCON5;            //0x10,LCD����5�Ĵ���
    u32 LCDSADDR1;          //0x14,֡��������ʼ��ַ1�Ĵ��� 
    u32 LCDSADDR2;          //0x18,֡��������ʼ��ַ2�Ĵ��� 
    u32 LCDSADDR3;          //0x1c,��������ַ���� 
    u32 REDLUT;             //0x20,��ɫ���ұ�Ĵ���
    u32 GREENLUT;           //0x24,��ɫ���ұ�Ĵ���
    u32 BLUELUT;            //0x28,��ɫ���ұ�Ĵ���
    u32 revs[8];
    u32 DITHMODE;           //0x4c,����ģʽ�Ĵ���
    u32 TPAL;               //0x50,��ʱ��ɫ��Ĵ��� 
    u32 LCDINTPND;          //0x54,LCD�жϹ���Ĵ���
    u32 LCDSRCPND;          //0x58,LCDԴ����Ĵ���
    u32 LCDINTMSK;          //0x5c,LCD�ж����μĴ���
    u32 TCONSEL;            //0x60,���� LPC3600/LCC3600ģʽ�Ĵ��� 
    
};


void __lcd_hard_init(void);

void __lcd_envid_of(int );

void __lcd_power_enable(int ,int );
bool_t __lcd_disp_ctrl(struct display_rsc *disp);
bool_t __lcd_format_pattern(u8 *pattern,struct st_rect_bitmap *bitmap);
bool_t __lcd_set_pixel_bm(struct st_rect_bitmap *bitmap,
                     s32 x,s32 y,u32 color,u32 r2_code);
bool_t __lcd_line_bm(struct st_rect_bitmap *bitmap,struct st_rect *limit,
                        s32 x1,s32 y1,s32 x2,s32 y2,u32 color,u32 r2_code);
bool_t __lcd_line_bm_ie(struct st_rect_bitmap *bitmap,struct st_rect *limit,
                        s32 x1,s32 y1,s32 x2,s32 y2,u32 color,u32 r2_code);
bool_t __lcd_fill_rect_bm(struct st_rect_bitmap *bitmap,
                      struct st_rect *dst_rect,u32 color);
bool_t __lcd_blt_bm_to_bm(struct st_rect_bitmap *dst_bitmap,
                        struct st_rect *dst_rect,
                        struct st_rect_bitmap *src_bitmap,s32 xsrc,s32 ysrc,
                        u8 *pat,struct st_rect_bitmap *bitmsk,u32 rop_code,
                        u32 transparentcolor);
u32 __lcd_get_pixel_bm(struct st_rect_bitmap *bitmap,s32 x,s32 y);
bool_t __lcd_get_rect_bm(struct st_rect_bitmap *src,struct st_rect *rect,
                     struct st_rect_bitmap *dest);
bool_t __lcd_set_pixel_screen(s32 x,s32 y,u32 color,u32 rop2_code);
bool_t __lcd_line_screen(struct st_rect *limit,
                    s32 x1,s32 y1,s32 x2,s32 y2,u32 color,u32 r2_code);
bool_t __lcd_line_screen_ie(struct st_rect *limit,
                        s32 x1,s32 y1,s32 x2,s32 y2,u32 color,u32 r2_code);
bool_t __lcd_fill_rect_screen(struct st_rect *dst_rect,u32 color);
bool_t __lcd_bm_to_screen(struct st_rect *dst_rect,
                struct st_rect_bitmap *src_bitmap,s32 xsrc,s32 ysrc);
u32 __lcd_get_pixel_screen(s32 x,s32 y);
bool_t __lcd_get_rect_screen(struct st_rect *rect,struct st_rect_bitmap *dest);
ptu32_t module_init_lcd(ptu32_t para);

#ifdef __cplusplus
}
#endif

#endif   //__LCDDRV_H_
