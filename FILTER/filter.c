#include "filter.h"  

// 初始化低通滤波器  
void initLPF(LPF* filter, uint16_t alpha) {  
    filter->alpha = alpha;  
    filter->prevOut = 0;  
}  

#ifdef USE_LPF  
uint16_t updateLPF(LPF* filter, uint16_t input) {  
    filter->prevOut = (filter->alpha * input + (65535 - filter->alpha) * filter->prevOut) / 65535;  
    return filter->prevOut;  
}  
#endif  

// 高通滤波器  
void initHPF(HPF* filter, uint16_t alpha) {  
    filter->alpha = alpha;  
    filter->prevIn = 0;  
    filter->prevOut = 0;  
}  

#ifdef USE_HPF  
uint16_t updateHPF(HPF* filter, uint16_t input) {  
    uint16_t output = (filter->alpha * (filter->prevOut + input - filter->prevIn)) / 65535;  
    filter->prevIn = input;  
    filter->prevOut = output;  
    return output;  
}  
#endif  

// 平均  
void initAvgF(AvgF* filter, uint8_t size) {  
    filter->sum = 0;  
    filter->size = size;  
    filter->vals = (uint16_t*)malloc(size * sizeof(uint16_t));  
    memset(filter->vals, 0, size * sizeof(uint16_t));  
    filter->index = 0;  
}  

#ifdef USE_AVGF  
uint16_t updateAvgF(AvgF* filter, uint16_t input) {  
    filter->sum += input - filter->vals[filter->index];  
    filter->vals[filter->index] = input;  
    filter->index = (filter->index + 1) % filter->size;  
    return (uint16_t)(filter->sum / filter->size);  
}  
void freeAvgF(AvgF* filter) {  
    free(filter->vals);  
}  
#endif  

// 中位  
void initMedF(MedF* filter, uint8_t size) {  
    filter->size = size;  
    filter->vals = (uint16_t*)malloc(size * sizeof(uint16_t));  
    memset(filter->vals, 0, size * sizeof(uint16_t));  
    filter->index = 0;  
}  

#ifdef USE_MEDF  
void quickSort(int16_t* arr, int low, int high) {  
    if (low < high) {  
        int16_t pivot = arr[high];  
        int i = low - 1;  
        for (int j = low; j < high; j++) {  
            if (arr[j] < pivot) {  
                i++;  
                int16_t temp = arr[i];  
                arr[i] = arr[j];  
                arr[j] = temp;  
            }  
        }  
        int16_t temp = arr[i + 1];  
        arr[i + 1] = arr[high];  
        arr[high] = temp;  
        int pivotIdx = i + 1;  
        quickSort(arr, low, pivotIdx - 1);  
        quickSort(arr, pivotIdx + 1, high);  
    }  
}  

uint16_t updateMedF(MedF* filter, uint16_t input) {  
    filter->vals[filter->index] = input;  
    filter->index = (filter->index + 1) % filter->size;  
    int16_t* sortedVals = (int16_t*)malloc(filter->size * sizeof(int16_t));  
    for (int i = 0; i < filter->size; i++) {  
        sortedVals[i] = filter->vals[i];  
    }  
    quickSort(sortedVals, 0, filter->size - 1);  
    uint16_t median;  
    if (filter->size % 2 == 0) {  
        median = (sortedVals[(filter->size/2)-1] + sortedVals[filter->size/2]) / 2;  
    } else {  
        median = sortedVals[filter->size/2];  
    }  
    free(sortedVals);  
    return median;  
}  
void freeMedF(MedF* filter) {  
    free(filter->vals);  
}  
#endif  

// 限幅  
void initClipF(ClipF* filter, uint16_t minVal, uint16_t maxVal) {  
    filter->minVal = minVal;  
    filter->maxVal = maxVal;  
}  

#ifdef USE_CLIPF  
uint16_t updateClipF(ClipF* filter, uint16_t input) {  
    if (input < filter->minVal) return filter->minVal;  
    if (input > filter->maxVal) return filter->maxVal;  
    return input;  
}  
#endif  

// 加权递推平均  
void initWMAF(WMAF* filter, int16_t* weights, uint8_t size) {  
    filter->weights = weights;  
    filter->vals = (uint16_t*)malloc(size * sizeof(uint16_t));  
    memset(filter->vals, 0, size * sizeof(uint16_t));  
    filter->size = size;  
    filter->index = 0;  
}  

#ifdef USE_WMAF  
uint16_t updateWMAF(WMAF* filter, uint16_t input) {  
    filter->vals[filter->index] = input;  
    filter->index = (filter->index + 1) % filter->size;  
    int32_t result = 0;  
    for (uint8_t i = 0; i < filter->size; i++) {  
        result += filter->weights[i] * filter->vals[(filter->index + i) % filter->size];  
    }  
    return (uint16_t)(result / 32768);  
}  
void freeWMAF(WMAF* filter) {  
    free(filter->vals);  
}  
#endif  

// 消抖  
void initDebF(DebF* filter, uint16_t threshold, uint8_t requiredCount) {  
    filter->threshold = threshold;  
    filter->stableVal = 0;  
    filter->stableCount = 0;  
    filter->requiredCount = requiredCount;  
}  

#ifdef USE_DEBF  
uint16_t updateDebF(DebF* filter, uint16_t input) {  
    if (abs((int16_t)input - (int16_t)filter->stableVal) > filter->threshold) {  
        filter->stableCount = 0;  
    } else {  
        filter->stableCount++;  
        if (filter->stableCount >= filter->requiredCount) {  
            filter->stableVal = input;  
        }  
    }  
    return filter->stableVal;  
}  
#endif  

// 限幅消抖  
void initClipDebF(ClipDebF* filter, uint16_t minVal, uint16_t maxVal, uint16_t threshold, uint8_t requiredCount) {  
    filter->minVal = minVal;  
    filter->maxVal = maxVal;  
    initDebF(&filter->debounce, threshold, requiredCount);  
}  

#ifdef USE_CLIPDEBF  
uint16_t updateClipDebF(ClipDebF* filter, uint16_t input) {  
    if (input < filter->minVal) input = filter->minVal;  
    if (input > filter->maxVal) input = filter->maxVal;  
    return updateDebF(&filter->debounce, input);  
}  
#endif