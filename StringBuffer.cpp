#include "StringBuffer.h"

StringBuffer::StringBuffer() {
    root = nullptr;
    piece_size = 0;
}

StringBuffer::StringBuffer(int piece_size) {
    root = nullptr;
    this->piece_size = piece_size;
}

StringBuffer::StringBuffer(int piece_size, string S) {
    if (piece_size <= 0) {
        cout << "Error: incorrect piece size." << endl;
        exit(-1);
    }
    this->piece_size = piece_size;
    // Creating root node
    root = new Node(S.substr(0, piece_size), nullptr);
    // Estimating symbols
    int estimating = static_cast<int>(S.size()) - piece_size;  //создаем указатель на корневую ячейку списка, до остальных
    Node* prev = root;  //доеберемся по указателям, потом впихиваем кусочек, длина которого пис сайз, и пока строка
    while (estimating > 0) {  //не заполнится полностью идет вайл, т е создаем новые вершинки, распихивая по ячейкам текст,
        Node *next = new Node(S.substr(static_cast<int>(S.size()) - estimating, piece_size), prev); //пока все не закончица.
        prev->next_node = next;
        estimating -= piece_size;
        prev = next;
    }
}

void StringBuffer::print() const {
    if (root == nullptr) {
        cout << "Error: nothing to print." << endl;
    }
    Node *curr = root;
    while (curr != nullptr) {
       cout << curr->data;
       curr = curr->next_node;
    }
    cout << endl;
}

bool StringBuffer::clean() {
    if (root == nullptr) {
        cout << "Buffer is already empty." << endl;
        return false;
    }
    Node *curr = root;
    while (curr != nullptr) {
        Node *curr_was = curr;
        curr = curr->next_node;
        delete curr_was;
    }
    root = nullptr;
    return true;
}

bool StringBuffer::append(const string &S) {
    if (root == nullptr) {
        if (piece_size == 0) {
            cout << "Error: cannot append string " << S << ": buffer is uninitialized." << endl;
            return false;
        } else {
            root = new Node(S.substr(0, piece_size), nullptr);
            // Estimating symbols
            int estimating = static_cast<int>(S.size()) - piece_size;
            Node* prev = root;
            while (estimating > 0)
            {
                Node *next = new Node(S.substr(static_cast<int>(S.size()) - estimating, piece_size), prev);
                prev->next_node = next;
                estimating -= piece_size;
                prev = next;
            }
        }
    } else {
        // Seeking for last string
        Node *last = root;
        while (last->next_node != nullptr) {
            last = last->next_node;
        }
        int estimating = static_cast<int>(S.size());
        Node* prev = last;
        while (estimating > 0) {
            Node *next = new Node(S.substr(static_cast<int>(S.size()) - estimating, piece_size), prev);
            prev->next_node = next;
            estimating -= piece_size;
            prev = next;
        }
    }
    return true;
}

int StringBuffer::full_length() const {
    if (root == nullptr) {
        return 0;
    }
    int length = 0;
    Node *curr = root;
    while (curr != nullptr) {
        length += static_cast<int>(curr->data.size());
        curr = curr->next_node;
    }
    return length;
}

bool StringBuffer::insert_string(const string& S, int pos) {
    if (root == nullptr) {
        if (piece_size == 0) {
            cout << "Error: buffer is uninitialized, cannot insert string." << endl;
            return false;
        }
        if (pos != 0) {
            cout << "Warning: buffer was clear, inserting " << S << " at position 0." << endl;
        }
        root = new Node(S.substr(0, piece_size), nullptr);
        int estimating = static_cast<int>(S.size()) - piece_size;
        Node* prev = root;
        while (estimating > 0) {
            Node *next = new Node(S.substr(static_cast<int>(S.size()) - estimating, piece_size), prev);
            prev->next_node = next;
            estimating -= piece_size;
            prev = next;
        }
        return true;
    }
    if (pos < 0 || pos >= full_length()) {
        cout << "Error: incorrect position." << endl;
        return false;
    }
    if (pos == full_length()-1) {
        // Seeking for last node
        Node *last = root;
        while (last->next_node != nullptr) {
            last = last->next_node;
        }
        int estimating = static_cast<int>(S.size());
        while (estimating > 0) {
            Node *next = new Node(S.substr(static_cast<int>(S.size()) - estimating, piece_size), last);
            last->next_node = next;
            estimating -= piece_size;
            last = next;
        }
        return true;
    }
    string curr_buffer = get_full_str();
    curr_buffer = curr_buffer.substr(0, pos) + S + curr_buffer.substr(pos, static_cast<int>(curr_buffer.size()) - pos);
    clean();
    root = new Node(curr_buffer.substr(0, piece_size), nullptr);
    int estimating = static_cast<int>(curr_buffer.size()) - piece_size;
    Node *prev = root;
    while (estimating > 0) {
        Node *next = new Node(curr_buffer.substr(static_cast<int>(curr_buffer.size()) - estimating, piece_size), prev);
        prev->next_node = next;
        estimating -= piece_size;
        prev = next;
    }
    return true;
}

string StringBuffer::get_full_str() const {
    if (root == nullptr || full_length() == 0) {
        cout << "Error: nothing to get." << endl;
        exit(-1);
    }
    string result = "";
    Node *curr = root;
    while (curr != nullptr) {
        result += curr->data;
        curr = curr->next_node;
    }
    return result;
}

bool StringBuffer::copy_string(char *to_copy) const {
    if (to_copy == nullptr) {
        cout << "Error: empty copy pointer." << endl;
        return false;
    }
    if (root == nullptr || full_length() == 0) {
        cout << "Error: nothing to copy." << endl;
        return false;
    }
    Node *curr = root;
    int pos = 0;
    while (curr != nullptr) {
        for (int i = 0; i < piece_size; ++i) {
            to_copy[pos] = curr->data[i];
            pos++;
        }
        curr = curr->next_node;
    }
    return true;
}

