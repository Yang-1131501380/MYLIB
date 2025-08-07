#include "Task.h"  

// 全局变量，用于任务跟踪  
uint16_t volatile ms1;  
uint16_t volatile ms2;  
uint16_t volatile ms3;  
//commit
// 任务函数声明  
void Task1(void);  
void Task2(void);  
void Task3(void);  

// 任务组件结构体定义  
typedef struct _TASK_COMPONENTS {  
    u8 Run;                 // 程序运行标志：0 - 不运行，1 - 运行  
    u8 Timer;               // 计时器，控制任务间隔  
    u8 ItvTime;             // 任务间隔时间（ms）  
    void (*TaskHook)(void); // 任务函数指针  
} TASK_COMPONENTS;  

// 任务频率定义数组  
static const u16 TaskFrequencies[] = {  
    100,  // 任务1频率  
    50,   // 任务2频率  
    33    // 任务3频率  
};  

// 任务定义数组  
static TASK_COMPONENTS TaskComps[] = {  
    {0, 0, 0, Task1},  // 任务1  
    {0, 0, 0, Task2},  // 任务2  
    {0, 0, 0, Task3},  // 任务3  
    // 添加更多任务...  
};  

// 示例任务实现  
void Task1(void) { ++ms1; } // 时钟显示的任务逻辑  
void Task2(void) { ++ms2; } // 按键扫描的任务逻辑  
void Task3(void) { ++ms3; } // 显示状态的任务逻辑  

// 初始化任务：根据频率计算 ItvTime  
void TaskInit(void) {  
    for (u8 i = 0; i < sizeof(TaskFrequencies) / sizeof(TaskFrequencies[0]); i++) {  
        if (TaskFrequencies[i] > 0) {  
            TaskComps[i].ItvTime = 1000 / TaskFrequencies[i];  
            TaskComps[i].Timer = TaskComps[i].ItvTime; // 初始化计时器  
        }  
    }  
}  

// 任务处理函数  
void TaskProcess(void) {  
    for (u8 i = 0; i < sizeof(TaskComps) / sizeof(TaskComps[0]); i++) {  
        if (TaskComps[i].Run) { // 如果任务准备运行  
            TaskComps[i].TaskHook(); // 执行任务  
            TaskComps[i].Run = 0;    // 重置运行标志  
        }  
    }  
}  

// 任务调度函数 (中断中调用)  
void TaskRemarks(void) {  
    for (u8 i = 0; i < sizeof(TaskComps) / sizeof(TaskComps[0]); i++) {  
        if (TaskComps[i].Timer) { // 如果计时器不为零  
            TaskComps[i].Timer--; // 减少计时器  
            if (TaskComps[i].Timer == 0) { // 计时器到期  
                TaskComps[i].Timer = TaskComps[i].ItvTime; // 重置计时器  
                TaskComps[i].Run = 1; // 标记任务可以运行  
            }  
        }  
    }  
}