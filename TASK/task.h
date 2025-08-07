#ifndef __TASK_H
#define __TASK_H
#include <stdint.h>
#include <stdbool.h>  
// 自定义整数类型
typedef uint64_t  u64;  // 无符号64位整数
typedef uint32_t  u32;  // 无符号32位整数
typedef uint16_t  u16;  // 无符号16位整数
typedef uint8_t   u8;   // 无符号8位整数
typedef int64_t   s64;  // 有符号64位整数
typedef int32_t   s32;  // 有符号32位整数
typedef int16_t   s16;  // 有符号16位整数
typedef int8_t    s8;   // 有符号8位整数
#endif 
extern volatile uint32_t msTicks; // 用于计数的全局变量
extern uint16_t volatile ms1;
extern uint16_t volatile ms2;
extern uint16_t volatile ms3;
void SysTick_Init(void);
void SysTick_Handler(void);
void TaskProcess(void);
void TaskRemarks(void);
void TaskInit(void);
