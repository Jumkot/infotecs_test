#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include "libstringops.h"

#define SERVER_PORT 8080
#define BACKLOG 5
#define BUFFER_SIZE 128

int main() {
    int server_sock, client_sock;
    sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Ошибка создания сокета.\n");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_sock, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Ошибка привязки сокета.\n");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    if (listen(server_sock, BACKLOG) < 0) {
        perror("Ошибка прослушивания.\n");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    std::cout << "Программа 2 ожидает подключения на порту " << SERVER_PORT << "...\n";

    while (true) {
        client_sock = accept(server_sock, (sockaddr*)&client_addr, &client_len);
        if (client_sock < 0) {
            perror("Ошибка подключения клиента.\n");
            continue;
        }

        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recv(client_sock, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            std::cerr << "Ошибка получения данных или клиент отключился.\n";
            close(client_sock);
            continue;
        }

        std::string received_data(buffer);
        if (analyze_length(received_data)) {
            std::cout << "Получены данные: " << received_data << "\n";
        } else {
            std::cerr << "Ошибка: длина данных некорректна.\n";
        }

        close(client_sock);
    }

    close(server_sock);
    return 0;
}