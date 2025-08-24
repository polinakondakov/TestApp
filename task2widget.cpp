#include "task2widget.h"
#include "ui_task2widget.h"

#include <QElapsedTimer>
#include <QStringList>

task2widget::task2widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::task2widget)
{
    ui->setupUi(this);
}

task2widget::~task2widget()
{
    delete ui;
}

// Счетаем количество слов по их длине + поддержка кириллицы
void task2widget::countWordLengths(const QString& text, int lengthCount[])
{
    for (int i = 0; i < 100; ++i) {
        lengthCount[i] = 0;
    }

    // Заменяем символы на пробелы
    QString cleaned = text;
    cleaned.replace(',', ' ');
    cleaned.replace('.', ' ');
    cleaned.replace('!', ' ');
    cleaned.replace('?', ' ');
    cleaned.replace(':', ' ');
    cleaned.replace(';', ' ');
    cleaned.replace('\t', ' ');

    QStringList words = cleaned.split(' ', QString::SkipEmptyParts); // Разибваем строку по пробелам

    for (int i = 0; i < words.size(); ++i) {
        QString word = words[i].trimmed();
        int len = word.length();
        if (len > 0 && len < 100) {
            lengthCount[len]++;
        }
    }
}

// Кнопка Подсчитать
void task2widget::on_buttonTask2_Calculate_clicked()
{
    QString input = ui->textEditTask2_Input->toPlainText().trimmed(); // Извлекаем текст и чистим от пробелов, табуляций в начале и конце

    // Проверка на пустой ввод
    if (input.isEmpty()) {
        ui->textEditTask2_Output->setText("Введите текст для анализа!");
        return;
    }

    // Измеряем затраченное время
    QElapsedTimer timer;
    timer.start();

    int lengthCount[100];
    countWordLengths(input, lengthCount);
    long long int time = timer.nsecsElapsed() / 1000;  // в микросекундах

    // Формируем результат
    QString output;
    int totalWords = 0;

    for (int len = 1; len < 100; ++len) {
        if (lengthCount[len] > 0) {
            totalWords += lengthCount[len];
            output += QString("Длина %1: %2 слов\n").arg(len).arg(lengthCount[len]);
        }
    }

    if (!output.isEmpty()) {
        output += QString("\nВсего слов: %1").arg(totalWords);
    }

    // Вывод
    ui->textEditTask2_Output->setText(output);
    ui->lineEditTask2_Time->setText(QString("%1 мкс").arg(time));
}

// Кнопка Очистить
void task2widget::on_buttonTask2_Clean_clicked()
{
    ui->textEditTask2_Input->clear();
    ui->textEditTask2_Output->clear();
    ui->lineEditTask2_Time->clear();
}

// Кнопка Назад
void task2widget::on_buttonBack_clicked()
{
    emit backToMainMenu();
}
