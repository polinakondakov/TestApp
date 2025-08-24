#include "task4widget.h"
#include "ui_task4widget.h"

#include <QString>

task4widget::task4widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::task4widget)
{
    ui->setupUi(this);
}

task4widget::~task4widget()
{
    delete ui;
}

// Считаем количество единиц в двоичной записи
int task4widget::countBits(unsigned int n)
{
    int count = 0;
    while (n > 0) {
        count += n & 1;  // Если младший бит = 1 → увеличиваем счётчик
        n = n >> 1;      // сдвигаем вправо на 1 бит
    }
    return count;
}

// Минимальное число с k единицами
unsigned int task4widget::minWith_k_Bits(int k)
{
    if (k == 0) return 0;
    if (k == 32) return 4294967295;
    return (static_cast<unsigned int>(1) << k) - 1; // Чтобы число было минимальным, единицы должны быть справа
}

// Максимальное число с k единицами
unsigned int task4widget::maxWith_k_Bits(int k)
{
    if (k == 0) return 0;
    if (k == 32) return 4294967295;  // все 32 бита = 1
    unsigned int ones = (static_cast<unsigned int>(1) << k) - 1;  // k единиц
    return ones << (32 - k);            // сдвигаем влево
}

// Переводим число в 32-битное двоичное с пробелами каждые 4 бита
QString task4widget::toBinary32(unsigned int n)
{
    QString bin = QString::number(n, 2);            // В двоичной системе
    bin = bin.rightJustified(32, '0');              // добавляем ведущие нули

    // Добавляем пробелы каждые 4 бита
    for (int i = 28; i > 0; i -= 4) {
        bin.insert(i, " ");
    }
    return bin;
}

// Кнопка Обработать
void task4widget::on_buttonTask4_Calculate_clicked()
{
    ui->lineEditTask4_OrigBites->clear();
    ui->lineEditTask4_OutputMin->clear();
    ui->lineEditTask4_OutputMinDouble->clear();
    ui->lineEditTask4_OutputMinBites->clear();
    ui->lineEditTask4_OutputMax->clear();
    ui->lineEditTask4_OutputMaxDouble->clear();
    ui->lineEditTask4_OutputMaxBites->clear();

    QString input = ui->lineEditTask4_Input->text();
        input = input.remove(' ');  // удаляем все пробелы

        bool ok;
        unsigned int n = input.toUInt(&ok, 10);  // только десятичное

     if (!ok) {
         ui->lineEditTask4_OrigBinary->setText("Ошибка: введите число не больше 4294967295");
         return;
     }

    // Количество единиц
    int ones = countBits(n);

    // Двоичное представление
    QString binary = toBinary32(n);

    // Минимальное и максимальное число
    unsigned int minVal = minWith_k_Bits(ones);
    unsigned int maxVal = maxWith_k_Bits(ones);

    // Выводим результаты
    ui->lineEditTask4_OrigBinary->setText(binary);
    ui->lineEditTask4_OrigBites->setText(QString::number(ones));

    ui->lineEditTask4_OutputMin->setText(QString::number(minVal));
    ui->lineEditTask4_OutputMinDouble->setText(toBinary32(minVal));
    ui->lineEditTask4_OutputMinBites->setText(QString::number(ones));

    ui->lineEditTask4_OutputMax->setText(QString::number(maxVal));
    ui->lineEditTask4_OutputMaxDouble->setText(toBinary32(maxVal));
    ui->lineEditTask4_OutputMaxBites->setText(QString::number(ones));
}

// Кнопка Очистить
void task4widget::on_buttonTask4_Clean_clicked()
{
    ui->lineEditTask4_Input->clear();
    ui->lineEditTask4_OrigBinary->clear();
    ui->lineEditTask4_OrigBites->clear();
    ui->lineEditTask4_OutputMin->clear();
    ui->lineEditTask4_OutputMinDouble->clear();
    ui->lineEditTask4_OutputMinBites->clear();
    ui->lineEditTask4_OutputMax->clear();
    ui->lineEditTask4_OutputMaxDouble->clear();
    ui->lineEditTask4_OutputMaxBites->clear();
}

// Кнопка Назад
void task4widget::on_buttonBack_clicked()
{
    emit backToMainMenu();
}
