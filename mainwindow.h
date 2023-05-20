#ifndef MAINWINDOW_H  
#define MAINWINDOW_H  

#include <QtGui>  
#include <QMainWindow>

class MainWindow : public QMainWindow  
{  
	Q_OBJECT  
public:  
	MainWindow(QWidget *parent = 0);  
	~MainWindow();  

private slots:  
	void openProcess();
	void slotRead();
	void slotReadError();

private:  
	QProcess *m_process;  
};  

#endif // MAINWINDOW_H 

