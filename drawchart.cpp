#include "drawchart.h"

DrawChart::DrawChart(QWidget *parent) : QWidget {parent}
{
	setLayout(new QVBoxLayout);

	series = new QLineSeries();
	series1 = new QLineSeries();
	series2 = new QLineSeries();
	chart = new QChart();

	chart->legend()->hide();
	series->setName("R");
	series1->setName("RW");
	series2->setName("W");
	chart->legend()->setVisible(true);
	chart->addSeries(series);
	chart->addSeries(series1);
	chart->addSeries(series2);
	chart->legend()->setAlignment(Qt::AlignBottom);

	QDateTimeAxis *axisX = new QDateTimeAxis;
	axisX->setTickCount(10);
	axisX->setFormat("hh:mm:ss");
	axisX->setTitleText("Date");
	chart->addAxis(axisX, Qt::AlignBottom);
	series->attachAxis(axisX);
	series1->attachAxis(axisX);
	series2->attachAxis(axisX);

	QValueAxis *axisY = new QValueAxis;
	axisY->setLabelFormat("%d");
	axisY->setTitleText("Bayt");
	chart->addAxis(axisY, Qt::AlignLeft);
	series->attachAxis(axisY);
	series1->attachAxis(axisY);
	series2->attachAxis(axisY);

	chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);
	chartView->setRubberBand(QChartView::HorizontalRubberBand);
	chartView->setRubberBand(QChartView::VerticalRubberBand);
	layout()->addWidget(chartView);
}

void DrawChart::append(float r, float rw, float w)
{
	for (int i = 0; i < unit; i++) {
		r = r / (1024 * unit);
		rw = rw / (1024 * unit);
		w = w / (1024 * unit);
	}

	series->append(QDateTime::currentDateTime().toMSecsSinceEpoch(), r);
	series1->append(QDateTime::currentDateTime().toMSecsSinceEpoch(), rw);
	series2->append(QDateTime::currentDateTime().toMSecsSinceEpoch(), w);
	cnt++;
	chart->axisX()->setMin(QDateTime::currentDateTime().addSecs(-30));
	chart->axisX()->setMax(QDateTime::currentDateTime().addSecs(30));
	if (r > maxValue)
		maxValue = r;
	if (rw > maxValue)
		maxValue = rw;
	if (w > maxValue)
		maxValue = w;

	if (unit == 0) {
		chart->axisY()->setMax(maxValue + 1000);
	} else if (unit == 1) {
		chart->axisY()->setMax(maxValue + 10);
	} else if (unit == 2) {
		chart->axisY()->setMax(maxValue + 1);
	} else
		chart->axisY()->setMax(maxValue + 0);
}

void DrawChart::clearSeries()
{
	series->clear();
	series1->clear();
	series2->clear();
	maxValue = 0;
}

void DrawChart::setChartName(const QString &newChartName)
{
	chart->setTitle(newChartName);
	clearSeries();
}

void DrawChart::setUnit(int newUnit)
{
	clearSeries();
	unit = newUnit;
	if (unit == 0) {
        chart->axisY()->setTitleText("Bayt");
	} else if (unit == 1) {
        chart->axisY()->setTitleText("Kilobayt");
	} else if (unit == 2) {
        chart->axisY()->setTitleText("Megabayt");
	} else
        chart->axisY()->setTitleText("Gigabayt");
}
