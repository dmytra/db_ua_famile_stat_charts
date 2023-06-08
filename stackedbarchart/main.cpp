#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtSql>

#define DEBUG

QT_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ///////// DB for SQLite open FIRST! /////////
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setDatabaseName("sqlite.db");
      db.setDatabaseName(":memory:");

    if (db.open()) {

            {
                #ifdef DEBUG
                        qDebug() << "OK" << db.isValid() << db.lastError().text();
                #endif
            }

        QSqlQuery query(db);
        query.exec("CREATE TABLE db_ua_man ("
                   " man_id INTEGER PRIMARY KEY,"
                   " man_id_famil TEXT NOT NULL UNIQUE REFERENCES man_id );");

        QFile file(":/popularnist-prizvis_in_ua"); // https://sites.google.com/site/uaname/popularnist-prizvis
        file.open(QIODevice::ReadOnly | QIODevice::Text);

        if(file.exists())
        {
                        {
                        #ifdef DEBUG
                                    qDebug() << "file exist";
                        #endif
                        }

            int i= 1;
            while (!file.atEnd()) {
                QString line = file.readLine();
                if (line != "\n")
                {
                    QString str_query = "INSERT INTO db_ua_man (man_id, man_id_famil) "
                                        "VALUES (" +  QString::number(i) + ", '" + line + "');";
                    query.exec(str_query);  // qDebug() << str_query;
                    i++;
                }
            }
        }
        file.close();

                    {
                    #ifdef DEBUG
                            qDebug()  <<  query.exec("SELECT man_id  FROM db_ua_man") << " | " << query.exec("SELECT man_id_famil  FROM db_ua_man") ;
                    #endif
                    }
    }
    int alphabet[33] = {0};
    //if (db.open()) {
        QSqlQuery query(db);
        query.exec("SELECT * FROM db_ua_man");
        while (query.next()) {
            // QString man_id = query.value(0).toString();
            QString man_id_famil = query.value(1).toString();

                    {
                    #ifdef DEBUG
                                qDebug() << man_id_famil[0].unicode() << man_id_famil.size();
                    #endif
                    }

            for (int j = 0; j < man_id_famil.size(); j++ ) {
                switch (man_id_famil[j].unicode())
                {
                case    0x0410:     //'А':
                    alphabet[0]++;
                    break;
                case 	0x0411:     //'Б':
                    alphabet[1]++;
                    break;
                case    0x0412:     //'В':
                    alphabet[2]++;
                    break;
                case    0x0413:     //'Г':
                    alphabet[3]++;
                    break;
                case    0x0490:     //'Ґ':
                    alphabet[4]++;
                    break;
                case    0x0414:     //'Д':
                    alphabet[5]++;
                    break;
                case    0x0415:     //'Е':
                    alphabet[6]++;
                    break;
//                case    0x0401:     //'Ё':
//                    alphabet[6]++;
//                    break;
                case    0x0404:     //'Є':
                    alphabet[7]++;
                    break;
                case    0x0416:     //'Ж':
                    alphabet[8]++;
                    break;
                case    0x0417:     //'З':
                    alphabet[9]++;
                    break;
                case    0x0418:     //'И':
                    alphabet[10]++;
                    break;
                case    0x0406:     //'І':
                    alphabet[11]++;;
                    break;
                case    0x0407:     //'Ї':
                    alphabet[12]++;
                    break;
                case    0x0419:     //'Й':
                    alphabet[13]++;
                    break;
                case    0x041A:     //'К':
                    alphabet[14]++;
                    break;
                case    0x041B:     //'Л':
                    alphabet[15]++;
                    break;
                case    0x041C:     //'М':
                    alphabet[16]++;
                    break;
                case    0x041D:     //'Н':
                    alphabet[17]++;
                    break;
                case    0x041E:     //'О':
                    alphabet[18]++;
                    break;
                case    0x041F:     //'П':
                    alphabet[19]++;
                    break;
                case    0x0420:     //'Р':
                    alphabet[20]++;
                    break;
                case    0x0421:     //'С':
                    alphabet[21]++;
                    break;
                case    0x0422:     //'Т':
                    alphabet[22]++;
                    break;
                case    0x0423:     //'У':
                    alphabet[23]++;
                    break;
                case    0x0424:     //'Ф':
                    alphabet[24]++;
                    break;
                case    0x0425:     //'Х':
                    alphabet[25]++;
                    break;
                case    0x0426:     //'Ц':
                    alphabet[26]++;
                    break;
                case    0x0427:     //'Ч':
                    alphabet[27]++;
                    break;
                case    0x0428:     //'Ш':
                    alphabet[28]++;
                    break;
                case    0x0429:     //'Щ':
                    alphabet[29]++;
                    break;
//                case    0x042A:     //'Ъ':
//                    alphabet[27]++;
//                    break;
//                case    0x042B:     //'Ы':
//                    alphabet[28]++;
//                    break;
                case    0x042C:     //'Ь':
                    alphabet[30]++;
                    break;
//                case    0x042D:     //'Э':
//                    alphabet[30]++;
//                    break;
                case    0x042E:     //'Ю':
                    alphabet[31]++;
                    break;
                case    0x042F:     //'Я':
                    alphabet[32]++;
                    break;
//                case    0x040E:     //'Ў':
//                    alphabet[17]++;
//                    break;
//                case    0x040B:    //'Ћ':
//                    alphabet[17]++;
//                    break;

                default:
                    break;
                }
            }

            {
            #ifdef DEBUG
                        qDebug()  << query.value(0).toString() << query.value(1).toString();
            #endif
            }
        }


    QBarSet *set[32]; // https://uk.wikipedia.org/wiki/Українська_абетка
