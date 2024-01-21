//#include <iostream>
//#include <thread>
//#include <mutex>
//#include <condition_variable>
//
//std::mutex mtx;
//std::condition_variable cv;
//bool ready = false;
//
//void sumNumbers() {
//    int sum = 0;
//    for (int i = 1; i <= 100; ++i) {
//        sum += i;
//
//        // 55�� ������ ��, T-2 �����忡 �˸�
//        if (i == 55) {
//            std::lock_guard<std::mutex> lock(mtx);
//            std::mutex lock();
//            ready = true;
//            cv.notify_one();
//        }
//    }
//}
//
//void waitForSum() {
//    std::unique_lock<std::mutex> lock(mtx);
//    cv.wait(lock, [] { return ready; });
//    std::cout << "T-2: T-1�� 55�� ���ϴ� ���� �����" << std::endl;
//}
//
//int main() {
//    std::thread t1(sumNumbers);
//    std::thread t2(waitForSum);
//
//    t1.join();
//    t2.join();
//
//    return 0;
//}

//**************************************************************************************************************************
//**************************************************************************************************************************
//**************************************************************************************************************************

//#include <iostream>
//#include <thread>
//#include <vector>
//#include <mutex>
//
//void worker(int& counter, std::mutex& m) {
//    for (int i = 0; i < 10000; i++) {
//
//        //m.lock();
//        std::lock_guard<std::mutex> lock(m);
//        counter += 1;
//        //m.unlock();
//        // scope �� ���� ������ lock �� �Ҹ�Ǹ鼭
//        // m �� �˾Ƽ� unlock �Ѵ�.
//    }
//}
//
//int main() {
//    int counter = 0;
//    std::mutex m;
//
//    std::vector<std::thread> workers;
//    for (int i = 0; i < 4; i++) {
//        // ���۷����� �����Ϸ��� ref �Լ��� ���ξ� �Ѵ� (���� ���� bind �Լ� ����)
//        workers.push_back(std::thread(worker, std::ref(counter), std::ref(m)));
//    }
//
//    for (int i = 0; i < 4; i++) {
//        workers[i].join();
//    }
//
//    std::cout << "Counter ���� �� : " << counter << std::endl;
//}

#include <chrono>  // std::chrono::miliseconds
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>
#include <condition_variable>

void producer(std::queue<std::string>* downloaded_pages, std::mutex* m,
    int index, std::condition_variable* cv) {
    for (int i = 0; i < 5; i++) {
        // ������Ʈ�� �ٿ�ε� �ϴµ� �ɸ��� �ð��̶� �����ϸ� �ȴ�.
        // �� ������ ���� �ٿ�ε� �ϴµ� �ɸ��� �ð��� �ٸ���.
        std::this_thread::sleep_for(std::chrono::milliseconds(100 * index));
        std::string content = "������Ʈ : " + std::to_string(i) + " from thread(" +
            std::to_string(index) + ")\n";

        // data �� ������ ���̿��� �����ǹǷ� critical section �� �־�� �Ѵ�.
        //m->lock();
        std::lock_guard<std::mutex> lock(*m);
        downloaded_pages->push(content);
        cv->notify_one();
        //m->unlock();
    }
}

void consumer(std::queue<std::string>* downloaded_pages, std::mutex* m,
    int* num_processed, std::condition_variable *cv) {
    // ��ü ó���ϴ� ������ ������ 5 * 5 = 25 ��.
    while (*num_processed < 25) {

        std::unique_lock<std::mutex> lk(*m);
        cv->wait(lk, [&] {
            return !downloaded_pages->empty() || *num_processed == 25;
            //return false;
        });
        if (*num_processed == 25) {
            lk.unlock();
            return;
        }
        //m->lock();
        //// ���� ���� �ٿ�ε��� �������� ���ٸ� �ٽ� ���.
        //if (downloaded_pages->empty()) {
        //    m->unlock();  // (Quiz) ���⼭ unlock �� ���Ѵٸ� ��� �ɱ��?

        //    // 10 �и��� �ڿ� �ٽ� Ȯ���Ѵ�.
        //    std::this_thread::sleep_for(std::chrono::milliseconds(10));
        //    continue;
        //}

        // �� ���� �������� �а� ��� ��Ͽ��� �����Ѵ�.
        std::string content = downloaded_pages->front();
        downloaded_pages->pop();

        (*num_processed)++;
        //m->unlock();

        // content �� ó���Ѵ�.
        std::cout << content;
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
    }
}

int main() {
    // ���� �ٿ�ε��� �������� ����Ʈ��, ���� ó������ ���� �͵��̴�.
    std::queue<std::string> downloaded_pages;
    std::mutex m;
    std::condition_variable cv;

    std::vector<std::thread> producers;
    for (int i = 0; i < 5; i++) {
        producers.push_back(std::thread(producer, &downloaded_pages, &m, i + 1, &cv));
    }

    int num_processed = 0;
    std::vector<std::thread> consumers;
    for (int i = 0; i < 3; i++) {
        consumers.push_back(
            std::thread(consumer, &downloaded_pages, &m, &num_processed, &cv));
    }

    for (int i = 0; i < 5; i++) {
        producers[i].join();
    }
    cv.notify_all();
    for (int i = 0; i < 3; i++) {
        consumers[i].join();
    }
}
