#ifndef TASK5WIDGET_H
#define TASK5WIDGET_H

#include <QWidget>

// Структура узла дерева
struct TreeNode {
    char value;              // например, 'A', 'B'
    TreeNode* leftChild;
    TreeNode* rightChild;
    TreeNode(char val) : value(val), leftChild(nullptr), rightChild(nullptr) {}
};

namespace Ui {
class task5widget;
}

class task5widget : public QWidget
{
    Q_OBJECT

public:
    explicit task5widget(QWidget *parent = nullptr);
    ~task5widget();

signals:
    void backToMainMenu();  // Для возврата в главное меню

private slots:
    void on_buttonTask5_Calculate_clicked();  // Обработать
    void on_buttonTask5_Clean_clicked();      // Очистить
    void on_buttonTask5_Help_clicked();       // Подсказка
    void on_buttonBack_clicked();             // Назад

public:
    TreeNode* parseTree(const QString& str, int& pos);           // Парсим строку в дерево
    void findPaths(TreeNode* node, QString path, int depth,
                   int& maxDepth, QStringList& resultPaths);     // Ищем все пути
    void freeTree(TreeNode* node);                               // Освобождаем память

    friend class testtask;

private:
    Ui::task5widget *ui;
};

#endif // TASK5WIDGET_H
