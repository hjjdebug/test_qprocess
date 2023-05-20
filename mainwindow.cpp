#include "mainwindow.h"  
#include <QPushButton>

	MainWindow::MainWindow(QWidget *parent)  
: QMainWindow(parent)  
{  
	QPushButton *bt = new QPushButton("execute", this);  
	connect(bt, SIGNAL(clicked()), this, SLOT(openProcess()));  
}  

MainWindow::~MainWindow()  
{  

	disconnect(m_process,SIGNAL(readyReadStandardOutput()),this,SLOT(slotRead()));
	disconnect(m_process,SIGNAL(readyReadStandardError()),this,SLOT(slotReadError()));
	m_process->close();
	delete m_process;
	printf("MainWindow destructure!\n");
}  

void MainWindow::openProcess()  
{  
	m_process = new QProcess(this);  
	printf("open process!\n");
	printf("state0:%d\n",m_process->state()); // 此时状态是0, NotRunning
//	QStringList list;
//	//北京卫视
//	list << "udp://239.3.1.241:8000";
//	p->start("/home/hjj/multiview/multiview");  
//	m_process->start("/home/hjj/multiview/demux_info",list);
	m_process->start("ffmpeg -y -i udp://239.3.1.241:8000 -c copy 1.ts");
	printf("state1:%d\n",m_process->state()); //此时状态是1, Starting,
//#define _WANT_READ_INFO
#ifdef _WANT_READ_INFO
	connect(m_process,SIGNAL(readyReadStandardOutput()),this,SLOT(slotRead()));
	connect(m_process,SIGNAL(readyReadStandardError()),this,SLOT(slotReadError()));
#else
	//,关闭通道读写,免得引起内存不断增长.
	m_process->closeReadChannel(QProcess::StandardOutput);	
	m_process->closeReadChannel(QProcess::StandardError);
	m_process->closeWriteChannel();
#endif
	printf("state2:%d\n",m_process->state());  //此时状态是1, Starting,
	printf("open process over!\n");
}

void MainWindow::slotRead()
{
	
	QByteArray array=m_process->readAllStandardOutput();
	qDebug()<<"out:"<<array;
}

void MainWindow::slotReadError()
{
	QByteArray array=m_process->readAllStandardError();
	qDebug()<<"err:"<<array;
//	printf("state3:%d\n",m_process->state()); //此时状态是2, Running
}
