/****************************************************************************
 ** This file is part of the MAIA® (Malagasy Artificial Intelligence Art) Open Project V2.0.
 **
 ** Copyright (C) 2012 ANDRIAMILAMINA Monge.
 ** All rights reserved.
 **
 ** License: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007.
 ** Author:  ANDRIAMILAMINA Monge.
 ** Contact: mongemilamina@gmail.com / +261 32 04 309 92.
 ** Year:    2012.
 ** Status:  Student in ISGEI, Madagasikara, Antananarivo.
 ** Domain:  Automatic.
 **
 ** Commercial Usage
 ** Please contact MAIA®.
 **
 ** GNU General Public License Usage
 ** This file may be used under the terms of the GNU
 ** General Public License version 3.0 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.GPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU General Public License version 3.0 requirements will be
 ** met: http://www.gnu.org/copyleft/gpl.html.
 **
 ** If you have questions regarding the use of this file, please contact
 ** the Author.
 **
 ****************************************************************************/

#include "maiaresizer.hpp"
#include "ui_maiaresizer.h"

#include <QMessageBox>
#include <QCloseEvent>
#include <QDir>
#include <QDirIterator>
#include <QFileDialog>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QRgb>
#include <QFile>


MaiaResizer::MaiaResizer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MaiaResizer)
{
    ui->setupUi(this);

    myUrlLabel = new QLabel("<b><a href='https://www.confluenti.com'>" + tr("MAIA on the web") + "</a></b>", this);
    myUrlLabel->setToolTip(tr("Go to the MAIA website"));
    myUrlLabel->setStatusTip(tr("Go to the MAIA® website"));
    myUrlLabel->setOpenExternalLinks(true);

    myActionNew = new QAction(QIcon(":/qrc_icons/icons/MAIA_icon_New.png"), "", this);
    myActionNew->setIconText(tr("&New"));
    myActionNew->setStatusTip(tr("Begin a new operation"));

    myActionLauch = new QAction(QIcon(":/qrc_icons/icons/MAIA_icon_Lauch.png"), "", this);
    myActionLauch->setIconText(tr("&Lauch"));
    myActionLauch->setStatusTip(tr("Lauch operation"));

    myActionAboutAndHelp = new QAction(QIcon(":/qrc_icons/icons/MAIA_icon_About.png"), "", this);
    myActionAboutAndHelp->setIconText(tr("&About"));
    myActionAboutAndHelp->setStatusTip(tr("About and Help"));

    myActionQuit = new QAction(QIcon(":/qrc_icons/icons/MAIA_icon_Quit.png"), "", this);
    myActionQuit->setStatusTip(tr("Quit the application"));
    myActionQuit->setIconText(tr("&Quit"));

    ui->toolBar->addAction(myActionNew);
    ui->toolBar->addAction(myActionLauch);
    ui->toolBar->addAction(myActionAboutAndHelp);
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(myActionQuit);
    ui->toolBar->addSeparator();
    ui->toolBar->addWidget(myUrlLabel);

    ui->progressBar->reset();
    myActionLauch->setEnabled(false);
    ui->lab_counter->setText("-- / --");
    ui->lab_counter->setToolTip("File counter " "(" + ui->lab_counter->text() + ")");

    //########################################################
    connect(myActionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(myActionNew, SIGNAL(triggered()), this, SLOT(new_()));
    connect(ui->b_src, SIGNAL(clicked()), this, SLOT(browseSrc()));
    connect(myActionLauch, SIGNAL(triggered()), this, SLOT(lauch()));
    connect(myActionAboutAndHelp, SIGNAL(triggered()), this, SLOT(aboutAndHelp()));
    connect(ui->boxOperations, SIGNAL(currentIndexChanged(int)), this, SLOT(handleResizeUi()));
    //########################################################
}
//########################################################
void MaiaResizer::aboutAndHelp()
{
    myAboutText = new QTextEdit(this);//create a textEdit object for about dialog
    myAboutText->setReadOnly(true);
    myAboutText->setText("\tMAIA® Image Operator 1.2 is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version. \n\n\tMAIA® Image Operator is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details. \n\n\tYou should have received a copy of the GNU General Public License along with MAIA® Image Operator; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA");
    myHelpText = new QTextEdit(this);//create a textEdit object for help dialog
    myHelpText->setReadOnly(true);
    myHelpText->setText("MAIA® Image Operator 1.2 helps you to operate on images in a folder and it's subfolders.\n\nYou just have to select an operation and select the appropriate parameters according to what you want to do.\n\nAuthor: ANDRIAMILAMINA Monge.\nE-mail: mongemilamina@gmail.com.");

    myTabWidget = new QTabWidget();//no parent, so this is gonna have its own window
    myTabWidget->setWindowFlags(Qt::WindowStaysOnTopHint);//make the tabwidget above other application windows
    myTabWidget->setAttribute(Qt::WA_ShowModal, true);//make the TabWidget Modal
    myTabWidget->insertTab(1, myAboutText, QIcon(":/qrc_icons/icons/MAIA_icon_About.png"), tr("&About"));//adding the appropriate label to the tabBar, with its title
    myTabWidget->insertTab(1, myHelpText, QIcon(":/qrc_icons/icons/MAIA_icon_Help.png"), tr("&Help"));//adding the appropriate label to the tabBar, with its title

    myTabWidget->setWindowTitle(tr("MAIA® Image Operator 1.2, About and Help"));
    myTabWidget->setMinimumSize(500, 300);
    myTabWidget->show();
}
//########################################################
void MaiaResizer::closeEvent(QCloseEvent *ev)//wait for a QCloseEvent *ev signal sent by close button click
{
    if(ev->type() == QEvent::Close)
    {
        QMessageBox::StandardButton reponse;
        reponse = QMessageBox::warning(this, tr("MAIA® Image Operator 1.0"), tr("Quit the application?"), QMessageBox::Cancel | QMessageBox::Yes);
        if (reponse == QMessageBox::Cancel)
        {
            ev->ignore();
            if(this->isHidden())
                this->show();
        }
        else if (reponse == QMessageBox::Yes)
            this->close();
    }
}
//########################################################
void MaiaResizer::handleResizeUi()
{
    if (ui->boxOperations->currentIndex() != 1)//Resize operation
    {
        ui->lineWidth->setEnabled(false);
        ui->lineHeight->setEnabled(false);
    }
    else if (ui->boxOperations->currentIndex() == 1)//Not resize operation
    {
        ui->lineWidth->setEnabled(true);
        ui->lineWidth->selectAll();
        ui->lineHeight->setEnabled(true);
        ui->lineHeight->selectAll();
    }
}
//########################################################
void MaiaResizer::new_()
{
    ui->line_src->clear();
    ui->progressBar->reset();
    myActionLauch->setEnabled(false);
    ui->boxFilters->setCurrentIndex(0);
    ui->boxOperations->setCurrentIndex(0);
    ui->lab_counter->setText("-- / --");
}
//########################################################
void MaiaResizer::browseSrc()
{
    QFileDialog srcDialog;
    QString srcPath = srcDialog.getExistingDirectory(this, tr("Select source directory"), QDir::homePath());
    //QString srcPath = srcDialog.getExistingDirectory(this, tr("Select source directory"), "Oxygen-4.6");
    if (srcPath.isEmpty())
    {
        return;
    }
    ui->line_src->setText(srcPath);

    QStringList srcFilter, srcList;//create a string list for file type list
    srcFilter << ui->boxFilters->currentText();//put the extension filter from the boxFilter ui in the string list
    QDir srcDir(srcPath);//create a directory with its path
    srcDir.setNameFilters(srcFilter);//set the directory filter to string lit content

    QDirIterator itSrc(srcDir, QDirIterator::Subdirectories);//create a dir iterator with its directory and subdirectory, the dir is already filter
    int srcItem = 0;//int to store file counting
    while(itSrc.hasNext())//test if there are still some file
    {
        srcItem++;//increment item counter
        srcList << itSrc.next();//go to the next item, and put each file path in a string list
        ui->lab_counter->setText("0 / " + QString::number(srcItem, 10));//put the number onto a label
    }

    if (srcItem == 0)
    {
        QMessageBox::information(this, "Information...", "No " + ui->boxFilters->currentText() + " files found in the directory!");
        ui->lab_counter->setText("0 / 0");//put the number onto a label
        ui->lab_counter->setToolTip("File counter " "(" + ui->lab_counter->text() + ")");
        myActionLauch->setEnabled(false);
    }
    else if (srcItem != 0)
    {
        ui->lab_counter->setToolTip("File counter " "(" + ui->lab_counter->text() + ")");
        myActionLauch->setEnabled(true);
    }

    //    for (int i = 0; i < srcList.size(); i++)
    //    {
    //        ui->textEdit->append(QString::number(i+1, 10) + srcList.at(i));//from the begining to the end of the path string list, show them
    //    }
}
//########################################################
void MaiaResizer::lauch()
{
    myActionNew->setEnabled(false);
    myActionLauch->setEnabled(false);
    ui->b_src->setEnabled(false);

    ui->boxFilters->setEnabled(false);
    ui->boxOperations->setEnabled(false);
    ui->lineWidth->setEnabled(false);
    ui->lineHeight->setEnabled(false);

    ui->line_src->setReadOnly(true);

    //.................................................................
    //here, the program scans subfolders before choosing any operation
    QStringList srcFilter, srcList;//create a string list for file type list
    srcFilter << ui->boxFilters->currentText();//put the extension filter from the boxFilter ui in the string list
    QDir srcDir(ui->line_src->text());//create a directory with its path
    srcDir.setNameFilters(srcFilter);//set the directory filter to string lit content
    QDirIterator itSrc(srcDir, QDirIterator::Subdirectories);//create a dir iterator with its directory and subdirectory, the dir is already filter
    int srcItem = 0;//int to store file counting
    while(itSrc.hasNext())//test if there are still some file
    {
        srcItem++;//increment item counter
        srcList << itSrc.next();//go to the next item, and put each file path in a string list
    }
    int totalItem = srcList.size();

    //.................................................................
    //after operation, put back the widgets status

    QMessageBox beforeLauchBox;
    beforeLauchBox.setWindowTitle("MAIA® Image Operator");
    beforeLauchBox.setText("Information:");
    beforeLauchBox.setInformativeText("This operation will overwrite the source files. Please, back up your images before!");
    beforeLauchBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

    int clickedButton = beforeLauchBox.exec();
    if (clickedButton == QMessageBox::Cancel)
    {
        QMessageBox::information(this, "Information...", "Operation was canceled.");
        myActionNew->setEnabled(true);
        myActionLauch->setEnabled(true);
        ui->b_src->setEnabled(true);

        ui->boxFilters->setEnabled(true);
        ui->boxOperations->setEnabled(true);

        ui->line_src->setReadOnly(false);
        ui->lab_counter->setToolTip("File counter " "(" + ui->lab_counter->text() + ")");
        return;
    }
    else if (clickedButton == QMessageBox::Ok)
    {
        //call the rgb2Gray methode
        for (int i = 0; i < srcList.size(); i++)//test until reaching the Dir list size
        {
            //choose which operation to apply, according to the user's choise in the listbox ui
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            if (ui->boxOperations->currentIndex() == 0)//RGB2Gray operation
            {
                QImage convertedImage = this->rgb2Gray(srcList.at(i));//call a method to convert to grayscale and put it in a QImage
                //update the label counter value
                ui->lab_counter->setText(QString::number(i+1, 10) + " / "+ QString::number(srcItem, 10));//put the number onto a label
                //update the progress bar value
                ui->progressBar->setValue(((i+1) * 100) / totalItem);
                //saving the image
                QString fileName = srcList.at(i);//file name contain the current file at index i
                QFile savedFile(fileName);
                if (!savedFile.open(QIODevice::WriteOnly))//test if can write
                {
                    QMessageBox::critical(this, "Warning...", "Unable to write the converted image file!");
                    return;
                }
                //save the current pixmap to file name in an uncompressed png image file
                convertedImage.save(fileName, "PNG", 100);//write the image to the same path with the same name, practicaly overwite the source image
                //ui->boxFilters->currentText().right(3) --> get the current text from right and keep 3 char
                savedFile.close(); //close the file
            }
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            else if (ui->boxOperations->currentIndex() == 1)//resize operation
            {//call resize methode
                QImage resizedImage = this->resizeImg(srcList.at(i));//call a method to convert to grayscale and put it in a QImage
                //update the label counter value
                ui->lab_counter->setText(QString::number(i+1, 10) + " / "+ QString::number(srcItem, 10));//put the number onto a label
                //update the progress bar value
                ui->progressBar->setValue(((i+1) * 100) / totalItem);
                //saving the image
                QString fileName = srcList.at(i);//file name contain the current file at index i
                QFile savedFile(fileName);
                if (!savedFile.open(QIODevice::WriteOnly))//test if can write
                {
                    QMessageBox::critical(this, "Warning...", "Unable to write the converted image file!");
                    return;
                }
                //save the current pixmap to file name in an uncompressed png image file
                resizedImage.save(fileName, "PNG", 100);//write the image to the same path with the same name, practicaly overwite the source image
                //ui->boxFilters->currentText().right(3) --> get the current text from right and keep 3 char
                savedFile.close(); //close the file
             //after calling it, put width and height in editable mode
                ui->lineWidth->setEnabled(true);
                ui->lineWidth->setEnabled(false);
            }
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            else if (ui->boxOperations->currentIndex() == 2)//invert operation
            {//call invert methode
                QImage invertedImage = this->invertImg(srcList.at(i));//call a method to convert to grayscale and put it in a QImage
                //update the label counter value
                ui->lab_counter->setText(QString::number(i+1, 10) + " / "+ QString::number(srcItem, 10));//put the number onto a label
                //update the progress bar value
                ui->progressBar->setValue(((i+1) * 100) / totalItem);
                //saving the image
                QString fileName = srcList.at(i);//file name contain the current file at index i
                QFile savedFile(fileName);
                if (!savedFile.open(QIODevice::WriteOnly))//test if can write
                {
                    QMessageBox::critical(this, "Warning...", "Unable to write the converted image file!");
                    return;
                }
                //save the current pixmap to file name in an uncompressed png image file
                invertedImage.save(fileName, "PNG", 100);//write the image to the same path with the same name, practicaly overwite the source image
                //ui->boxFilters->currentText().right(3) --> get the current text from right and keep 3 char
                savedFile.close(); //close the file
            }
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        }
    }
    myActionNew->setEnabled(true);
    myActionLauch->setEnabled(true);
    ui->b_src->setEnabled(true);

    ui->boxFilters->setEnabled(true);
    ui->boxOperations->setEnabled(true);

    ui->line_src->setReadOnly(false);
    ui->lab_counter->setToolTip("File counter " "(" + ui->lab_counter->text() + ")");
}
//########################################################
QImage MaiaResizer::rgb2Gray(QString receivedRGB)
{
    //load the RGB image
    myRGBImage = new QImage(receivedRGB);//get the RGB image filename given by lauch methode
    myGrayImage = new QImage(myRGBImage->width(), myRGBImage->height(), QImage::Format_Indexed8);//convert the image
    //operation on the image
    QVector<QRgb> table(256);
    for (int pix = 0; pix < 256; pix++)
    {
        table[pix] = qRgb(pix, pix, pix);
    }
    myGrayImage->setColorTable(table);

    for (int w = 0; w < myRGBImage->width(); w++)
    {
        for (int h = 0; h < myRGBImage->height(); h++)
        {
            QRgb value = myRGBImage->pixel(w, h);
            myGrayImage->setPixel(w, h, qGray(value));
        }
    }
    return *myGrayImage;

}
//########################################################
QImage MaiaResizer::invertImg(QString receivedImg2Invert)
{
    myToInvertImage = new QImage(receivedImg2Invert);
    //invert the image
    myToInvertImage->invertPixels();
    return *myToInvertImage;
}
//########################################################
QImage MaiaResizer::resizeImg(QString receivedImg2Resize)
{
    //load the image
    int IntForScaledWidth = ui->lineWidth->text().toInt();
    int IntForScaledHeight = ui->lineHeight->text().toInt();
    myToResisedImage = new QImage(receivedImg2Resize);//get the RGB image filename given by lauch methode
    //resize the image
    myResizedImage = new QImage(myToResisedImage->scaled(IntForScaledWidth, IntForScaledHeight, Qt::KeepAspectRatio));
    return *myResizedImage;

}
//########################################################
MaiaResizer::~MaiaResizer()
{
    delete ui;
}
