#include "biginteger.h"

BigInteger::BigInteger(int value, int rank)
{
	this->countRank = rank + 1;
	this->rawNm = new unsigned int[rank + 1];
	this->intialize();
	this->rawNm[rank] = value;
}

void BigInteger::sumWithInt(int value, int rank)
{
	//Первым делом делаем проверку на возможность провести операцию сложения по разрядам
	if (rank >= countRank) {
		//Создаем новый массив и переносим данные
		unsigned int* tempRaw = new unsigned int[rank + 1];
		for (int i = 0; i < countRank; ++i) {
			//Продолжить
			tempRaw[i] = this->rawNm[i];
		}
		//Остаток заполняем 0. Любую выделенную память надо обязательно инициализировать в C++, чтобы избежать мусора
		for (int i = countRank; i < rank; ++i) {
			tempRaw[i] = 0;
		}
		//Теперь ставим актуальное количество разрядов
		this->countRank = rank + 1;
		//Удаляем старую память и проставляем актуальную в переменную
		delete this->rawNm;
		this->rawNm = tempRaw;
	}
	//Если наше число отрицательно
	if (isNegative == true) {
		//Если число, которое складываем тоже отрицательно, то мы проводим сложение по модулю
		if (value < 0) {
			value = value * -1;
			//Если наше число вылезает за пределы int'а, то мы добавляем единицу в новый разряд и записываем остаток. Если нет, то просто прибавляем
			if ((unsigned int) maxInt - rawNm[rank] < (unsigned int) value) {
				//Мы добавляем минус 1, потому что исходное число отрицательно
				sumWithInt(-1, rank + 1);
				rawNm[rank] = maxInt - rawNm[rank] + value;
			}
			else {
				rawNm[rank] += value;
			}
		}
		//Если число, которое складываем отрицательно, то мы проводим вычитание
		else {
			//Перед тем как вычитать, необходимо проверить, не является ли вычитаемое больше уменьшаемого. Если да, то меняем их местами и считаем результат.
			//Проходим по всем битам рабочего разряда
			for (int bit = sizeof(int) * 8; bit >= 0; --bit) {
				//Если обнаружили, что рабочий разряд у вычитаемого больше, то проверяем предыдущие числа нашего на поиск не нуля
				if ((value >> bit) > (rawNm[rank] >> bit)) {
					for (int i = rank + 1; i < countRank; i++) {
						//Если в старших разрядах есть ненулевое число, то можем считать как обычно.
						if (rawNm[i] != 0) {
							bit = -1;
							break;
						}
					}
					//Итого, дойдя до сюда, мы пришли к тому, что вычитаемое больше уменьшаемого. Поэтому присваиваем нашему числу значение разницы между вычитаемым и уменьшаемым. Они уже по условию разных знаков, так что просто складываем
					if (bit == -1) {
						*this = BigInteger(value, rank) + *this;
						//Сразу завершаем функцию, чтобы она не производила лишних расчётов
						return;
					}
				}
			}
			//Теперь само вычитание
			//Если результат вычитания будет отрицательным, то мы вычитаем из следующего разряда единицу и записываем остаток. Если нет, то просто вычитаем
			if (rawNm[rank] - value < 0) {
				//Тут же наоборот единица, чтобы была операция сложения для отрицательного числа
				sumWithInt(1, rank + 1);
				rawNm[rank] = rawNm[rank] - value + maxInt;
			}
			else {
				rawNm[rank] -= value;
			}
		}
	}
	//Если наше число положительное
	else {
		//Если складываемое число больше 0, то производим сложение
		if (value > 0) {
			//Если наше число вылезает за пределы int'а, то мы добавляем единицу в новый разряд и записываем остаток. Если нет, то просто прибавляем
			if (maxInt - rawNm[rank] < value) {
				sumWithInt(1, rank + 1);
				rawNm[rank] = maxInt - rawNm[rank] + value;
			}
			else {
				rawNm[rank] += value;
			}
		}
		// Если число меньше 0, то производим вычитание
		else {
			value *= -1;
			//Перед тем как вычитать, необходимо проверить, не является ли вычитаемое больше уменьшаемого. Если да, то меняем их местами и считаем результат.
			//Проходим по всем битам рабочего разряда
			for (int bit = sizeof(int) * 8; bit >= 0; --bit) {
				//Если обнаружили, что рабочий разряд у вычитаемого больше, то проверяем предыдущие числа нашего на поиск не нуля
				if ((value >> bit) > (rawNm[rank] >> bit)) {
					for (int i = rank + 1; i < countRank; i++) {
						//Если в старших разрядах есть ненулевое число, то можем считать как обычно.
						if (rawNm[i] != 0) {
							bit = -1;
							break;
						}
					}
					//Итого, дойдя до сюда, мы пришли к тому, что вычитаемое больше уменьшаемого. Поэтому присваиваем нашему числу значение разницы между вычитаемым и уменьшаемым. Они уже по условию разных знаков, так что просто складываем
					if (bit == -1) {
						*this = BigInteger(value, rank) + *this;
						//Сразу завершаем функцию, чтобы она не производила лишних расчётов
						return;
					}
				}
			}
			//Если результат вычитания будет отрицательным, то мы вычитаем из следующего разряда единицу и записываем остаток. Если нет, то просто вычитаем
			if (rawNm[rank] - value < 0) {
				//Тут же наоборот единица, чтобы была операция сложения для отрицательного числа
				sumWithInt(1, rank + 1);
				rawNm[rank] = rawNm[rank] - value + maxInt;
			}
			else {
				rawNm[rank] -= value;
			}
		}
	}
}

