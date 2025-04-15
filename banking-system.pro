QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    account.cpp \
    accountmodel.cpp \
    adminnotif.cpp \
    adminnotifmodel.cpp \
    gerantnotif.cpp \
    gerantnotifmodel.cpp \
    main.cpp \
    message.cpp \
    messagemodel.cpp \
    notif.cpp \
    notifmodele.cpp \
    settingsmodel.cpp \
    transaction.cpp \
    uiabstractwindow.cpp \
    controller.cpp \
    dbmanager.cpp \
    service.cpp \
    uiaddclient.cpp \
    uiadminnotif.cpp \
    uiclient.cpp \
    uigerantnotif.cpp \
    uiinspectaccount.cpp \
    uilistuser.cpp \
    uilistclient.cpp \
    uilistaccount.cpp \
    uilistvirement.cpp \
    uiloginin.cpp \
    uimessage.cpp \
    uimessagegestionnaire.cpp \
    uinotif.cpp \
    uisettings.cpp \
    uiuser.cpp \
    user.cpp \
    usermodel.cpp \
    transactionmodel.cpp \
    uilisttransaction.cpp \
    uiaccount.cpp

HEADERS += \
    account.h \
    accountmodel.h \
    adminnotif.h \
    adminnotifmodel.h \
    gerantnotif.h \
    gerantnotifmodel.h \
    message.h \
    messagemodel.h \
    notif.h \
    notifmodele.h \
    settingsmodel.h \
    transaction.h \
    uiabstractwindow.h \
    controller.h \
    dbmanager.h \
    service.h \
    uiaddclient.h \
    uiadminnotif.h \
    uiclient.h \
    uigerantnotif.h \
    uiinspectaccount.h \
    uilistuser.h \
    uilistclient.h \
    uilistaccount.h \
    uilistvirement.h \
    uiloginin.h \
    uimessage.h \
    uimessagegestionnaire.h \
    uinotif.h \
    uisettings.h \
    uiuser.h \
    user.h \
    usermodel.h \
    transactionmodel.h \
    uilisttransaction.h \
    uiaccount.h

FORMS += \
    uiaddclient.ui \
    uiadminnotif.ui \
    uiclient.ui \
    uigerantnotif.ui \
    uiinspectaccount.ui \
    uilistuser.ui \
    uilistclient.ui \
    uilistaccount.ui \
    uilistvirement.ui \
    uiloginin.ui \
    uimessage.ui \
    uimessagegestionnaire.ui \
    uinotif.ui \
    uisettings.ui \
    uiuser.ui \
    uilisttransaction.ui \
    uiaccount.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
