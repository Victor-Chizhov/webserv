#ifndef CLIENT_HPP
#define CLIENT_HPP

//Этот класс представляет собой абстракцию клиентского соединения, и его методы могут включать операции чтения и записи данных, а также другие функции, связанные с клиентским соединением.

class Client {
public:
	Client(int clientSocket);
    ~Client();
    
	// Методы для чтения и записи данных
    ssize_t readData(char* buffer, size_t bufferSize);
    ssize_t writeData(const char* data, size_t dataSize);

	// Метод для получения информации о клиенте (например, IP-адрес, порт)
    // Возможно, ты захочешь добавить дополнительные методы в зависимости от того, что ты планируешь использовать

private:
    int clientSocket;
    // Другие члены данных
};

#endif