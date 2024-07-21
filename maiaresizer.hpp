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

#ifndef MAIARESIZER_HPP
#define MAIARESIZER_HPP

#include <QMainWindow>
#include <QImage>
#include <QAction>
#include <QLabel>
#include <QTabWidget>
#include <QTextEdit>
#include <QLibrary>

namespace Ui {
class MaiaResizer;
}

class MaiaResizer : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MaiaResizer(QWidget *parent = 0);
    ~MaiaResizer();

private slots:
    void closeEvent(QCloseEvent *ev);
    void new_();
    void browseSrc();
    void lauch();
    void handleResizeUi();
    void aboutAndHelp();
    QImage rgb2Gray(QString receivedRGB);//receive the filename
    QImage resizeImg(QString receivedImg2Resize);//receive the filename
    QImage invertImg(QString receivedImg2Invert);//receive the filename
private:
    Ui::MaiaResizer *ui;
    QImage* myRGBImage;
    QImage* myGrayImage;

    QImage* myToResisedImage;
    QImage* myResizedImage;

    QImage* myToInvertImage;
    QImage* myInvertedImage;

    QLabel* myUrlLabel;
    QAction* myActionNew;
    QAction* myActionLauch;
    QAction* myActionAboutAndHelp;
    QAction* myActionQuit;
    QTabWidget* myTabWidget;
    QTextEdit* myAboutText;
    QTextEdit* myHelpText;

    QLibrary* libQtCore;
    QLibrary* libQtGui;
    QLibrary* libQtNetwork;
};

#endif // MAIARESIZER_HPP
