QT += charts sql widgets

SOURCES += \
    main.cpp

target.path = $$[QT_INSTALL_EXAMPLES]/charts/stackedbarchart
INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    popularnist-prizvis_in_ua \
    sqlite.db

QMAKE_PROJECT_NAME = stackedbarchart
