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
	//������ ����� ������ �������� �� ����������� �������� �������� �������� �� ��������
	if (rank >= countRank) {
		//������� ����� ������ � ��������� ������
		unsigned int* tempRaw = new unsigned int[rank + 1];
		for (int i = 0; i < countRank; ++i) {
			//����������
			tempRaw[i] = this->rawNm[i];
		}
		//������� ��������� 0. ����� ���������� ������ ���� ����������� ���������������� � C++, ����� �������� ������
		for (int i = countRank; i < rank; ++i) {
			tempRaw[i] = 0;
		}
		//������ ������ ���������� ���������� ��������
		this->countRank = rank + 1;
		//������� ������ ������ � ����������� ���������� � ����������
		delete this->rawNm;
		this->rawNm = tempRaw;
	}
	//���� ���� ����� ������������
	if (isNegative == true) {
		//���� �����, ������� ���������� ���� ������������, �� �� �������� �������� �� ������
		if (value < 0) {
			value = value * -1;
			//���� ���� ����� �������� �� ������� int'�, �� �� ��������� ������� � ����� ������ � ���������� �������. ���� ���, �� ������ ����������
			if ((unsigned int) maxInt - rawNm[rank] < (unsigned int) value) {
				//�� ��������� ����� 1, ������ ��� �������� ����� ������������
				sumWithInt(-1, rank + 1);
				rawNm[rank] = maxInt - rawNm[rank] + value;
			}
			else {
				rawNm[rank] += value;
			}
		}
		//���� �����, ������� ���������� ������������, �� �� �������� ���������
		else {
			//����� ��� ��� ��������, ���������� ���������, �� �������� �� ���������� ������ ������������. ���� ��, �� ������ �� ������� � ������� ���������.
			//�������� �� ���� ����� �������� �������
			for (int bit = sizeof(int) * 8; bit >= 0; --bit) {
				//���� ����������, ��� ������� ������ � ����������� ������, �� ��������� ���������� ����� ������ �� ����� �� ����
				if ((value >> bit) > (rawNm[rank] >> bit)) {
					for (int i = rank + 1; i < countRank; i++) {
						//���� � ������� �������� ���� ��������� �����, �� ����� ������� ��� ������.
						if (rawNm[i] != 0) {
							bit = -1;
							break;
						}
					}
					//�����, ����� �� ����, �� ������ � ����, ��� ���������� ������ ������������. ������� ����������� ������ ����� �������� ������� ����� ���������� � �����������. ��� ��� �� ������� ������ ������, ��� ��� ������ ����������
					if (bit == -1) {
						*this = BigInteger(value, rank) + *this;
						//����� ��������� �������, ����� ��� �� ����������� ������ ��������
						return;
					}
				}
			}
			//������ ���� ���������
			//���� ��������� ��������� ����� �������������, �� �� �������� �� ���������� ������� ������� � ���������� �������. ���� ���, �� ������ ��������
			if (rawNm[rank] - value < 0) {
				//��� �� �������� �������, ����� ���� �������� �������� ��� �������������� �����
				sumWithInt(1, rank + 1);
				rawNm[rank] = rawNm[rank] - value + maxInt;
			}
			else {
				rawNm[rank] -= value;
			}
		}
	}
	//���� ���� ����� �������������
	else {
		//���� ������������ ����� ������ 0, �� ���������� ��������
		if (value > 0) {
			//���� ���� ����� �������� �� ������� int'�, �� �� ��������� ������� � ����� ������ � ���������� �������. ���� ���, �� ������ ����������
			if (maxInt - rawNm[rank] < value) {
				sumWithInt(1, rank + 1);
				rawNm[rank] = maxInt - rawNm[rank] + value;
			}
			else {
				rawNm[rank] += value;
			}
		}
		// ���� ����� ������ 0, �� ���������� ���������
		else {
			value *= -1;
			//����� ��� ��� ��������, ���������� ���������, �� �������� �� ���������� ������ ������������. ���� ��, �� ������ �� ������� � ������� ���������.
			//�������� �� ���� ����� �������� �������
			for (int bit = sizeof(int) * 8; bit >= 0; --bit) {
				//���� ����������, ��� ������� ������ � ����������� ������, �� ��������� ���������� ����� ������ �� ����� �� ����
				if ((value >> bit) > (rawNm[rank] >> bit)) {
					for (int i = rank + 1; i < countRank; i++) {
						//���� � ������� �������� ���� ��������� �����, �� ����� ������� ��� ������.
						if (rawNm[i] != 0) {
							bit = -1;
							break;
						}
					}
					//�����, ����� �� ����, �� ������ � ����, ��� ���������� ������ ������������. ������� ����������� ������ ����� �������� ������� ����� ���������� � �����������. ��� ��� �� ������� ������ ������, ��� ��� ������ ����������
					if (bit == -1) {
						*this = BigInteger(value, rank) + *this;
						//����� ��������� �������, ����� ��� �� ����������� ������ ��������
						return;
					}
				}
			}
			//���� ��������� ��������� ����� �������������, �� �� �������� �� ���������� ������� ������� � ���������� �������. ���� ���, �� ������ ��������
			if (rawNm[rank] - value < 0) {
				//��� �� �������� �������, ����� ���� �������� �������� ��� �������������� �����
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

//����������� ��-���������. �������� ���� ����� � ������ �������� 0
BigInteger::BigInteger()
{
	this->countRank = 1;
	this->rawNm = new unsigned int[1];
	this->rawNm[0] = 0;
	this->isNegative = false;
}

//����������� �� int. ���������� ���, ��� �� ������ � ���������� ����������� �������� value
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

//����������� �� long
BigInteger::BigInteger(long value)
{
	//� �������� ���������� ���������� �����, ������������ ��������� long � int. �� ����� ��� 2, �� ��� ������� ������������ ������� � ����� �� �������. � �����, ���������� �� ����� � unsigned int, ������� ���������� ��� ������ ����� �� 1 ������ ������. �� � ����� ������, ��� �� �������
	this->countRank = sizeof(long) / sizeof(int);
	this->rawNm = new unsigned int[this->countRank];
	intialize();
	//����������� �������� �� ���������������
	if (value >= 0) {
		this->isNegative = false;
	}
	else {
		this->isNegative = true;
		value *= -1;
	}
	//��� �������. � ������, ����� ���� �� ����� 2 ����� � ������ ������ � ��������������� �����. �� ��� � �� ������� ������� (��� ���), �� ��������� �������� ������ ������� ���� ��������.
	//���������� ���� long
	int bit = 0;
	//������ �����, � ������� ����� ������������
	int rank = 0;
	//���� � long �������� ����, �� ����� �� ����������
	while (value != 0) {
		//������ ���, ����� �� ������� ��� ���� int'�, �� ������� ���� ����� �� ���������
		if (bit % (sizeof(int) * 8) == 0)
			rank++;
		//����� ���������� ������ ���������� ���� long'� � ��������������� ����� � �������� ����� long'� ������, ����� �������� ��������� ��������
		this->rawNm[rank] += (value & 1) << bit++;
		value >>= 1;
	}
}

//�������� ���������� ����������
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

//������ ����������� �� 10 ������� ��������� � �������� ��� (� ������ ���� ����� � ������ ���������� ������ � �������� ����), ������� �� ����� ������������ � �����������
BigInteger::BigInteger(std::string value)
{
	//��� ������ �������� ������� BigInteger 
	this->countRank = 0;
	this->rawNm = new unsigned int[1];
	this->rawNm[0] = 0;
	//����� ������� ������ �������� �� ������, ����� ���� ����� � ��� ��������
	const char* c_str = value.c_str();
	int index = 0;
	//���� ������ ������ - �����, �� ���������� ������������ � ����������� ���������� �������, ����� �� ���������� �� ���� ��� ���
	if (c_str[0] == '-') {
		index++;
		this->isNegative = true;
	}
	else {
		this->isNegative = false;
	}
	//������ ������� ������ ������ � ���������� ��� �� ��������� ����� �������, ��������� ��� ������������ ��������������� �������. ���� �� ������� ������ ����� ����� ����, �� ������� ����� 0. ����� ��� �������� ����������, �� ����� � �� �� ����
	//��� ��� ���������� ���, ��� ����
	for (; index < value.size(); ++index) {
		//���� �������� �� �����, �� ������ 0 � ��������
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

//��� ����������� �����������. �� ��������� ��������� ��� ������, �� ������ ������ ������ ��������, ����� �� �� ��� ������
BigInteger::BigInteger(const BigInteger& other)
{
	this->countRank = other.countRank;
	this->rawNm = new unsigned int[other.countRank];
	this->isNegative = other.isNegative;
	for (int i = 0; i < other.countRank; ++i) {
		this->rawNm[i] = other.rawNm[i];
	}
}

//��� ����������� ��������. �� ������ �������� ������ � ����������� BigInteger
BigInteger::BigInteger(const BigInteger&& other)
{
	this->countRank = other.countRank;
	this->rawNm = other.rawNm;
	this->isNegative = other.isNegative;
}

//�������� ����������� �� ���� ������������ ������ ������ ������������ �����������
BigInteger& BigInteger::operator=(const BigInteger& other)
{
	BigInteger* result = new BigInteger(other);
	return *result;
}

//��� �� � �������� ��������� ��������
BigInteger& BigInteger::operator=(const BigInteger&& other)
{
	BigInteger* result = new BigInteger(other);
	return *result;
}

//����� ����� �������� ���������������
bool BigInteger::operator==(BigInteger other)
{
	//��� ������ ������� ������������ ������ �����, �� �������� ����� ����������. ��� ���������� ������� �����, ��������� �� ����� ���������� �����
	int usingRank = this->countRank;
	//���� ���������� �������� � ����� ������, �� ��� ���������� ���������, ��� ������� ���� �������� �������, ����� ����� ����� �� �����
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
	//����� �������� �� ���� ��������. ���� ���� 1 ���������, �� ���������� false. ���� �� ������ ��� ��������, �� ������, �� ����� true
	for (int i = 0; i < usingRank; ++i) {
		if (this->rawNm[i] != other.rawNm[i]) {
			return false;
		}
	}
	return true;
}

//�������� ����������� ����� �������������� ��������� ���������, ��� ��� ������ ���������� �������� �������� �� ���������� �������
bool BigInteger::operator!=(BigInteger other)
{
	return !this->operator==(other);
}

//�������� ������, � ����� ����� �� �������� ���������, �� ����� ����������� ���� �� �������� ������� � ��������
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

//�������� ������ ��� ����� ��������� �������� �� ��������� ������, ��� � �������������
bool BigInteger::operator>=(BigInteger other)
{
	return !this->operator<(other);
}

//�������� ������ �� ����� ���� ����� ��, ��� � "������", �� � �������� �� ������ true � false �������. ��� �� �������� ���������� return, ������� ���������� ��������� �����.
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

//�������� �������� ������ ���������� ��������� �������� ������, ������ ���� ������������� ��������� ���������������
bool BigInteger::operator<=(BigInteger other)
{
	return !this->operator>(other);
}

//�������� ��������
BigInteger BigInteger::operator+(BigInteger other)
{
	//������� ������, ���������� ���������, ���������� ������ �������� BigInteger
	BigInteger result = BigInteger(*this);
	//�����, ��������� � ���� � ������ ������ �������������� ����� �� ������� bigInteger
	for (int i = 0; i < other.countRank; ++i) {
		result.sumWithInt(other.rawNm[i], i);
	}
	return result;
}

//�������� ���������. � ��� ������� �������
BigInteger BigInteger::operator-(BigInteger other)
{
	//������ ����� ����� ��
	BigInteger result = BigInteger(*this);
	//�� ��� �� ������ ���� ����� �� ���������������, ����� ���������� ���������
	result.isNegative = !result.isNegative;
	for (int i = 0; i < other.countRank; ++i) {
		result.sumWithInt(other.rawNm[i], i);
	}
	//������ ���� ���������, ��� ����� �� ����� 0
	for (int i = 0; i < result.countRank; ++i) {
		//���� ��� ���, �� ������� ������ ���� ����� � ���������� ���������
		if (result.rawNm[i] != 0) {
			result.isNegative = !result.isNegative;
			return result;
		}
	}
	//���� 0, �� ����������� ���� ��� �����������������
	result.isNegative = false;
	return result;

}

//��� ���������� ������������� ������� �������� ���������
BigInteger BigInteger::operator*(BigInteger other)
{
	//���� ������ ���������: ��������� � ���������� ��� ����� ��������� (������ ��������), �� ��������� ����� ���������� ��� ���������. �� ������ ����� �� ���������� ��� ������� ������, �� � ������
	//������� �� ����� �������� �� ������ ����������, ��� � �������� ������ � ����� ������� ��������� ����������� � �������� �����, ������� ������ ����� ������������ ������� ��������� �� 2^n
	BigInteger result = BigInteger();
	//��� ����� ��������� ������ ���������, ���������� �� 2^n
	BigInteger part = BigInteger(*this);
	//��� ������� ��� ������� �����, � ������� �� ��������
	int bit = 0;
	//���� ����� �������� ��� ���� ������� �����
	while (bit < other.countRank * sizeof(int) * 8) {
		//��������������, ���� n-�� ��� ����� 1, �� �� ��������� � ���������� bigInteger1 * 2^n
		if (((other.rawNm[bit / (8 * sizeof(int))] >> (bit % (8 * sizeof(int)))) & 1) == 1) {
			result += part;
		}
		//� �������� �������� � ����� ������������ ��������� �� 2
		part += part;
		bit++;
	}
	return result;
}

//� ���������, ��������� �������� ������� �� ���������� ��� ������� ��������, ������� ��� ����� ������������ ����� ��������� ������� ����� �� ������� �� ��� ���, ���� ��� ��������
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

//��� �������� �������� ������. � ��� �� �������� ������, �� ������ ����� ����� �������������. ����� 0, �����������.
BigInteger BigInteger::operator-() const
{
	BigInteger result = BigInteger(*this);
	//������ ���� ���������, ��� ����� �� ����� 0
	for (int i = 0; i < result.countRank; ++i) {
		//���� ��� ���, �� ������� ������ ���� ����� � ���������� ���������
		if (result.rawNm[i] != 0) {
			result.isNegative = true;
			return result;
		}
	}
	//���� 0, �� ����������� ���� ��� �����������������
	result.isNegative = false;
	return result;
}

//�������� �������� ����� ������ ����� �������������. ��� ���� �������� �� 0 �� �����
BigInteger BigInteger::operator+() const
{
	BigInteger result = BigInteger(*this);
	result.isNegative = false;
	return result;
}

//�������� += ������������ ������������ ���������� �������� � ������������
BigInteger BigInteger::operator+=(BigInteger other)
{
	*this = *this + other;
	return *this;
}

//�� � �������� ���������� ������������ += 1
BigInteger BigInteger::operator++()
{
	*this += 1;
	return *this;
}

//� �� �����, ��� �������� ���������� ������������ -= 1
BigInteger BigInteger::operator--()
{
	*this += -1;
	return *this;
}

//������������� ���-�� ���������� BigInteger � ������ ������, ������� ����� ������������ ���� ���� ������� �����
std::string BigInteger::to_string(const BigInteger& other)
{
	//������ ���������� ������������� ������
	std::string result = "";
	//����� �� ������������� ���������� ��������, ������� ��� �����
	BigInteger copy = BigInteger(other);
	//��� ������� �� 10, �������� ������ ��� BigInteger
	BigInteger ten = BigInteger(10);
	while (copy > ten) {
		//���� ������ � ���������: �� ���� ������� �� ������� ����� �� 10 � ���������� ��� ������ � ������, ����� ���� ����� ����� �� 10
		BigInteger temp = copy / ten;
		result = (char)((copy - temp * ten).rawNm[0] % 10 + '0') + result;
		copy = temp;
	}
	//���� ����� ���������, �� ��� ���� �� ���������, ��� ��� �� 0. �������� � ���, ��� ������������� ��������� -0 � ���� ������ �� �����, �� �� � ����� ������ �� ������ �� ��������, ������� ����� ���� �� ��������� ����� ���������� ��� ������
	if (other.isNegative) {
		for (int i = 0; i < result.size(); ++i) {
			if (result.c_str()[i] != '0') {
				result = '-' + result;
			}
		}
	}
	return result;
}