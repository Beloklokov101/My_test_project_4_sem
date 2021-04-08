#include <iostream>

//This file doesn't have header.
//You need to change func. name 'BankCell' to 'main'

class BankCell
{
	int cell_number;

public:
	BankCell(const int &number): cell_number(number) 
	{
		std::cout << "Bank Cell number " << cell_number << " has been opened.\n";
	}
	~BankCell() 
	{
		std::cout << "Bank Cell number " << cell_number << " has been destroyed.\n";
	}

	friend	std::ostream& operator<< (std::ostream& out, const BankCell& cell);
};

std::ostream& operator<<(std::ostream& out, const BankCell &cell)
{
	std::cout << "Bank cell number " << cell.cell_number;
	return out;
}



class Human
{
	std::shared_ptr<BankCell> cell_ptr;
	std::string human_name;

public:
	Human(const std::string& name) : human_name(name) 
	{
		std::cout << "Human with the name " << human_name << " is born.\n";
	}
	~Human() 
	{
		std::cout << "Human with the name " << human_name << " is dead.\n";
	}

	void set_cell_ptr(const std::shared_ptr<BankCell>& new_cell_ptr) 
	{
		cell_ptr = new_cell_ptr;
	}

	std::shared_ptr<BankCell> get_cell_ptr()
	{
		return cell_ptr;
	}

	friend std::ostream& operator<<(std::ostream& out, const Human& h);
};

std::ostream& operator<<(std::ostream& out, const Human& h)
{
	std::cout << "Human named " << h.human_name << " has cell pointer " << h.cell_ptr << std::endl;
	return out;
}



int BankCell()
{
	//std::shared_ptr<BankCell> cell_222 = std::make_shared<BankCell>(222);
	
	
	std::unique_ptr<Human> anton = std::make_unique<Human>("Anton");
	std::unique_ptr<Human> egor = std::make_unique<Human>("Egor");
	//std::unique_ptr<Human> maksim = std::make_unique<Human>("Maksim");

	anton->set_cell_ptr(std::make_shared<BankCell>(222));
	egor->set_cell_ptr(anton->get_cell_ptr());
	//maksim->set_cell_ptr(egor->get_cell_ptr());
	

	//std::cout << *cell_222 << " has pointer " << cell_222 << std::endl;
	std::cout << *anton << *egor;
}