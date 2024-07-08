#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <io.h>
#include <fcntl.h>
#include "HashTable.h"

using namespace std;

HashTable hashTable = HashTable();

bool MatchByCarNumber(wstring value, Info info) {
	return (info.number.find(value) != wstring::npos);
}

bool MatchByFullname(wstring value, Info info) {
	return (info.fullName.find(value) != wstring::npos);
}

bool MatchByCarBrand(wstring value, Info info) {
	return (info.brand.find(value) != wstring::npos);
}

bool GetAll(wstring value, Info info) {
	return true;
}

wstring InputWithCheckingValidityOfCarNumber(wistream& in) {
	wstring carNumber;
	bool flag;
	vector<int> mask = { 0, 1, 1, 1, 0, 0, 1, 1, 1 };
	wstring letters = L"АВЕКМНОРСТУХавекмнорстухABEKMHOPCTYXabekmhopctyx";
	wstring numbers = L"0123456789";
	in >> carNumber;
	while (true) {
		if (carNumber.size() != 9) {
			wcout << "Invalid size of car number " << carNumber << ". Enter new car number:" << endl << "> ";
			wcin >> carNumber;
			continue;
		}
		flag = true;
		for (int i = 0; i < mask.size(); i++) {
			if (!(!mask[i] && letters.find(carNumber[i]) != wstring::npos
				|| mask[i] && numbers.find(carNumber[i]) != wstring::npos)) {
				wcout << "The car number " << carNumber << " does not match the mask (LNNNLLNNN) or uses unresolved letters."
					<< "Enter new car number:" << endl << "> ";
				flag = false;
				break;
			}
		}
		if (flag) break;
		wcin >> carNumber;
	}
	return carNumber;
}

void ConsoleInput() {
	wstring carNumber, name, surname, patronymic, carBrand, fullName;
	wcout << "Enter the new user's full name:" << endl;
	wcout << "Surname:" << endl << "> ";
	wcin >> surname;
	wcout << "Name:" << endl << "> ";
	wcin >> name;
	wcout << "Patronymic:" << endl << "> ";
	wcin >> patronymic;
	fullName = surname + L" " + name + L" " + patronymic;

	wcout << "Enter the new user's car number:" << endl << "> ";
	carNumber = InputWithCheckingValidityOfCarNumber(wcin);

	wcout << "Enter the new user's car brand (together):" << endl << "> ";
	wcin >> carBrand;

	hashTable.Push(carNumber, Info(carNumber, carBrand, fullName));
	wcout << "New user added." << endl;
}

void FileInput() {
	wcout << "WARNING!!!" << endl
		<< "File filling format:" << endl
		<< "In one line separated by a space:" << endl
		<< "1. User's surname;" << endl
		<< "2. User's name;" << endl
		<< "3. User's patronymic;" << endl
		<< "4. User car's number;" << endl
		<< "5. User car's brand (together)." << endl
		<< "If the wrong text is entered, the reading process will be interrupted." << endl;

	wstring filePath;
	wcout << "Specify absolute path of file:" << endl << "> ";
	wcin >> filePath;
	wifstream wfIn(filePath);
	while (true) {
		if (wfIn.is_open()) {
			break;
		}
		else wcout << "File cannot be opened using this path." << endl;
		wcout << "Specify new absolute path of file:" << endl << "> ";
		wcin >> filePath;
		wifstream wfIn(filePath);
	}

	wfIn.imbue(locale("ru_RU"));
	
	wstring carNumber, name, surname, patronymic, carBrand, fullName;
	while (true) {
		wfIn >> surname;
		wfIn >> name;
		wfIn >> patronymic;
		fullName = surname + L" " + name + L" " + patronymic;
		carNumber = InputWithCheckingValidityOfCarNumber(wfIn);
		wfIn >> carBrand;

		hashTable.Push(carNumber, Info(carNumber, carBrand, fullName));

		if (wfIn.eof()) {
			wcout << "Reading is over." << endl;
			wfIn.close();
			break;
		}
	}
}

void Input() {
	int choice;
	while (true) {
		system("cls");
		wcout << "Choose action:" << endl
			<< "0. Exit;" << endl
			<< "1. Add new user data of a single user (console input);" << endl
			<< "2. Add new user data for multiple users (file input)." << endl
			<< "> ";
		wcin >> choice;
		system("cls");
		switch (choice) {
		case 0:
			return;
		case 1:
			ConsoleInput();
			break;
		case 2:
			FileInput();
			break;
		default:
			wcout << "Action with number " << choice << " does not exist." << endl;
		}
		system("pause");
	}
}

void OutputBy(wstring value, bool (*match)(wstring, Info)) {
	wcout << "User data:" << endl
		<< setw(40) << "Full name" << " " << setw(10) << "Car number" << " " << setw(16) << "Car brand" << endl;
	vector<wstring> keys = hashTable.GetKeys();
	for (int i = 0; i < keys.size(); i++) {
		wstring key = keys[i];
		Info info = hashTable.Get(key);
		if (match(value, info)) {
			wcout << setw(40) << info.fullName << " " << setw(10) << info.number << " " << setw(16) << info.brand << endl;
		}
	}
}

