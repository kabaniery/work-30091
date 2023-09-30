#pragma once

#ifndef INCLUDE_BIGINT
#define INCLUDE_BIGINT
#include <string>
#include <limits>
#endif // !INCLUDE_BIGINT


class BigInteger
{
public:
	// BigInteger ������������ �� ���� �������������� ����� Int'��. ����������� ��������� ��� ������������� �������� ��������, � ������� ����� � ��������. �������������� ������ ����� ���������� int
	// ������������ �� ���� ���������� ��������. ������, � ������� ������ ��� ����� ������ ��������������.
	unsigned int* rawNm;
	//����� �������� ������
	int countRank;
	//�������� ���������������
	bool isNegative = false;
	//������������ ����� int (��� ������� ����)
	int maxInt = std::numeric_limits<unsigned int>::max();
	BigInteger(int value, int rank);
	//������� ������� ��� ������������ ������ BigInteger � ������� ����� ������, ������������ � ������������ ������
	void sumWithInt(int value, int rank);

	//�������, ������� �������������� ��� �����
	void intialize();


	//�������, ������� ���������� ��������� ����� BigInteger �� �����
	void multWithRaw(unsigned int value);
public:
	//����������� ��-���������
	BigInteger();
	//����������� �� ������ �����
	BigInteger(int value);
	//����������� �� ������ �����, �� � 2 ���� ������� ��������� 
	BigInteger(long value);
	//����������� �� ������ �����, �� ��� ������� � 2 ����
	BigInteger(long long value);
	//����������� �� ������
	BigInteger(std::string value);
	//����������� �����������
	BigInteger(const BigInteger& other);
	//����������� �����������
	BigInteger(const BigInteger&& other);

	//�������� �������������� ������������
	BigInteger& operator =(const BigInteger& other);
	//�������� ����������� ����������
	BigInteger& operator =(const BigInteger&& other);
	//�������� ��������� ���������������
	bool operator ==(BigInteger other);
	//�������� ��������� �����������
	bool operator !=(BigInteger other);
	//�������� ��������� "������ ������"
	bool operator >(BigInteger other);
	//�������� ��������� "�� ������"
	bool operator >=(BigInteger other);
	//�������� ��������� "������ ������"
	bool operator <(BigInteger other);
	//�������� ���������� "�� ������"
	bool operator <=(BigInteger other);

	//�������� ��������
	BigInteger operator +(BigInteger other);
	//�������� ���������
	BigInteger operator -(BigInteger other);
	//�������� ���������
	BigInteger operator *(BigInteger other);
	//�������� �������
	BigInteger operator /(BigInteger other);
	//�������� �������� ������
	BigInteger operator -() const;
	//�������� �������� �����
	BigInteger operator +() const;
	//�������� ����������
	BigInteger operator +=(BigInteger other);
	//�������� ����������
	BigInteger operator ++();
	//�������� ����������
	BigInteger operator --();

	//������� ���������� � ������
	std::string to_string(const BigInteger& other);
};


