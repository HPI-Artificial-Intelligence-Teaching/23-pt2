#include <iomanip>
#include <iostream>

using namespace std;

// A class that represents strings of fixed length efficiently
class MyString {
    char* str;  // the pointer to the actual (non-zero-terminated!) string
    int len;    // the length of the string
   public:
    // default constructor
    MyString() : str(nullptr), len(0) {}

    // default constructor for undefined string with fixed length
    MyString(const int l) {
        if (l < 0) exit(-1);
        len = l;
        str = new char[len];
    }

    // constructs a string from a C-style string
    MyString(const char* s) {
        // counts the length of the C-string (without the terminating '\0')
        len = 0;
        for (int i = 0; s[i]; i++, len++)
            ;

        // allocate the memory for all the characters
        str = new char[len];

        // copy all the characters
        for (int i = 0; i < len; i++)
            str[i] = s[i];
    }
    // copy constructor
    MyString(const MyString& ms) : len(ms.len) {
        // allocate the memory for all the characters
        str = new char[len];

        // copy all the characters
        for (int i = 0; i < len; i++)
            str[i] = ms.str[i];
    }
    // move constructor
    MyString(MyString&& ms) : len(ms.len), str(ms.str) {
        ms.len = 0;
        ms.str = nullptr;
    }
    // destructor
    ~MyString() {
        delete[] str;
    }
    // copy assignment operator
    MyString& operator=(const MyString& ms) {
        // free the existing string
        delete[] str;

        // copy the length of the assigned string
        len = ms.len;

        // allocate the memory for all the characters
        str = new char[len];

        // copy all the characters
        for (int i = 0; i < len; i++)
            str[i] = ms.str[i];
        return (*this);
    }
    // move assignment operator
    MyString& operator=(MyString&& ms) {
        // free the existing string
        delete[] str;

        // copy the length of the assigned string
        len = ms.len;

        // copy the pointer from the moved MyString ...
        str = ms.str;

        // ... and invalidate the moved data
        ms.len = 0;
        ms.str = nullptr;
        return (*this);
    }
    // index operator overload
    char& operator[](size_t pos) const {
        if (pos < 0 || pos > (len - 1))
            exit(-1);
        return (str[pos]);
    }

    // returns the length of the string
    int length() const { return len; }

    // output the string on an output stream
    void print() const {
        for (int i = 0; i < len; i++)
            cout << str[i];
        return;
    }
};

// implementation of the stream output of MyString
ostream& operator<<(ostream& out, const MyString& ms) {
    for (int i = 0; i < ms.length(); i++)
        out << ms[i];
    return (out);
}

// string concatenation as the addition operation
MyString operator+(const MyString& lhs, const MyString& rhs) {
    MyString out(lhs.length() + rhs.length());

    // first copy the characters of the left hands side ...
    int i = 0;
    for (int j = 0; j < lhs.length(); j++, i++)
        out[i] = lhs[j];
    // ... and then copy the characters of the right hand side
    for (int j = 0; j < rhs.length(); j++, i++)
        out[i] = rhs[j];

    return (out);
}

// Transforms a string to upper case
MyString to_upper(const MyString& ms) {
    MyString tmp = ms;

    for (int i = 0; i < tmp.length(); i++)
        tmp[i] = toupper(tmp[i]);
    return (tmp);
}

// main entry point of the program
int main(void) {
    MyString s1("Hello world!");
    MyString s2(s1);
    MyString s3;
    MyString s4 = "Hello";
    MyString s5 = " World!";
    MyString s6;

    // change one character in the first string
    s1[5] = ',';

    // then set the default initialized string to the result of an operation
    s3 = to_upper(s2);

    // and then concatenate two string
    s6 = s4 + s5;

    cout << setw(10) << "s1 = ";
    s1.print();
    cout << endl;

    cout << setw(10) << "s2 = " << s2 << endl;
    cout << setw(10) << "s3 = " << s3 << endl;
    cout << setw(10) << "s4 = " << s4 << endl;
    cout << setw(10) << "s5 = " << s5 << endl;
    cout << setw(10) << "s6 = " << s6 << endl;

    return (0);
}