///////////////////////////////////////////////////////////////////////////////
//
/// \file       crc_macros.h
/// \brief      Some endian-dependent macros for CRC32 and CRC64
//
//  Author:     Lasse Collin
//
//  This file has been put into the public domain.
//  You can do whatever you want with this file.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#   define A(x) ((x) & 0xFF)
#   define B(x) (((x) >> 8) & 0xFF)
#   define C(x) (((x) >> 16) & 0xFF)
#   define D(x) ((x) >> 24)

#   define S8(x) ((x) >> 8)
#   define S32(x) ((x) >> 32)
