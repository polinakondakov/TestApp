#ifndef TASK1WIDGET_H
#define TASK1WIDGET_H

#include <QWidget>

namespace Ui {
class task1widget;
}

class task1widget : public QWidget
{
    Q_OBJECT

public:
    explicit task1widget(QWidget *parent = nullptr);
    ~task1widget();

signals:
    void backToMainMenu(); // Сигнал для возврата в главное меню

private slots:
    void on_buttonTask1_Calculate_clicked();  // Выполнить
    void on_buttonTask1_Clean_clicked();      // Очистить
    void on_buttonBack_clicked();             // Назад

private:
    bool isPrime(int number);                    // Проверяем простое ли число?
    void findFirstNPrimes(int n, int result[]);  // Находим N простых чисел и кладём в массив
    bool saveToFile(int n, int primes[]);  // Сохраняем в файл N.txt

    friend class testtask;

private:
    Ui::task1widget *ui;
};

#endif // TASK1WIDGET_H
