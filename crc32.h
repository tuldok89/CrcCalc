/* ------------------------------------------------------------------------- *
 * CRC-32 Version 2.0.0 by Craig Bruce, 2006-04-29.
 *
 * The CRC-32 values generated by this program are the same CRC-32 values used
 * by GZIP, PKZIP and ZMODEM.
 *
 * Based on the byte-oriented implementation "File Verification using CRC"
 * by Mark. Nelson in Dr. Dobb's Journal, May 1992, pp. 64-67.
 *
 * THIS PROGRAM IS PUBLIC-DOMAIN SOFTWARE
 *
 * Rewritten as a C++ Class by DIBGazo <tuldok89@gmail.com>
 * ------------------------------------------------------------------------- */

#ifndef CRC32_H
#define CRC32_H

//!
//! \brief The CRC32 class
//!
class CRC32
{
public:
    CRC32();
    virtual ~CRC32();
    void Update(char* buffer, int bufsize);

    //!
    //! \brief Reset the crc32 value to a pristine state
    //!
    void Reset() { m_crc32 = 0;}
    unsigned int GetChecksum() const;

private:
    unsigned int m_crc32;
    static const unsigned int crcTable[256];
};

#endif