#include "mainwindow.h"
#include "ui_mainwindow.h"

// Подключаем виджеты для страниц
#include "task1widget.h"
#include "task2widget.h"
#include "task3widget.h"
#include "task4widget.h"
#include "task5widget.h"

#include <QMessageBox>
#include <QTimer>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Добавляем страницы в QStackedWidget
    task1widget *task1Page = new task1widget(this);
    ui->stackedWidget->addWidget(task1Page);

    task2widget *task2Page = new task2widget(this);
    ui->stackedWidget->addWidget(task2Page);

    task3widget *task3Page = new task3widget(this);
    ui->stackedWidget->addWidget(task3Page);

    task4widget *task4Page = new task4widget(this);
    ui->stackedWidget->addWidget(task4Page);

    task5widget *task5Page = new task5widget(this);
    ui->stackedWidget->addWidget(task5Page);

    //Подключаем сигнал "назад" (возврат в главное меню) для всех страниц
    connect(task1Page, &task1widget::backToMainMenu, this, [this]() {
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(task2Page, &task2widget::backToMainMenu, this, [this]() {
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(task3Page, &task3widget::backToMainMenu, this, [this]() {
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(task4Page, &task4widget::backToMainMenu, this, [this]() {
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(task5Page, &task5widget::backToMainMenu, this, [this]() {
        ui->stackedWidget->setCurrentIndex(0);
    });

    //this->setFixedSize(1050, 500);

    //Обновляем даты и времени
    updateDateTime();
    // Таймер обновляется каждую секунду
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateDateTime);
    timer->start(1000);  // 1000 мс = 1 секунда
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Метод обновления даты и времени
void MainWindow::updateDateTime()
{
    QDateTime now = QDateTime::currentDateTime();
    QString dateTimeStr = now.toString("ddd, d MMMM yyyy, hh:mm:ss");
    ui->labelDateTime->setText(dateTimeStr);
}

//Кнопки для показ описания задания
void MainWindow::on_buttonMain_whattask1_clicked()
{
    QMessageBox::information(this, "Задание 1",
        "Напишите функцию, которая вычисляет первые N простых чисел и размещает их в массив.");
}

void MainWindow::on_buttonMain_whattask2_clicked()
{
    QMessageBox::information(this, "Задание 2",
        "Напишите функцию, которая посчитывает количество слов в тексте и их длину "
        "(X слов с длиной 1 символ, Y слов длиной 2 символа и так далее).");
}

void MainWindow::on_buttonMain_whattask3_clicked()
{
    QString text = "Дан список:\n"
                   "struct List {\n"
                   "    struct List* next;\n"
                   "    SomeDataType payload;\n"
                   "};\n\n"
                   "Напишите функцию, которая удаляет каждый пятый (5) элемент из данного списка.";

    QMessageBox::information(this, "Задание 3", text);
}

void MainWindow::on_buttonMain_whattask4_clicked()
{
    QMessageBox::information(this, "Задание 4",
        "Напишите функцию, которая принимает 32-битное целое число без знака и возвращает "
        "максимальное и минимальное 32-битное целое число без знака, которые могут быть получены "
        "с помощью того же количества бит, установленных в 1, как в взятом числе.");
}

void MainWindow::on_buttonMain_whattask5_clicked()
{
    QString text = "Дано бинарное дерево:\n"
                   "struct TreeNode {\n"
                   "    struct TreeNode* leftChild;\n"
                   "    struct TreeNode* rightChild;\n"
                   "};\n\n"
                   "Напишите функцию подсчёта глубины дерева\n"
                   "(максимальное количество узлов на пути от корневого узла до листа).\n\n"
                   "Решение должно возвращать все пути в дереве, имеющие такую глубину.";

    QMessageBox::information(this, "Задание 5", text);
}

//Кнопки для переход на страницу с формой задания
void MainWindow::on_buttonMain_task1_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);  // task1
}

void MainWindow::on_buttonMain_task2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);  // task2
}

void MainWindow::on_buttonMain_task3_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);  // task3
}

void MainWindow::on_buttonMain_task4_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);  // task4
}

void MainWindow::on_buttonMain_task5_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);  // task5
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Выход",
                                  "Вы действительно хотите выйти из приложения?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        event->accept();  // Разрешаем закрытие
    } else {
        event->ignore();  // Отменяем закрытие
    }
}
