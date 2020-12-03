#include "Node.h"

Node::Node() {
    data = string();
    next_node = prev_node = nullptr;
}

Node::Node(string data, Node* prev) {
    this->data = data;
    prev_node = prev;
    next_node = nullptr;
}

string Node::Get_String() const {
    return data;
}

Node& Node::operator=(const Node &N) {
    data = N.data;
    next_node = N.next_node;
    prev_node = N.prev_node;

    return *this;
}
