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

#include <QApplication>
#include "maiaresizer.hpp"

#include <QIcon>
#include <QSplashScreen>
#include <QPixmap>
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication myAppli(argc, argv);

    MaiaResizer myWindow;

    QPixmap mySplashPix(":/qrc_icons/icons/MAIA_Splash_Image_Operator.png");
    QSplashScreen mySplash(mySplashPix);
    mySplash.show();
    myAppli.processEvents();
    QThread::sleep(0.5);
    myAppli.processEvents();
    QThread::sleep(0.5);
    myAppli.processEvents();
    QThread::sleep(0.5);
    mySplash.close();

    myWindow.setWindowTitle("MAIA® Image Operator 1.2");
    myWindow.setWindowIcon(QIcon(":/qrc_icons/icons/MAIA_icon.png"));
    myWindow.setFixedSize(528, 140);
    myWindow.show();
    
    return myAppli.exec();
}
