#ifndef FIFO_H
#define FIFO_H

#include <stdint.h>

// 控制是否启用原子操作的宏（默认禁用）
#ifndef USE_ATOMIC_OPERATIONS
#define USE_ATOMIC_OPERATIONS 1
#endif

// 锁函数类型定义
typedef void (*lock_fun)(void);

/**

 * FIFO结构体定义
   */
   typedef struct {
   uint8_t *buf;               // 缓冲区基址
   uint8_t *pwrite;            // 写指针
   uint8_t *pread;             // 读指针
   uint32_t buf_size;          // 缓冲区大小
   uint32_t occupy_size;       // 已占用大小
   lock_fun lock;              // 锁函数指针
   lock_fun unlock;            // 解锁函数指针
   } _fifo_t;

/**

 * @brief  获取fifo总大小
 * @param  pfifo: fifo结构体指针
 * @retval fifo总大小
   */
   uint32_t fifo_get_total_size(const _fifo_t *pfifo);

/**

 * @brief  获取fifo空闲大小
 * @param  pfifo: fifo结构体指针
 * @retval fifo空闲大小
   */
   uint32_t fifo_get_free_size(const _fifo_t *pfifo);

/**

 * @brief  获取fifo已用大小
 * @param  pfifo: fifo结构体指针
 * @retval fifo已用大小
   */
   uint32_t fifo_get_occupy_size(const _fifo_t *pfifo);

/**

 * @brief  注册一个fifo
 * @param  pfifo: fifo结构体指针
 * pfifo_buf: fifo内存块
 * size: 长度
 * @retval none
   */
   void fifo_register(_fifo_t *pfifo, uint8_t *pfifo_buf, uint32_t size,
                  lock_fun lock, lock_fun unlock);

/**

 * @brief  释放fifo
 * @param  pfifo: fifo结构体指针
 * @retval none
   */
   void fifo_release(_fifo_t *pfifo);

/**

 * @brief  往fifo写数据（优化版）
 * @param  pfifo: fifo结构体指针
 * pbuf: 待写数据
 * size: 待写数据大小
 * @retval 实际写大小
   */
   uint32_t fifo_write(_fifo_t *pfifo, const uint8_t *pbuf, uint32_t size);

/**

 * @brief  从fifo读数据（优化版）
 * @param  pfifo: fifo结构体指针
 * pbuf: 待读数据缓存
 * size: 待读数据大小
 * @retval 实际读大小
   */
   uint32_t fifo_read(_fifo_t *pfifo, uint8_t *pbuf, uint32_t size);

#endif // FIFO_H