#include "task3widget.h"
#include "ui_task3widget.h"

#include <QElapsedTimer>
#include <QStringList>

task3widget::task3widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::task3widget)
{
    ui->setupUi(this);
}

task3widget::~task3widget()
{
    delete ui;
}

// Создаём список из строки разделяем по пробелам
List* task3widget::createList(const QString& input)
{
    QStringList parts = input.split(' ', QString::SkipEmptyParts);
    List* head = nullptr;
    List* tail = nullptr;

    for (int i = 0; i < parts.size(); ++i) {
        QString part = parts[i].trimmed();
        List* node = new List(part);
        if (!head) {
            head = node;
        } else {
            tail->next = node;
        }
        tail = node;
    }

    return head;
}

// Удаляем каждый пятый элемент из списка
void task3widget::removeEveryFifth(List*& head)
{
    List* prev = nullptr;
    List* current = head;
    int index = 1;

    while (current != nullptr) {
        if (index % 5 == 0) {
            List* toDelete = current;
            if (prev == nullptr) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            current = current->next;
            delete toDelete;
        } else {
            prev = current;
            current = current->next;
        }
        index++;
    }
}

// Преобразуем список в формат 1->2->3...
QString task3widget::listToString(const List* head) const
{
    QString result;
    const List* current = head;

    while (current != nullptr) {
        result += current->payload;
        if (current->next != nullptr) {
            result += " → ";
        }
        current = current->next;
    }
    if (!result.isEmpty()) {
        result += " → nullptr";
    }

    return result;
}

// Освобождаем память списка
void task3widget::freeList(List* head)
{
    while (head != nullptr) {
        List* temp = head;
        head = head->next;
        delete temp;
    }
}

// Кнопка Обработать
void task3widget::on_buttonTask3_Calculate_clicked()
{
    QString input = ui->textEditTask3_Input->toPlainText().trimmed();

    if (input.isEmpty()) {
        ui->textEditTask3_Original->setText("Введите элементы (через пробел).");
        ui->textEditTask3_Output->setText("");
        ui->lineEditTask3_Time->clear();
        return;
    }

    // Создаём исходный список
    List* original = createList(input);

    // Выводим исходный список
    QString originalStr = listToString(original);
    ui->textEditTask3_Original->setText(originalStr);

    // Измеряем время
    QElapsedTimer timer;
    timer.start();

    // Удаляем каждый пятый элемент
    removeEveryFifth(original);
    long long int time = timer.nsecsElapsed() / 1000;

    // Выводим результат
    QString resultStr = listToString(original);
    ui->textEditTask3_Output->setText(resultStr);
    ui->lineEditTask3_Time->setText(QString("%1 мкс").arg(time));

    // Освобождаем память
    freeList(original);
}

// Кнопка Очистить
void task3widget::on_buttonTask3_Clean_clicked()
{
    ui->textEditTask3_Input->clear();
    ui->textEditTask3_Original->clear();
    ui->textEditTask3_Output->clear();
    ui->lineEditTask3_Time->clear();
}

// Кнопка Назад
void task3widget::on_buttonBack_clicked()
{
    emit backToMainMenu();
}
