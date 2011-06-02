/****************************************************************************
** Skander calc project V1.0
** mainwindowimpl.h
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

#ifndef MAINWINDOWIMPL_H
#define MAINWINDOWIMPL_H
//
#include <QDialog>
#include <QtGui>
#include <QSystemTrayIcon>
#include <QMenu>
//#include <QIcon>

#include "ui_mainwindow.h"
//
class MainWindowImpl : public QMainWindow, public Ui::MainWindow
{
Q_OBJECT
public:	
	MainWindowImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
	
protected:
	void keyPressEvent(QKeyEvent *event);
	void closeEvent(QCloseEvent *event);
	 
private slots:	
	void addText0();
	void addText1();
	void addText2();
	void addText3();
	void addText4();
	void addText5();
	void addText6();
	void addText7();
	void addText8();
	void addText9();
	void addDot();
	void addClr();
	void clr();
	void backSpace();
	void add();
	void mult();
	void subs();
	void div();
	void equal();
	void min_plus();
	void one_by_x();
	void root_square();
	void power2();
	void iconActivated(QSystemTrayIcon::ActivationReason reason);
	void _copy();
	void _paste();
	void _about();
	
private:
	QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;
	QSystemTrayIcon *trayIcon;
	QMenu *trayIconMenu;
	void createActions();
	void createTrayIcon();
	void setVisible(bool);
	void adjustDotPosition();
	void checkSign(double);	
	bool dotUsed;
	double result;
	QChar sign;
	bool newNum;
	bool Gfirst; 
};
#endif




