#ifndef LZ_CRC32_H
#define LZ_CRC32_H

#include <cstdint>

extern uint32_t lzma_crc32(const uint8_t *buf, size_t size, uint32_t crc);

#endif // LZ_CRC32_H
