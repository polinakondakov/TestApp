#include "testtask.h"
#include <QtTest>

// Подключаем заголовочные файлы виджетов, чтобы иметь доступ к их методам
#include "task1widget.h"
#include "task2widget.h"
#include "task3widget.h"
#include "task4widget.h"
#include "task5widget.h"


// ---------------------------------------- ТЕСТЫ ДЛЯ ЗАДАНИЯ 1 ------------------------------------------- //
// Задание 1 - Поиск N-первых простых чисел
void testtask::testIsPrime() // Тест для метода isPrime
{
    task1widget w;

    // Ожидаем, что функция вернёт true для известных простых чисел
    QVERIFY(w.isPrime(2));
    QVERIFY(w.isPrime(3));
    QVERIFY(w.isPrime(5));
    QVERIFY(w.isPrime(7));
    QVERIFY(w.isPrime(11));
    QVERIFY(w.isPrime(13));
    QVERIFY(w.isPrime(17));
    QVERIFY(w.isPrime(19));
    QVERIFY(w.isPrime(9973));

    // Ожидаем, что функция вернёт false для составных чисел
    QVERIFY(!w.isPrime(4));
    QVERIFY(!w.isPrime(6));
    QVERIFY(!w.isPrime(8));
    QVERIFY(!w.isPrime(9));
    QVERIFY(!w.isPrime(10));
    QVERIFY(!w.isPrime(25));
    QVERIFY(!w.isPrime(9801));

    // Проверка граничных значений
    QVERIFY(!w.isPrime(0));     // 0 — не простое число
    QVERIFY(!w.isPrime(1));     // 1 — особый случай, не является простым
    QVERIFY( w.isPrime(2));     // 2 — единственное чётное простое число
    QVERIFY(!w.isPrime(-5));    // отрицательные числа не могут быть простыми
    QVERIFY(!w.isPrime(-100));  // аналогично — отрицательные вне диапазона простых
}

