
//
QT += charts sql
requires(qtConfig(tableview))

HEADERS += \
    customtablemodel.h \
    tablewidget.h

SOURCES += \
    customtablemodel.cpp \
    main.cpp \
    tablewidget.cpp

target.path = $$[QT_INSTALL_EXAMPLES]/charts/modeldata
INSTALLS += target

RESOURCES += \
    res.qrc
