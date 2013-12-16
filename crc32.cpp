/* ------------------------------------------------------------------------- *
 * Copyright (c) 2013 DIBGazo <tuldok89@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ------------------------------------------------------------------------- */

#include "crc32.h"
#include "lz_crc32.h"

#include <QtGlobal>

//!
//! \brief Constructor
//!
CRC32::CRC32() : m_crc32(0)
{
}

//!
//! \brief Destructor
//!
CRC32::~CRC32()
{
}


//!
//! \brief          Accumulate the CRC-32 value of a buffer
//! \param buffer   Buffer to compute CRC-32 value for
//! \param bufsize  number of bytes in buffer
//!
void CRC32::Update(quint8 *buffer, quint32 bufsize)
{
    m_crc32 = lzma_crc32(buffer, bufsize, m_crc32);
}

//!
//! \brief  Get the accumulated CRC-32 value
//! \return CRC-32
//!
unsigned int CRC32::GetChecksum() const
{
    return m_crc32;
}
