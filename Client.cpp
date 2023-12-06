using namespace std;
#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
struct Person {
	string name;
	int diffury;
	int physics;
	int maths;
	int oop;
}Stud1;


int main() {
	long size_pred;
	int answer;
	setlocale(LC_ALL, "ru");
	ofstream fout;
	ifstream fin;
	const char* nameA = "D:/answer.txt";
	const char* nameR = "D:/request.txt";

	size_pred = 0;

	while (true) {
		cout << "Введите данные оценки студента: Диффуры, Физика, Матан, ООП\n";
		cin >> Stud1.name >> Stud1.diffury>> Stud1.physics >> Stud1.maths >> Stud1.oop;
		try {
			fout.open(nameR, ios::app);
		}
		catch (exception& е) {
			cout << "Error!Ошибка чтения!" << endl;
			continue;
		}

		fout.write((char*)&Stud1, sizeof(Stud1));
		fout.close();
		cout << "Добавлено \n";

		try {
			fin.open(nameA);
		}
		catch (exception& e) {
			cout << "Error! Ошибка чтения!" << endl;
			continue;
		}
		fin.seekg(0, ios::end);
		while (size_pred >= fin.tellg()) {
			Sleep(100);
			fin.seekg(0, ios::end);
		}

		fin.seekg(size_pred, ios::beg);
		fin.read((char*)&answer, sizeof(answer));
		size_pred = fin.tellg();
		fin.close();

		switch (answer) {
		case 0: {cout << "Вас отчислили :(\n"; break; }
		case 1: {cout << "Вы живы\n"; break; }
		case 2: {cout << "Вы на стипендии\n"; break; }
		}
	}
	return 0;
}
