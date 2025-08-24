#ifndef TASK4WIDGET_H
#define TASK4WIDGET_H

#include <QWidget>

namespace Ui {
class task4widget;
}

class task4widget : public QWidget
{
    Q_OBJECT

public:
    explicit task4widget(QWidget *parent = nullptr);
    ~task4widget();

signals:
    void backToMainMenu();  // Для возврата в главное меню

private slots:
    void on_buttonTask4_Calculate_clicked();  // Обработать
    void on_buttonTask4_Clean_clicked();      // Очистить
    void on_buttonBack_clicked();             // Назад

private:
    int countBits(unsigned int n);                    // Считаем количество единиц
    unsigned int minWith_k_Bits(int k);              // Min число с k единицами
    unsigned int maxWith_k_Bits(int k);              // Max число с k единицами
    QString toBinary32(unsigned int n);               // Переводим в 32-битное двоичное с пробелами

    friend class testtask;

private:
    Ui::task4widget *ui;
};

#endif // TASK4WIDGET_H
