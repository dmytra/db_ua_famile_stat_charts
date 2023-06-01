#include "tablewidget.h"
#include "customtablemodel.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTableView>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QVXYModelMapper>
#include <QtWidgets/QHeaderView>

QT_USE_NAMESPACE

TableWidget::TableWidget(QWidget *parent)
    : QWidget(parent)
{
    // create simple model for storing data
    // user's table data model
    CustomTableModel *model = new CustomTableModel;

    // create table view and add model to it
    QTableView *tableView = new QTableView;
    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QChart *chart = new QChart;
    chart->setAnimationOptions(QChart::AllAnimations);

    // series 1
    QLineSeries *series = new QLineSeries;
    series->setName("Line 1");
    QVXYModelMapper *mapper = new QVXYModelMapper(this);
    mapper->setXColumn(0);
    mapper->setYColumn(1);
    mapper->setSeries(series);
    mapper->setModel(model);
    chart->addSeries(series);

    // for storing color hex from the series
    QString seriesColorHex = "#000000";

    // get the color of the series and use it for showing the mapped area
    seriesColorHex = "#" + QString::number(series->pen().color().rgb(), 16).right(6).toUpper();
    model->addMapping(seriesColorHex, QRect(0, 0, 2, model->rowCount()));

//    // series 2
//    series = new QLineSeries;
//    series->setName("Line 2");

//    mapper = new QVXYModelMapper(this);
//    mapper->setXColumn(2);
//    mapper->setYColumn(3);
//    mapper->setSeries(series);
//    mapper->setModel(model);
//    chart->addSeries(series);

    // get the color of the series and use it for showing the mapped area
    seriesColorHex = "#" + QString::number(series->pen().color().rgb(), 16).right(6).toUpper();
    model->addMapping(seriesColorHex, QRect(2, 0, 2, model->rowCount()));

    chart->createDefaultAxes();
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(640, 480);

    // create main layout
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(tableView, 1, 0);
    mainLayout->addWidget(chartView, 1, 1);
    mainLayout->setColumnStretch(1, 1);
    mainLayout->setColumnStretch(0, 0);
    setLayout(mainLayout);
}
