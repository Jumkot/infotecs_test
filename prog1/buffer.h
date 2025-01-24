#ifndef BUFFER_H
#define BUFFER_H

#include <string>
#include <atomic>
#include <mutex>
#include <condition_variable>

class Buffer {
public:
    Buffer() : has_data(false) {}

    void put(const std::string& input) {
        std::unique_lock<std::mutex> lock(mtx);
        while (has_data) {
            producer_cv.wait(lock);
        }
        data = input;
        has_data = true;
        consumer_cv.notify_one();
    }

    std::string get() {
        std::unique_lock<std::mutex> lock(mtx);
        while (!has_data) {
            consumer_cv.wait(lock);
        }
        std::string result = data;
        has_data = false;
        producer_cv.notify_one();
        return result;
    }

private:
    std::string data;
    bool has_data;
    std::mutex mtx;
    std::condition_variable producer_cv;
    std::condition_variable consumer_cv;
};

#endif