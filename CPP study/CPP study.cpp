// CPP study.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

using namespace std;

class Calc
{
private:
    int m_Value = 0;

public:
    Calc& Add(int value) { m_Value += value; return *this; }
    Calc& Sub(int value) { m_Value -= value; return *this; }
    Calc& Mul(int value) { m_Value *= value; return *this; }

    int GetValue() { return m_Value; }
};
int z = 100;
int &reftest(int &a){
    int aa = 10;
    int& bb = aa;
    return z;
}

struct MyStruct
{

};

namespace hello {
    enum {
        A = 1,
        B = 2
    };
}

enum class MyEnumClass
{
    C = 199
};

struct A
{

};

struct B : A
{

};

int main()
{
    Calc calc;
    const int z = 10;
   
    static_assert(true, "죽어");

    //static_assert(constant - expression); // C++17 (Visual Studio 2017 and later)

    calc.Add(5).Sub(3).Mul(4);

    cout << calc.GetValue() << endl; // 8
    int a = 0;
    int& b = a;
    int& c = b;


    int aa = 0;  
    int &bb = reftest(aa);
    bb++;
    cout << aa << endl << bb << endl << z << endl;


    MyEnumClass A = MyEnumClass::C;

    if (A == MyEnumClass::C) {
        cout << "된다." << endl;
    }
    cout << (int)MyEnumClass::C << endl;


    return 0;
}
