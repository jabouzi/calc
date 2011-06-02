/****************************************************************************
** Skander calc project V1.0
** mainwindowimpl.cpp
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

#include "mainwindowimpl.h"
//
MainWindowImpl::MainWindowImpl( QWidget * parent, Qt::WFlags f) 
	: QMainWindow(parent, f)
{
	setupUi(this);
	QDesktopWidget *desktop = QApplication::desktop();
    trayIcon = new QSystemTrayIcon(this);
	trayIconMenu = new QMenu(this);
	int screenWidth, width; 
	int screenHeight, height;
	int x, y;
	QSize windowSize;
	 
	screenWidth = desktop->width(); // get width of screen
	screenHeight = desktop->height(); // get height of screen
	 
	windowSize = size(); // size of our application window
	width = windowSize.width(); 
	height = windowSize.height();
	 
	// little computations
	x = (screenWidth - width) / 2;
	y = (screenHeight - height) / 2;
	y -= 50;
	 
	// move window to desired coordinates
	move ( x, y );
	this->result = 0;
	this->sign = '$';
	this->dotUsed = false;
	this->newNum = true;
	createActions();
	createTrayIcon();
	setVisible(true);
	
	lineEdit->setAlignment(Qt::AlignRight);
	
	Gfirst = true; 
	
	//create buttons actions
	connect(pushButton_0, SIGNAL(clicked()), this, SLOT(addText0()));
	connect(pushButton_1, SIGNAL(clicked()), this, SLOT(addText1()));
	connect(pushButton_2, SIGNAL(clicked()), this, SLOT(addText2()));
	connect(pushButton_3, SIGNAL(clicked()), this, SLOT(addText3()));
	connect(pushButton_4, SIGNAL(clicked()), this, SLOT(addText4()));
	connect(pushButton_5, SIGNAL(clicked()), this, SLOT(addText5()));
	connect(pushButton_6, SIGNAL(clicked()), this, SLOT(addText6()));
	connect(pushButton_7, SIGNAL(clicked()), this, SLOT(addText7()));
	connect(pushButton_8, SIGNAL(clicked()), this, SLOT(addText8()));
	connect(pushButton_9, SIGNAL(clicked()), this, SLOT(addText9()));	
	connect(pushButton_11, SIGNAL(clicked()), this, SLOT(addDot()));
	connect(pushButton_ce, SIGNAL(clicked()), this, SLOT(addClr()));
	connect(pushButton_bcksp, SIGNAL(clicked()), this, SLOT(backSpace()));
	connect(pushButton_min_plus, SIGNAL(clicked()), this, SLOT(min_plus()));
	connect(pushButton_1byx, SIGNAL(clicked()), this, SLOT(one_by_x()));
	connect(pushButton_plus, SIGNAL(clicked()), this, SLOT(add()));
	connect(pushButton_minus, SIGNAL(clicked()), this, SLOT(subs()));
	connect(pushButton_mult, SIGNAL(clicked()), this, SLOT(mult()));
	connect(pushButton_div, SIGNAL(clicked()), this, SLOT(div()));
	connect(pushButton_equal, SIGNAL(clicked()), this, SLOT(equal()));
	connect(pushButton_x_pwr_2, SIGNAL(clicked()), this, SLOT(power2()));
	connect(pushButton_sqrt, SIGNAL(clicked()), this, SLOT(root_square()));
	connect(pushButton_c, SIGNAL(clicked()), this, SLOT(clr()));
	connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

//Get the keyboard keys pressed events
void MainWindowImpl::keyPressEvent(QKeyEvent *event)
{
	QMainWindow::keyPressEvent(event);		
	switch (event->key()) {
		case Qt::Key_0:	// 0 button pressed and so on....		
			pushButton_0->animateClick(100);
			break;
		case Qt::Key_1:			
			pushButton_1->animateClick(100);
			break;
		case Qt::Key_2:			
			pushButton_2->animateClick(100);
			break;
		case Qt::Key_3:			
			pushButton_3->animateClick(100);
			break;
		case Qt::Key_4:			
			pushButton_4->animateClick(100);
			break;
		case Qt::Key_5:			
			pushButton_5->animateClick(100);
			break;
		case Qt::Key_6:			
			pushButton_6->animateClick(100);
			break;
		case Qt::Key_7:			
			pushButton_7->animateClick(100);
			break;
		case Qt::Key_8:			
			pushButton_8->animateClick(100);
			break;
		case Qt::Key_9:			
			pushButton_9->animateClick(100);
			break;
		case Qt::Key_Backspace:
			pushButton_bcksp->animateClick(100);
			break;
		case Qt::Key_Delete:
			pushButton_ce->animateClick(100);
			break;
		case Qt::Key_Period:
			pushButton_11->animateClick(100);
			break;		
		case Qt::Key_Escape:
			//hide();
			pushButton_ce->animateClick(100);	       	
			break;
		case Qt::Key_Enter:
			pushButton_equal->animateClick(100);			
			break;
		case Qt::Key_Equal:
			pushButton_equal->animateClick(100);			
			break;
		case Qt::Key_Minus:
			pushButton_minus->animateClick(100);
			break;
		case Qt::Key_Plus:
			pushButton_plus->animateClick(100);
			break;
		case Qt::Key_Asterisk:
			pushButton_mult->animateClick(100);
			break;
		case Qt::Key_Slash:
			pushButton_div->animateClick(100);
			break;
		case Qt::Key_plusminus:
			pushButton_min_plus->animateClick(100);
			break;
		default:
			QMainWindow::keyPressEvent(event);
	}
}

//Hide the window on closing the application
void MainWindowImpl::closeEvent(QCloseEvent *event)
{
	QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(1);
	if (Gfirst == true){
		trayIcon->showMessage("Information about this application", "skaCalc application is still runing", icon,10000);
		Gfirst = false;
	}
		
	hide();
	event->ignore();
}

//Action when the calc 0 button is clicked
void MainWindowImpl::addText0(){
	QString texte = lineEdit->text();
	if (this->newNum == true){
		lineEdit->setText("0");
		this->newNum = false;
	}
	else if (texte.isEmpty()) {
		lineEdit->insert("0");
	}
	else if (texte.length() >= 1 && texte != "0"){
		this->adjustDotPosition();
		lineEdit->insert("0");		
	}
	QString ttmessage = "Skander Calc V1.0\n" + lineEdit->text();	
	trayIcon->setToolTip(ttmessage);
}
	
//Action when the calc 1 button is clicked
void MainWindowImpl::addText1(){
	QString texte = lineEdit->text();
	if ((texte.length() == 1 && texte == "0") || this->newNum == true) {
		this->adjustDotPosition();
		lineEdit->setText("1");
		this->newNum = false;
	}
	else{
		this->adjustDotPosition();
		lineEdit->setText(lineEdit->text()+'1');
	}	
	QString ttmessage = "Skander Calc V1.0\n" + lineEdit->text();	
	trayIcon->setToolTip(ttmessage);
	trayIcon->show();
}
	
//Action when the calc 2 button is clicked
void MainWindowImpl::addText2(){
	QString texte = lineEdit->text();
	if ((texte.length() == 1 && texte == "0") || this->newNum == true) {
		this->adjustDotPosition();
		lineEdit->setText("2");
		this->newNum = false;
	}
	else{
		this->adjustDotPosition();
		lineEdit->setText(lineEdit->text()+'2');
	}	
	QString ttmessage = "Skander Calc V1.0\n" + lineEdit->text();	
	trayIcon->setToolTip(ttmessage);
}
	
//Action when the calc 3 button is clicked
void MainWindowImpl::addText3(){
	QString texte = lineEdit->text();
	if ((texte.length() == 1 && texte == "0") || this->newNum == true) {
		this->adjustDotPosition();
		lineEdit->setText("3");
		this->newNum = false;
	}
	else{
		this->adjustDotPosition();
		lineEdit->setText(lineEdit->text()+'3');
	}	
	QString ttmessage = "Skander Calc V1.0\n" + lineEdit->text();	
	trayIcon->setToolTip(ttmessage);
}
	
//Action when the calc 4 button is clicked
void MainWindowImpl::addText4(){
	QString texte = lineEdit->text();
	if ((texte.length() == 1 && texte == "0") || this->newNum == true) {
		this->adjustDotPosition();
		lineEdit->setText("4");
		this->newNum = false;
	}
	else{
		this->adjustDotPosition();
		lineEdit->setText(lineEdit->text()+'4');
	}	
	QString ttmessage = "Skander Calc V1.0\n" + lineEdit->text();	
	trayIcon->setToolTip(ttmessage);
}
	
//Action when the calc 5 button is clicked
void MainWindowImpl::addText5(){
	QString texte = lineEdit->text();
	if ((texte.length() == 1 && texte == "0") ||this->newNum == true) {
		this->adjustDotPosition();
		lineEdit->setText("5");
		this->newNum = false;
	}
	else{
		this->adjustDotPosition();
		lineEdit->setText(lineEdit->text()+'5');
	}	
	QString ttmessage = "Skander Calc V1.0\n" + lineEdit->text();	
	trayIcon->setToolTip(ttmessage);
}
	
//Action when the calc 6 button is clicked
void MainWindowImpl::addText6(){
	QString texte = lineEdit->text();
	if ((texte.length() == 1 && texte == "0") || this->newNum == true) {
		this->adjustDotPosition();
		lineEdit->setText("6");
		this->newNum = false;
	}
	else{
		this->adjustDotPosition();
		lineEdit->setText(lineEdit->text()+'6');
	}	
	QString ttmessage = "Skander Calc V1.0\n" + lineEdit->text();	
	trayIcon->setToolTip(ttmessage);
}
	
//Action when the calc 7 button is clicked
void MainWindowImpl::addText7(){
	QString texte = lineEdit->text();
	if ((texte.length() == 1 && texte == "0") || this->newNum == true) {
		this->adjustDotPosition();
		lineEdit->setText("7");
		this->newNum = false;
	}
	else{
		this->adjustDotPosition();
		lineEdit->setText(lineEdit->text()+'7');
	}	
	QString ttmessage = "Skander Calc V1.0\n" + lineEdit->text();	
	trayIcon->setToolTip(ttmessage);
}
	
//Action when the calc 8 button is clicked
void MainWindowImpl::addText8(){
	QString texte = lineEdit->text();
	if ((texte.length() == 1 && texte == "0") || this->newNum == true) {
		this->adjustDotPosition();
		lineEdit->setText("8");
		this->newNum = false;
	}
	else{
		this->adjustDotPosition();
		lineEdit->setText(lineEdit->text()+'8');
	}	
	QString ttmessage = "Skander Calc V1.0\n" + lineEdit->text();	
	trayIcon->setToolTip(ttmessage);
}
	
//Action when the calc 9 button is clicked
void MainWindowImpl::addText9(){
	QString texte = lineEdit->text();
	if ((texte.length() == 1 && texte == "0") || this->newNum == true) {
		this->adjustDotPosition();
		lineEdit->setText("9");
		this->newNum = false;
	}
	else{
		this->adjustDotPosition();
		lineEdit->insert("9");
	}	
	QString ttmessage = "Skander Calc V1.0\n" + lineEdit->text();	
	trayIcon->setToolTip(ttmessage);
}

//Action when the calc . button is clicked
void MainWindowImpl::addDot(){
	QString texte = lineEdit->text();
	if (!texte.contains('.')) {
		//if (lineEdit->text().isEmpty()){		
		if (this->newNum == true){
			texte = "0";
			texte.append(".");		
			this->dotUsed = true;
			this->newNum = false;
		}	
		else{				
			texte.append(".");	
			this->dotUsed = true;
		}
		lineEdit->setText(texte);
	}
	QString ttmessage = "Skander Calc V1.0\n" + lineEdit->text();	
	trayIcon->setToolTip(ttmessage);
}

//Action when the calc CE button is clicked
void MainWindowImpl::addClr(){		
	lineEdit->setText("0");	
	this->result = 0;
	this->sign = '$';
	QString ttmessage = "Skander Calc V1.0\n" + lineEdit->text();	
	trayIcon->setToolTip(ttmessage);
}

//Action when the calc C button is clicked
void MainWindowImpl::clr(){		
	lineEdit->setText("0");	
	QString ttmessage = "Skander Calc V1.0\n" + lineEdit->text();	
	trayIcon->setToolTip(ttmessage);
}

//Action when the calc BackSpace button is clicked
void MainWindowImpl::backSpace(){		
	lineEdit->backspace();	
	if (lineEdit->text().isEmpty() || lineEdit->text() == "-"){
		lineEdit->setText("0");	
	}	
	QString ttmessage = "Skander Calc V1.0\n" + lineEdit->text();	
	trayIcon->setToolTip(ttmessage);
}

//Action when the calc +/- button is clicked
void MainWindowImpl::min_plus(){		
	bool ok;
	double num = lineEdit->text().toDouble(&ok);
	if (ok){
		num = -num;
		//display->setText(cutZeros(QString::number(d, 'f', precision)));
		lineEdit->setText(QString::number(num));
	}	
	QString ttmessage = "Skander Calc V1.0\n" + lineEdit->text();	
	trayIcon->setToolTip(ttmessage);
}

//Action when the calc 1/x button is clicked
void MainWindowImpl::one_by_x(){
	bool ok;
	double num = lineEdit->text().toDouble(&ok);
	if (0 != num && ok){
		lineEdit->setText(QString::number(1/num));
	}
	else{
		this->newNum = true;
		lineEdit->setText("Err : Div by Zero");
	}	
	QString ttmessage = "Skander Calc V1.0\n" + lineEdit->text();	
	trayIcon->setToolTip(ttmessage);
}

//Action when the calc + button is clicked
void MainWindowImpl::add(){	
	bool ok;
	double temp = this->result;
	this->result = lineEdit->text().toDouble(&ok);
	if (ok){		
		this->checkSign(temp);			
		this->sign = '+';
		this->newNum = true;					
	}
	QString ttmessage = "Skander Calc V1.0\n" + lineEdit->text();	
	trayIcon->setToolTip(ttmessage);
}

//Action when the calc x button is clicked
void MainWindowImpl::mult(){
	bool ok;
	double temp = this->result;
	this->result = lineEdit->text().toDouble(&ok);
	if (ok){		
		this->checkSign(temp);			
		this->sign = '*';	
		this->newNum = true;				
	}	
	QString ttmessage = "Skander Calc V1.0\n" + lineEdit->text();	
	trayIcon->setToolTip(ttmessage);
}

//Action when the calc - button is clicked
void MainWindowImpl::subs(){
	bool ok;
	double temp = this->result;
	this->result = lineEdit->text().toDouble(&ok);
	if (ok){		
		this->checkSign(temp);			
		this->sign = '-';	
		this->newNum = true;				
	}		
	QString ttmessage = "Skander Calc V1.0\n" + lineEdit->text();	
	trayIcon->setToolTip(ttmessage);
}

//Action when the calc / button is clicked
void MainWindowImpl::div(){
	bool ok;
	double temp = this->result;
	this->result = lineEdit->text().toDouble(&ok);
	if (ok){		
		this->checkSign(temp);			
		this->sign = '/';
		this->newNum = true;					
	}	
	QString ttmessage = "Skander Calc V1.0\n" + lineEdit->text();	
	trayIcon->setToolTip(ttmessage);
}

//Action when the calc = button is clicked
void MainWindowImpl::equal(){
	bool ok;
	double temp = this->result;
	this->result = lineEdit->text().toDouble(&ok);
	if (ok){		
		this->checkSign(temp);			
		this->sign = '$';
		this->newNum = true;					
	}	
	QString ttmessage = "Skander Calc V1.0\n" + lineEdit->text();	
	trayIcon->setToolTip(ttmessage);
}

//Action when the calc x² button is clicked
void  MainWindowImpl::power2(){
	bool ok;
	double temp = lineEdit->text().toDouble(&ok);
	if (ok){		
		lineEdit->setText(QString::number(temp*temp));			
	}	
	QString ttmessage = "Skander Calc V1.0\n" + lineEdit->text();	
	trayIcon->setToolTip(ttmessage);
}

//Action when the calc root square button is clicked
void  MainWindowImpl::root_square(){
	bool ok;
	double temp = lineEdit->text().toDouble(&ok);
	if (ok){		
		lineEdit->setText(QString::number(sqrt(temp)));			
	}	
	QString ttmessage = "Skander Calc V1.0\n" + lineEdit->text();	
	trayIcon->setToolTip(ttmessage);
}

//Action when the copy menu is selected
void MainWindowImpl::_copy(){	
	lineEdit->selectAll();
	lineEdit->copy();
	lineEdit->deselect();
}

//Action when the past menu is selected
void MainWindowImpl::_paste(){
	lineEdit->setReadOnly(false);	
	lineEdit->setText("");
	lineEdit->paste();
	lineEdit->setReadOnly(true);
	QString ttmessage = "Skander Calc V1.0\n" + lineEdit->text();	
	trayIcon->setToolTip(ttmessage);
}

void MainWindowImpl::_about()
 {
    QMessageBox::about(this, tr("About Skander Calc"),
             tr("The <b>Skander Calc V1.0</b> Copyright © 2008 Skander Jabouzi skander@skanderjabouzi.com<br>"             
             	" This is a free software distributed under the terms of the GNU General Public License version 3\n(http://www.gnu.org/licenses/gpl-3.0.html)"));
 }

//Set the application menu actions
void MainWindowImpl::createActions()
{
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit())); 
    
    action_Close->setShortcut(tr("Ctrl+Q"));
    connect(action_Close, SIGNAL(triggered()), qApp, SLOT(quit()));
    
    action_Hide->setShortcut(tr("Ctrl+H"));
    connect(action_Hide, SIGNAL(triggered()), this, SLOT(hide()));
    
    action_Copy->setShortcut(tr("Ctrl+C"));
    connect(action_Copy, SIGNAL(triggered()), this, SLOT(_copy()));
    
    action_Paste->setShortcut(tr("Ctrl+V"));
    connect(action_Paste, SIGNAL(triggered()), this, SLOT(_paste())); 
    
    connect(action_About, SIGNAL(triggered()), this, SLOT(_about()));    
}

//Create the app tray icon
void MainWindowImpl::createTrayIcon()
{
	
	setWindowIcon(QIcon("images/calc.png"));
   
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(QIcon("images/calc.png"));
	QString ttmessage = "Skander Calc V1.0\n" + lineEdit->text();
	//QMessageBox::warning(this, tr("My Application"),lineEdit->text(),QMessageBox::Ok);	
    //trayIcon->setToolTip("Skander Calulator V1.0");
    trayIcon->setToolTip(ttmessage);

	trayIcon->show();	
}

//Set the tray click actions
void MainWindowImpl::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason) {
	case QSystemTrayIcon::Trigger:    
	case QSystemTrayIcon::MiddleClick:
		showNormal();
		break;
	default:
		;
	}
}

//Set the tray icon menu
void MainWindowImpl::setVisible(bool visible)
{
    minimizeAction->setEnabled(visible);
    //maximizeAction->setEnabled(!isMaximized());
    restoreAction->setEnabled(!visible);
    QMainWindow::setVisible(visible);
}

//Adjust the number when the '.' is added
void MainWindowImpl::adjustDotPosition(){
	if (this->dotUsed){
			this->dotUsed = false;
			lineEdit->setText(lineEdit->text().remove(QChar('.'), Qt::CaseInsensitive));
			lineEdit->insert(".");
	}
}

//Check the numer sign
void MainWindowImpl::checkSign(double temp){
	if ('-' == this->sign){
		this->result = temp - this->result;						
	}
	else if ('+' == this->sign){
		this->result = temp + this->result;
	}
	else if ('/' == this->sign){
		this->result = temp / this->result;
	}
	else if ('*' == this->sign){
		this->result = temp * this->result;
	}
	lineEdit->setText(QString::number(this->result));
}
//
