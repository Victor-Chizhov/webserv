#include "../../include/ServerSocket.hpp"

ServerSocket::ServerSocket() : listenSocket(-1), port(0), backlog(0) {}

ServerSocket::~ServerSocket() {
    if (listenSocket != -1) {
        close(listenSocket);
    }
}

void ServerSocket::start() {
    // Создание слушающего сокета и настройка сервера
    listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	/* socket() - это системный вызов, который создает новый сокет. В данном случае, мы создаем сокет для работы с IPv4 (AF_INET) и TCP (SOCK_STREAM).
	Результатом вызова socket() является дескриптор сокета (listenSocket), который используется для дальнейшего взаимодействия с сокетом. */
	if (listenSocket == -1) {
    // Обработка ошибки при создании сокета
		perror("Error creating socket");
		exit(EXIT_FAILURE);
	}

    // Настройка сервера (установка параметров, bind, listen)

	/* После создания сокета, необходимо установить параметры сервера, такие как адрес и порт, которые он будет слушать.
	Для этого используется структура struct sockaddr_in, которая представляет собой структуру для хранения информации об адресе IPv4. */

	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);  // Слушаем все интерфейсы
	serverAddr.sin_port = htons(port);  // Установка порта

	//После настройки структуры, используется функция bind(), чтобы связать сокет с указанным адресом и портом.
	if (bind(listenSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
		perror("Error binding socket");
		close(listenSocket);
		exit(EXIT_FAILURE);
	}

	//После связывания сокета, вызывается listen(), чтобы перевести сокет в режим прослушивания входящих соединений.
	if (listen(listenSocket, backlog) == -1) {
		perror("Error listening on socket");
		close(listenSocket);
		exit(EXIT_FAILURE);
	}

	std::cout << "Server listening on port " << port << std::endl;

	// настройка event-менеджера
    eventManager.addServerSocket(listenSocket);
	eventManager.waitAndHandleEvents();
	stop();
}

void ServerSocket::configure(int port, int backlog) {
    // Этот метод предназначен для настройки параметров сервера, таких как порт и размер очереди ожидания соединений (backlog).
	this->port = port;
    this->backlog = backlog;
	//При использовании этого метода в коде нужно сначала создать объект ServerSocket, а затем вызвать метод configure():
}

void ServerSocket::stop() {
    // Остановка сервера, например, закрытие слушающего сокета
	if (close(listenSocket) == -1) {
        perror("Error closing socket");
        // Можно продолжить завершение работы сервера или выйти из метода, в зависимости от требований
    }
}
