#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <windows.h>
#include "board.h"
#include "generator.h"
#include "drawer.h"
#include "network.h"

using namespace std;
using namespace sf;

int main() {
	setlocale(LC_ALL, "rus");
	srand(time(0));

	int port = 3177;

	SetConsoleTitle("Logger");

	TcpSocket data;

	char mode = NULL;
	int repeat;

	while (mode != 'S' && mode != 'C') {
		cout << "Вы сервер или клиент (S/C): ";
		cin >> mode;
	}

	cout << "Установить залипание клавиш?(0/1): ";
	cin >> repeat;

	//Создание сокета, установка соединения с клиентом
	if (mode == 'S') {
		IpAddress YourIp = IpAddress::getLocalAddress();

		cout << "Ваш IP: " << YourIp << endl << "Сообщите его другому игроку" << endl;

		TcpListener listener;

		size_t received;

		if (listener.listen(port) != Socket::Done)
		{
			cout << "Неудачное подключение..." << endl << "Выхожу из игры..." << endl;
			system("pause");
			return 0;
		}

		cout << "Ждём клиента..." << endl;

		if (listener.accept(data) != Socket::Done)
		{
			cout << "Неудачное подключение..." << endl << "Выхожу из игры..." << endl;
			system("pause");
			return 0;
		}

		cout << "Клиент найден!" << endl;

		cout << "Устанавливаем соединение..." << endl;

		int key = rand();

		cout << "Ваш ключ " << key << " сравните его с ключом второго игрока..." << endl;

		data.send(&key, sizeof(int));

		bool answer = false;
		cout << "Ключи совпадают (0/1): ";
		cin >> answer;

		if (!answer) {
			cout << "Неудачное подключение..." << endl << "Выхожу из игры..." << endl;
			data.send(&answer, sizeof(bool));
			system("pause");
			return 0;
		}
		else {
			cout << "Ждём ответа другого игрока..." << endl;
			data.send(&answer, sizeof(bool));
			bool answer2 = false;
			data.receive(&answer2, sizeof(bool), received);
			if (!answer2) {
				cout << "Неудачное подключение..." << endl << "Выхожу из игры..." << endl;
				system("pause");
				return 0;
			}
		}
		cout << "Удачно! Начинаем игру..." << endl;
		data.setBlocking(false);

	}
	else if (mode == 'C') {
		IpAddress ServerIp;

		cout << "Введите IP сервера: ";

		cin >> ServerIp;

		if (data.connect(ServerIp, port) != Socket::Done) {
			cout << "Неудачное подключение..." << endl << "Выхожу из игры..." << endl;
			system("pause");
			return 0;
		}

		size_t received;

		int key;

		data.receive(&key, sizeof(int), received);

		cout << "Ваш ключ " << key << " сравните его с ключом второго игрока..." << endl;

		bool answer = false;
		cout << "Ключи совпадают (0/1): ";
		cin >> answer;

		if (!answer) {
			cout << "Неудачное подключение..." << endl << "Выхожу из игры..." << endl;
			data.send(&answer, sizeof(bool));
			system("pause");
			return 0;
		}
		else {
			cout << "Ждём ответа другого игрока..." << endl;
			data.send(&answer, sizeof(bool));
			bool answer2;
			data.receive(&answer2, sizeof(bool), received);
			if (!answer2) {
				cout << "Неудачное подключение..." << endl << "Выхожу из игры..." << endl;
				system("pause");
				return 0;
			}
		}
		cout << "Удачно! Начинаем игру..." << endl;
		data.setBlocking(false);
	}

	//Переменные 
	Board MainBoard;
	RenderWindow window(VideoMode(550, 700), "Tetrix", Style::Close);
	Clock TurnClock;
	int score = 0;
	bool Move1 = true, Move2 = true;
	int CanStart1 = true, CanStart2 = true, GenType = -1;
	int gen1 = -1, gen2 = -1;
	int i = 0;
	int canstart = true;

	window.setKeyRepeatEnabled(repeat);

	while (window.isOpen())
	{
		//Генерация фигур
		if ((gen1 != -1) && (gen2 != -1)) {
			MainBoard.Deactive();
			score += MainBoard.ClearStripes();
			if (!MainBoard.CheckGame()) {
				window.close();
				LogCommand("Game over");
				Packet p;
				p << QUIT << 0;
				data.send(p);
				system("pause");
				return 0;
			}
			sleep(milliseconds(100));
			GenerateFigure(MainBoard, FIRST_PLAYER, gen1);
			GenerateFigure(MainBoard, SECOND_PLAYER, gen2);
			TurnClock.restart();
			gen1 = -1;
			gen2 = -1;
			canstart = true;
			Move1 = true;
			Move2 = true;
			i++;
			cout << "#" << i << " " << score << " " << mode << endl;
		}

		//Обработчик нажатий клавиш
		Event event;
		while (window.pollEvent(event))
		{
			int mytype;
			if (mode == 'S')
				mytype = FIRST_PLAYER;
			else if (mode == 'C')
				mytype = SECOND_PLAYER;

			if (event.type == Event::Closed || ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape))) {
				window.close();
				LogCommand("Game over");
				Packet p;
				p << QUIT << 0;
				data.send(p);
				system("pause");
				return 0;
			}
			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Right)) {
				MainBoard.MoveActiveRight(mytype);
				Packet p;
				p << MOVERIGHT << 0;
				data.send(p);
			}
			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Left)) {
				MainBoard.MoveActiveLeft(mytype);
				Packet p;
				p << MOVELEFT << 0;
				data.send(p);
			}
			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Down)) {
				if (mode == 'S')
					Move1 = MainBoard.MoveActiveDown(mytype);
				else if (mode == 'C')
					Move2 = MainBoard.MoveActiveDown(mytype);
				TurnClock.restart();
				Packet p;
				p << MOVEDOWN << 0;
				data.send(p);
			}
			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Up)) {
				MainBoard.RotateActiveFigure(mytype);
				Packet p;
				p << ROTATE << 0;
				data.send(p);
			}
			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::LControl)) {
				MainBoard.BigMoveDown(mytype);
				if (mode == 'S')
					Move1 = false;
				else if (mode == 'C')
					Move2 = false;
				Packet p;
				p << FULLMOVEDOWN << 0;
				data.send(p);
			}
		}

		//Движение блоков вниз по времени, если некуда двигать, отсылание комманды готовности к новой генерации
		if (Move1 || Move2) {
			if (TurnClock.getElapsedTime().asMilliseconds() >= 750) {
				TurnClock.restart();
				if (mode == 'S')
					Move1 = MainBoard.MoveActiveDown(FIRST_PLAYER);
				else if (mode == 'C')
					Move2 = MainBoard.MoveActiveDown(SECOND_PLAYER);
				Packet p;
				p << MOVEDOWN << 0;
				data.send(p);
			}
		}
		else if (canstart) {
			Packet p;
			TurnClock.restart();
			p << CANSTART << 0;
			data.send(p);
			if (mode == 'S') {
				CanStart1 = true;
				LogCommand("Server can start");
			}
			else if (mode == 'C') {
				CanStart2 = true;
				LogCommand("Client can start");
			}
			canstart = false;
		}

		//Обмен сообщениями о готовности генерации
		if (CanStart1 && CanStart2) {
			int param = rand() % 7;
			if (mode == 'S') {
				gen1 = param;
				LogCommand("Server can generate");
			}
			else if (mode == 'C') {
				gen2 = param;
				LogCommand("Client can generate");
			}
			Packet p;
			p << GENERATEDFIGURE << param;
			data.send(p);
			CanStart1 = false;
			CanStart2 = false;
		}

		//Обработчики получаемых через сокет комманд для сервера и клиента
		Packet p;
		Socket::Status s = data.receive(p);
		if (s == Socket::Status::Done) {
			int action, param, receivertype;

			if (mode == 'S')
				receivertype = SECOND_PLAYER;
			else if (mode == 'C')
				receivertype = FIRST_PLAYER;

			p >> action >> param;

			switch (action) {
			case MOVELEFT:
				MainBoard.MoveActiveLeft(receivertype);
				break;
			case MOVERIGHT:
				MainBoard.MoveActiveRight(receivertype);
				break;
			case MOVEDOWN:
				if (mode == 'S')
					Move2 = MainBoard.MoveActiveDown(receivertype);
				else if (mode == 'C')
					Move1 = MainBoard.MoveActiveDown(receivertype);
				break;
			case ROTATE:
				MainBoard.RotateActiveFigure(receivertype);
				break;
			case GENERATEDFIGURE:
				if (mode == 'S')
					gen2 = param;
				else if (mode == 'C')
					gen1 = param;
				break;
			case CANSTART:
				if (mode == 'S')
					CanStart2 = true;
				else if (mode == 'C')
					CanStart1 = true;
				break;
			case QUIT:
				window.close();
				LogCommand("Game over");
				system("pause");
				return 0;
				break;
			case FULLMOVEDOWN:
				MainBoard.BigMoveDown(receivertype);
				if (mode == 'S')
					Move2 = false;
				else if (mode == 'C')
					Move1 = false;
			}
		}

		Draw(MainBoard, window, score);
	}

	return 0;
}