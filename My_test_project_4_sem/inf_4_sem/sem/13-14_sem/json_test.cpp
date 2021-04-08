//#include "C:\for_cpp\cpp_bibl\json\json.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>  

#include "../../aux_files/json.hpp"

// This file doesn't have header.
// You need to change func.name 'json_test' to 'main'
// Don't forget to add "json.hpp" to your project

using json = nlohmann::json;

int main()
{
	std::string Name, Surname, Age;

	std::cout << "Enter Name: ";
	std::getline(std::cin, Name);

	std::cout << "Enter Surname: ";
	std::getline(std::cin, Surname);

	std::cout << "Enter Age: ";
	std::getline(std::cin, Age);
	std::cout << "\n";

	json j;
	j["Name"] = Name;
	j["Surname"] = Surname;
	j["Age"] = Age;

	const char* path = "inf_4_sem/sem/13-14_sem/pearson.json";
	std::ofstream fout(path, std::ios::out);

	if (fout.is_open())
	{
		fout << std::setw(4) << j;
	}
	else
		std::cout << "File is unavailable\n";
}