#include "fifo.h"  
#include <string.h>  
#include <stdbool.h>  

void fifo_init(_fifo_t *pfifo, uint8_t *buf, uint32_t size) {  
    pfifo->buf = buf;  
    pfifo->buf_size = size;  
    pfifo->pread = buf;  
    pfifo->pwrite = buf;  
    pfifo->occupy_size = 0;  
}  

void fifo_clear(_fifo_t *pfifo) {  
    // 重置读写指针和已占用大小  
    pfifo->pread = pfifo->buf;  
    pfifo->pwrite = pfifo->buf;  
    ATOMIC_SUB(&pfifo->occupy_size, ATOMIC_LOAD(&pfifo->occupy_size)); // Set to 0  
}  

uint32_t fifo_write(_fifo_t *pfifo, const uint8_t *pbuf, uint32_t size) {  
    if (!pfifo || !pbuf || size == 0) {  
        return 0;  
    }  

    // 获取空闲大小  
    uint32_t free_size = pfifo->buf_size - ATOMIC_LOAD(&pfifo->occupy_size);  
    if (free_size == 0) {  
        return 0; // 满  
    }  
    
    // 限制写入大小  
    if (size > free_size) {  
        size = free_size;  
    }  
    
    // 计算尾部空间  
    uint32_t tail_space = pfifo->buf + pfifo->buf_size - pfifo->pwrite;  
    
    // 分段写入  
    if (size <= tail_space) {  
        memcpy(pfifo->pwrite, pbuf, size);  
        pfifo->pwrite += size;  
    } else {  
        memcpy(pfifo->pwrite, pbuf, tail_space);  
        memcpy(pfifo->buf, pbuf + tail_space, size - tail_space);  
        pfifo->pwrite = pfifo->buf + (size - tail_space);  
    }  
    
    // 更新占用大小  
    ATOMIC_ADD(&pfifo->occupy_size, size);  
    return size;  

}  

uint32_t fifo_read(_fifo_t *pfifo, uint8_t *pbuf, uint32_t size) {  
    if (!pfifo || !pbuf || size == 0) {  
        return 0;  
    }  

    // 获取当前已占用大小  
    uint32_t occupy_size = ATOMIC_LOAD(&pfifo->occupy_size);  
    if (occupy_size == 0) {  
        return 0; // 空  
    }  
    
    // 限制读取大小  
    if (size > occupy_size) {  
        size = occupy_size;  
    }  
    
    // 计算可读尾部空间  
    uint32_t tail_space = pfifo->buf + pfifo->buf_size - pfifo->pread;  
    
    // 分段读取  
    if (size <= tail_space) {  
        memcpy(pbuf, pfifo->pread, size);  
        pfifo->pread += size;  
    } else {  
        memcpy(pbuf, pfifo->pread, tail_space);  
        memcpy(pbuf + tail_space, pfifo->buf, size - tail_space);  
        pfifo->pread = pfifo->buf + (size - tail_space);  
    }  
    
    // 更新占用大小  
    ATOMIC_SUB(&pfifo->occupy_size, size);  
    return size;  

}  

uint32_t fifo_get_total_size(const _fifo_t *pfifo) {  
    return pfifo ? pfifo->buf_size : 0;  
}  

uint32_t fifo_get_free_size(const _fifo_t *pfifo) {  
    return pfifo ? (pfifo->buf_size - ATOMIC_LOAD(&pfifo->occupy_size)) : 0;  
}  

uint32_t fifo_get_occupy_size(const _fifo_t *pfifo) {  
    return pfifo ? ATOMIC_LOAD(&pfifo->occupy_size) : 0;  
}