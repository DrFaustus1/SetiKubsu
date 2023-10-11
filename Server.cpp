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

int main()
{
	ifstream f_request;
	ofstream f_answer;
	setlocale(LC_ALL, "rus");
	const char* nameRequest = "D:\REQUEST.txt";
	const char* nameAnswer = "D:\ANSWER.txt";

	cout << "server is working" << endl;

	f_request.open(nameRequest, ios::binary);
	f_request.seekg(0, ios::end);
	size_pred = f_request.tellg();

	f_request.close();

	//начало работы сервера 
	while (true) {
		f_request.open(nameRequest, ios::binary);
		f_request.seekg(0, ios::end);
		while (size_pred >= f_request.tellg()) {
			Sleep(100);
			f_request.seekg(0, ios::end);
		}
		f_request.seekg(size_pred, ios::beg);
		f_request.read((char*)&Stud, sizeof(Stud));
		size_pred = f_request.tellg();
		f_request.close();

		double IMT = (Stud.diffury + Stud.physics+ Stud.maths + Stud.oop)/4;
		if (IMT <= 3) answer = 0;
		if (IMT > 3 && IMT < 4) answer = 1;
		if (IMT >= 4) answer = 2;

		answer = 2;

		f_answer.open(nameAnswer, ios::binary || ios :: app);
		f_answer.write(reinterpret_cast<const char*>(&answer), sizeof(answer));
		//f_answer.write((char*)&answer, sizeof(answer));

		f_answer.close();

	}
	
}

