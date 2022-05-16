#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <diskmonitor.h>
#include <drawchart.h>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_listWidget_currentItemChanged();

	void on_radioButton_clicked();

	void on_radioButton_2_clicked();

	void on_radioButton_3_clicked();

	void timerTimeOut();

	void on_comboBox_currentIndexChanged(int index);

signals:
	void changedSelectedItem();

private:
	Ui::MainWindow *ui;
	DiskMonitor *diskMonitor;
	mon::AllDiskResponse diskResponse;
	int mode = 1;
	void GetDiskBPS(std::string diskName);
	void GetDiskIOPS(std::string diskName);
	void GetDiskRequestSizeInBytesPerRead(std::string diskName);
	void readData();
	QTimer *timer;
	DrawChart *chart;
	int cnt = 0;
};
#endif // MAINWINDOW_H
