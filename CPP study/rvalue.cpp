#include <iostream>

using namespace std;

//class A {
//    int data_;
//
//public:
//    A(int data) : data_(data) { std::cout << "�Ϲ� ������ ȣ��!" << std::endl; }
//
//    A(const A& a) : data_(a.data_) {
//        std::cout << "���� ������ ȣ��!" << std::endl;
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
    //A a(1);  // �Ϲ� ������ ȣ��
    //A b(a);  // ���� ������ ȣ��

    //// �׷��ٸ� �̰���?
    //A c(A(2));

    //const int (&park)[2] = suza();
    //cout << park << endl;
    const hi& h = suza();

   
}