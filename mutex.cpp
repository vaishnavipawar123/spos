#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>
#include <random>

class ReaderWriter {
private:
    int readerCount;  // Number of active readers
    std::mutex mtx;   // Mutex for critical section
    std::condition_variable cv;  // Condition variable for writer signaling

public:
    ReaderWriter() : readerCount(0) {}

    void reader(int id) {
        std::unique_lock<std::mutex> lock(mtx);
        // Increment the number of readers
        readerCount++;
        if (readerCount == 1) {
            // If first reader, wait until no writers
            cv.wait(lock, [this]() { return readerCount == 0; });
        }
        lock.unlock();

        // Simulate reading
        std::cout << "Reader " << id << " has started reading." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(rand() % 3 + 1)); // Random sleep
        std::cout << "Reader " << id << " has stopped reading." << std::endl;

        lock.lock();
        // Decrement the number of readers
        readerCount--;
        if (readerCount == 0) {
            // If last reader, notify writers
            cv.notify_all();
        }
    }

    void writer(int id) {
        std::unique_lock<std::mutex> lock(mtx);
        // Wait until there are no readers
        cv.wait(lock, [this]() { return readerCount == 0; });

        // Simulate writing
        std::cout << "Writer " << id << " has started writing." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(rand() % 3 + 1)); // Random sleep
        std::cout << "Writer " << id << " has stopped writing." << std::endl;

        // Notify readers
        cv.notify_all();
    }
};

int main() {
    ReaderWriter rw;
    std::vector<std::thread> threads;
    int choice;

    std::cout << "WELCOME to the Readers-Writers Problem Simulation" << std::endl;

    while (true) {
        std::cout << "Enter your choice: \n1) Read\n2) Write\n3) Exit\n";
        std::cin >> choice;

        if (choice == 1) {
            // Create a reader thread
            threads.emplace_back(&ReaderWriter::reader, &rw, threads.size() + 1);
        } else if (choice == 2) {
            // Create a writer thread
            threads.emplace_back(&ReaderWriter::writer, &rw, threads.size() + 1);
        } else if (choice == 3) {
            break; // Exit the loop
        } else {
            std::cout << "Invalid choice. Please enter 1 for Read or 2 for Write." << std::endl;
        }

        // Join all threads to ensure they complete
        for (auto& t : threads) {
            if (t.joinable()) {
                t.join();
            }
        }
    }

    return 0;
}

//OUTPUT:

// Reader-1 has started Reading
// Reader-2 has started Reading
// Reader-3 has started Reading
// Reader-4 has started Reading
// Reader-5 has started Reading
// Reader-3 has stopped Reading
// Reader-1 has stopped Reading
// Reader-2 has stopped Reading
// Reader-4 has stopped Reading
// Reader-5 has stopped Reading
// Writer-1 has started Writing
// Writer-1 has stopped Writing
// Writer-2 has started Writing
// Writer-2 has stopped Writing
