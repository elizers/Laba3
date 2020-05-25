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

// печать пунктов меню для изменения записи счёта
void print_change_menu()
{
	std::cout << std::endl
		<< "Выберите один из пунктов записи, который необходимо изменить:" << "\n"
		<< "1 - название фирмы" << "\n"
		<< "2 - вид работ" << "\n"
		<< "3 - единица измерения" << "\n"
		<< "4 - стоимость единицы выполненной работы" << "\n"
		<< "5 - дата исполнения" << "\n"
		<< "6 - объем работ" << "\n"
		<< "0 - ничего не нужно изменять" << "\n"
		<< std::endl;
}

// печать пунктов главного меню в зависимости от наличия элементов в списке
int print_main_menu(bool ContainerIsEmpty = false) 
{
	int stop_item = 2;
	std::cout << std::endl << "Выберите один из пунктов меню:" << std::endl	
	<< "1 - добавить запись" << std::endl;
	if (!ContainerIsEmpty) 
	{
		std::cout << "2 - изменить запись" << std::endl
			<< "3 - удалить запись" << std::endl
			<< "4 - очистить контейнер" << std::endl
			<< "5 - вывести записи в консоль" << std::endl
			<< "6 - напечатать записи в новый файл" << std::endl
			<< "7 - создать контейнер из записей по заданному критерию" << std::endl
			<< "8 - сохранить записи в контейнере" << std::endl;
		stop_item = 8;
	}
	std::cout << "0 - выйти из программы" << std::endl;
	std::cout << std::endl;
	return stop_item;
}

// проверка имени файла на несовпадение с файлом "Container.txt"
bool check_equal(std::string name_file)
{
	return (name_file == CONTAINER);
}

// главное меню для программы
void main_menu()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::cout << "Программа демонстрирует виртуальную смету работ." << std::endl;
	int stop_item, 
	cur_item = 1;
	Accounts<AccountStructure> controller;
	controller.fill_container(CONTAINER);

	while (cur_item != 0)
	{
		stop_item = print_main_menu(controller.empty());

		cur_item = get_num("Ваш выбор - ", "Ошибка! Такой пункт отсутствует в меню. Повторите ввод: ", 0, stop_item);
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
						cur_change_item = get_num("Ваш выбор - ", "Ошибка! Такой пункт отсутствует в меню. Повторите ввод: ", 0, 6);
						if (cur_change_item != 0)
						{
							std::cout << std::endl << "Введите новое значение для выбранного пункта: ";
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
				std::cout << std::endl << "Контейнер очищен." << std::endl;
				break;
			}

			case 5:
			{
				controller.print_container();
				break;
			}

			case 6:
			{
				std::string name = get_string(check_equal, "Введите имя текстового файла: ", "Недоступное имя файла! Введите другое имя текстового файла: ");
				controller.fill_file_from_container(name, "Файл успешно создан и заполнен.");
				break;
			}

			case 7:
			{				
				std::list<AccountStructure> result;
				AccountStructure tmp;
				int search_element = get_num("По какому элементу будет осуществляться поиск?\n1 - название фирмы\n2 - вид работ\n3 - дата исполнения\nВаш выбор - ", "\nОшибка, повторите ввод!\n", 1, 3);
				switch (search_element)
				{
					case 1:
					{
						std::string firm;
						std::cout << "Введите название фирмы: ";
						getline(std::cin, firm);
						auto check = [firm](const AccountStructure& br)
						{
							return br.get_name_of_firm() == firm;
						};
						if (get_num("Какой алгоритм поиска нужно использовать: 1 - линейный, 2 - бинарный?\nВаш выбор - ", "\nОшибка, повторите ввод!\n", 1, 2) == 1)
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
						std::cout << "Введите вид работы: ";
						getline(std::cin, type_of_work);
						auto check = [type_of_work](const AccountStructure& br)
						{
							return br.get_type_of_work() == type_of_work;
						};
						if (get_num("Какой алгоритм поиска нужно использовать: 1 - линейный, 2 - бинарный?\nВаш выбор - ", "\nОшибка, повторите ввод!\n", 1, 2) == 1)
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
						std::cout << "Введите дату исполнения: ";
						input_date(date);
						auto check = [date](const AccountStructure& br)
						{
							return br.get_date_of_execution() == date;
						};
						if (get_num("Какой алгоритм поиска нужно использовать: 1 - линейный, 2 - бинарный?\nВаш выбор - ", "\nОшибка, повторите ввод!\n", 1, 2) == 1)
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
					std::cout << std::endl << "Записи с заданным критерием отсутствуют!" << std::endl;
				}
				else 
				{
					std::cout << std::endl << "По заданному критерию сформирован контейнер из " << result.size() << " записи(-ей)." << std::endl;
					print(result);
					if (get_num("Хотите записать данный контейнер в файл? 1 - да, 2 - нет.\nВаш выбор - ", "\nОшибка, повторите ввод!\n", 1, 2) == 1)
					{
						std::string name = get_string(check_equal, "Введите имя текстового файла: ", "Недоступное имя файла! Введите другое имя текстового файла: ");
						fill_file(result, name, "Файл успешно создан и заполнен.");
					}
				}
				break;
			}

			case 8:
			{
				controller.fill_file_from_container(CONTAINER, "Записи успешно сохранены в контейнере");
				break;
			}

			case 0:
			{
				if (get_num("Хотите сохранить записи в контейнере? 1 - да, 2 - нет.\nВаш выбор - ", "\nОшибка, повторите ввод!\n", 1, 2) == 1)
				{
					controller.fill_file_from_container(CONTAINER, "Записи успешно сохранены в контейнере");
				}
				else
				{
					break;
				}				
			}
		}
	}
}