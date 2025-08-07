#ifndef FILTER_H  
#define FILTER_H  

#include <stdint.h>  
#include <stdlib.h>  
#include <string.h>  

// 过滤器配置宏（可选择注释或取消注释）  
#define USE_LPF  
#define USE_HPF  
#define USE_AVGF  
#define USE_MEDF  
#define USE_CLIPF  
#define USE_WMAF  
#define USE_DEBF  
#define USE_CLIPDEBF  

// 定义低通滤波器结构体  
typedef struct {  
    uint16_t alpha;    // 滤波因子（定点数）  
    uint16_t prevOut; // 上一个输出值  
} LPF;  

// 定义高通滤波器结构体  
typedef struct {  
    uint16_t alpha;  
    uint16_t prevIn;  
    uint16_t prevOut;  
} HPF;  

// 定义平均值滤波器结构体  
typedef struct {  
    uint32_t sum;  
    uint8_t size;  
    uint16_t* vals;  
    uint8_t index;  
} AvgF;  

// 定义中位值滤波器结构体  
typedef struct {  
    uint8_t size;  
    uint16_t* vals;  
    uint8_t index;  
} MedF;  

// 定义限幅滤波器结构体  
typedef struct {  
    uint16_t minVal;  
    uint16_t maxVal;  
} ClipF;  

// 定义加权递推平均滤波器结构体  
typedef struct {  
    int16_t* weights;  
    uint16_t* vals;  
    uint8_t size;  
    uint8_t index;  
} WMAF;  

// 定义消抖滤波器结构体  
typedef struct {  
    uint16_t threshold;  
    uint16_t stableVal;  
    uint8_t stableCount;  
    uint8_t requiredCount;  
} DebF;  

// 定义限幅消抖滤波器  
typedef struct {  
    uint16_t minVal;  
    uint16_t maxVal;  
    DebF debounce;  
} ClipDebF;  

// 函数声明（不变，参数改为 `uint16_t`）  
void initLPF(LPF* filter, uint16_t alpha);  
uint16_t updateLPF(LPF* filter, uint16_t input);  
void initHPF(HPF* filter, uint16_t alpha);  
uint16_t updateHPF(HPF* filter, uint16_t input);  

void initAvgF(AvgF* filter, uint8_t size);  
uint16_t updateAvgF(AvgF* filter, uint16_t input);  
void freeAvgF(AvgF* filter);  

void initMedF(MedF* filter, uint8_t size);  
uint16_t updateMedF(MedF* filter, uint16_t input);  
void freeMedF(MedF* filter);  

void initClipF(ClipF* filter, uint16_t minVal, uint16_t maxVal);  
uint16_t updateClipF(ClipF* filter, uint16_t input);  

void initWMAF(WMAF* filter, int16_t* weights, uint8_t size);  
uint16_t updateWMAF(WMAF* filter, uint16_t input);  
void freeWMAF(WMAF* filter);  

void initDebF(DebF* filter, uint16_t threshold, uint8_t requiredCount);  
uint16_t updateDebF(DebF* filter, uint16_t input);  

void initClipDebF(ClipDebF* filter, uint16_t minVal, uint16_t maxVal, uint16_t threshold, uint8_t requiredCount);  
uint16_t updateClipDebF(ClipDebF* filter, uint16_t input);  

void quickSort(int16_t* arr, int low, int high);  

#endif // FILTER_H