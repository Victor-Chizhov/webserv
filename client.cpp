#include "tcpClient.hpp"

int main() {
    tcpClient client = tcpClient("127.0.0.1", 11111);
    client.runClient();
}