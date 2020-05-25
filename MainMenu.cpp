#include "MainMenu.h"
#include "Accounts.h"
#include "AccountStructure.h"
#include "Utils.h"
#include <Windows.h>
#include <cstdio>
#include <string>
#include <list>
#include <iostream>

const std::string CONTAINER = "Container.txt";

// ������ ������� ���� ��� ��������� ������ �����
void print_change_menu()
{
	std::cout << std::endl
		<< "�������� ���� �� ������� ������, ������� ���������� ��������:" << "\n"
		<< "1 - �������� �����" << "\n"
		<< "2 - ��� �����" << "\n"
		<< "3 - ������� ���������" << "\n"
		<< "4 - ��������� ������� ����������� ������" << "\n"
		<< "5 - ���� ����������" << "\n"
		<< "6 - ����� �����" << "\n"
		<< "0 - ������ �� ����� ��������" << "\n"
		<< std::endl;
}

// ������ ������� �������� ���� � ����������� �� ������� ��������� � ������
int print_main_menu(bool ContainerIsEmpty = false) 
{
	int stop_item = 2;
	std::cout << std::endl << "�������� ���� �� ������� ����:" << std::endl	
	<< "1 - �������� ������" << std::endl;
	if (!ContainerIsEmpty) 
	{
		std::cout << "2 - �������� ������" << std::endl
			<< "3 - ������� ������" << std::endl
			<< "4 - �������� ���������" << std::endl
			<< "5 - ������� ������ � �������" << std::endl
			<< "6 - ���������� ������ � ����� ����" << std::endl
			<< "7 - ������� ��������� �� ������� �� ��������� ��������" << std::endl
			<< "8 - ��������� ������ � ����������" << std::endl;
		stop_item = 8;
	}
	std::cout << "0 - ����� �� ���������" << std::endl;
	std::cout << std::endl;
	return stop_item;
}

// �������� ����� ����� �� ������������ � ������ "Container.txt"
bool check_equal(std::string name_file)
{
	return (name_file == CONTAINER);
}

