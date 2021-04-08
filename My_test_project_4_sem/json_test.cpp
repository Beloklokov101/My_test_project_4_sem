#include "C:\for_cpp\cpp_bibl\json\json.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>  

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

	std::ofstream fout("pearson.json", std::ios::out);
	fout << std::setw(4) << j;
}