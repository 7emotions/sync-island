
#include "sync_island.hpp"
#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

struct StudentSample {
    int id;
    std::string name;
    std::string address;
    std::string phone;

    friend std::ostream& operator<<(std::ostream& os, const StudentSample& s) {
        os << "id: " << s.id << ", name: " << s.name << ", address: " << s.address
           << ", phone: " << s.phone;
        return os;
    }
};

using BufferType = StudentSample;

void producer(sync_island::DoubleBuffer<BufferType>& db, int value) {
    for (int i = 0; i < 10; ++i) {
        BufferType buffer{i + value, "name", "address", "phone"};
        db.set(buffer);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void consumer(sync_island::DoubleBuffer<BufferType>& db) {
    for (int i = 0; i < 20; ++i) {
        if (auto buffer = db.get()) {
            std::cout << "Consumed: " << *buffer << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(15));
        } else {
            i--;
        }
    }
}

auto main() -> int {
    sync_island::DoubleBuffer<BufferType> db;

    std::vector<std::thread> threads;
    threads.emplace_back(producer, std::ref(db), 10);
    threads.emplace_back(producer, std::ref(db), 100);
    threads.emplace_back(consumer, std::ref(db));

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