// ������� ���� ��� ���������
void main_menu()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::cout << "��������� ������������� ����������� ����� �����." << std::endl;
	int stop_item, 
	cur_item = 1;
	Accounts<AccountStructure> controller;
	controller.fill_container(CONTAINER);

	while (cur_item != 0)
	{
		stop_item = print_main_menu(controller.empty());

		cur_item = get_num("��� ����� - ", "������! ����� ����� ����������� � ����. ��������� ����: ", 0, stop_item);
		switch (cur_item)
		{
			case 1:
			{
				controller.add_elem();
				break;
			}
			case 2:
			{
				controller.change_elem([](AccountStructure& br) -> void
				{
					int cur_change_item = 1;
					while (cur_change_item != 0)
					{
						int tmp_int;
						float tmp_float;
						std::string tmp_str;
						Date tmp_date;
						print_change_menu();
						cur_change_item = get_num("��� ����� - ", "������! ����� ����� ����������� � ����. ��������� ����: ", 0, 6);
						if (cur_change_item != 0)
						{
							std::cout << std::endl << "������� ����� �������� ��� ���������� ������: ";
							switch (cur_change_item)
							{
								case 1:
								{
									getline(std::cin, tmp_str);
									br.set_name_of_firm(tmp_str);
									break;
								}
								case 2:
								{
									getline(std::cin, tmp_str);
									br.set_type_of_work(tmp_str);
									break;
								}
								case 3:
								{
									getline(std::cin, tmp_str);
									br.set_unit(tmp_str);
									break;
								}
								case 4:
								{
									std::cin >> tmp_int;
									br.set_cost_per_unit(tmp_int);
									break;
								}
								case 5:
								{
									input_date(tmp_date);
									br.set_date_of_execution(tmp_date);
									break;
								}
								case 6:
								{
									std::cin >> tmp_float;
									br.set_scope_of_work(tmp_float);
									break;
								}						
							}
						}
					}
				}
				);
				break;
			}

			case 3:
			{
				controller.delete_elem();
				break;
			}

			case 4:
			{
				controller.clear();
				std::cout << std::endl << "��������� ������." << std::endl;
				break;
			}

			case 5:
			{
				controller.print_container();
				break;
			}

			case 6:
			{
				std::string name = get_string(check_equal, "������� ��� ���������� �����: ", "����������� ��� �����! ������� ������ ��� ���������� �����: ");
				controller.fill_file_from_container(name, "���� ������� ������ � ��������.");
				break;
			}

			case 7:
			{				
				std::list<AccountStructure> result;
				AccountStructure tmp;
				int search_element = get_num("�� ������ �������� ����� �������������� �����?\n1 - �������� �����\n2 - ��� �����\n3 - ���� ����������\n��� ����� - ", "\n������, ��������� ����!\n", 1, 3);
				switch (search_element)
				{
					case 1:
					{
						std::string firm;
						std::cout << "������� �������� �����: ";
						getline(std::cin, firm);
						auto check = [firm](const AccountStructure& br)
						{
							return br.get_name_of_firm() == firm;
						};
						if (get_num("����� �������� ������ ����� ������������: 1 - ��������, 2 - ��������?\n��� ����� - ", "\n������, ��������� ����!\n", 1, 2) == 1)
						{
							result = controller.linear_search_elements(check);
						}
						else
						{
							tmp.set_name_of_firm(firm);
							result = controller.binary_search_elements(tmp, [](const AccountStructure& rec1, const AccountStructure& rec2) -> bool
							{
								return rec1.get_name_of_firm() < rec2.get_name_of_firm();
							});
						}
						break;					
					}

					case 2:
					{
						std::string type_of_work;
						std::cout << "������� ��� ������: ";
						getline(std::cin, type_of_work);
						auto check = [type_of_work](const AccountStructure& br)
						{
							return br.get_type_of_work() == type_of_work;
						};
						if (get_num("����� �������� ������ ����� ������������: 1 - ��������, 2 - ��������?\n��� ����� - ", "\n������, ��������� ����!\n", 1, 2) == 1)
						{
							result = controller.linear_search_elements(check);
						}
						else
						{
							tmp.set_type_of_work(type_of_work);
							result = controller.binary_search_elements(tmp, [](const AccountStructure& rec1, const AccountStructure& rec2) -> bool
							{
								return rec1.get_type_of_work() < rec2.get_type_of_work();
							});
						}
						break;
					}

					case 3:
					{
						Date date;
						std::cout << "������� ���� ����������: ";
						input_date(date);
						auto check = [date](const AccountStructure& br)
						{
							return br.get_date_of_execution() == date;
						};
						if (get_num("����� �������� ������ ����� ������������: 1 - ��������, 2 - ��������?\n��� ����� - ", "\n������, ��������� ����!\n", 1, 2) == 1)
						{
							result = controller.linear_search_elements(check);
						}
						else
						{
							tmp.set_date_of_execution(date);
							result = controller.binary_search_elements(tmp, [](const AccountStructure& rec1, const AccountStructure& rec2) -> bool
							{
								return (rec1.get_date_of_execution() < rec2.get_date_of_execution());
							});
						}
						break;
					}
				}

				if (result.empty()) 
				{
					std::cout << std::endl << "������ � �������� ��������� �����������!" << std::endl;
				}
				else 
				{
					std::cout << std::endl << "�� ��������� �������� ����������� ��������� �� " << result.size() << " ������(-��)." << std::endl;
					print(result);
					if (get_num("������ �������� ������ ��������� � ����? 1 - ��, 2 - ���.\n��� ����� - ", "\n������, ��������� ����!\n", 1, 2) == 1)
					{
						std::string name = get_string(check_equal, "������� ��� ���������� �����: ", "����������� ��� �����! ������� ������ ��� ���������� �����: ");
						fill_file(result, name, "���� ������� ������ � ��������.");
					}
				}
				break;
			}

			case 8:
			{
				controller.fill_file_from_container(CONTAINER, "������ ������� ��������� � ����������");
				break;
			}

			case 0:
			{
				if (get_num("������ ��������� ������ � ����������? 1 - ��, 2 - ���.\n��� ����� - ", "\n������, ��������� ����!\n", 1, 2) == 1)
				{
					controller.fill_file_from_container(CONTAINER, "������ ������� ��������� � ����������");
				}
				else
				{
					break;
				}				
			}
		}
	}
}