void Output() {
	int choice;
	wstring carNumber, carBrand, name, surname, patronymic, fullName;
	while (true) {
		system("cls");
		wcout << "Choose action:" << endl
			<< "0. Exit;" << endl
			<< "1. Output of user data by car number;" << endl
			<< "2. Output of user data by full name;" << endl
			<< "3. Output of user data by car brand;" << endl
			<< "4. Output of all user data." << endl
			<< "> ";
		wcin >> choice;
		system("cls");
		switch (choice) {
		case 0:
			return;
		case 1:
			wcout << "Output of user data by car number." << endl << endl 
				<< "Enter the car number of user whose data you want find:" << endl << "> ";
			carNumber = InputWithCheckingValidityOfCarNumber(wcin);
			OutputBy(carNumber, MatchByCarNumber);
			break;
		case 2:
			wcout << "Output of user data by full name." << endl << endl
				<< "Enter the full name of user whose data you want find:" << endl;
			wcout << "Surname:" << endl << "> ";
			wcin >> surname;
			wcout << "Name:" << endl << "> ";
			wcin >> name;
			wcout << "Patronymic:" << endl << "> ";
			wcin >> patronymic;
			fullName = surname + L" " + name + L" " + patronymic;
			OutputBy(fullName, MatchByFullname);
			break;
		case 3:
			wcout << "Output of user data by car brand." << endl << endl
				<< "Enter the car brand (together) of user whose data you want find:" << endl << "> ";
			wcin >> carBrand;
			OutputBy(carBrand, MatchByCarBrand);
			break;
		case 4:
			wcout << "Output of all user data." << endl << endl;
			OutputBy(L"", GetAll);
			break;
		default:
			wcout << "Action with number " << choice << " does not exist." << endl;
		}
		system("pause");
	}
}

void DeleteBy(wstring value, bool (*match)(wstring, Info)) {
	wcout << "User data that have been deleted:" << endl
		<< setw(40) << "Full name" << " " << setw(10) << "Car number" << " " << setw(16) << "Car brand" << endl;
	vector<wstring> keys = hashTable.GetKeys();
	for (int i = 0; i < keys.size(); i++) {
		wstring key = keys[i];
		Info info = hashTable.Get(key);
		if (match(value, info)) {
			wcout << setw(40) << info.fullName << " " << setw(10) << info.number << " " << setw(16) << info.brand << endl;
			hashTable.Delete(info.number);
		}
	}
}

void Deletion() {
	int choice;
	wstring carNumber, name, surname, patronymic, fullName, carBrand;
	while (true) {
		system("cls");
		wcout << "Choose action:" << endl
			<< "0. Exit;" << endl
			<< "1. Delete user data by car number;" << endl
			<< "2. Delete user data by full name;" << endl
			<< "3. Delete user data by car brand;" << endl
			<< "4. Delete all user data." << endl
			<< "> ";
		wcin >> choice;
		system("cls");
		switch (choice) {
		case 0:
			return;
		case 1:
			wcout << "Delete user data by car number." << endl << endl
				<< "Enter the car number of user whose data you want delete:" << endl << "> ";
			carNumber = InputWithCheckingValidityOfCarNumber(wcin);
			DeleteBy(carNumber, MatchByCarNumber);
			break;
		case 2:
			wcout << "Delete user data by full name." << endl << endl
				<< "Enter the full name of user whose data you want delete:" << endl;
			wcout << "Surname:" << endl << "> ";
			wcin >> surname;
			wcout << "Name:" << endl << "> ";
			wcin >> name;
			wcout << "Patronymic:" << endl << "> ";
			wcin >> patronymic;
			fullName = surname + L" " + name + L" " + patronymic;
			DeleteBy(fullName, MatchByFullname);
			break;
		case 3:
			wcout << "Delete user data by car brand." << endl << endl
				<< "Enter the car brand (together) of user whose data you want delete:" << endl << "> ";
			wcin >> carBrand;
			DeleteBy(carBrand, MatchByCarBrand);
			break;
		case 4:
			wcout << "Delete all user data." << endl << endl;
			hashTable.Clear();
			wcout << "All users deleted." << endl;
			break;
		default:
			wcout << "Action with number " << choice << " does not exist." << endl;
		}
		system("pause");
	}
}

void Menu() {
	int choice;
	while (true) {
		system("cls");
		wcout << "Choose action:" << endl
			<< "0. Exit;" << endl
			<< "1. Add new user(-s);" << endl
			<< "2. Output data;" << endl
			<< "3. Deletion." << endl
			<< "> ";
		wcin >> choice;
		system("cls");
		switch (choice) {
		case 0:
			return;
		case 1:
			Input();
			break;
		case 2:
			Output();
			break;
		case 3:
			Deletion();
			break;
		default:
			wcout << "Action with number " << choice << " does not exist." << endl;
		}
		system("pause");
	}
}

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);
	Menu();
	hashTable.Clear();
}