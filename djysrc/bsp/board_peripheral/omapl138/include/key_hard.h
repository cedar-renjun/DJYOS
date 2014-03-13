//----------------------------------------------------
//Copyright (C), 2004-2009,  luoshitian.
//版权所有 (C), 2004-2009,   罗侍田.
//所属模块:标准输入--键盘输入模块
//作者:  罗侍田.
//版本：V1.1.0
//文件描述: 键盘输入
//其他说明:
//修订历史:
//1. 日期: 2009-01-04
//   作者:  罗侍田.
//   新版本号: V1.0.0
//   修改说明: 原始版本
//------------------------------------------------------

#if (cfg_keyboard== 1)

#ifndef __KEY_HARD_H__
#define __KEY_HARD_H__

#ifdef __cplusplus
extern "C" {
#endif

//按键定义，参考的是windows的虚拟键码
#define CN_KeyValueUp       38
#define CN_KeyValueDown     40
#define CN_KeyValueLeft     37
#define CN_KeyValueRight    39
#define CN_KeyValueEnter    13
#define CN_KeyValueRetrun   27
#define CN_KeyValueF1       112
#define CN_KeyValueF2       113


ptu32_t module_init_keyboard_hard(ptu32_t para);

#ifdef __cplusplus
}
#endif

#endif /* __KEY_HARD_H__ */

#endif  //for #if (cfg_single_touch == 1)

