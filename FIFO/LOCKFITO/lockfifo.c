#include <stdint.h>`
`#include <stdbool.h>`
`#include <string.h>`
`#include "fifo.h"`
`#include <stddef.h>`


`// 根据宏定义选择原子操作实现`
`#if USE_ATOMIC_OPERATIONS`
`#define __ARM_ARCH_7M__` 
    `// 原子操作实现（ARM Cortex-M系列）`
    `#ifdef __ARM_ARCH_7M__  // Cortex-M3及以上支持LDREX/STREX`
    `#define ATOMIC_ADD(ptr, val) __sync_fetch_and_add(ptr, val)
        #define ATOMIC_SUB(ptr, val) __sync_fetch_and_sub(ptr, val)`
        `#define ATOMIC_LOAD(ptr) __sync_val_compare_and_swap(ptr, 0, 0)`
    `#else`
        `// 其他架构使用非原子操作（有volatile保证可见性）`
    `#define ATOMIC_ADD(ptr, val) (*(ptr) += (val))
        #define ATOMIC_SUB(ptr, val) (*(ptr) -= (val))`
        `#define ATOMIC_LOAD(ptr) (*(ptr))
    #endif
#else
    // 非原子操作（原始实现）
    #define ATOMIC_ADD(ptr, val) (*(ptr) += (val))`
`#define ATOMIC_SUB(ptr, val) (*(ptr) -= (val))
    #define ATOMIC_LOAD(ptr) (*(ptr))`
`#endif`

`/**`

 * `@brief  获取fifo总大小`
   `*/`
   `uint32_t fifo_get_total_size(const _fifo_t *pfifo)`
   `{`
`return pfifo ? pfifo->buf_size : 0;`
    `}`
 
 `/**`

  * `@brief  获取fifo空闲大小`
    `*/`
`uint32_t fifo_get_free_size(const _fifo_t *pfifo)`
    `{`
    `return pfifo ? (pfifo->buf_size - ATOMIC_LOAD(&pfifo->occupy_size)) : 0;`
    `}`
