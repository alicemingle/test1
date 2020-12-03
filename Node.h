#pragma once
#include "StringBuffer.h"
using namespace std;
class StringBuffer;
class Node {
private:
    string data;
    Node* next_node;
    Node* prev_node;
public:
    Node();
    Node(string data, Node* prev);
    string Get_String() const;
    friend class StringBuffer;
    Node& operator=(const Node &N);
};
