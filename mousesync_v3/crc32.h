#ifndef _CRC_CRC32_H
#define _CRC_CRC32_H

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus  */

uint32_t calculateCRC32(const void* s, int len);

#ifdef __cplusplus
}
#endif /* __cplusplus  */
#endif
