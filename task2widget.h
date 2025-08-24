#ifndef TASK2WIDGET_H
#define TASK2WIDGET_H

#include <QWidget>

namespace Ui {
class task2widget;
}

class task2widget : public QWidget
{
    Q_OBJECT

public:
    explicit task2widget(QWidget *parent = nullptr);
    ~task2widget();

signals:
    void backToMainMenu();  // Сигнал для возврата в главное меню

private slots:
    void on_buttonTask2_Calculate_clicked();  // Кнопка Подсчитать
    void on_buttonTask2_Clean_clicked();      // Кнопка Очистить
    void on_buttonBack_clicked();             // Кнопка Назад

private:
    // Подсчёт слов по длине
    void countWordLengths(const QString& text, int lengthCount[]);

    friend class testtask;

private:
    Ui::task2widget *ui;
};

#endif // TASK2WIDGET_H
