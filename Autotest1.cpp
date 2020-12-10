#include "StringBuffer.h"
#include "Autotest1.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void Autotest(void) {
    StringBuffer Test(2, "0123");
    int i = 0;
    Test.clean();
    Test.append("56");
    Test.append("65");
    if (Test.get_full_str() == "5665") {
        i = i + 1;
    } cout << i << endl;
    Test.full_length();
    if (Test.full_length() == 4) {
        i = i + 1;
    } cout << i << endl;
    Test.insert_string(">INSERT_STRING<", 2);
    if (Test.get_full_str() == "56>INSERT_STRING<65") {
        i = i + 1;
    } cout << i << endl;
    Test.find_substr(">");
    if (Test.find_substr(">") == 2) {
        i = i + 1;
    } cout << i << endl;
    Test.swap_substring("SER", "-I am inserted string ^^-");
    if (Test.get_full_str() == "56>IN-I am inserted string ^^-T_STRING<65") {
        i = i + 1;
    } cout << i << endl;
    Test.cut(3);
    if (Test.get_full_str() == "56>") {
        i = i + 1;
    } cout << i << endl;
    if (i == 6) {
        cout << "Autotest passed!" << endl;
    } else {
        cout << "I'm stuck here..." << endl;
    }
}
