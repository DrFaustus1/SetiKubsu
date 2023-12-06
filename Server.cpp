using namespace std;
#include <iostream>
#include <fstream>
#include <Windows.h>

struct Person {
	string name;
	int diffury;
	int physics;
	int maths;
	int oop;
}Stud;

int answer;
long size_pred;

int main() {
	setlocale(LC_ALL, "ru");
	ifstream fin;
	ofstream fout;
	const char* nameA = "D:/answer.txt";
	const char* nameR = "D:/request.txt";

	fout.open(nameA, ios::trunc);
	fout.close();
	fout.open(nameR, ios::trunc);
	fout.close();

	fin.open(nameR);
	fin.seekg(0, ios::end);
	long size_pred = fin.tellg();
	fin.close();

	cout << "Server is working" << endl;

	while (true) {
		int answer;
		try {
			fin.open(nameR);
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
		fin.read((char*)&Stud, sizeof(Stud));
		size_pred = fin.tellg();
		fin.close();

		double IMT = (Stud.diffury + Stud.physics + Stud.maths + Stud.oop) / 4;
		if (IMT <= 3) answer = 0;
		if (IMT > 3 && IMT < 4) answer = 1;
		if (IMT >= 4) answer = 2;


		fout.open(nameA, ios::app);
		fout.write((char*)&answer, sizeof(answer));
		fout.close();
		cout << "Имя: " << Stud.name << endl << "Диффуры: " << Stud.diffury << endl << "Физика: " << Stud.physics << endl << "Матан: " << Stud.maths << endl << "ООП: " << Stud.oop;
	}
	return 0;
}