void BigInteger::intialize()
{
	for (int i = 0; i < this->countRank; ++i) {
		this->rawNm[i] = 0;
	}
}


void BigInteger::multWithRaw(unsigned int value)
{
	BigInteger val = BigInteger(*this);
	BigInteger sum = BigInteger();
	while (value != 0) {
		if ((value & 1) == 1) {
			sum += val;
		}
		val += val;
		value = value >> 1;
	}
}

//Конструктор по-умолчанию. Выделяем одно число и ставим значение 0
BigInteger::BigInteger()
{
	this->countRank = 1;
	this->rawNm = new unsigned int[1];
	this->rawNm[0] = 0;
	this->isNegative = false;
}

//Конструктор от int. Отличается тем, что мы теперь в содержимое прописываем значение value
BigInteger::BigInteger(int value)
{
	this->countRank = 1;
	this->rawNm = new unsigned int[1];
	if (value >= 0) {
		this->isNegative = false;
	}
	else {
		this->isNegative = true;
		value *= -1;
	}
	this->rawNm[0] = value;
}

//Конструктор от long
BigInteger::BigInteger(long value)
{
	//В качестве количества выделяемых чисел, используется отношение long к int. По факту это 2, но для чистоты эксперимента спросим у среды их размеры. К слову, записываем мы числа в unsigned int, который использует под модуль числа на 1 разряд больше. Но в любом случае, это не страшно
	this->countRank = sizeof(long) / sizeof(int);
	this->rawNm = new unsigned int[this->countRank];
	intialize();
	//Класическая проверка на отрицательность
	if (value >= 0) {
		this->isNegative = false;
	}
	else {
		this->isNegative = true;
		value *= -1;
	}
	//Тут веселее. В теории, можно было бы взять 2 маски и забить данные в соответствующие числа. Но раз я не доверяю системе (что зря), то использую алгоритм записи каждого бита отдельно.
	//Переменная бита long
	int bit = 0;
	//индекс числа, в которое будем записываться
	int rank = 0;
	//Пока в long остаются биты, мы будем их записывать
	while (value != 0) {
		//Каждый раз, когда мы обходим все биты int'а, мы смещаем наше число на следующее
		if (bit % (sizeof(int) * 8) == 0)
			rank++;
		//Здесь происходит запись последнего бита long'а в соответствующее место и смещение битов long'а вправо, чтобы получить следующее значение
		this->rawNm[rank] += (value & 1) << bit++;
		value >>= 1;
	}
}

