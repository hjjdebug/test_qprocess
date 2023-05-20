#include <QApplication>
#include "mainwindow.h"

QApplication* gApp; 
int main(int argc, char *argv[])
{
	gApp = new QApplication(argc, argv);
	MainWindow mainw;
	mainw.show();
	return gApp->exec();
}