bool StringBuffer::copy_substring(char* to_copy, int substr_start, int substr_length) const {
    if (root == nullptr || full_length() == 0) {
        cout << "Error: nothing to copy." << endl;
        return false;
    }
    if (to_copy == nullptr) {
        cout << "Error: empty copy pointer." << endl;
        return false;
    }
    if (substr_start + substr_length > full_length()) {
        cout << "Error: incorrect substring parameters. " <<endl;
        return false;
    }
    int cell_number = (substr_start%piece_size) + 1;
    Node *goal = root;
    for (int i = 0; i < cell_number-1; ++i) {
        goal = goal->next_node;
    }
    int pos = 0, estimating = substr_length;
    while (estimating > 0) {
        if (pos == 0) {
            for (int i = 0; i < piece_size - substr_start%piece_size; ++i) {
                to_copy[pos] = goal->data[i];
                pos++;
                estimating--;
            }
        } else {
            for (int i = 0; i < piece_size && i < estimating; ++i) {
                to_copy[pos] = goal->data[i];
                pos++;
                estimating--;
            }
        }
        goal = goal->next_node;
    }
    return true;
}

char StringBuffer::get_symbol(int pos) const {
    if (root == nullptr || full_length() == 0) {
        cout << "Error: nothing to get." << endl;
        exit(-1);
    }
    if (pos < 0 || pos >= full_length()) {
        cout << "Error: incorrect symbol position." << endl;
        exit(-1);
    }
    int cell_number = pos%piece_size + 1;
    Node *goal = root;
    for (int i=0; i < cell_number-1; ++i) {
        goal = goal->next_node;
    }
    return static_cast<char>(goal->data[pos%piece_size]);
}

bool StringBuffer::set_symbol(int pos, char symbol) {
    if (root == nullptr || full_length() == 0) {
        cout << "Error: nowhere to set." << endl;
        return false;
    }
    if (pos < 0 || pos >= full_length()) {
        cout << "Error: incorrect setting position." << endl;
        return false;
    }
    int cell_number = pos%piece_size + 1;
    Node *goal = root;
    for (int i=0; i < cell_number-1; ++i) {
        goal = goal->next_node;
    }
    goal->data[pos%piece_size] = symbol;
    return true;
}

int StringBuffer::find_symbol(char symbol) const {
    if (root == nullptr || full_length() == 0) {
        cout << "Error: nowhere to search." << endl;
        return -1;
    }
    int pos = 0;
    Node *curr = root;
    while (curr != nullptr) {
        for (int i = 0; i < piece_size; ++i) {
            if (curr->data[i] == symbol) {
                return pos;
            }
            pos++;
        }
        curr = curr->next_node;
    }
    return -1;
}

int StringBuffer::find_substr(const string &S) const {
    if (root == nullptr || full_length() == 0) {
        cout << "Error: nowhere to search." << endl;
        return -1;
    }
    if (static_cast<int>(S.size()) > full_length()) {
        cout << "Warning: too big substring to search." << endl;
        return -1;
    }
    int pos = 0;
    int symbol_pos = 0;
    Node *curr = root;
    while (curr != nullptr) {
        for (int i = 0; i < piece_size && i < static_cast<int>(curr->data.size()); ++i) {
            if (curr->data[i] == S[symbol_pos]) {
                symbol_pos++;
                if (symbol_pos == static_cast<int>(S.size())) {
                    return pos - symbol_pos + 1;
                }
            } else {
                symbol_pos = 0;
            }
            pos++;
        }
        curr = curr->next_node;
    }
    return -1;
}

bool StringBuffer::swap_substring(const string &to_remove, const string &to_insert) {
    if (root == nullptr || full_length() == 0) {
        if (piece_size == 0) {
            cout << "Error: buffer is uninitialized." << endl;
            return false;
        } else {
            insert_string(to_insert, 0);
            return true;
        }
    }
    int rem_index = find_substr(to_remove);
    if (rem_index == -1) {
        cout << "Cannot swap such strings: " << to_remove << " is not in buffer." << endl;
        return false;
    }
    string curr_buffer = get_full_str();
    curr_buffer = curr_buffer.substr(0, rem_index) +
    to_insert +
    curr_buffer.substr(rem_index + static_cast<int>(to_remove.size()), static_cast<int>(curr_buffer.size()) - rem_index - static_cast<int>(to_remove.size()));
    clean();
    root = new Node(curr_buffer.substr(0, piece_size), nullptr);
    int estimating = static_cast<int>(curr_buffer.size()) - piece_size;
    Node *prev = root;
    while (estimating > 0) {
        Node *next = new Node(curr_buffer.substr(static_cast<int>(curr_buffer.size()) - estimating, piece_size), prev);
        prev->next_node = next;
        estimating -= piece_size;
        prev = next;
    }
    return true;
}
bool StringBuffer::cut(int length) {
    if (root == nullptr || full_length() == 0) {
        cout << "Error: nothing to cut." << endl;
        return false;
    }
    string curr_buffer = get_full_str();
    curr_buffer = curr_buffer.substr(0, length);
    clean();
    root = new Node(curr_buffer.substr(0, piece_size), nullptr);
    int estimating = static_cast<int>(curr_buffer.size()) - piece_size;
    Node *prev = root;
    while (estimating > 0) {
        Node *next = new Node(curr_buffer.substr(static_cast<int>(curr_buffer.size()) - estimating, piece_size), prev);
        prev->next_node = next;
        estimating -= piece_size;
        prev = next;
    }
    return true;
}