//Работает аналогично предыдущей
BigInteger::BigInteger(long long value)
{
	this->countRank = sizeof(long long) / sizeof(int);
	this->rawNm = new unsigned int[this->countRank];
	this->intialize();
	if (value >= 0) {
		this->isNegative = false;
	}
	else {
		this->isNegative = true;
		value *= -1;
	}
	int bit = 0;
	int rank = 0;
	while (value != 0) {
		if (bit % (sizeof(int) * 8) == 0)
			rank++;
		this->rawNm[rank] += (value & 1) << bit++;
		value >>= 1;
	}
}

//Прямых конвертеров из 10 системы счисления в двоичную нет (а запись всех чисел в памяти происходит именно в двоичном коде), поэтому мы будем обрабатывать её посимвольно
BigInteger::BigInteger(std::string value)
{
	//Для начала создадим нулевой BigInteger 
	this->countRank = 0;
	this->rawNm = new unsigned int[1];
	this->rawNm[0] = 0;
	//Далее вытащим массив символов из строки, чтобы было легче с ней работать
	const char* c_str = value.c_str();
	int index = 0;
	//Если первый символ - минус, то выставляем негативность и увеличиваем переменную индекса, чтобы не наткнуться на него ещё раз
	if (c_str[0] == '-') {
		index++;
		this->isNegative = true;
	}
	else {
		this->isNegative = false;
	}
	//Теперь обходим каждый символ и записываем его по сложенной схеме Горнера, используя уже существующие вспомогательные функции. Если мы получим вместо числа нечто иное, то сделаем число 0. Можно ещё вбросить исключение, но этого в ТЗ не было
	//так что ограничусь тем, что есть
	for (; index < value.size(); ++index) {
		//Если получили не цифру, то делаем 0 и забиваем
		if (c_str[index] < '0' || c_str[index] > '9') {
			this->isNegative = false;
			delete this->rawNm;
			this->rawNm = new unsigned int[1];
			this->rawNm[0] = 0;
		}
		this->sumWithInt(c_str[index] - '0', 0);
		this->multWithRaw(10);
	}
}

//Это конструктор копирования. Мы полностью переносим все данные, но массив данных именно копируем, чтобы он не был связан
BigInteger::BigInteger(const BigInteger& other)
{
	this->countRank = other.countRank;
	this->rawNm = new unsigned int[other.countRank];
	this->isNegative = other.isNegative;
	for (int i = 0; i < other.countRank; ++i) {
		this->rawNm[i] = other.rawNm[i];
	}
}

//Это конструктор переноса. Он просто забирает данные у переданного BigInteger
BigInteger::BigInteger(const BigInteger&& other)
{
	this->countRank = other.countRank;
	this->rawNm = other.rawNm;
	this->isNegative = other.isNegative;
}

//Оператор копирования из себя представляет просто замену конструктора копирования
BigInteger& BigInteger::operator=(const BigInteger& other)
{
	BigInteger* result = new BigInteger(other);
	return *result;
}

//Это же и касается оператора переноса
BigInteger& BigInteger::operator=(const BigInteger&& other)
{
	BigInteger* result = new BigInteger(other);
	return *result;
}

//Здесь будет оператор эквивалентности
bool BigInteger::operator==(BigInteger other)
{
	//Для начала зададим максимальный разряд числа, по которому будем сравнивать. Это необходимо сделать здесь, поскольку он может измениться далее
	int usingRank = this->countRank;
	//Если количества разрядов у чисел разные, то нам необходимо убедиться, что старшие биты большего нулевые, иначе числа точно не равны
	if (this->countRank != other.countRank) {
		if (this->countRank > other.countRank) {
			for (int i = other.countRank; i < this->countRank; ++i) {
				if (this->rawNm[i] != 0) {
					return false;
				}
			}
			usingRank = other.countRank;
		}
		else {
			for (int i = this->countRank; i < other.countRank; ++i) {
				if (other.rawNm[i] != 0) {
					return false;
				}
			}
		}
	}
	//Далее проходим по всем разрядам. Если хоть 1 отличаеся, то возвращаем false. Если же спустя все проверки, всё хорошо, то вернём true
	for (int i = 0; i < usingRank; ++i) {
		if (this->rawNm[i] != other.rawNm[i]) {
			return false;
		}
	}
	return true;
}

