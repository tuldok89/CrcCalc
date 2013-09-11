#include <QFile>
#include <QString>
#include <stdexcept>

#include "filecrc32.h"

const int FileCRC32::bufsize = 32768;

FileCRC32::FileCRC32(QString fileName) : CRC32(), m_fileName(fileName), m_hasError(false)
{

}

FileCRC32::~FileCRC32()
{

}

//!
//! \brief Compute the CRC-32 value of the given file
//! \return CRC-32 checksum
//!
unsigned int FileCRC32::compute()
{
    char buffer[bufsize];
    QFile file(m_fileName);


    bool isOpen = file.open(QIODevice::ReadOnly);

    if(!isOpen)
    {
        m_hasError = true;
        return 0;
    }

    while (!file.atEnd())
    {
        qint64 bytesRead = file.read(buffer, bufsize);
        CRC32::Update(buffer, bytesRead);
    }

    file.close();

    return CRC32::GetChecksum();
}

//!
//! \brief Function that gets called by QThreadPool
//!
void FileCRC32::run()
{
    compute();

    if (!m_hasError)
        emit doneProcessing(CRC32::GetChecksum());
    else
        emit errorRaised();

}

