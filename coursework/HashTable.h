#pragma once
#include <vector>
#include <string>

using namespace std;

const int TABLE_SIZE = 16;

struct Info {
	wstring number;
	wstring brand;
	wstring fullName;

	Info();
	Info(wstring _number, wstring _brand, wstring _fullName);
};

class HashTable {
private:
	struct Node {
		Info _info;
		bool deleted;
		
		Node(Info info);
	};
	vector<Node*> table;

	void restructureTable();

	int hashFunction(wstring value);
public:
	HashTable();

	int Size();

	void Push(wstring number, Info info);

	Info Get(wstring number);

	vector<wstring> GetKeys();
	
	void Delete(wstring number);

	void Clear();
};