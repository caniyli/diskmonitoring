#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	diskMonitor = new DiskMonitor("10.5.5.0:30561");
	diskResponse = diskMonitor->GetBPS();
	for (int i = 0; i < diskResponse.resp_size(); ++i) {
		ui->listWidget->addItem(
			QString::fromStdString(diskResponse.resp(i).name()));
	}
	ui->radioButton->setChecked(true);

	ui->label->hide();
	chart = new DrawChart();
	ui->frame_2->layout()->addWidget(chart);
	timer = new QTimer();
	timer->setInterval(1000);
	connect(timer, &QTimer::timeout, this, &MainWindow::timerTimeOut);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_listWidget_currentItemChanged()
{

	if (!timer->isActive())
		timer->start();

	if (mode == 1)
		chart->setChartName("BPS/" + ui->listWidget->currentItem()->text());
	else if (mode == 2)
		chart->setChartName("IOPS/" + ui->listWidget->currentItem()->text());
	else
		chart->setChartName("DiskRequestSizeInBytesPerRead/" +
							ui->listWidget->currentItem()->text());

	readData();
}

void MainWindow::on_radioButton_clicked()
{

	if (mode != 1) {
		mode = 1;
		GetDiskBPS(ui->listWidget->currentItem()->text().toStdString());
		chart->setChartName("BPS/" + ui->listWidget->currentItem()->text());
	}
}

void MainWindow::on_radioButton_2_clicked()
{
	if (mode != 2) {
		mode = 2;
		GetDiskIOPS(ui->listWidget->currentItem()->text().toStdString());
		chart->setChartName("IOPS/" + ui->listWidget->currentItem()->text());
	}
}

void MainWindow::on_radioButton_3_clicked()
{
	if (mode != 3) {
		mode = 3;
		GetDiskRequestSizeInBytesPerRead(
			ui->listWidget->currentItem()->text().toStdString());
		chart->setChartName("DiskRequestSizeInBytesPerRead/" +
							ui->listWidget->currentItem()->text());
	}
}

void MainWindow::timerTimeOut()
{
	readData();
}

void MainWindow::GetDiskBPS(std::string diskName)
{
	int r = diskMonitor->GetDiskBPS(diskName).value().r();
	int rw = diskMonitor->GetDiskBPS(diskName).value().rw();
	int w = diskMonitor->GetDiskBPS(diskName).value().w();
	ui->label->setText("r = " + QString::number(r) + "\n" +
					   "rw = " + QString::number(rw) + "\n" +
					   "w = " + QString::number(w));

	chart->append((float)r, (float)rw, (float)w);
}

void MainWindow::GetDiskIOPS(std::string diskName)
{
	int r = diskMonitor->GetDiskIOPS(diskName).value().r();
	int rw = diskMonitor->GetDiskIOPS(diskName).value().rw();
	int w = diskMonitor->GetDiskIOPS(diskName).value().w();
	ui->label->setText("r = " + QString::number(r) + "\n" +
					   "rw = " + QString::number(rw) + "\n" +
					   "w = " + QString::number(w));
	chart->append((float)r, (float)rw, (float)w);
}

void MainWindow::GetDiskRequestSizeInBytesPerRead(std::string diskName)
{
	int r = diskMonitor->GetDiskRequestSizeInBytesPerRead(diskName).value().r();
	int rw =
		diskMonitor->GetDiskRequestSizeInBytesPerRead(diskName).value().rw();
	int w = diskMonitor->GetDiskRequestSizeInBytesPerRead(diskName).value().w();
	ui->label->setText("r = " + QString::number(r) + "\n" +
					   "rw = " + QString::number(rw) + "\n" +
					   "w = " + QString::number(w));
	chart->append((float)r, (float)rw, (float)w);
}

void MainWindow::readData()
{
	if (mode == 1)
		GetDiskBPS(ui->listWidget->currentItem()->text().toStdString());
	else if (mode == 2)
		GetDiskIOPS(ui->listWidget->currentItem()->text().toStdString());
	else
		GetDiskRequestSizeInBytesPerRead(
			ui->listWidget->currentItem()->text().toStdString());
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
	chart->setUnit(index);
}
