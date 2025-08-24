#include "task1widget.h"
#include "ui_task1widget.h"

#include <cmath>
#include <QElapsedTimer>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

task1widget::task1widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::task1widget)
{
    ui->setupUi(this);
}

task1widget::~task1widget()
{
    delete ui;
}

// Проверяем, является ли число простым
bool task1widget::isPrime(int number)
{
    if (number < 2) return false;
    if (number == 2) return true;
    if (number % 2 == 0) return false;

    int limit = static_cast<int>(std::sqrt(number)) + 1;
    for (int i = 3; i <= limit; i += 2) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

// Находим первые N простых чисел и сохраняем в массив
void task1widget::findFirstNPrimes(int n, int result[])
{
    int count = 0;
    int num = 2;

    while (count < n) {
        if (isPrime(num)) {
            result[count] = num;  // Кладём в массив
            count++;              // Увеличиваем счётчик
        }
        num++;
    }
}

// Сохраняем простые числа в файл N.txt
bool task1widget::saveToFile(int n, int primes[])
{
    QString filename = QString("%1.txt").arg(n);
    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", QString("Не удалось создать файл: %1").arg(filename));
        return false;
    }

    QTextStream out(&file);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            out << ", ";
        }
        out << primes[i];
    }
    file.close();

    return true;
}

// Кнопка Выполнить
void task1widget::on_buttonTask1_Calculate_clicked()
{
    int n = ui->spinBoxTask1_Input->value();

    // Проверка диапазона
    if (n <= 0 || n > 10000) {
        ui->textEditTask1_Output->setText("Ошибка: N должно быть от 1 до 10000");
        ui->lineEditTask1_Time->clear();
        return;
    }

    // Массив для хранения простых чисел
    int primes[10000];

    // Измеряем время
    QElapsedTimer timer;
    timer.start();

    // Находим простые числа
    findFirstNPrimes(n, primes);

    long long int time = timer.nsecsElapsed() / 1000;  // в микросекундах

    // Формируем строку с результатом
    QString result;
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            result += ", ";
        }
        result += QString::number(primes[i]);
    }

    // Выводим результат
    ui->textEditTask1_Output->setText(result);
    ui->lineEditTask1_Time->setText(QString("%1 мкс").arg(time));

    // Спрашиваем, сохранить ли в файл
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Сохранить в файл?",
                                  QString("Хотите сохранить результат в файл %1.txt?").arg(n),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (saveToFile(n, primes)) {
            QMessageBox::information(this, "Успех", QString("Результат сохранён в %1.txt").arg(n));
        }
    }
}

// Кнопка Очистить
void task1widget::on_buttonTask1_Clean_clicked()
{
    ui->spinBoxTask1_Input->setValue(0);
    ui->textEditTask1_Output->clear();
    ui->lineEditTask1_Time->clear();
}

// Кнопка Назад
void task1widget::on_buttonBack_clicked()
{
    emit backToMainMenu();
}
