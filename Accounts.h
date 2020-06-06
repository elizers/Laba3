#pragma once
#include <iterator>
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <functional>
#include <list>
#include <numeric>

// ���������� ����� ���������� ������������
template<typename T>
void fill_file(const std::list<T>& list, std::string filename, std::string message);		

// ������ ��������� ������������ � �������
template<typename T>
void print(const std::list<T>& list);	


// ��������� ����� 
template<typename T>
class Accounts
{
private:	
	// ��������� ��� ���������� ��� �������� ������ - ������
	std::list<T> _list;	
public:
	// ���������� ��������
	void add_elem(); 

	// ��������� �������� � ������� ���������� ������� 
	bool change_elem(std::function<void(T&)> change);

	// �������� ��������
	bool delete_elem(); 

	// ������� ����������
	void clear(); 

	// �������� ���������� �� �������
	bool empty(); 

	// ���� ��������� �� �����
	void fill_container(std::string filename); 

	// ���������� ����� ���������� ����������
	void fill_file_from_container(std::string filename, std::string message); 

	// ������ ��������� ���������� � �������	
	void print_container(); 

	// �������� ����� ��������� �� �������� ��������� 
	std::list<T> linear_search_elements(std::function<bool(const T&)> check);

	// �������� ����� ��������� �� �������� ��������
	std::list<T> binary_search_elements(const T& value, std::function<bool(const T&, const T&)> compare);
};

template<typename T>
void Accounts<T>::add_elem()
{
	std::cout << std::endl << "������� �������, ������� ���������� ��������:" << std::endl;
	T tmp;
	add(tmp);
	_list.push_back(tmp);
	std::cout << std::endl << "�������� ������� ������� ��������." << std::endl;
}

template<typename T>
bool Accounts<T>::change_elem(std::function<void(T&)> change)
{
	std::cout << std::endl << "������� �������, ������� ���������� ��������:" << std::endl;
	T tmp;
	add(tmp);
	auto iter = find(_list.begin(), _list.end(), tmp);
	if (iter != _list.end())
	{
		std::cout << std::endl << "�������� ������� ������." << std::endl;
		change(*iter);
		std::cout << std::endl << "�������� ������� ������� ������." << std::endl;
		return true;
	}
	else
	{
		std::cout << std::endl << "�������� ������� �����������." << std::endl;
		return false;
	}
}

template<typename T>
bool Accounts<T>::delete_elem()
{
	std::cout << std::endl << "������� �������, ������� ���������� �������:" << std::endl;
	T tmp;
	add(tmp);
	auto iter = find(_list.begin(), _list.end(), tmp);
	if (iter != _list.end())
	{
		_list.erase(iter);
		std::cout << std::endl << "�������� ������� ������� �����." << std::endl;
		return true;
	}
	else
	{
		std::cout << std::endl << "�������� ������� �����������." << std::endl;
		return false;
	}
}

template<typename T>
void Accounts<T>::clear()
{
	_list.clear();
}

template<typename T>
bool Accounts<T>::empty()
{
	return _list.empty();
}

template<typename T>
void Accounts<T>::fill_container(std::string filename)
{
	std::ifstream fin(filename);
	if (!fin.is_open())
		std::cout << std::endl << "�� ������ ������� ���������!" << std::endl;
	else
	{
		if (fin.peek() == EOF)
		{
			std::cout << std::endl << "��������� ������." << std::endl;
		}
		else
		{
			copy(std::istream_iterator<T>(fin), std::istream_iterator<T>(), std::back_inserter(_list));
		}
		fin.close();
	}
}

template<typename T>
void Accounts<T>::fill_file_from_container(std::string filename, std::string message)
{	
	fill_file(_list, filename, message);
}

template<typename T>
void Accounts<T>::print_container()
{
	if (_list.empty())
	{
		std::cout << std::endl << "������ ��������� ����!" << std::endl;
	}
	else
	{
		std::ostream_iterator<T> ositer(std::cout);
		std::cout << std::endl << "������ ��������� �������� ��������� ��������:" << std::endl;
		std::for_each(_list.begin(), _list.end(), [&ositer](const T& elem)
		{
			*ositer++ = elem;
			std::cout << "������ ��������� ������: " << elem.get_cost_per_unit() * elem.get_scope_of_work() << std::endl;
			std::cout << std::endl;
		});
		std::cout << "�������� ��������� ���� �����: " <<
			std::accumulate(_list.begin(), _list.end(), 0.0f, [](float number, const T& elem)
		{ return  number + elem.get_cost_per_unit() * elem.get_scope_of_work(); }) << std::endl;
	}
}

template<typename T>
std::list<T> Accounts<T>::linear_search_elements(std::function<bool(const T&)> check)
{
	std::list<T> result_list;
	for (T elem : _list)
	{
		if (check(elem))
		{
			result_list.push_back(elem);
		}
	}
	return result_list;
}

template<typename T>
std::list<T> Accounts<T>::binary_search_elements(const T& value, std::function<bool(const T&, const T&)> compare)
{
	_list.sort(compare);
	std::list<T> result;
	result.insert(result.begin(), std::lower_bound(_list.begin(), _list.end(), value, compare), std::upper_bound(_list.begin(), _list.end(), value, compare));
	return result;
}
 
template<typename T>
void fill_file(const std::list<T>& list, std::string filename, std::string message)
{
	std::ofstream fout(filename);
	if (!fout.is_open())
	{
		std::cout << std::endl << "���� � ����� ������ �� ������� �������!" << std::endl;
	}
	else
	{
		std::ostream_iterator<T> ositer(fout, "\n");
		copy(list.begin(), list.end(), ositer);
		std::cout << std::endl << message << std::endl;
		fout.close();
	}
}

// delete
template<typename T>
void print(const std::list<T>& list)
{
	
}
