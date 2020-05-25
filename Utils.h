#pragma once
#include <string>
#include <functional>

// ������ ������� ����� ������ �� �������
void get_eoln();

// ���� ����� � ����������� ��������� ��� �� �������������� ������� [min, max]
template<typename T>
T get_num(std::string str, std::string err, T min, T max);

// ���� ������ �� �������
std::string get_string(const std::function<bool(const std::string&)>& check, std::string text, std::string error_text);

// ��������� ��������� �� ������
std::string take_field(std::string str);

// �������������� ������ 
template<typename T>
T str_to_val(std::string str);