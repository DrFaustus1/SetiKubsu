#include <iostream>  
#include <winsock2.h> 
#include <windows.h> 
#include <string> 

#pragma comment (lib, "Ws2_32.lib")  
#define SRV_PORT 1234  
#define BUF_SIZE 128

using namespace std;

struct  House {
	char adress[20];
	int floor;
	int rooms;
	int plosh;
};

const string greeting = "Server is ready to work";

int main() {
	setlocale(LC_ALL, "rus");
	// Оформление окна
	cout << "\t Сервер\n";
	for (int i = 0; i < 30; i++)
		cout << "-";
	cout << endl;

	// Инициализируем библиотеку 
	char buff[1024];
	if (WSAStartup(0x0202, (WSADATA*)&buff[0])) {
		cout << "Ошибка инициализации! \n" << WSAGetLastError();   // Ошибка!
		return -1;
	}

	SOCKET sListener, sNew;
	sockaddr_in sin, clntSin;

	sListener = socket(AF_INET, SOCK_STREAM, 0);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = 0;
	sin.sin_port = htons(SRV_PORT);
	bind(sListener, (sockaddr*)&sin, sizeof(sin));

	int len, MaxPlosh = 500;
	char buf[BUF_SIZE] = { 0 };
	string msg;
	listen(sListener, 3);
	while (true) {
		len = sizeof(clntSin);
		sNew = accept(sListener, (sockaddr*)&clntSin, &len);
		cout << "New connected client! " << endl;
		msg = greeting;
		while (true) {
			send(sNew, (char*)&msg[0], msg.size(), 0);
			len = recv(sNew, (char*)buf, BUF_SIZE, 0);
			if (len == SOCKET_ERROR) {
				break;
			}
			House* y = (House*)(&buf);

			cout << "Адрес: " << (*y).adress << endl;
			cout << "Этаж: " << (*y).floor << endl;
			cout << "Комнаты: " << (*y).rooms << endl;
			cout << "Площадь: " << (*y).plosh << endl;


			if (MaxPlosh < (*y).plosh)
				msg = "Лимит превышен!\n";
			else
				msg = "Лимит непревышен!\n";
			cout << msg << endl;
		}
		cout << "Client is lost \n";
		closesocket(sNew);
	}
	return 0;
}