//Оператор неравенства прямо противоположен оператору равенства, так что просто возвращаем обратное значение от предыдущей функции
bool BigInteger::operator!=(BigInteger other)
{
	return !this->operator==(other);
}

//Оператор больше, в целом похож на оператор равенства, но здесь обязательно идти от большего разряда к меньшему
bool BigInteger::operator>(BigInteger other)
{
	if (this->countRank > other.countRank) {
		for (int i = other.countRank; i < this->countRank; ++i) {
			if (this->rawNm[i] != 0) {
				return true;
			}
		}
	}
	else if (this->countRank < other.countRank) {
		for (int i = this->countRank; i < other.countRank; ++i) {
			if (other.rawNm[i] != 0) {
				return false;
			}
		}
	}
	for (int i = this->countRank - 1; i >= 0; --i) {
		if (this->countRank > other.countRank) {
			return true;
		}
		else if (this->countRank < other.countRank) {
			return false;
		}
	}
	return false;
}

//Оператор больше или равно являетсся обратным от оператора меньше, чем и воспользуемся
bool BigInteger::operator>=(BigInteger other)
{
	return !this->operator<(other);
}

//Оператор меньше по своей сути такой же, как и "больше", но в возврате мы меняем true и false местами. Это не касается последнего return, который обозначает равенство чисел.
bool BigInteger::operator<(BigInteger other)
{
	if (this->countRank > other.countRank) {
		for (int i = other.countRank; i < this->countRank; ++i) {
			if (this->rawNm[i] != 0) {
				return false;
			}
		}
	}
	else if (this->countRank < other.countRank) {
		for (int i = this->countRank; i < other.countRank; ++i) {
			if (other.rawNm[i] != 0) {
				return true;
			}
		}
	}
	for (int i = this->countRank - 1; i >= 0; --i) {
		if (this->countRank > other.countRank) {
			return false;
		}
		else if (this->countRank < other.countRank) {
			return true;
		}
	}
	return false;
}

//Оператор нестрого меньше аналогичен оператору нестрого больше, только знак используемого оператора противоположный
bool BigInteger::operator<=(BigInteger other)
{
	return !this->operator>(other);
}

//Оператор сложения
BigInteger BigInteger::operator+(BigInteger other)
{
	//Создаем массив, содержащий результат, являющийся копией текущего BigInteger
	BigInteger result = BigInteger(*this);
	//Далее, добавляем к нему в каждый разряд соответсвующее число из другого bigInteger
	for (int i = 0; i < other.countRank; ++i) {
		result.sumWithInt(other.rawNm[i], i);
	}
	return result;
}

//Оператор вычитания. С ним немного сложнее
BigInteger BigInteger::operator-(BigInteger other)
{
	//Начало точно такое же
	BigInteger result = BigInteger(*this);
	//Но тут мы меняем знак числа на противоположный, чтобы обеспечить вычитание
	result.isNegative = !result.isNegative;
	for (int i = 0; i < other.countRank; ++i) {
		result.sumWithInt(other.rawNm[i], i);
	}
	//Теперь надо проверить, что число не равно 0
	for (int i = 0; i < result.countRank; ++i) {
		//Если это так, то обратно меняем знак числа и возвращаем результат
		if (result.rawNm[i] != 0) {
			result.isNegative = !result.isNegative;
			return result;
		}
	}
	//Если 0, то гарантируем себе его неотрицательность
	result.isNegative = false;
	return result;

}