//А а, Б б, В в, Г г, Ґ ґ, Д д, Е е, Є є, Ж ж, З з, И и, І і, Ї ї, Й й, К к, Л л,
// М м, Н н, О о, П п, Р р, С с, Т т, У у, Ф ф, Х х, Ц ц, Ч ч, Ш ш, Щ щ, ь, Ю ю, Я я
    set[0]  = new QBarSet("A");
    set[1]  = new QBarSet("Б");
    set[2]  = new QBarSet("В");
    set[3]  = new QBarSet("Г");
    set[4]  = new QBarSet("Ґ");
    set[5]  = new QBarSet("Д");
    set[6]  = new QBarSet("Е");
    set[7]  = new QBarSet("Є");
    set[8]  = new QBarSet("Ж");
    set[9]  = new QBarSet("З");
    set[10] = new QBarSet("И");
    set[11] = new QBarSet("І");
    set[12] = new QBarSet("Ї");
    set[13] = new QBarSet("Й");
    set[14] = new QBarSet("К");
    set[15] = new QBarSet("Л");
    set[16] = new QBarSet("М");
    set[17] = new QBarSet("Н");
    set[18] = new QBarSet("О");
    set[19] = new QBarSet("П");
    set[20] = new QBarSet("Р");
    set[21] = new QBarSet("С");
    set[22] = new QBarSet("Т");
    set[23] = new QBarSet("У");
    set[24] = new QBarSet("Ф");
    set[25] = new QBarSet("Х");
    set[26] = new QBarSet("Ц");
    set[27] = new QBarSet("Ч");
    set[28] = new QBarSet("Ш");
    set[29] = new QBarSet("Щ");
    set[30] = new QBarSet("Ь");
    set[31] = new QBarSet("Ю");
    set[32] = new QBarSet("Я");

    *set[0] << alphabet[0] <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0;
    *set[1]<< 0 << alphabet[1] <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0;
    *set[2]<< 0 <<0 << alphabet[2] <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0;
    *set[3]<< 0 <<0 <<0 << alphabet[3] <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0;
    *set[4]<< 0 <<0 <<0 <<0 << alphabet[4] <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0;
    *set[5]<< 0 <<0 <<0 <<0 <<0 <<alphabet[5] <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0;
    *set[6]<< 0 <<0 <<0 <<0 <<0 <<0 <<alphabet[6] <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0;
    *set[7]<< 0 <<0 <<0 <<0 <<0 <<0 <<0 <<alphabet[7] <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0;;
    *set[8]<< 0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<alphabet[8] <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0;
    *set[9]<< 0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<alphabet[9] <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0;
    *set[10]<< 0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<alphabet[10] <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0;
    *set[11]<< 0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<alphabet[11] <<0 <<0 <<0 <<0 <<0 <<0 <<0;;
    *set[12]<< 0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<alphabet[12] <<0 <<0 <<0 <<0 <<0 <<0;
    *set[13]<< 0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<alphabet[13] <<0 <<0 <<0 <<0 <<0;
    *set[14]<< 0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<alphabet[14] <<0 <<0 <<0 <<0;
    *set[15]<< 0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<alphabet[15] <<0 <<0 <<0;
    *set[16]<< 0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<alphabet[16] <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0;
    *set[17]<< 0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<alphabet[17] <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0;
    *set[18]<< 0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<alphabet[18] <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0;
    *set[19]<< 0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<alphabet[19] <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0;
    *set[20]<< 0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<alphabet[20] <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0;
    *set[21]<< 0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<alphabet[21] <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0;
    *set[22]<< 0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<alphabet[22] <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0;
    *set[23]<< 0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<alphabet[23] <<0 <<0 <<0 <<0 <<0 <<0 <<0;
    *set[24]<< 0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<alphabet[24] <<0 <<0 <<0 <<0 <<0 <<0;
    *set[25]<< 0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<alphabet[25] <<0 <<0 <<0 <<0 <<0;
    *set[26]<< 0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<alphabet[26] <<0 <<0 <<0 <<0;
    *set[27]<< 0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<alphabet[27] <<0 <<0 <<0;
    *set[28]<< 0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<alphabet[28] <<0 <<0;
    *set[29]<< 0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<alphabet[29] <<0;
    *set[30]<< 0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<alphabet[30];
    *set[31]<< 0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 << alphabet[31];
    *set[32]<< 0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 <<0 << alphabet[32];


    QStackedBarSeries *series = new QStackedBarSeries();
    series->append(set[0]);
    series->append(set[1]);
    series->append(set[2]);
    series->append(set[3]);
    series->append(set[4]);
    series->append(set[5]);
    series->append(set[6]);
    series->append(set[7]);
    series->append(set[8]);
    series->append(set[9]);
    series->append(set[10]);
    series->append(set[11]);
    series->append(set[12]);
    series->append(set[13]);
    series->append(set[14]);
    series->append(set[15]);
    series->append(set[16]);
    series->append(set[17]);
    series->append(set[18]);
    series->append(set[19]);
    series->append(set[20]);
    series->append(set[21]);
    series->append(set[22]);
    series->append(set[23]);
    series->append(set[24]);
    series->append(set[25]);
    series->append(set[26]);
    series->append(set[27]);
    series->append(set[28]);
    series->append(set[29]);
    series->append(set[30]);
    series->append(set[31]);
    series->append(set[32]);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("простой частоний анализ");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "А"<<"Б"<<"В"<<"Г"<<"Ґ"<<"Д"<<"Е"<<"Є"<<"Ж"<<"З"<<"И"<<"І"<<"Ї"<< "Й"<< "К"<< "Л"<<"М"<<"Н"<<"О"<<"П"<<"Р"<<"С"<<"Т"<<"У"<<"Ф"<<"Х"<<"Ц"<<"Ч"<<"Ш"<<"Щ"<<"ь"<<"Ю"<<"Я";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QWidget      wgt;
    QGridLayout* pgrdLayout = new QGridLayout;
    pgrdLayout->addWidget(chartView, 0, 0,1,32);


    QLabel *setLabelName[32];
    for(int i=0; i<32;i++) {
                        setLabelName[i]  = new QLabel(categories[i]); }

    for(int i=0; i<32;i++)  {
                        pgrdLayout->addWidget(setLabelName[i], 1, i,1,1);
    setLabelName[i]->setStyleSheet( "font-weight: bold; font-size: 12pt;");
    }

    QLabel *setLabel[32];
    for(int i=0; i<32;i++) {
                        setLabel[i]  = new QLabel(QString::number( alphabet[i]) );
    setLabel[i]->setStyleSheet( " font-size: 8pt;");
    }

    for(int i=0; i<32;i++)  {
                        pgrdLayout->addWidget(setLabel[i], 2, i,1,1); }

    wgt.setLayout(pgrdLayout);
    wgt.resize(620, 600);

    wgt.show();

    return a.exec();
}

