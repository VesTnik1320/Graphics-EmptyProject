#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>
#include <math.h>
#include <cmath>
#include <string>
const int MAXS = 10000;
template <class T>
class TStack
{
	T* pMem;
	int MaxSize, Num;
public:
	TStack(int _MaxSize = 10); 
	~TStack(); 
	TStack(const TStack& s); 
	int GetSize() { return MaxSize; } 
	int GetStartIndex() { return Num; } 
	TStack& operator=(const TStack<T> s); 
	bool operator==(const TStack& s) const;
	bool operator!=(const TStack& s) const;
	T Pop(); 
	void Push(T val); 
	bool Empty() const;
	bool Full() const; 
	T Top() const; 
	void Clear();
	bool Check(std::string str);
};
template <class T>
TStack<T>::TStack(int _MaxSize)
{
	if (_MaxSize < 0 || _MaxSize > MAXS)
		throw - 52;
	MaxSize = _MaxSize;
	Num = -1;
	pMem = new T[MaxSize];
}
template <class T>
TStack<T>::TStack(const TStack<T>& s)
{
	if (s.MaxSize < 0 || s.MaxSize > MAXS || s.Num < -1 || s.Num >= s.MaxSize)
		throw - 2;
	MaxSize = s.MaxSize;
	Num = s.Num;
	pMem = new T[MaxSize];
	for (int i = 0; i <= Num; i++)
		pMem[i] = s.pMem[i];
}
template <class T>
TStack<T>::~TStack()
{
	delete[] pMem;
}
template <class T>
TStack<T>& TStack<T>::operator=(const TStack<T> s)
{
	if (this == &s)
		return *this;
	if (MaxSize != s.MaxSize)
	{
		MaxSize = s.MaxSize;
		delete[] pMem;
		pMem = new T[MaxSize];
	}
	Num = s.Num;
	for (int i = 0; i <= Num; i++)
		pMem[i] = s.pMem[i];
	return *this;
}
template <class T>
bool TStack<T>::operator==(const TStack& s) const
{
	if (this == &s)
		return true;
	if (MaxSize != s.MaxSize)
		return false;
	if (Num != s.Num)
		return false;
	for (int i = 0; i <= Num; i++) {
		if (pMem[i] != s.pMem[i])
			return false;
	}
	return true;
}
template <class T>
bool TStack<T>::operator!=(const TStack& s) const
{
	return !(*this == s);
}
template <class T>
bool TStack<T>::Empty() const
{
	if (Num == -1)
		return true;
	return false;
}
template <class T>
bool TStack<T>::Full() const
{
	if (Num == MaxSize - 1)
		return true;
	return false;
}
template <class T>
T TStack<T>::Pop()
{
	if (this->Empty())
		throw - 3;
	T tmp = pMem[Num];
	Num--;
	return tmp;
}
template <class T>
void TStack<T>::Push(T val)
{
	if (this->Full())
		throw - 4;
	Num++;
	pMem[Num] = val;
}
template <class T>
T TStack<T>::Top() const
{
	if (this->Empty())
		throw - 5;
	return pMem[Num];
}
template <class T>
void TStack<T>::Clear() {
	Num = -1;
}
template <class T>
bool TStack<T>::Check(std::string str)
{
	TStack<char> s;
	bool res = true;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '(')
			s.Push('(');
		if (str[i] == ')')
		{
			if (s.Empty())
				return false;
			s.Pop();
		}
	}
	if (!s.Empty())
		return false;
	return true;
}
class TCalc
{
	std::string infix;
	std::string postfix;
	TStack<double> StNum;
	TStack<char> StChar;
public:
	TCalc();
	void SetInfix(std::string _infix) {
		infix = _infix;
	}
	void SetPostfix(std::string _postfix) {
		postfix = _postfix;
	}
	std::string GetInfix() {
		return infix;
	}
	std::string GetPostfix() {
		return postfix;
	}
	void ToPostfix();
	double CalcPostfix();
	double Calc();
	int Prior(char op);
};
TCalc::TCalc()
{
	StNum = TStack<double>(MAXS);
	StChar = TStack<char>(MAXS);
}
int TCalc::Prior(char op)
{
	if (op == '+' || op == '-')
		return 1;
	else if (op == '*' || op == '/')
		return 2;
	else if (op == '^')
		return 3;
	else return 0;
}
double TCalc::CalcPostfix() {
	StNum.Clear();
	std::string number = "";
	for (int i = 0; i < postfix.length(); i++) {
		if (postfix[i] >= '0' && postfix[i] <= '9' || postfix[i] == '.' || postfix[i] == '_') {
			if (postfix[i] == '_') { 
				number += '-';
			}
			else {
				number += postfix[i];
			}
		}
		else if (postfix[i] == ' ' && !number.empty()) {
			
			StNum.Push(stod(number));
			number = "";
		}
		else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '^') {
			double Num2 = StNum.Pop();
			double Num1 = StNum.Pop();
			if (postfix[i] == '+') {
				StNum.Push(Num1 + Num2);
			}
			else if (postfix[i] == '-') {
				StNum.Push(Num1 - Num2);
			}
			else if (postfix[i] == '*') {
				StNum.Push(Num1 * Num2);
			}
			else if (postfix[i] == '/') {
				if (Num2 == 0) throw - 6;
				StNum.Push(Num1 / Num2);
			}
			else if (postfix[i] == '^') {
				StNum.Push(pow(Num1, Num2));
			}
		}
	}
	if (!number.empty()) {
		StNum.Push(stod(number));
	}
	double a = StNum.Pop();
	if (!StNum.Empty()) {
		throw - 7;
	}
	return a;
}
void TCalc::ToPostfix() {
	postfix = "";
	StChar.Clear();
	std::string s = "(" + infix + ")";
	if (!StChar.Check(infix)) {
		throw - 8;
	}

	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '(') {
			StChar.Push(s[i]);
		}
		else if (s[i - 1] == '(' && s[i] == '-') {
			postfix += "_";
		}
		else if ((s[i] >= '0' && s[i] <= '9') || s[i] == '.') {
			while (i < s.length() && ((s[i] >= '0' && s[i] <= '9') || s[i] == '.')) {
				postfix += s[i];
				i++;
			}
			i--;
			postfix += ' ';
		}
		else if (s[i] == ')') {
			while (!StChar.Empty() && StChar.Top() != '(') {
				postfix += StChar.Pop();
				postfix += ' ';
			}
			if (!StChar.Empty()) {
				StChar.Pop();
			}
		}
		else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^') {
			while (!StChar.Empty() && Prior(StChar.Top()) >= Prior(s[i])) {
				postfix += StChar.Pop();
				postfix += ' ';
			}
			StChar.Push(s[i]);
		}
	}
	if (!StChar.Empty()) {
		throw - 9;
	}
}
double TCalc::Calc() {
	std::string str = "(" + infix + ")";
	StNum.Clear();
	StChar.Clear();
	if (!StChar.Check(infix)) {
		throw - 10;
	}
	for (int i = 0; i < str.size(); i++)
	{
		char tmp = str[i];
		if (tmp == '(')
			StChar.Push(tmp);
		else if (str[i - 1] == '(' && tmp == '-')
			str[i] = '_';
		else if (i > 0 && tmp >= '0' && tmp <= '9' && str[i - 1] == '_')
		{
			size_t idx;
			double num = std::stod(&tmp, &idx);
			StNum.Push(num * (-1.0));
			i += idx - 1;
		}
		else if (tmp >= '0' && tmp <= '9' || tmp == '.') {
			size_t idx;
			double num = std::stod(&tmp, &idx);
			StNum.Push(num);
			i += idx - 1;
		}
		else if (tmp == ')')
		{
			char a = StChar.Pop();
			while (a != '(')
			{
				double Num2 = StNum.Pop();
				double Num1 = StNum.Pop();
				if (a == '+')
					StNum.Push(Num1 + Num2);
				if (a == '-')
					StNum.Push(Num1 - Num2);
				if (a == '*')
					StNum.Push(Num1 * Num2);
				if (a == '/')
				{
					if (Num2 == 0)
						throw - 1;
					StNum.Push(Num1 / Num2);
				}
				if (a == '^')
				{
					int p = pow(Num2, -1);
					if (p % 2 == 0 && Num1 < 0)
						throw - 11;
					StNum.Push(pow(Num1, Num2));
				}
				a = StChar.Pop();
			}
		}
		else if (tmp == '+' || tmp == '-' || tmp == '*' || tmp == '/' || tmp == '^')
		{
			while (Prior(StChar.Top()) >= Prior(tmp)) {
				double Num2 = StNum.Pop();
				double Num1 = StNum.Pop();
				char a = StChar.Pop();
				if (a == '+')
					StNum.Push(Num1 + Num2);
				if (a == '-')
					StNum.Push(Num1 - Num2);
				if (a == '*')
					StNum.Push(Num1 * Num2);
				if (a == '/')
				{
					if (Num2 == 0)
						throw - 12;
					StNum.Push(Num1 / Num2);
				}
				if (a == '^')
				{
					int p = pow(Num2, -1);
					if (p % 2 == 0 && Num1 < 0)
						throw - 13;
					StNum.Push(pow(Num1, Num2));
				}
			}
			StChar.Push(tmp);
		}
	}
	double a = StNum.Pop();
	if (StNum.Empty() == 0)
		throw - 14;
	return a;
}