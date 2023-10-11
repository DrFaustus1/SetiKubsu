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


long pred_size;
int answer;

int main()
{
	setlocale(LC_ALL, "rus");
	const char* nameRequest = "D:\REQUEST.txt";
	const char* nameAnswer = "D:\ANSWER.txt";
	
	ofstream f_REQ;
	ifstream f_ANS;
	
	
	while (true) {
		//Передача данных от клиента серверу
		cout << "Введите запрос: Имя студента и его оценки по: диффурам, физике, матану, ооп " << endl;
		cin >> Stud1.name >> Stud1.diffury >> Stud1.physics >> Stud1.maths >> Stud1.oop;
		cout << Stud1.name << " " << Stud1.diffury << " " << Stud1.physics << " " << Stud1.maths << " " << Stud1.oop << endl;
		
		f_REQ.open(nameRequest, ios::app|| ios::binary);
		f_REQ.write((char*)&Stud1, sizeof(Stud1));
		f_REQ.close();

		//поступил ли ответ от сервера?
		f_ANS.open(nameAnswer, ios::binary);
		f_ANS.seekg(0, ios::end);
		pred_size = f_ANS.tellg();
		while (pred_size > f_ANS.tellg()) {
			Sleep(100);
			f_ANS.seekg(0, ios::end);
		}
		f_ANS.seekg(pred_size, ios::beg);
		f_ANS.read((char*)&answer, sizeof(answer));
		f_ANS.close();
		
		cout << answer << endl;

		switch (answer) {
		case 0: {cout << "С новым годом, вас отчислили!! \n"; break; }
		case 1: {cout << "Вас не отчислили :( \n"; break; }
		case 2: {cout << "Поздравляем, у вас будет стипендия \n"; break; }
		}
	
	}




}
