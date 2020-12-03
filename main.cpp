#include "StringBuffer.h"

int main(void) {
    StringBuffer Test(3, "0123456789");
    Test.print();
    Test.clean();
    cout << "-------------" << endl;
    Test.append("123456");
    Test.append("654321");
    Test.print();
    cout << "Full length is " << Test.full_length() << endl;
    cout << "-------------" << endl;
    Test.insert_string(">INSERT_STRING<", 4);
    Test.print();
    cout << "-------------" << endl;
    cout << Test.find_substr(">") << endl;
    cout << "-------------" << endl;
    Test.swap_substring("SER", "-I am inserted string ^^-");
    Test.print();
    cout << "-------------" << endl;
    Test.cut(11);
    Test.print();
    return 0;
}
