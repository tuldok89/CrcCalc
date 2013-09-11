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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mysetting.h"
#include "filecrc32.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QThreadPool>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}

//!
//! \brief About box
//!
void MainWindow::on_action_About_triggered()
{
    QMessageBox msgBox;
    QString title(tr("CRC-32 Calculator"));
    QString msg;

    msg.append(tr("<h1><center>CRC-32 Calculator %1</center></h1><p><center>A simple CRC-32 calculator</center></p>").arg(qApp->applicationVersion()));
    msg.append(tr("<p><center>Written by: DIBGazo &lt;tuldok89@gmail.com&gt;</center></p>"));

    msgBox.about(this, title, msg);
}

//!
//! \brief Browse for input file
//!
void MainWindow::on_browseFileButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Browse for File"), "", tr("All Files (*.*)"));

    if (fileName == "")
        return;

    ui->filenameLineEdit->setText(fileName);
}

//!
//! \brief calculateHashButton click slot
//!
void MainWindow::on_calculateHashButton_clicked()
{
    QMessageBox msgbox;

    if (ui->filenameLineEdit->text() == QString("")) // check if filename box is empty
    {
        msgbox.setText(tr("There is no input file!"));
        msgbox.setIcon(QMessageBox::Critical);
        msgbox.exec();
        return;
    }

    ui->calculateHashButton->setEnabled(false);

    FileCRC32 *crc32 = new FileCRC32(ui->filenameLineEdit->text());

    connect(crc32, SIGNAL(doneProcessing(uint)), this, SLOT(doneProcessing(uint)));
    connect(crc32, SIGNAL(errorRaised()), this, SLOT(errorRaised()));
    connect(crc32, SIGNAL(progress(int)), this, SLOT(progress(int)));

    QThreadPool::globalInstance()->start(crc32);
}

//!
//! \brief MainWindow::doneProcessing
//! \param crc32
//!
void MainWindow::doneProcessing(unsigned int crc32)
{
    ui->calculateHashButton->setEnabled(true);

    QString ckstr;
    ckstr = ckstr.sprintf("CRC32: %.8X", crc32);

    ui->hashTextEdit->clear();
    ui->hashTextEdit->appendPlainText(ckstr);
}

void MainWindow::errorRaised()
{
    ui->hashTextEdit->clear();
    ui->hashTextEdit->appendPlainText("Can't open file!");
    ui->calculateHashButton->setEnabled(true);
}

void MainWindow::progress(int val)
{
    ui->progressBar->setValue(val);
}
