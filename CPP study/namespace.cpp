#include <iostream>

using namespace std;

namespace Lib {
    inline namespace Lib_1 {
        void new_function() { std::cout << "I'm new function from Lib::Lib_1\\n"; }
    } // namespace Lib_1
    inline namespace Lib_2 {
        void new_function() { std::cout << "I'm new function from Lib::Lib_2\\n"; }
    } // namespace Lib_2
    void old_function() { std::cout << "I'm old function from Lib\\n"; }
} // namespace Lib

int main(int argc, char const* argv[]) {

    Lib::old_function();
    Lib::Lib_1::new_function(); // 사용가능! 자동으로 Lib_1가 포함된다.

    using namespace Lib; // using으로 네임스페이스 이름 생략
    old_function();
    Lib_2::new_function(); // 사용가능! 자동으로 Lib_1가 포함된다.
    return 0;
}