//Для реализации воспользуемся методом быстрого умножения
BigInteger BigInteger::operator*(BigInteger other)
{
	//Суть метода следующая: поскольку в процессоре нет блока умножения (только сложения), то умножение числа заменяется его сложением. Но данный метод не эффективен при больших числах, да и вообще
	//Поэтому мы будем работать со вторым множителем, как с двоичным числом и таким образом умножение превратится в сложение чисел, которые являют собой произведения первого множителя на 2^n
	BigInteger result = BigInteger();
	//Тут будет храниться первый множитель, умноженный на 2^n
	BigInteger part = BigInteger(*this);
	//Это текущий бит второго числа, с которым мы работаем
	int bit = 0;
	//Цикл будет обходить все биты другого числа
	while (bit < other.countRank * sizeof(int) * 8) {
		//Соответственно, если n-ый бит равен 1, то мы добавляем к результату bigInteger1 * 2^n
		if (((other.rawNm[bit / (8 * sizeof(int))] >> (bit % (8 * sizeof(int)))) & 1) == 1) {
			result += part;
		}
		//А операция сложения с собой эквивалентна умножению на 2
		part += part;
		bit++;
	}
	return result;
}

//К сожалению, алгоритма быстрого деления не существует для текущей ситуации, поэтому оно будет представлять собой вычитание второго числа из первого до тех пор, пока это возможно
BigInteger BigInteger::operator/(BigInteger other)
{
	BigInteger copy = BigInteger(*this);
	BigInteger result = BigInteger();
	while (copy > other) {
		copy = copy - other;
		++result;
	}
	return result;
}

//Это оператор унарного минуса. С ним всё довольно просто, он делает любое число отрицательным. Кроме 0, естественно.
BigInteger BigInteger::operator-() const
{
	BigInteger result = BigInteger(*this);
	//Теперь надо проверить, что число не равно 0
	for (int i = 0; i < result.countRank; ++i) {
		//Если это так, то обратно меняем знак числа и возвращаем результат
		if (result.rawNm[i] != 0) {
			result.isNegative = true;
			return result;
		}
	}
	//Если 0, то гарантируем себе его неотрицательность
	result.isNegative = false;
	return result;
}

//Оператор унарного плюса делает число положительным. Тут даже проверка на 0 не нужна
BigInteger BigInteger::operator+() const
{
	BigInteger result = BigInteger(*this);
	result.isNegative = false;
	return result;
}

//Оператор += представляет конкатенацию операторов сложения и присваивания
BigInteger BigInteger::operator+=(BigInteger other)
{
	*this = *this + other;
	return *this;
}

//Ну а оператор инкремента эквивалентен += 1
BigInteger BigInteger::operator++()
{
	*this += 1;
	return *this;
}

//В то время, как оператор декремента эквивалентен -= 1
BigInteger BigInteger::operator--()
{
	*this += -1;
	return *this;
}

//Преобразовать как-то эффективно BigInteger в строку нельзя, поэтому будем использовать хоть один рабочий метод
std::string BigInteger::to_string(const BigInteger& other)
{
	//Строка результата первоначально пустая
	std::string result = "";
	//Чтобы не редактировать переданное значение, сделаем его копию
	BigInteger copy = BigInteger(other);
	//Для деления на 10, создадим равный ему BigInteger
	BigInteger ten = BigInteger(10);
	while (copy > ten) {
		//Суть метода в следующем: мы берём остаток от деления числа на 10 и записываем его первым в строку, после чего делим число на 10
		BigInteger temp = copy / ten;
		result = (char)((copy - temp * ten).rawNm[0] % 10 + '0') + result;
		copy = temp;
	}
	//Если число негативно, то нам надо бы проверить, что это не 0. Проблема в том, что гарантировать получение -0 я могу далеко не везде, но он в любом случае не влияет на операции, поэтому важно лишь не допустить такую оплошность при выводе
	if (other.isNegative) {
		for (int i = 0; i < result.size(); ++i) {
			if (result.c_str()[i] != '0') {
				result = '-' + result;
			}
		}
	}
	return result;
}