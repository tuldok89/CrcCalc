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
#include <QStringList>
#include <QDebug>
#include <QtGui>
#include <QUrl>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Uniform initialization is not supported in some compilers
    //QStringList headers = {"File", "Progress", "Status", "CRC-32"};
    QStringList headers;
    headers.push_back("File");
    headers.push_back("Progress");
    headers.push_back("Status");
    headers.push_back("CRC-32");
    ui->filesTable->setHorizontalHeaderLabels(headers);
    ui->filesTable->setColumnWidth(0, 350);
    QThreadPool::globalInstance()->setMaxThreadCount(1);
    this->setMinimumSize(this->size());

    setAcceptDrops(true);
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


void MainWindow::errorRaised(QString fileName)
{
    auto cell = ui->filesTable->findItems(fileName, Qt::MatchFixedString);
    ui->filesTable->item(cell[0]->row(), 2)->setText(tr("ERROR"));
    ui->calculateCrcButton->setEnabled(true);
}

void MainWindow::doneProcessing(QString fileName, unsigned int crc32)
{
    QString str;
    auto cell = ui->filesTable->findItems(fileName, Qt::MatchFixedString);
    ui->filesTable->item(cell[0]->row(), 3)->setText(QString("%1").arg(str.sprintf("%.8X", crc32)));
    ui->filesTable->item(cell[0]->row(), 2)->setText(QString(tr("Done")));
    ui->calculateCrcButton->setEnabled(true);
}

void MainWindow::progress(QString fileName, int val)
{
    auto cell = ui->filesTable->findItems(fileName, Qt::MatchFixedString);
    ui->filesTable->item(cell[0]->row(), 1)->setText(QString("%1%").arg(val));
}

void MainWindow::on_addFilesButton_clicked()
{
    QStringList files;
    files = QFileDialog::getOpenFileNames(this, tr("Browse for Files"), "", tr("All Files (*.*)"));

    foreach (QString file, files)
    {
        if (m_fileNames.contains(file))
            continue;

        addNewRow(file, ui->filesTable);
        m_fileNames.push_back(file);
    }
}

//!
//! \brief Add new row to a QTableWidget
//! \param fileName
//! \param table
//! \param progress
//! \param status
//! \param crc32
//! \todo Genericize the function. Use either variadic templates or a QStringList for parameters
//!
void MainWindow::addNewRow(QString fileName, QTableWidget* table, QString progress, QString status, QString crc32)
{
    auto fileItem = new QTableWidgetItem(fileName);
    auto progressItem = new QTableWidgetItem(progress);
    auto statusItem = new QTableWidgetItem(status);
    auto crc32Item = new QTableWidgetItem(crc32);

    int rowCount = table->rowCount();

    table->setRowCount(rowCount + 1);

    table->setItem(rowCount, 0, fileItem);
    table->setItem(rowCount, 1, progressItem);
    table->setItem(rowCount, 2, statusItem);
    table->setItem(rowCount, 3, crc32Item);
}

void MainWindow::on_calculateCrcButton_clicked()
{
    ui->calculateCrcButton->setEnabled(false);
    foreach (QString file, m_fileNames)
    {
        auto fileCRC = new FileCRC32(file);

        connect(fileCRC, SIGNAL(doneProcessing(QString,uint)), this, SLOT(doneProcessing(QString,uint)));
        connect(fileCRC, SIGNAL(errorRaised(QString)), this, SLOT(errorRaised(QString)));
        connect(fileCRC, SIGNAL(progress(QString,int)), this, SLOT(progress(QString,int)));

        // queue input files
        QThreadPool::globalInstance()->start(fileCRC);
    }
}

void MainWindow::on_clearItemsButton_clicked()
{
    ui->filesTable->clearContents();
    ui->filesTable->setRowCount(0);
    m_fileNames.clear();
}

void MainWindow::on_deleteItemButton_clicked()
{
    auto items = ui->filesTable->selectedItems();
    QList<int> idxToDelete;

    foreach(QTableWidgetItem* item, items)
    {
        if (!idxToDelete.contains(item->row()))
        {
            int row = item->row();
            idxToDelete.push_back(row);
            ui->filesTable->removeRow(0);
        }
    }
}

void MainWindow::on_exportResultsButton_clicked()
{
    QMessageBox::information(this, "TODO", "Not yet implemented");
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    foreach (const QUrl &url, event->mimeData()->urls())
    {
        const QString &fileName = url.toLocalFile();
        addNewRow(fileName, ui->filesTable);
        m_fileNames.push_back(fileName);
    }
}
