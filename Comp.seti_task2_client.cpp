#include <iostream> 
#include <string>
#define _WINSOCK_DEPRECATED_NO_WARNINGS  
#include <WinSock2.h>
#include <Windows.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma warning(disable: 4996)

#define SRV_HOST "localhost"
#define SRV_PORT 1234
#define CLNT_PORT 1235
#define BUF_SIZE 128

using namespace std;

struct  House {
	char adress[20];
	int floor;
	int rooms;
	int plosh;
};


int main() {
	setlocale(LC_ALL, "rus");

	cout << "\t Клиент\n";
	for (int i = 0; i < 30; i++)
		cout << "-";
	cout << endl;

	House* hs = new House[3];
	hs[0] = { "Ставропольская\0", 2, 29, 1000};
	hs[1] = { "Павлова\0", 4, 15, 1500};
	hs[2] = { "Московская", 1, 45, 150};

	// Инициализируем библиотеку 
	char buff[1024];
	if (WSAStartup(0x0202, (WSADATA*)&buff[0])) {
		cout << "Ошибка инициализации! \n" << WSAGetLastError();
		return -1;
	}

	// Создание сокета TCP
	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET) {
		cout << "Ошибка создания сокета! \n" << WSAGetLastError();
		return -1;
	}

	// Создание структуры локального адресасокетов клиента и сервера
	sockaddr_in clntSin, srvSin;

	// Заполняем структуру адреса для клиента
	clntSin.sin_family = AF_INET;
	clntSin.sin_addr.s_addr = 0;// ~ clntSin.sin_addr.S_un.S_addr
	clntSin.sin_port = htons(CLNT_PORT);

	// Связываем сокет с адресом и номером порта
	if (bind(s, (sockaddr*)&clntSin, sizeof(clntSin))) {
		cout << "Ошибка привязки сокета! \n" << WSAGetLastError();
		return -1;
	}

	// Заполняем структуру адреса для сервера
	hostent* hp;
	srvSin.sin_family = AF_INET;
	srvSin.sin_port = htons(SRV_PORT);
	hp = gethostbyname(SRV_HOST);
	((unsigned long*)&srvSin.sin_addr)[0] =
		((unsigned long**)hp->h_addr_list)[0][0];

	// Устанавливаем соединение с сервером
	connect(s, (sockaddr*)&srvSin, sizeof(srvSin));

	// Цикл общения с сервером
	int len = 0, i = -1;
	char buf[BUF_SIZE] = { 0 };
	do {
		i++;
		len = recv(s, (char*)&buf, BUF_SIZE, 0);
		if (len == SOCKET_ERROR) {
			cout << "Ошибка приема сообщения! \n" << WSAGetLastError();
			return -1;
		}

		buf[len] = 0; // Устанавливаем символ конца
		cout << '"' << buf << '"' << endl;
		cout << "Введите адрес: \n " << hs[i].adress << endl;
		cout << "Введите кол-во этажей: \n " << hs[i].floor<< endl;
		cout << "Введите кол-во комнат: \n " << hs[i].rooms << endl;

		cout << "Введите адрес: \n " << hs[i].plosh<< endl;
		// Преобразование структуры в массив байтов
		char* msg = (char*)&hs[i];
		send(s, (char*)&msg[0], sizeof(House), 0);

	} while (i < 2);

	cout << "Conversation is over" << endl;
	closesocket(s);
	return 0;
}
