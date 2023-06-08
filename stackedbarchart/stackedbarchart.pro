QT += charts sql widgets

SOURCES += \
    main.cpp

target.path = stackedbarchart
INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    popularnist-prizvis_in_ua \
    sqlite.db

QMAKE_PROJECT_NAME = stackedbarchart

VERSION = 7.0

QMAKE_TARGET_COMPANY = stackedbarchart
QMAKE_TARGET_PRODUCT = chapyland Application
QMAKE_TARGET_DESCRIPTION = chapyland stuff
QMAKE_TARGET_COPYRIGHT = COPYRIGHT (C) $${QMAKE_TARGET_COMPANY} 2023 - ALL RIGHTS RESERVED - FOR INTERNAL USE ONLY

DEFINES += DECODER_COPYRIGHT_STRING="\"$${QMAKE_TARGET_COPYRIGHT}\""
DEFINES += DECODER_VERSION_STRING="\"$${QMAKE_TARGET_PRODUCT} $${VERSION}\""
DEFINES += LATEST_PROCESSABLE_VERSION="\"3.4\""
