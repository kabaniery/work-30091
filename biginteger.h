#pragma once

#ifndef INCLUDE_BIGINT
#define INCLUDE_BIGINT
#include <string>
#include <limits>
#endif // !INCLUDE_BIGINT


class BigInteger
{
public:
	// BigInteger представляет из себя неограниченное число Int'ов. Оптимальным вариантом для представления является двоичным, в котором число и записано. Соответственно каждая новая переменная int
	// представляет из себя расширение разрядов. Кстати, в массиве данных все числа строго неотрицательны.
	unsigned int* rawNm;
	//Число разрядов данных
	int countRank;
	//Проверка отрицательности
	bool isNegative = false;
	//Максимальное число int (для справки себе)
	int maxInt = std::numeric_limits<unsigned int>::max();
	BigInteger(int value, int rank);
	//Скрытая функция для суммирования нашего BigInteger с обычным целым числом, перенесенным в определенный разряд
	void sumWithInt(int value, int rank);

	//Функция, которая инициализирует все числа
	void intialize();


	//Функция, которая производит умножение всего BigInteger на число
	void multWithRaw(unsigned int value);
public:
	//Конструктор по-умолчанию
	BigInteger();
	//Конструктор от целого числа
	BigInteger(int value);
	//Конструктор от целого числа, но в 2 раза большим разбросом 
	BigInteger(long value);
	//Конструктор от целого числа, но еще большим в 2 раза
	BigInteger(long long value);
	//Конструктор от строки
	BigInteger(std::string value);
	//Конструктор копирования
	BigInteger(const BigInteger& other);
	//Конструктор перемещения
	BigInteger(const BigInteger&& other);

	//Оператор резервирования копированием
	BigInteger& operator =(const BigInteger& other);
	//Оператор приложениям пермещения
	BigInteger& operator =(const BigInteger&& other);
	//Оператор сравнения эквивалентности
	bool operator ==(BigInteger other);
	//Оператор сравнения неравенства
	bool operator !=(BigInteger other);
	//Оператор сравнения "Строго больше"
	bool operator >(BigInteger other);
	//Оператор сравнения "Не меньше"
	bool operator >=(BigInteger other);
	//Оператор сравнения "Строго меньше"
	bool operator <(BigInteger other);
	//Оператор сраввнения "Не больше"
	bool operator <=(BigInteger other);

	//Операция сложения
	BigInteger operator +(BigInteger other);
	//Операция вычитания
	BigInteger operator -(BigInteger other);
	//Операция умножения
	BigInteger operator *(BigInteger other);
	//Операция деления
	BigInteger operator /(BigInteger other);
	//Операция унарного минуса
	BigInteger operator -() const;
	//Операция унарного плюса
	BigInteger operator +() const;
	//Оператор приращения
	BigInteger operator +=(BigInteger other);
	//Оператор инкремента
	BigInteger operator ++();
	//Оператор декремента
	BigInteger operator --();

	//Функция приведения к строке
	std::string to_string(const BigInteger& other);
};


