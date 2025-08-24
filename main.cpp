#include <QApplication>
#include "mainwindow.h"

#include "testtask.h"
#include <QTest>
#include <QDebug>

// Закомментировать, если запускаются тесты
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow w;
    w.show();
    return app.exec();
}
