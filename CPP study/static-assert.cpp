#include <iostream>
struct Command {
    int cmd;
    int len;
};

using namespace std;

template <class T>
void foo(T& a) {
    cout << sizeof(Command) << endl;
    cout << sizeof(a.cmd) + sizeof(a.len) << endl;

    static_assert(sizeof(Command) == sizeof(a.cmd) + sizeof(a.len), "Command size is different");
}
int main() {
    Command a;

    foo(a);
}