#include "HashTable.h"

Info::Info() {}

Info::Info(wstring _number, wstring _brand, wstring _fullName) {
	number = _number;
	brand = _brand;
	fullName = _fullName;
}

HashTable::Node::Node(Info info) {
	_info = info;
	deleted = false;
}

void HashTable::restructureTable() {
	vector<Node*> prevTable = table;
	table.clear();
	for (int i = 0; i < prevTable.size() * 2; i++) {
		Node* element = new Node(Info(L"", L"", L""));
		element->deleted = true;
		table.push_back(element);
	}
	for (int i = 0; i < prevTable.size(); i++) {
		if (!prevTable[i]->deleted) {
			Push(prevTable[i]->_info.number, prevTable[i]->_info);
		}
	}
	prevTable.clear();
}

int HashTable::hashFunction(wstring number) {
	wstring letters = L"ÀÂÅÊÌÍÎĞÑÒÓÕàâåêìíîğñòóõABEKMHOPCTYXabekmhopctyx";
	wstring::iterator it;
	for (it = letters.begin(); it != letters.end(); it++) {
		wchar_t ch = *it;
		erase(number, ch);
	}
	int key = stoi(number) % table.size();
	return key;
}

HashTable::HashTable() {
	for (int i = 0; i < TABLE_SIZE; i++) {
		Node* element = new Node(Info(L"", L"", L""));
		element->deleted = true;
		table.push_back(element);
	}
}

int HashTable::Size() {
	return table.size();
}

void HashTable::Push(wstring number, Info info) {
	Node* element = new Node(info);
	int key = hashFunction(number);
	for (int i = 0; i < table.size(); i++) {
		if (table[key]->deleted) {
			table[key] = element;
			return;
		}
		key = (key + 1) % table.size();
	}
	restructureTable();
	Push(number, info);
}

Info HashTable::Get(wstring number) {
	int key = hashFunction(number);
	for (int i = 0; i < table.size(); i++) {
		if (!table[key]->deleted && table[key]->_info.number == number) {
			return table[key]->_info;
		}
		key = (key + 1) % table.size();
	}
}

vector<wstring> HashTable::GetKeys() {
	vector<wstring> numbers;
	for (int i = 0; i < table.size(); i++) {
		if (!table[i]->deleted) {
			numbers.push_back(table[i]->_info.number);
		}
	}
	return numbers;
}

void HashTable::Delete(wstring number) {
	int key = hashFunction(number);
	for (int i = 0; i < table.size(); i++) {
		if (!table[key]->deleted && table[key]->_info.number == number) {
			table[key]->deleted = true;
			break;
		}
		key = (key + 1) % table.size();
	}
}

void HashTable::Clear() {
	table.clear();
	HashTable();
}