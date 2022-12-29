#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Object
{
	string Name;
	int cost;
	string date;
	string country;
	int series;
};

struct Node
{
	Object data;
	Node* next;
};

Node* F = NULL;
Node* C = NULL;
int Count = 0;

bool CreateList(Object data)
{
	F = new Node;
	F->next = NULL;
	F->data = data;
	C = F;
	Count++;
	return true;
}

bool AddNext(Object data)
{
	if (F == NULL)
		return CreateList(data);
	Node* temp = C->next;
	C->next = new Node;
	C->next->next = temp;
	C = C->next;
	C->data = data;
	Count++;
	return true;
}

bool Remove(Object& data)
{
	if (C == NULL)
		return false;
	Node* temp;
	if (C == F)
	{
		temp = F;
		F = F->next;
		data = temp->data;
		delete temp;
		Count--;
		C = F;
		return true;
	}
	if (C->next == NULL)
	{
		data = C->data;
		temp = F;
		while (temp->next->next != NULL)
			temp = temp->next;
		delete temp->next;
		temp->next = NULL;
		Count--;
		C = temp;
		return true;
	}
	temp = F;
	data = C->data;
	do
	{
		if (temp->next == C)
		{
			temp->next = C->next;
			delete C;
			C = temp;
			Count--;
			return true;
		}
		temp = temp->next;
	} while (temp->next != NULL);
	return false;
}

bool Print()
{
	if (Count == 0)
		cout << endl << "List empty" << endl;
	else
		cout << endl << "List:\n";
	if (F == NULL)
		return false;
	Node* temp = F;
	do
	{
		cout << "Name: " << temp->data.Name << endl;
		cout << "Cost: " << temp->data.cost << endl;
		cout << "Country: " << temp->data.country << endl;
		cout << "Date: " << temp->data.date << endl;
		cout << "Series: " << temp->data.series << endl << endl;
		temp = temp->next;
	} while (temp != NULL);
	cout << endl << "count = " << Count << endl;
}

bool MoveFirst()
{
	if (F == NULL)
		return false;
	C = F;
	return true;
}

bool MoveNext()
{
	if (F == NULL)
		return false;
	if (C == NULL)
	{
		C = F;
		return true;
	}
	if (C->next == NULL)
		return false;
	C = C->next;
	return true;
}

void WriteToFile(string filename)
{
	ofstream f("file.txt");

	Node* temp = F;
	do
	{
		f << temp->data.Name << endl;
		f << temp->data.cost << endl;
		f << temp->data.country << endl;
		f << temp->data.date << endl;
		f << temp->data.series << endl << endl;
		temp = temp->next;
	} while (temp != NULL);
	cout << endl << "count = " << Count << endl;

	f.close();
}

void AddFromFile(string filename,Object data)
{
	ifstream f("file.txt");
	while (f >> data.Name >> data.cost >> data.country >> data.date >> data.series)
	{
		AddNext(data);
	}
	f.close();
}

int main()
{
	Object data;
	int input, a;
	
	cout << "1. Print table\n";
	cout << "2. Add element in table\n";
	cout << "3. Delete element from table\n";
	cout << "4. Clear table\n";
	cout << "5. Save in file\n";
	cout << "6. Load table from file\n";
	cout << "8. Exit\n";
	cout << "Selection: ";
	cin >> input;
	while (input != 8)
	{
		switch (input)
		{
		case 1:
			Print();
			break;
		case 2:
			cout << endl;
			cout << "Name: ";
			cin >> data.Name;
			cout << "Cost: ";
			cin >> data.cost;
			cout << "Country: ";
			cin >> data.country;
			cout << "Date: ";
			cin >> data.date;
			cout << "Series: ";
			cin >> data.series;
			AddNext(data);
			break;
		case 3:
			cout << "Enter series of object: ";
			cin >> a;
			MoveFirst();
			while (C != NULL)
			{
				if (C->data.series == a)
					Remove(data);
				else if (!MoveNext())
					C = NULL;
			}
			MoveFirst();
			break;
		case 4:
			while (Remove(data));
			break;
		case 5:
			WriteToFile("file.txt");
			break;
		case 6:
			AddFromFile("file.txt", data);
			break;
		case 7:
			while (!MoveNext());
			break;
		case 8:
			break;
		default:
			cout << "Error, bad input, quitting\n";
			break;
		}
		cout << endl;
		cout << "1. Print table\n";
		cout << "2. Add element in table\n";
		cout << "3. Delete element from table\n";
		cout << "4. Clear table\n";
		cout << "5. Save in file\n";
		cout << "6. Load table from file\n";
		cout << "7. Move to the end\n";
		cout << "8. Exit\n";
		cout << endl << "Selection: ";
		cin >> input;
	}
	return 0;
}