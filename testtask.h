#ifndef TESTTASK_H
#define TESTTASK_H

#include <QObject>

class testtask : public QObject
{
    Q_OBJECT

private slots:
// ------------- 1 Задание ------------- //
    void testIsPrime();           // Тест для isPrime
    void testFindFirstNPrimes();  // Тест для findFirstNPrimes

// ------------- 2 Задание ------------- //
    void testCountWordLengths_SimpleText();             // Простой текст на русском и английском
    void testCountWordLengths_WithPunctuation();        // Текст со знаками препинания
    void testCountWordLengths_MultipleSpacesAndTabs();  // Много пробелов, табуляций и переносов
    void testCountWordLengths_EmptyAndWhitespace();     // Пустая строка и только пробелы/знаки

// ------------- 3 Задание ------------- //
    void testCreateList_Empty();           // Пустая строка, должен создаваться пустой список
    void testCreateList_Multiple();        // При нескольких словах создаётся цепочка узлов A → B → C → nullptr
    void testRemoveEveryFifth_Empty();     // Удаление 5-ого элемента при пустой строке
    void testRemoveEveryFifth_LessThan5(); // Удаление каждого 5-ого если в списке меньше 5 элементов
    void testRemoveEveryFifth_Exact5();    // Удаление каждого 5-ого если в списке = 5 элементов
    void testRemoveEveryFifth_10();        // Удаление каждого 5-ого если в списке = 10 элементов

// ------------- 4 Задание ------------- //
    void testCountBits_Zero();           // Количество единиц для 0 - 0 единиц
    void testCountBits_PowersOfTwo();    // Количество единиц для 1, 2, 4, 8... (степени числа 2) - 1 единица
    void testCountBits_Random();         // Количество единиц для случайных чисел: 3, 5, 7, 15...
    void testCountBits_Max();            // Количество единиц для 4294967295 (все биты = 1) - 32

    void testMinWith_k_Bits_Zero();      // Минимальное число с 0 единиц
    void testMinWith_k_Bits_Random();      // Минимальное число с некоторым количеством единиц
    void testMinWith_k_Bits_Max();       // Минимальное число с 32 единицами

    void testMaxWith_k_Bits_Zero();      // Максимальное число с 0 единиц
    void testMaxWith_k_Bits_Random();      // Максимальное с некоторым количеством единиц
    void testMaxWith_k_Bits_Max();       // Максимальное число с 32 единицами

    void testToBinary32_Zero();          // Формирование нуля в 32-битную строку
    void testToBinary32_PowerOfTwo();    // Формирование чисел степени двойки в 32-битную строку - 1 единица
    void testToBinary32_Full();          // Формирование 4294967295 в 32-битную строку - все единицы

// ------------- 5 Задание ------------- //
    void testParseTree_SingleNode();         // Построение дерева из строки один узел
    void testParseTree_LeftOnly();           // Построение дерева из строки. Есть только левый потомок
    void testParseTree_RightOnly();          // Построение дерева из строки. Есть только правый потомок
    void testParseTree_Big();                // Построение дерева из строки. Большое дерево вложенные узлы
    void testParseTree_Empty();              // Построение дерева из пустрой строки

    void testFindPaths_Single();             // Ищем глубину. Одно значение - глубина 1
    void testFindPaths_Three();            //  Ищем глубину. Глубина 3
    void testFindPaths_Four();            //  Ищем глубину. Mаксимальная глубина = 4, путь A→C→E→G
};

#endif // TESTTASK_H