void testtask::testFindFirstNPrimes() // Тест для метода findFirstNPrimes
{
    task1widget w;
    int result[10000];

    const int n = 10;  // проверяем первые 10 простых чисел
    w.findFirstNPrimes(n, result);

    // Ожидаемые значения: первые 10 простых чисел
    int expected[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

    for (int i = 0; i < n; ++i) {
        QCOMPARE(result[i], expected[i]);
    }
}

// ---------------------------------------- ТЕСТЫ ДЛЯ ЗАДАНИЯ 2 ------------------------------------------- //
// Задание 2 - Подсчёт слов по длине

void testtask::testCountWordLengths_SimpleText() // Простой текст на русском и английском
{
    task2widget w;
    int lengthCount[100];

    QString text = "Привет мир hello world";

    w.countWordLengths(text, lengthCount);

    // "Привет" — 6 букв, "мир" — 3, "hello" — 5, "world" — 5
    QCOMPARE(lengthCount[3], 1);  // мир
    QCOMPARE(lengthCount[5], 2);  // hello, world
    QCOMPARE(lengthCount[6], 1);  // Привет

    // Остальные — 0
    QCOMPARE(lengthCount[1], 0);
    QCOMPARE(lengthCount[2], 0);
    QCOMPARE(lengthCount[4], 0);
}

void testtask::testCountWordLengths_WithPunctuation() // Текст со знаками препинания
{
    task2widget w;
    int lengthCount[100];

    // Текст со знаками препинания
    QString text = "Привет, мир! Как дела? Отлично... Всё; хорошо: нормально?";

    w.countWordLengths(text, lengthCount);

    // После очистки: Привет мир Как дела Отлично Всё хорошо нормально
    QCOMPARE(lengthCount[3], 3);  // мир, как, всё
    QCOMPARE(lengthCount[4], 1);  // дела
    QCOMPARE(lengthCount[6], 2);  // хорошо, Привет
    QCOMPARE(lengthCount[7], 1);  // Отлично
    QCOMPARE(lengthCount[9], 1);  // нормально
}

void testtask::testCountWordLengths_MultipleSpacesAndTabs()  // Много пробелов, табуляций и переносов
{
    task2widget w;
    int lengthCount[100];

    // Много пробелов и табуляций
    QString text = "ковшик\t\t  солнце    огурец\n\t молоко";

    w.countWordLengths(text, lengthCount);

    // Все слова длиной 6
    QCOMPARE(lengthCount[6], 4);
}

void testtask::testCountWordLengths_EmptyAndWhitespace() // Пустая строка и только пробелы/знаки
{
    task2widget w;
    int lengthCount[100];

    // Пустая строка
    QString text = "";
    w.countWordLengths(text, lengthCount);
    for (int i = 1; i < 20; ++i) {
        QCOMPARE(lengthCount[i], 0);
    }

    // Только пробелы и знаки
    text = "   \t\n ... !!! ??? :::";
    w.countWordLengths(text, lengthCount);
    for (int i = 1; i < 20; ++i) {
        QCOMPARE(lengthCount[i], 0);
    }
}

// ---------------------------------------- ТЕСТЫ ДЛЯ ЗАДАНИЯ 3 ------------------------------------------- //
// Задание 3 - Работа со односвязным списком
static void assertListEquals(const List* head, const QStringList& expected) // Сравнивает связный список с ожидаемым списком строк
{
    QStringList actual;
    const List* current = head;
    while (current != nullptr) {
        actual.append(current->payload);
        current = current->next;
    }
    QCOMPARE(actual, expected);
}

void testtask::testCreateList_Empty() // Проверка если была введена пустая строка, должен создаваться пустой список
{
    task3widget w;
    List* list = w.createList("");
    assertListEquals(list, {});  // пустой список
    w.freeList(list);
}

void testtask::testCreateList_Multiple() // При нескольких словах создаётся цепочка узлов A → B → C → nullptr
{
    task3widget w;
    List* list = w.createList("A B C");
    assertListEquals(list, {"A", "B", "C"});
    w.freeList(list);
}

void testtask::testRemoveEveryFifth_Empty() // Удаление 5-ого элемента при пустой строке
{
    task3widget w;
    List* list = nullptr;
    w.removeEveryFifth(list);
    assertListEquals(list, {});  // остаётся пустым
}

void testtask::testRemoveEveryFifth_LessThan5() // Удаление каждого 5-ого если в списке меньше 5 элементов
{
    task3widget w;
    List* list = w.createList("A B C D");
    w.removeEveryFifth(list);
    assertListEquals(list, {"A", "B", "C", "D"});  // ничего не удалено
    w.freeList(list);
}

void testtask::testRemoveEveryFifth_Exact5() // Удаление каждого 5-ого если в списке = 5 элементов
{
    task3widget w;
    List* list = w.createList("A B C D E");
    w.removeEveryFifth(list);
    assertListEquals(list, {"A", "B", "C", "D"});  // 5-й (E) удалён
    w.freeList(list);
}

void testtask::testRemoveEveryFifth_10() // Удаление каждого 5-ого если в списке = 10 элементов
{
    task3widget w;
    List* list = w.createList("1 2 3 4 5 6 7 8 9 10");
    w.removeEveryFifth(list);
    assertListEquals(list, {"1", "2", "3", "4", "6", "7", "8", "9"});  // 5 и 10 удалены
    w.freeList(list);
}

// ---------------------------------------- ТЕСТЫ ДЛЯ ЗАДАНИЯ 4 ------------------------------------------- //
// Задание 4 - Работа с битами 32-битного числа

void testtask::testCountBits_Zero() // Подсчет единиц в двоичной записи для 0 - 0 единиц
{
    task4widget w;
    QCOMPARE(w.countBits(0), 0);
}

void testtask::testCountBits_PowersOfTwo() // Подсчет единиц для степеней числа 2 - 1 единица
{
    task4widget w;
    QCOMPARE(w.countBits(1), 1);   // ...1
    QCOMPARE(w.countBits(2), 1);   // ...10
    QCOMPARE(w.countBits(4), 1);   // ...100
    QCOMPARE(w.countBits(8), 1);   // ...1000
    QCOMPARE(w.countBits(16), 1);  // ...10000
}

void testtask::testCountBits_Random() // Подсчет единиц для некоторых чисел
{
    task4widget w;
    QCOMPARE(w.countBits(3), 2);   // ...11
    QCOMPARE(w.countBits(5), 2);   // ...101
    QCOMPARE(w.countBits(7), 3);   // ...111
    QCOMPARE(w.countBits(15), 4);  // ...1111
    QCOMPARE(w.countBits(255), 8); // ...11111111
}

void testtask::testCountBits_Max() // Подсчет единиц для макисмального 32-x-битного числа
{
    task4widget w;
    QCOMPARE(w.countBits(4294967295U), 32);  // Все 32 бита = 1
}

void testtask::testMinWith_k_Bits_Zero() // Минимально число с 0 единиц
{
    task4widget w;
    QCOMPARE(w.minWith_k_Bits(0), 0);
}

void testtask::testMinWith_k_Bits_Random() // Минимально число с каким-то количеством единиц
{
    task4widget w;
    QCOMPARE(w.minWith_k_Bits(1), 1);      // ...1
    QCOMPARE(w.minWith_k_Bits(2), 3);      // ...11
    QCOMPARE(w.minWith_k_Bits(3), 7);      // ...111
    QCOMPARE(w.minWith_k_Bits(4), 15);     // ...1111
    QCOMPARE(w.minWith_k_Bits(5), 31);     // ...11111
}

void testtask::testMinWith_k_Bits_Max()
{
    task4widget w;
    QCOMPARE(w.minWith_k_Bits(32), 4294967295);  // Все 32 бита = 1
}

void testtask::testMaxWith_k_Bits_Zero() // Максимальное число с 0 единиц
{
    task4widget w;
    QCOMPARE(w.maxWith_k_Bits(0), 0);
}

void testtask::testMaxWith_k_Bits_Random() // Максимальное число с некоторым числом единиц
{
    task4widget w;
    // k=1: 10000000 00000000 00000000 00000000 → 2147483648
    QCOMPARE(w.maxWith_k_Bits(1), 2147483648);

    // k=2: 11000000 00000000 00000000 00000000 → 3221225472
    QCOMPARE(w.maxWith_k_Bits(2), 3221225472);

    // k=3: 11100000 00000000 00000000 00000000 → 3758096384
    QCOMPARE(w.maxWith_k_Bits(3), 3758096384);

    // k=4: 11110000 00000000 00000000 00000000 → 4043309056
    QCOMPARE(w.maxWith_k_Bits(4), 4026531840);
}

void testtask::testMaxWith_k_Bits_Max() // Максимальное число с 32 единициами
{
    task4widget w;
    QCOMPARE(w.maxWith_k_Bits(32), 4294967295);  // Все биты = 1
}

void testtask::testToBinary32_Zero() // Формирование нуля в 32-битную строку
{
    task4widget w;
    QString expected = "0000 0000 0000 0000 0000 0000 0000 0000";
    QCOMPARE(w.toBinary32(0), expected);
}

void testtask::testToBinary32_PowerOfTwo() // Формирование чисел степени двойки в 32-битную строку - 1 единица
{
    task4widget w;
    // 1 - ...0001
    QCOMPARE(w.toBinary32(1),
             "0000 0000 0000 0000 0000 0000 0000 0001");

    // 2 - ...0010
    QCOMPARE(w.toBinary32(2),
             "0000 0000 0000 0000 0000 0000 0000 0010");

    // 16 - ...10000
    QCOMPARE(w.toBinary32(16),
             "0000 0000 0000 0000 0000 0000 0001 0000");
}

void testtask::testToBinary32_Full() // Формирование 4294967295 в 32-битную строку - все единицы
{
    task4widget w;
    QString expected = "1111 1111 1111 1111 1111 1111 1111 1111";
    QCOMPARE(w.toBinary32(4294967295U), expected);
}


// ---------------------------------------- ТЕСТЫ ДЛЯ ЗАДАНИЯ 5 ------------------------------------------- //
// Задание 5 - Поиск глубины дерева

// Тесты для parseTree — построение дерева из строки
void testtask::testParseTree_SingleNode() // Один узел
{
    task5widget w;
    int pos = 0;
    TreeNode* root = w.parseTree("A", pos);

    QVERIFY(root != nullptr);     // Убеждаемся, что узел создан

    QCOMPARE(root->value, 'A');     // Проверяем значение

    QVERIFY(root->leftChild == nullptr);      // Убеждаемся, что потомков нет
    QVERIFY(root->rightChild == nullptr);

    w.freeTree(root);
}

void testtask::testParseTree_LeftOnly() // Только левый потомок
{
    task5widget w;
    int pos = 0;
    TreeNode* root = w.parseTree("A(B)", pos);

    QVERIFY(root != nullptr);
    QCOMPARE(root->value, 'A');

    QVERIFY(root->leftChild != nullptr);     // Левый потомок есть
    QCOMPARE(root->leftChild->value, 'B');

    QVERIFY(root->rightChild == nullptr);     // Правого потомка нет

    w.freeTree(root);
}

void testtask::testParseTree_RightOnly() // Только правый потомок
{
    task5widget w;
    int pos = 0;
    TreeNode* root = w.parseTree("A(,C)", pos);

    QVERIFY(root != nullptr);
    QCOMPARE(root->value, 'A');

    QVERIFY(root->leftChild == nullptr);

    QVERIFY(root->rightChild != nullptr);
    QCOMPARE(root->rightChild->value, 'C');

    w.freeTree(root);
}

void testtask::testParseTree_Big() // Большое дерево
{
    task5widget w;
    int pos = 0;
    TreeNode* root = w.parseTree("A(B(D),C(E,F))", pos);

    QVERIFY(root != nullptr);
    QCOMPARE(root->value, 'A');

    // Проверяем левую ветвь: A → B → D
    QVERIFY(root->leftChild != nullptr);
    QCOMPARE(root->leftChild->value, 'B');
    QVERIFY(root->leftChild->leftChild != nullptr);
    QCOMPARE(root->leftChild->leftChild->value, 'D');
    QVERIFY(root->leftChild->rightChild == nullptr);

    // Проверяем правую ветвь: A → C → E, F
    QVERIFY(root->rightChild != nullptr);
    QCOMPARE(root->rightChild->value, 'C');
    QVERIFY(root->rightChild->leftChild != nullptr);
    QCOMPARE(root->rightChild->leftChild->value, 'E');
    QVERIFY(root->rightChild->rightChild != nullptr);
    QCOMPARE(root->rightChild->rightChild->value, 'F');

    w.freeTree(root);
}

void testtask::testParseTree_Empty() // Пустая строка или пробелы
{
    task5widget w;
    int pos = 0;

    // Пустая строка
    TreeNode* root1 = w.parseTree("", pos);
    QVERIFY(root1 == nullptr);

    // Только пробелы
    pos = 0;
    TreeNode* root2 = w.parseTree("   ", pos);
    QVERIFY(root2 == nullptr);
}

void runPathTest(const QString& input, int expectedDepth, const QStringList& expectedPaths) // Вспомогательная функция для определения глубины дерева
{
    task5widget w;
    int pos = 0;
    TreeNode* root = w.parseTree(input, pos);  // строим дерево

    int maxDepth = 0;
    QStringList resultPaths;
    w.findPaths(root, "", 0, maxDepth, resultPaths);  // ищем пути

    // Проверяем, что максимальная глубина совпадает
    QCOMPARE(maxDepth, expectedDepth);

    // Проверяем, что найдено правильное количество путей
    QCOMPARE(resultPaths.size(), expectedPaths.size());

    // Проверяем, что каждый ожидаемый путь присутствует в результате
    for (const QString& path : expectedPaths) {
        QVERIFY(resultPaths.contains(path));
    }

    // Освобождаем память дерева
    w.freeTree(root);
}


//Тесты для findPaths — поиск путей максимальной длины
void testtask::testFindPaths_Single() // Одно значение - глубина 1
{
    runPathTest("A", 1, {"A"});
}

void testtask::testFindPaths_Three() // Глубина 3, два пути
{
    runPathTest("A(B(D),C(E))",
                3, {"A → B → D","A → C → E"});
}


//       A
//      / \
//     B   C
//    /   / \
//   D   E   F
//      /
//     G
void testtask::testFindPaths_Four() // Mаксимальная глубина = 4, путь A→C→E→G
{
    runPathTest("A(B(D),C(E(G),F))",
                4,
                {"A → C → E → G"});
}

// Раскомментировать, если запускаются тесты
//QTEST_MAIN(testtask)
