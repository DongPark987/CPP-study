#include <iostream>

using namespace std;

//class A {
//    int data_;
//
//public:
//    A(int data) : data_(data) { std::cout << "일반 생성자 호출!" << std::endl; }
//
//    A(const A& a) : data_(a.data_) {
//        std::cout << "복사 생성자 호출!" << std::endl;
//    }
//};

class hi {
    int hello[10];
};

//int* suza() {
//    int a[] = {10, 11};
//    int b = 10;
//    return &b;
//}

hi suza() {
    hi h{};
    return h;
}
//
//int susuza() {
//    int&& park = suza();
//    return park;
//}

int main() {
    //A a(1);  // 일반 생성자 호출
    //A b(a);  // 복사 생성자 호출

    //// 그렇다면 이것은?
    //A c(A(2));

    //const int (&park)[2] = suza();
    //cout << park << endl;
    const hi& h = suza();

   
}