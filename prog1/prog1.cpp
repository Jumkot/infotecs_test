#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>
#include <cstring>
#include <algorithm>
#include <arpa/inet.h>
#include <unistd.h>
#include "libstringops.h"

#define SERVER_PORT 8080
#define BUFFER_SIZE 128

std::queue<std::string> buffer;
std::mutex mtx;
std::condition_variable cv;
bool stop_processing = false;

void input_thread() {
    while (true) {
        std::string input;
        std::cout << "Введите строку (цифры, максимум 64 символа, для выхода введите 'exit'):\n";
        std::cin >> input;

        if (input == "exit") {
            std::lock_guard<std::mutex> lock(mtx);
            stop_processing = true;
            cv.notify_one();
            break;
        }

        if (input.length() > 64 || !std::all_of(input.begin(), input.end(), ::isdigit)) {
            std::cerr << "Ошибка ввода: строка должна содержать только цифры и не превышать 64 символа.\n";
            continue;
        }

        sort_and_replace(input);

        {
            std::lock_guard<std::mutex> lock(mtx);
            buffer.push(input);
        }
        cv.notify_one();
    }
}

void processing_thread() {
    while (true) {
        std::string data;
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [] { return !buffer.empty() || stop_processing; });

            if (buffer.empty() && stop_processing) break;

            data = buffer.front();
            buffer.pop();
        }

        int sum = sum_numeric(data);

        int client_sock = socket(AF_INET, SOCK_STREAM, 0);
        if (client_sock < 0) {
            perror("Ошибка создания сокета.\n");
            continue;
        }

        sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(SERVER_PORT);
        inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

        if (connect(client_sock, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            std::cerr << "Ошибка подключения к серверу. Попробуйте снова.\n";
            close(client_sock);
            continue;
        }

        char buffer[BUFFER_SIZE];
        sprintf(buffer, "%d", sum);
        send(client_sock, buffer, strlen(buffer), 0);
        close(client_sock);

        std::cout << "Обработанные данные отправлены: " << data << ", сумма: " << sum << "\n";
    }
}

int main() {
    std::thread t1(input_thread);
    std::thread t2(processing_thread);

    t1.join();

    {
        std::lock_guard<std::mutex> lock(mtx);
        stop_processing = true;
        cv.notify_one();
    }

    t2.join();

    return 0;
}