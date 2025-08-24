#include "task5widget.h"
#include "ui_task5widget.h"

#include <QMessageBox>

task5widget::task5widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::task5widget)
{
    ui->setupUi(this);
}

task5widget::~task5widget()
{
    delete ui;
}

// Парсим строку в дерево
TreeNode* task5widget::parseTree(const QString& str, int& pos)
{
    if (pos >= str.length()) return nullptr;

    QChar ch = str[pos];
    pos++;

    if (ch == '(' || ch == ',' || ch == ' ') {
        return parseTree(str, pos);
    }

    if (ch == ')') {
        return nullptr;
    }

    TreeNode* node = new TreeNode(ch.toLatin1());

    // Проверяем, есть ли потомки
    if (pos < str.length() && str[pos] == '(') {
        pos++; // пропускаем '('

        // Проверяем, есть ли левый потомок
        if (pos < str.length() && (str[pos] == ',' || str[pos] == ')')) {
            node->leftChild = nullptr; // левого нет
        } else {
            node->leftChild = parseTree(str, pos); // есть — парсим
        }

        // Обрабатываем запятую
        if (pos < str.length() && str[pos] == ',') {
            pos++;
        }

        // Правый потомок
        if (pos < str.length() && str[pos] == ')') {
            node->rightChild = nullptr; // правого нет
        } else {
            node->rightChild = parseTree(str, pos);
        }

        // Закрываем скобку
        if (pos < str.length() && str[pos] == ')') {
            pos++;
        }
    }

    return node;
}

// Ищем все пути от корня до листьев и сохраняет те, что максимальной длины
void task5widget::findPaths(TreeNode* node, QString path, int depth,
                           int& maxDepth, QStringList& resultPaths)
{
    if (node == nullptr) return;

    path += node->value; // Добавляем текущий узел в путь
    depth++;

    if (node->leftChild == nullptr && node->rightChild == nullptr) {
        // Это лист
        if (depth > maxDepth) {  // Если путь длинее
            maxDepth = depth; // Обновляем глубину
            resultPaths.clear(); // Удаляем старые
            resultPaths.append(path); // Добавляем этот путь
        } else if (depth == maxDepth) {
            resultPaths.append(path); // Добавляем путь в список
        }
    } else { // Если это не лист, если есть потомки
        if (node->leftChild != nullptr) {
            findPaths(node->leftChild, path + " → ", depth, maxDepth, resultPaths);
        }
        if (node->rightChild != nullptr) {
            findPaths(node->rightChild, path + " → ", depth, maxDepth, resultPaths);
        }
    }
}

// Освобождаем память дерева
void task5widget::freeTree(TreeNode* node)
{
    if (node == nullptr) return;
    freeTree(node->leftChild);
    freeTree(node->rightChild);
    delete node;
}

// Кнопка Подсказка
void task5widget::on_buttonTask5_Help_clicked()
{
    QString helpText =
        "Введите дерево в скобочной записи.\n\n"
        "Пример:\n"
        "A(B(D), C(E(G), F))\n\n"
        "Это дерево выглядит так:\n\n"
        "        A\n"
        "       / \\\n"
        "      B   C\n"
        "     /   / \\\n"
        "    D   E   F\n"
        "       /\n"
        "      G\n\n"
        "Глубина — количество узлов от корня до листа.";

    QMessageBox::information(this, "Как вводить дерево", helpText);
}

// Кнопка Обработать
void task5widget::on_buttonTask5_Calculate_clicked()
{
    QString input = ui->lineEditTask5_Input->text();

    if (input.isEmpty()) {  //Если ничего не ввели
        ui->lineEditTask5_Output->setText("Введите дерево");
        return;
    }

    int pos = 0;
    TreeNode* root = parseTree(input, pos); //Вызываем парсер, который строит дерево из строки

    int maxDepth = 0;
    QStringList paths;
    findPaths(root, "", 0, maxDepth, paths);

    // Выводим результаты
    ui->lineEditTask5_Output->setText(QString::number(maxDepth));
    ui->textEditTask5_TreeOutput->setText(paths.join("\n"));

    // Освобождаем память
    freeTree(root);
}

// Кнопка Очистить
void task5widget::on_buttonTask5_Clean_clicked()
{
    ui->lineEditTask5_Input->clear();
    ui->lineEditTask5_Output->clear();
    ui->textEditTask5_TreeOutput->clear();
}

// Кнопка Назад
void task5widget::on_buttonBack_clicked()
{
    emit backToMainMenu();
}
