#include "board.h"
#include "generator.h"
#include "drawer.h"
#include "network.h"
#include "scoreboard.h"
#include "menu.h"
#include "stdinclude.h"
#include "mbox.h"

using namespace std;
using namespace sf;

#define CONNECTPORT 3177

int main() {
	setlocale(LC_ALL, "rus");
	srand((unsigned int)time(0));

	SetConsoleTitle("Logger");

	int menuChoice = 1;
	while (menuChoice != 3) {
		menuChoice = CreateWindowMenu();

		if (menuChoice == 1) {
			TcpSocket data;
			char mode = NULL;
			string name;
			while (mode != 'S' && mode != 'C') {
				mode = mbox("Server/cleint (S/C)", 0, 1)[0];
			}

			//Создание сокета, установка соединения с клиентом
			if (mode == 'S') {
				IpAddress YourIp = IpAddress::getLocalAddress();
				string app = "Your IP is:\n";
				app.append(YourIp.toString());
				app.append("\nDeliver it to client");
				mbox(app);
				TcpListener listener;

				//Слушаем порт
				if (listener.listen(CONNECTPORT) != Socket::Done)
				{
					string app = "Error...\nGoing to main menu...";
					mbox(app);
					continue;
				}
				thread thread1(mbox, "Waiting for client", 0, 0, true, true);
				thread1.detach();

				//Подключаем клиента
				if (listener.accept(data) != Socket::Done)
				{
					string app = "Error...\nGoing to main menu...";
					mbox(app);
					continue;
				}

				DropThread();

				name = mbox("Enter team's name: ", 0, 10);

				//Тестовая отправка данных + простейшая проверка подлинности
				Packet test;
				test << name;
				data.send(test);
				data.setBlocking(false);

				mbox("Sucess", 2500, 0, true);
			}
			else if (mode == 'C') {
				IpAddress ServerIp;
				string app = "Enter server IP:";
				ServerIp = mbox(app, 0, 15);

				thread thread2(mbox, "Connecting", 0, 0, true, true);
				thread2.detach();

				if (data.connect(ServerIp, CONNECTPORT) != Socket::Done) {
					string app = "Error...\nGoing to main menu...";
					mbox(app);
					continue;
				}

				//Тестовый приём данных + простейшая проверка подлинности
				Packet test;
				data.receive(test);
				test >> name;
				app = "Your team's name:\n";
				app.append(name);
				DropThread();
				mbox(app, 2500, 0, true);
				data.setBlocking(false);
			}

			//Игровое поле 
			Board MainBoard;

			//Окно
			RenderWindow window(VideoMode(550, 700), "Tetrix", Style::Close);

			//Установка красивой иконки
			Image icon;
			icon.loadFromFile("redist/blocks/Blue.png");
			window.setIcon(24, 24, icon.getPixelsPtr());

			//Таймеры "падения" блоков
			Clock TurnClock1, TurnClock2;

			//Счёт
			int score = 0;

			//Индикаторы новой генерации
			bool Move1 = true, Move2 = true;

			while (window.isOpen())
			{
				//Обработчик нажатий клавиш (ивентов)
				Event event;
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed || ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape))) {
						SendSocketMessage(data, QUIT);
						window.close();
						string app = "Game over...";
						mbox(app);
					}
					if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Right)) {
						if (mode == 'S') {
							MainBoard.MoveActiveRight(FIRST_PLAYER);
							SendGameData(data, MainBoard, score);
						}
						else if (mode == 'C') {
							SendSocketMessage(data, MOVERIGHT);
						}
					}
					if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Left)) {
						if (mode == 'S') {
							MainBoard.MoveActiveLeft(FIRST_PLAYER);
							SendGameData(data, MainBoard, score);
						}
						else if (mode == 'C') {
							SendSocketMessage(data, MOVELEFT);
						}
					}
					if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Down)) {
						if (mode == 'S') {
							Move1 = MainBoard.MoveActiveDown(FIRST_PLAYER);
							TurnClock1.restart();
							SendGameData(data, MainBoard, score);
						}
						else if (mode == 'C') {
							SendSocketMessage(data, MOVEDOWN);
						}
					}
					if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Up)) {
						if (mode == 'S') {
							MainBoard.RotateActiveFigure(FIRST_PLAYER);
							SendGameData(data, MainBoard, score);
						}
						else if (mode == 'C') {
							SendSocketMessage(data, ROTATE);
						}
					}
					if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::RControl)) {
						if (mode == 'S') {
							MainBoard.BigMoveDown(FIRST_PLAYER);
							Move1 = false;
							SendGameData(data, MainBoard, score);
						}
						else if (mode == 'C') {
							SendSocketMessage(data, FULLMOVEDOWN);
						}
					}
				}

				//"Падение" блоков вниз по времени
				if (mode == 'S') {
					if (Move1 || Move2) {
						if (TurnClock1.getElapsedTime().asMilliseconds() >= 750) {
							TurnClock1.restart();
							Move1 = MainBoard.MoveActiveDown(FIRST_PLAYER);
							SendGameData(data, MainBoard, score);
						}
						else if (TurnClock2.getElapsedTime().asMilliseconds() >= 750) {
							TurnClock2.restart();
							Move2 = MainBoard.MoveActiveDown(SECOND_PLAYER);
							SendGameData(data, MainBoard, score);
						}
					}
					else {
						MainBoard.Deactive();
						score += MainBoard.ClearStripes();
						if (!MainBoard.CheckGame()) {
							SendSocketMessage(data, QUIT);
							window.close();
							string app = "Game over...";
							mbox(app);
						}
						GenerateFigure(MainBoard, FIRST_PLAYER);
						GenerateFigure(MainBoard, SECOND_PLAYER);
						SendGameData(data, MainBoard, score);
						TurnClock1.restart();
						TurnClock2.restart();
						Move1 = true;
						Move2 = true;
					}
				}

				//Обработчики получаемых через сокет комманд для сервера и клиента
				Packet p;
				Socket::Status s = data.receive(p);
				if (s == Socket::Status::Done) {
					int action;
					p >> action;
					switch (action) {
					case MOVELEFT:
					{
						MainBoard.MoveActiveLeft(SECOND_PLAYER);
						SendGameData(data, MainBoard, score);
					}
					break;
					case MOVERIGHT:
					{
						MainBoard.MoveActiveRight(SECOND_PLAYER);
						SendGameData(data, MainBoard, score);
					}
					break;
					case MOVEDOWN:
					{
						Move2 = MainBoard.MoveActiveDown(SECOND_PLAYER);
						SendGameData(data, MainBoard, score);
						TurnClock2.restart();
					}
					break;
					case ROTATE:
					{
						MainBoard.RotateActiveFigure(SECOND_PLAYER);
						SendGameData(data, MainBoard, score);
					}
					break;
					case QUIT:
					{
						window.close();
						string app = "Game over...";
						mbox(app);
						break;
					}
					case FULLMOVEDOWN:
					{
						MainBoard.BigMoveDown(SECOND_PLAYER);
						Move2 = false;
						SendGameData(data, MainBoard, score);
					}
					break;
					case BOARD:
						MainBoard.DeserializeFromPacket(p, score);
						break;
					}
				}

				//Отрисовка доски
				Draw(MainBoard, window, score);
			}
			if (score > 0) {
				ofstream file;
				file.open("score.dat", ios::app | ios::out);
				file << endl << name << endl << score;
				file.close();
			}
		}
		else if (menuChoice == 2) {
			ShowScore();
		}
	}
	return 0;
}