#include <iostream>
#include <cstring>
#include <utility>
#include <type_traits>

class MyString {
    char* string_content;  // ���ڿ� �����͸� ����Ű�� ������
    int string_length;     // ���ڿ� ����

    int memory_capacity;  // ���� �Ҵ�� �뷮

public:
    MyString();

    // ���ڿ��� ���� ����
    MyString(const char* str);

    // ���� ������
    MyString(const MyString& str);

    // �̵� ������
    MyString(MyString&& str);

    MyString& operator=(const MyString& s);

    // 
    MyString& operator=(MyString&& s) noexcept;
    ~MyString();

    int length() const;

    void println();
};

MyString::MyString() {
    std::cout << "������ ȣ�� ! " << std::endl;
    string_length = 0;
    memory_capacity = 0;
    string_content = NULL;
}

MyString::MyString(const char* str) {
    std::cout << "������ ȣ�� ! " << std::endl;
    string_length = strlen(str);
    memory_capacity = string_length;
    string_content = new char[string_length];

    for (int i = 0; i != string_length; i++) string_content[i] = str[i];
}
MyString::MyString(const MyString& str) {
    

    std::cout << "���� ������ ȣ�� ! " << std::endl;
    string_length = str.string_length;
    string_content = new char[string_length];

    for (int i = 0; i != string_length; i++)
        string_content[i] = str.string_content[i];
}
MyString::MyString(MyString&& str) {
    std::cout << "�̵� ������ ȣ�� !" << std::endl;
    string_length = str.string_length;
    string_content = str.string_content;
    memory_capacity = str.memory_capacity;

    // �ӽ� ��ü �Ҹ� �ÿ� �޸𸮸� ��������
    // ���ϰ� �Ѵ�.
    str.string_content = nullptr;
}
MyString::~MyString() {
    if (string_content) delete[] string_content;
}

MyString& MyString::operator=(const MyString& s) {
    std::cout << "����!" << std::endl;
    if (s.string_length > memory_capacity) {
        delete[] string_content;
        string_content = new char[s.string_length];
        memory_capacity = s.string_length;
    }
    string_length = s.string_length;
    for (int i = 0; i != string_length; i++) {
        string_content[i] = s.string_content[i];
    }

    return *this;
}

MyString& MyString::operator=(MyString&& str) noexcept{
    std::cout << "�̵�!" << std::endl;
    string_length = str.string_length;
    string_content = str.string_content;
    memory_capacity = str.memory_capacity;

    str.string_content = nullptr;
    str.memory_capacity = 0;
    str.string_length = 0;
    return *this;
}

int MyString::length() const { return string_length; }
void MyString::println() {
    for (int i = 0; i != string_length; i++) std::cout << string_content[i];

    std::cout << std::endl;
}
template <typename T>
void my_swap(T& a, T& b) {
    T tmp(static_cast<T&&>(a));
    //T tmp(std::move(a));
    //a = std::move(b);
    a = static_cast<std::remove_reference_t<T>&&>(b);
    //b = std::move(tmp);
    b = static_cast<std::remove_reference_t<T>&&>(tmp);
}

int main() {
    MyString str1("abc");
    MyString str2("def");
    std::cout << "Swap �� -----" << std::endl;
    str1.println();
    str2.println();

    std::cout << "Swap �� -----" << std::endl;
    my_swap(str1, str2);
    str1.println();
    str2.println();
}