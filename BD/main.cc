/*
 * main.cc
 *
 *  Created on: 11 апр. 2022 г.
 *      Author: HP
 */
#include <iostream>
#include <limits>
#include <iomanip>
#include <fstream>
#include <vector>

const char *DB_FILE_NAME = "empl_roster.db";

struct Employee
{
	char name[21];
	char job [16];
	int salary;
};

void print_table_header(){
	std::cout <<
			"  №  |       Employee     |      Job      |Salary|\n"
			"-----+--------------------+---------------+------|\n";
}

void print_table_row(const Employee &empl, int row){
	std::cout <<
		std::setw(4) <<std::right << row << " |" <<
		std::setw(20) << std::left  << empl.name   << "|" <<
		std::setw(15) << std::left  << empl.job    << "|"<<
		std::setw(6)  << std::right << empl.salary << "|"<<
		std::endl;
}

void read_file(const char*filename, std::vector <Employee> &list)
{
	list.clear();
	std::ifstream data_file {filename, std::ios::binary};
	if (not data_file) return;
	Employee empl;
	while(data_file.read( reinterpret_cast<char*>(&empl), sizeof(empl)))
		list.push_back(empl);
	data_file.close();
}

void write_file(const char*filename, std::vector <Employee> &list){
	std::ofstream data_file{filename, std::ios::binary };
	for(auto &&e : list) data_file.write(reinterpret_cast<char*>(&e), sizeof(e));
	data_file.close();
}

void input_employee(std::vector <Employee> &list){
	Employee empl;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Введите имя сотдурника: ";
	std::cin.getline(empl.name, sizeof(empl.name));
	std::cout << "Введите должность     : ";
	std::cin.getline(empl.job, sizeof(empl.job));
	std::cout << "Введите зарплату      : ";
	std::cin >> empl.salary;
	list.push_back(empl);
}
int main(){

	std::vector <Employee> empl_roster;
	read_file(DB_FILE_NAME, empl_roster);
	int choice;
	do{
		menu:
		std::cout <<
				"Действия над списокм:\n"
				"---------------------\n"
				"1. Вывести список\n"
				"2. Добавить сотрудника\n"
				"3. Изменить запись\n"
				"4. Удалить запись\n"
				"\n"
				"0. Выход\n"
				"---->";
		if(not(std::cin >> choice)){
			if(std::cin.eof()){
				std::cerr << "ошбика ввода/вывода" << std::endl;
				return 1;
			}
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			goto menu;
		}
		int i = 0;
		switch(choice){
		case 0:
			std::cout <<"До свидания!" << std::endl;
			break;
		case 1:
			print_table_header();
			for(auto &&e : empl_roster)
					print_table_row(e, i++);
			break;
		case 2:
			input_employee(empl_roster);
			break;
		default:
			std::cout << "Такого варианта нет!" << std::endl;
		}
	}while (choice != 0);
	write_file(DB_FILE_NAME, empl_roster);
	return 0;
}
