/****************************************************************************
** Skander calc project V1.0
** main.cpp
**
** Copyright (C) 2008 Skander Jabouzi (Skander Software Solutions).
** Contact: skander@skanderjabouzi.com or jabouzi@gmail.com
**
** This file is part of the Skander calc open source software.
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU
** General Public License versions 2.0 or 3.0 as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file.  Please review the following information
** to ensure GNU General Public Licensing requirements will be met:
** http://www.fsf.org/licensing/licenses/info/GPLv2.html and
** http://www.gnu.org/copyleft/gpl.html.  In addition, as a special
** exception, Nokia gives you certain additional rights. These rights
** are described in the Nokia Qt GPL Exception version 1.3, included in
** the file GPL_EXCEPTION.txt in this package.
**
***************************************************************************/

#include <QApplication>
#include <QCleanlooksStyle>
#include "mainwindowimpl.h"
#include "dsingleapplication.h"
//
int main(int argc, char ** argv)
{
	QApplication app( argc, argv );
	
	DSingleApplication instance( "CALC" );
  
	  if ( instance.isRunning() ) {
	    instance.sendMessage( "Hey, i'm the other instance" );
	    return 0;
	}
	//QPixmap pixmap("images/splash.png");
	//QSplashScreen splash(pixmap);
	//splash.show();
	//app.processEvents();
	//Q_INIT_RESOURCE(calc);
	if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"),
                              QObject::tr("I couldn't detect any system tray "
                                          "on this system."));
        return 1;
    }
	MainWindowImpl win;	
	win.show(); 
	//splash.finish(&win);
	//app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );	
	QApplication::setQuitOnLastWindowClosed(false);
	//QApplication::setStyle(new QCleanlooksStyle);
	return app.exec();
}
