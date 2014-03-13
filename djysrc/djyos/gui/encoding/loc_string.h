//----------------------------------------------------
//Copyright (C), 2011,  .
//��Ȩ���� (C), 2011,   djy.
//����ģ��: ���ֽ��ַ�������
//���ߣ�mjh
//�汾��V1.0.0
//�ļ�����: ���ֽ��ַ�������
//����˵��:
//�޶���ʷ:
//    2. ...
//    1. ����:2011-05-17
//       ����:mjh
//       �°汾�ţ�
//       �޸�˵��:��ʼ�汾
//------------------------------------------------------
#if (cfg_gui_kernel == 1)

#ifndef __LOC_STRING_H_
#define __LOC_STRING_H_

//#include <locale.h>

#ifdef __cplusplus
extern "C" {
#endif

s32 djy_mblen(const char* s, u32 n);
s32 djy_mbtowc(u32* pwc, const char* s, u32 n);
s32 djy_mbstowcs(u32* pwc, const char* s, u32 n);
s32 djy_wctomb(char* s, u32 wc);
s32 djy_wcstombs(char* s, const u32* pwc, u32 n);

s32 djy_mblen_l(const char* s, u32 n, struct char_encoding_rsc* locale);
s32 djy_mbtowc_l(u32* pwc, const char* s, u32 n, struct char_encoding_rsc* locale);
s32 djy_mbstowcs_l(u32* pwc, const char* s,u32 n,struct char_encoding_rsc* locale);
s32 djy_wctomb_l(char* s, u32 wc, struct char_encoding_rsc* locale);
s32 djy_wcstombs_l(char* s, const u32* pwc,u32 n,struct char_encoding_rsc* locale);

#ifdef __cplusplus
}
#endif

#endif

#endif      //for #if (cfg_gui_kernel == 1)

