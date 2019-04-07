// TuringMachine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include <vector>
#include <string>

#include <iostream>
#include <fstream>
#include <sstream>

#include <conio.h>
#include <windows.h>

#define TURING_MACHINE_SIZE 1000


void textcolor(int foreground, int background)
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

class TuringMachine
{
private:
	std::vector<int> TuringTable;
	char* functionTable;

	int cur_table;
	int cur_function_state;

public:

	TuringMachine(std::vector<int> var);
	~TuringMachine();

	void PrintCurTable();
	void Do();

	inline char* get_FunctionTable() { return functionTable; }
	inline int get_cur_table() { return cur_table; }
	inline int get_cur_function_state() { return cur_function_state; }
};

TuringMachine::TuringMachine(std::vector<int> var) : cur_table(0), cur_function_state(0)
{
	for (std::vector<int>::iterator iter = var.begin() ; iter !=  var.end() ; iter++) {
		TuringTable.insert(TuringTable.end(), *iter, 1);
		TuringTable.push_back(0);
	}

	functionTable = new char[1000];
}

TuringMachine::~TuringMachine()
{
	delete[] functionTable;
}

void TuringMachine::PrintCurTable()
{
	for (int i = 0 ; i < TuringTable.size() ; i++)
	{
		if (i == this->get_cur_table())
		{
			textcolor(1, 0);
			std::cout << TuringTable[i];
			textcolor(15, 0);
		}
		else {
			std::cout << TuringTable[i];
		}
	}
	std::cout << std::endl << "=========== State" << std::endl;
}

void TuringMachine::Do()
{
	int cur_state = TuringTable[cur_table];
	int to_do = functionTable[cur_function_state * 4 + cur_state];
	
	switch (to_do)
	{
	case '0':   // 0 으로 만들기

		cur_function_state = (int)functionTable[cur_function_state *4 + 2 + cur_state];

		TuringTable[cur_table] = 0;

		break;

	case '1':

		cur_function_state = (int)functionTable[cur_function_state * 4 + 2 + cur_state];

		TuringTable[cur_table] = 1;

		break;

	case 'L' :

		cur_function_state = (int)functionTable[cur_function_state * 4 + 2 + cur_state];

		if (cur_table){
			cur_table -= 1;
		}
		else {
			TuringTable.insert(TuringTable.begin(), 1, 0);
		}
		
		break;

	case 'R':
		
		cur_function_state = (int)functionTable[cur_function_state * 4 + 2 + cur_state];

		if (cur_table != TuringTable.size() - 1){
			cur_table += 1;
		}
		else {
			TuringTable.push_back(0);
			cur_table += 1;
		}
		
		break;
	}
}


int main()
{
	std::vector<int> input;
	int n, arg;
	std::cout << "Give Number of Arguement" << std::endl;
	std::cin >> n;
	for (int i = 0; i < n; i++)
	{
		std::cout << "Give " << i << "th Arguement" << std::endl;
		std::cin >> arg;
		input.insert(input.end(), 1, arg);
	}

	TuringMachine a(input);

	a.PrintCurTable();
	
	std::string filePath = "turing.txt";

	std::ifstream openFile( filePath.c_str() );
	if (openFile.is_open())
	{
		std::string line;
		int cur = 0;
		int tmp;

		while (!openFile.eof())
		{
			openFile >> line;
			cur = std::stoi(line);

			openFile >> line;
			a.get_FunctionTable()[cur * 4 + 0] = *(line.c_str());
			openFile >> line;
			a.get_FunctionTable()[cur * 4 + 2] = std::stoi(line);
			openFile >> line;
			a.get_FunctionTable()[cur * 4 + 1] = *(line.c_str());
			openFile >> line;
			a.get_FunctionTable()[cur * 4 + 3] = std::stoi(line);
		}
		openFile.close();
	}


	for (int i = 0; i = 100; i++) {
		a.Do();
		a.PrintCurTable();
		std::cout << "tape number is : " << a.get_cur_table() << std::endl << "function state is " << a.get_cur_function_state() << std::endl;
		std::cout<< std::endl;
		_getch();
	}

}

