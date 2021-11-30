#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo> //ces 3 dernières bibliotèque seront a mettre dans arraigne.h

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "controlArraignee_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    //-----------------------------------------------------------------------------------------------------
    //ne rien écrire en dehors de ces limites
    //TODO mettre test pour liaison série
    //ne rien ecrire après cette limite
    //-----------------------------------------------------------------------------------------------------
    return a.exec();


}
