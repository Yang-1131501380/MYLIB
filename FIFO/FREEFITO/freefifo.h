#ifndef FIFO_H  
#define FIFO_H`  

`#include <stdint.h>  
#include <stdbool.h>`  

`// 控制是否启用原子操作的宏（默认启用）  
#ifndef USE_ATOMIC_OPERATIONS  
#define USE_ATOMIC_OPERATIONS 1  
#endif`  

`// 锁函数类型定义  
typedef void (*lock_fun)(void);`  

`// 原子操作宏定义  
#if USE_ATOMIC_OPERATIONS  
#include <stdatomic.h>  
#define ATOMIC_ADD(ptr, val) atomic_fetch_add(ptr, val)  
#define ATOMIC_SUB(ptr, val) atomic_fetch_sub(ptr, val)  
#define ATOMIC_LOAD(ptr) atomic_load(ptr)  
#else  
#define ATOMIC_ADD(ptr, val) (*(ptr) += (val))  
#define ATOMIC_SUB(ptr, val) (*(ptr) -= (val))  
#define ATOMIC_LOAD(ptr) (*(ptr))  
#endif`  

`/**`  

 * `FIFO结构体定义  
   */  
   typedef struct {  
   uint8_t *buf;               // 缓冲区指针  
   uint8_t *pread;             // 读指针  
   uint8_t *pwrite;            // 写指针  
   uint32_t buf_size;          // 缓冲区大小  
   volatile uint32_t occupy_size; // 已占用大小  
   } _fifo_t;`  

`/**`  

 * `@brief  初始化 FIFO`  
 * `@param  pfifo: FIFO 结构体指针`  
 * `buf: FIFO 缓冲区`  
 * `size: 缓冲区大小  
    */  
   void fifo_init(_fifo_t *pfifo, uint8_t *buf, uint32_t size);`  

`/**`  

 * `@brief  清空 FIFO`  
 * `@param  pfifo: FIFO 结构体指针  
   */  
   void fifo_clear(_fifo_t *pfifo);`  

`/**`  

 * `@brief  往 FIFO 写数据`  
 * `@param  pfifo: FIFO 结构体指针`  
 * `pbuf: 待写数据`  
 * `size: 待写数据大小`  
 * `@retval 实际写入大小  
   */  
   uint32_t fifo_write(_fifo_t *pfifo, const uint8_t *pbuf, uint32_t size);`  

`/**`  

 * `@brief  从 FIFO 读数据`  
 * `@param  pfifo: FIFO 结构体指针`  
 * `pbuf: 读取数据缓存`  
 * `size: 待读取大小`  
 * `@retval 实际读取大小  
   */  
   uint32_t fifo_read(_fifo_t *pfifo, uint8_t *pbuf, uint32_t size);`  

`/**`  

 * `@brief  获取 FIFO 总大小`  
 * `@param  pfifo: FIFO 结构体指针`  
 * `@retval FIFO 总大小  
   */  
   uint32_t fifo_get_total_size(const _fifo_t *pfifo);`  

`/**`  

 * `@brief  获取 FIFO 空闲大小`  
 * `@param  pfifo: FIFO 结构体指针`  
 * `@retval FIFO 空闲大小  
   */  
   uint32_t fifo_get_free_size(const _fifo_t *pfifo);`  

`/**`  

 * `@brief  获取 FIFO 已用大小`  
 * `@param  pfifo: FIFO 结构体指针`  
 * `@retval FIFO 已用大小  
   */  
   uint32_t fifo_get_occupy_size(const _fifo_t *pfifo);`  

`#endif // FIFO_H