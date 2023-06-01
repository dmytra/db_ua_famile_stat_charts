#include "customtablemodel.h"
#include <QtCore/QList>
#include <QtCore/QRandomGenerator>
#include <QtCore/QRect>
#include <QtGui/QColor>

#include <QtSql>

//#define DEBUG

CustomTableModel::CustomTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_columnCount = 2;
    m_rowCount = 32;

        ///////// DB for SQLite open FIRST! /////////
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("sqlite.db");

        if (db.open()) {
                    #ifdef DEBUG
                                qDebug() << "OK" << db.isValid() << db.lastError().text();
                    #endif//

            QSqlQuery query(db);
            query.exec("CREATE TABLE db_ua_man ("
                       " man_id INTEGER PRIMARY KEY,"
                       " man_id_famil TEXT NOT NULL UNIQUE REFERENCES man_id );");

            //QFile file(":/man");
            QFile file(":/popularnist-prizvis_in_ua"); // https://sites.google.com/site/uaname/popularnist-prizvis
            file.open(QIODevice::ReadOnly | QIODevice::Text);

            if(file.exists())
            {
                    #ifdef DEBUG
                                    qDebug() << "file exist";
                    #endif//
                //
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
                    #ifdef DEBUG
                                qDebug()  <<  query.exec("SELECT man_id  FROM db_ua_man") << " | " << query.exec("SELECT man_id_famil  FROM db_ua_man") ;
                    #endif
        }
        int alphabet[33] = {0};
        if (db.open()) {
        QSqlQuery query(db);
        query.exec("SELECT * FROM db_ua_man");
        while (query.next()) {
           // QString man_id = query.value(0).toString();
            QString man_id_famil = query.value(1).toString();

                #ifdef DEBUG
                qDebug() << man_id_famil[0].unicode() << man_id_famil.size();
                #endif

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
                    case    0x0414:     //'Д':
                        alphabet[4]++;
                        break;
                    case    0x0415:     //'Е':
                        alphabet[5]++;
                        break;
                    case    0x0401:     //'Ё':
                        alphabet[6]++;
                        break;
                    case    0x0416:     //'Ж':
                        alphabet[7]++;
                        break;
                    case    0x0417:     //'З':
                         alphabet[8]++;
                        break;
                    case    0x0418:     //'И':
                        alphabet[9]++;
                        break;
                    case    0x0419:     //'Й':
                        alphabet[10]++;
                        break;
                    case    0x041A:     //'К':
                        alphabet[11]++;
                        break;
                    case    0x041B:     //'Л':
                        alphabet[12]++;
                        break;
                    case    0x041C:     //'М':
                        alphabet[13]++;
                        break;
                    case    0x041D:     //'Н':
                        alphabet[14]++;
                        break;
                    case    0x041E:     //'О':
                        alphabet[15]++;
                        break;
                    case    0x041F:     //'П':
                        alphabet[16]++;
                        break;
                    case    0x0420:     //'Р':
                        alphabet[17]++;
                        break;
                    case    0x0421:     //'С':
                        alphabet[18]++;
                        break;
                    case    0x0422:     //'Т':
                        alphabet[19]++;
                        break;
                    case    0x0423:     //'У':
                        alphabet[20]++;
                        break;
                    case    0x0424:     //'Ф':
                        alphabet[21]++;
                        break;
                    case    0x0425:     //'Х':
                        alphabet[22]++;
                        break;
                    case    0x0426:     //'Ц':
                        alphabet[23]++;
                        break;
                    case    0x0427:     //'Ч':
                        alphabet[24]++;
                        break;
                    case    0x0428:     //'Ш':
                        alphabet[25]++;
                        break;
                    case    0x0429:     //'Щ':
                        alphabet[26]++;
                        break;
                    case    0x042A:     //'Ъ':
                        alphabet[27]++;
                        break;
                    case    0x042B:     //'Ы':
                        alphabet[28]++;
                        break;
                    case    0x042C:     //'Ь':
                        alphabet[29]++;
                        break;
                    case    0x042D:     //'Э':
                        alphabet[30]++;
                        break;
                    case    0x042E:     //'Ю':
                        alphabet[31]++;
                        break;
                    case    0x042F:     //'Я':
                        alphabet[32]++;
                        break;
//                    case    0x0404:     //'Є':
//                        alphabet[17]++;
//                        break;
//                    case    0x0407:     //'Ї':
//                        alphabet[17]++;
//                        break;
//                    case    0x0406:     //'І':
//                        alphabet[17]++;;
//                        break;
//                    case    0x0490:     //'Ґ':
//                        alphabet[17]++;
//                        break;
//                    case    0x040E:     //'Ў':
//                        alphabet[17]++;
//                        break;
//                    case    0x040B:    //'Ћ':
//                        alphabet[17]++;
//                        break;

                    default:
                        break;
                    }
            }


                    #ifdef DEBUG
                                qDebug()  << query.value(0).toString() << query.value(1).toString();
                    #endif
        }
        }

        // m_data
        for (int i = 0; i < m_rowCount; i++) {
        QList<qreal> *dataList = new QList<qreal>(m_columnCount);

        for (int k = 0; k < dataList->size(); k++) {
            if (k % 2 == 0)
                dataList->replace(k, i );
            else
                dataList->replace(k, alphabet[i]);

            #ifdef DEBUG
                        qDebug()  << alphabet[i];
            #endif

        }
        m_data.append(dataList);
    }
}

int CustomTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}

int CustomTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_columnCount;
}

QVariant CustomTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        if (section % 2 == 0)
            return "Number Letter:";
        else
            return "Stat Letter:";
    } else {
        return QString("%1").arg(section + 1);
    }
}

QVariant CustomTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        return m_data[index.row()]->at(index.column());
    } else if (role == Qt::EditRole) {
        return m_data[index.row()]->at(index.column());
    } else if (role == Qt::BackgroundRole) {
        for (const QRect &rect : m_mapping) {
            if (rect.contains(index.column(), index.row()))
                return QColor(m_mapping.key(rect));
        }
        // cell not mapped return white color
        return QColor(Qt::white);
    }
    return QVariant();
}

bool CustomTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        m_data[index.row()]->replace(index.column(), value.toDouble());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags CustomTableModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void CustomTableModel::addMapping(QString color, QRect area)
{
    m_mapping.insert(color, area);
}
