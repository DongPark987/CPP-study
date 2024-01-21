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
//        // 55를 더했을 때, T-2 스레드에 알림
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
//    std::cout << "T-2: T-1이 55를 더하는 순간 실행됨" << std::endl;
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
//        // scope 를 빠져 나가면 lock 이 소멸되면서
//        // m 을 알아서 unlock 한다.
//    }
//}
//
//int main() {
//    int counter = 0;
//    std::mutex m;
//
//    std::vector<std::thread> workers;
//    for (int i = 0; i < 4; i++) {
//        // 레퍼런스로 전달하려면 ref 함수로 감싸야 한다 (지난 강좌 bind 함수 참조)
//        workers.push_back(std::thread(worker, std::ref(counter), std::ref(m)));
//    }
//
//    for (int i = 0; i < 4; i++) {
//        workers[i].join();
//    }
//
//    std::cout << "Counter 최종 값 : " << counter << std::endl;
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
        // 웹사이트를 다운로드 하는데 걸리는 시간이라 생각하면 된다.
        // 각 쓰레드 별로 다운로드 하는데 걸리는 시간이 다르다.
        std::this_thread::sleep_for(std::chrono::milliseconds(100 * index));
        std::string content = "웹사이트 : " + std::to_string(i) + " from thread(" +
            std::to_string(index) + ")\n";

        // data 는 쓰레드 사이에서 공유되므로 critical section 에 넣어야 한다.
        //m->lock();
        std::lock_guard<std::mutex> lock(*m);
        downloaded_pages->push(content);
        cv->notify_one();
        //m->unlock();
    }
}

void consumer(std::queue<std::string>* downloaded_pages, std::mutex* m,
    int* num_processed, std::condition_variable *cv) {
    // 전체 처리하는 페이지 개수가 5 * 5 = 25 개.
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
        //// 만일 현재 다운로드한 페이지가 없다면 다시 대기.
        //if (downloaded_pages->empty()) {
        //    m->unlock();  // (Quiz) 여기서 unlock 을 안한다면 어떻게 될까요?

        //    // 10 밀리초 뒤에 다시 확인한다.
        //    std::this_thread::sleep_for(std::chrono::milliseconds(10));
        //    continue;
        //}

        // 맨 앞의 페이지를 읽고 대기 목록에서 제거한다.
        std::string content = downloaded_pages->front();
        downloaded_pages->pop();

        (*num_processed)++;
        //m->unlock();

        // content 를 처리한다.
        std::cout << content;
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
    }
}

int main() {
    // 현재 다운로드한 페이지들 리스트로, 아직 처리되지 않은 것들이다.
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
