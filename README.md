# coursework

Курсовая работа 2 курса 1 семестра

## Задание:

### В соответствии с выбранным вариантом (таблица 2):

1) Организуйте данные из предметной области в виде хеш-таблицы (первичный ключ хеш-таблицы выделен курсивом). Метод хеширования также указан в таблице с вариантами заданий. В качестве алгоритма хеширования использовать метод деления. Обратите внимание, что для вычисления хеш-функции, значение ключевого поля должно быть целым (для перевода строковых данных в целые можно воспользоваться функцией atoi).
2) Реализуйте следующие функции:
    -	Меню для выбора функции (используя конструкцию switch — case).
    -	Добавление записи (в случае закрытого хеширования необходимо отслеживать заполненность хеш-таблицы).
    -	Проверку корректности вводимой информации.
    -	Удаление записи.
    -	Просмотр всех имеющихся записей.
    -	Удаление всех записей.
    -	Поиск записи по ключевому полю.
    -	Поиск данных по фрагменту одного из не ключевых полей (см. вариант задания). Для поиска подстроки в строке необходимо использовать прямой поиск.

### Таблица 2. Варианты заданий:

|№|Предметная область, характеристики|Метод хеширования|Поиск по фрагменту строки|
|-|-|-|-|
|3|Данные об авто: <br> Гос. регистрационный № автомобиля – строка формата «ANNNAANNN», где N-цифра, A – буква из множества: А, В, Е, К,  М, Н, О, Р, С, Т, У, Х. <br> Марка - строка <br> ФИО владельца – строка|Закрытое хеширование с линейным опробованием. В качестве ключевого значения для расчета функции хеширования взять число, состоящее из цифр номера авто.|Поиск авто заданной марки|

*Примечание – длина строк (кроме строк с указанным форматом) определяется студентом самостоятельно.


## Файлы:

- coursework.cpp - main, структура меню и функции для обработки класса HashTable.
- HashTable.h - структура класса HashTable и структуры Info.
- Source.cpp - реализация методов класса HashTable и структуры Info.
- testData.txt - вводимые данные.

## Генераторы:

- генератор имён: <https://randomus.ru/name>
- генератор номеров авто: <https://generand.ru/html/auto.html>
- генератор марок авто: <https://www.getrandomthings.com/list-car-brands.php>
