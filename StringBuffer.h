#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Node.h"
using namespace std;

class Node;
class StringBuffer {
private:
    Node* root;
    int piece_size;
public:
    StringBuffer();
    StringBuffer(int piece_size); // Creates empty buffer which will contain strings by pieces with taken size
    StringBuffer(int piece_size, string S); // Creates buffer and initializes it with first string

    void print() const; // Prints entire buffer
    bool clean(); // Cleans buffer
    bool append(const string &S); // Adding a string to the buffer end
    bool insert_string(const string &S, int pos); // Inserting string in buffer
    bool copy_string(char* to_copy) const; // copying string to pointer
    bool copy_substring(char* to_copy, int substr_start, int substr_length) const; // copying substring to pointer
    char get_symbol(int pos) const; // returning symbol at given position
    bool set_symbol(int pos, char symbol); // setting symbol at position
    int find_symbol(char symbol) const; // returning index of finded symbol (-1 if not found)
    int find_substr(const string &S) const; // returning first index of finded substring (-1 if not found)
    bool swap_substring(const string &to_remove, const string &to_insert);
    bool cut(int length);
    int full_length() const;
    string get_full_str() const;
};
