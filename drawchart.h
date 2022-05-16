#ifndef DRAWCHART_H
#define DRAWCHART_H

#include <QVBoxLayout>
#include <QWidget>

#include <QLineSeries>
#include <QtCharts/QChartView>
#include <QtCharts>

class DrawChart : public QWidget
{
	Q_OBJECT
public:
	explicit DrawChart(QWidget *parent = nullptr);
	void append(float r, float rw, float w);
	void clearSeries();

	void setChartName(const QString &newChartName);

	void setUnit(int newUnit);

signals:
private:
	QLineSeries *series;
	QLineSeries *series1;
	QLineSeries *series2;
	QChart *chart;
	QChartView *chartView;
	int cnt = 0;
	int maxValue = 0;
	int unit = 0;
	QString chartName;
};

#endif // DRAWCHART_H
