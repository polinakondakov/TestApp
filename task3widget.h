#ifndef TASK3WIDGET_H
#define TASK3WIDGET_H

#include <QWidget>

// Структура односвязного списка — payload теперь QString
struct List {
    QString payload;
    List* next;
    explicit List(const QString& value) : payload(value), next(nullptr) {}
};

namespace Ui {
class task3widget;
}

class task3widget : public QWidget
{
    Q_OBJECT

public:
    explicit task3widget(QWidget *parent = nullptr);
    ~task3widget();

signals:
    void backToMainMenu();  // Для возврата в главное меню

private slots:
    void on_buttonTask3_Calculate_clicked();  // Обработка
    void on_buttonTask3_Clean_clicked();      // Очистка
    void on_buttonBack_clicked();            // назад

private:
    List* createList(const QString& input);           // Создаём список из строки
    void removeEveryFifth(List*& head);               // Удаляем каждый 5-й элемент
    QString listToString(const List* head) const;     // Преобразуем список в строку
    void freeList(List* head);                        // Освобождаем память

    friend class testtask;

private:
    Ui::task3widget *ui;
};

#endif // TASK3WIDGET_H
