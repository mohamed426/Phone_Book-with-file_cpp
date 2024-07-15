#include <bits/stdc++.h>
using namespace std;

// Functions prototype
void contact_search(string n);
void contact_add();
void contacts_display();
void contact_delete();
void contact_update();
bool contact_exists(string p);

int main()
{
	while (true)
	{
		cout << endl;
		string operation;
		string n;
		cout << "======== My Contacts ========" << endl;
		cout << "1. Search for contact" << endl;
		cout << "2. Add contact" << endl;
		cout << "3. Display all contacts" << endl;
		cout << "4. Delete contact" << endl;
		cout << "5. Update contact" << endl;
		cout << "6. Exit" << endl;
		cout << "=============================" << endl;
		cin >> operation;
		if (operation == "1")
		{
			cout << "Contact name to search: ";
			cin.ignore();
			getline(cin, n);
			contact_search(n);
		}
		else if (operation == "2")
		{
			contact_add();
		}
		else if (operation == "3")
		{
			contacts_display();
		}
		else if (operation == "4")
		{
			contact_delete();
		}
		else if (operation == "5")
		{
			contact_update();
		}
		else if (operation == "6")
		{
			cout << "Good Bye ^_^" << endl;
			break;
		}
		else
		{
			cout << "Invalid Operation" << endl;
		}
	}
	return 0;
}

void contact_search(string n)
{
	fstream book("PhoneBook.csv");
	if (!book)
	{
		cout << "Error opening file!" << endl;
		return;
	}

	string line;
	bool found = false;
	while (getline(book, line))
	{
		if (line.find(n) != string::npos)
		{
			cout << line << endl;
			found = true;
		}
	}

	if (!found)
	{
		cout << "Not Found" << endl;
	}
	book.close();
}

void contact_add()
{
	string n, p;
	cout << "Enter name: ";
	cin.ignore();
	getline(cin, n);

	cout << "Enter phone: ";
	cin >> p;
	if (contact_exists(p))
	{
		cout << "Contact already exists!" << endl;
		return;
	}

	fstream book("PhoneBook.csv", ios::app);
	if (!book)
	{
		cout << "Error opening file!" << endl;
		return;
	}
	book << n << "," << p << endl;
	cout << "Contact Added Successfully" << endl;
	book.close();
}

void contacts_display()
{
	ifstream book("PhoneBook.csv");
	if (!book)
	{
		cout << "Error opening file!" << endl;
		return;
	}

	string line;
	bool hasContacts = false;
	while (getline(book, line))
	{
		if (!line.empty())
		{
			cout << line << endl;
			hasContacts = true;
		}
	}
	if (!hasContacts)
	{
		cout << "No contacts to display." << endl;
	}
	book.close();
}

void contact_delete()
{
	ifstream book("PhoneBook.csv");
	if (!book)
	{
		cout << "Error opening file!" << endl;
		return;
	}
	ofstream temp("temp.csv");
	if (!temp)
	{
		cout << "Error opening file!" << endl;
		return;
	}

	string n, line;
	bool deleted = false;
	cout << "Contact name to delete: ";
	cin.ignore();
	getline(cin, n);
	while (getline(book, line))
	{
		if (line.find(n) == string::npos)
		{
			temp << line << endl;
		}
		else
		{
			deleted = true;
		}
	}

	book.close();
	temp.close();
	if (deleted)
	{
		remove("PhoneBook.csv");
		rename("temp.csv", "PhoneBook.csv");
		cout << "Contact Deleted Successfully" << endl;
	}
	else
	{
		remove("temp.csv");
		cout << "Contact Not Found" << endl;
	}
}

void contact_update()
{
	ifstream book("PhoneBook.csv");
	if (!book)
	{
		cout << "Error opening file!" << endl;
		return;
	}
	ofstream temp("temp.csv");
	if (!temp)
	{
		cout << "Error opening file!" << endl;
		return;
	}

	string name, newName, newPhone, line;
	cout << "Enter name of contact to update: ";
	cin.ignore();
	getline(cin, name);
	bool found = false;
	while (getline(book, line))
	{
		if (line.find(name) != string::npos)
		{
			cout << "Enter new name (or press Enter to keep the current name): ";
			getline(cin, newName);
			cout << "Enter new phone (or press Enter to keep the current phone): ";
			getline(cin, newPhone);

			size_t commaPos = line.find(',');
			string currentName = line.substr(0, commaPos);
			string currentPhone = line.substr(commaPos + 1);

			if (newName.empty())
			{
				newName = currentName;
			}
			if (newPhone.empty())
			{
				newPhone = currentPhone;
			}

			temp << newName << "," << newPhone << endl;
			cout << "Contact Updated Successfully" << endl;
			found = true;
		}
		else
		{
			temp << line << endl;
		}
	}

	book.close();
	temp.close();

	if (found)
	{
		remove("PhoneBook.csv");
		rename("temp.csv", "PhoneBook.csv");
	}
	else
	{
		remove("temp.csv");
		cout << "Contact Not Found" << endl;
	}
}

bool contact_exists(string p)
{
	fstream book("PhoneBook.csv");
	if (!book)
	{
		cout << "Error opening file!" << endl;
		return false;
	}

	string line;
	while (getline(book, line))
	{
		if (line.find(p) != string::npos)
		{
			cout << line << endl;
			book.close();
			return true;
		}
	}
	book.close();
	return false;
}
