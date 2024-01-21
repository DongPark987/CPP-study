#include <iostream>

using namespace std;

class MyClass
{
public:
	int a;
	MyClass(int i) : a(i) {
	
	};
	~MyClass();

	void aaa() {
		cout << a << endl;
	}

private:

};


MyClass::~MyClass()
{
}

int main() {
	MyClass mc(10);
	mc.aaa();
}                                                                                                                     