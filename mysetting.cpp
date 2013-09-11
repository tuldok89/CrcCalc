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

#include "mysetting.h"
#include <QSettings>

MySetting MySetting::sInstance;

MySetting::MySetting()
{   
}

MySetting::~MySetting()
{
}

//!
//! \brief Instance function
//! \return The one and only instance of this class
//!
MySetting& MySetting::instance()
{
    return sInstance;
}

//!
//! \brief Retrieve the language setting
//! \return Two-character string that represents the ISO-646 code of the language
//!
QString MySetting::GetLanguage()
{
    QSettings setting;
    return setting.value("Language", "en").toString();
}

//!
//! \brief Save the language setting
//! \param lang Two-character string that represents the ISO-646 code of the language
//!
void MySetting::SetLanguage(QString lang)
{
    QSettings setting;
    setting.setValue("Language", lang);
}
