#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node *prev;
    Node *next;

    Node(int val) {
        data = val;
        prev = NULL;
        next = NULL;
    }
    friend Node* operator+(const Node& node1, const Node& node2);
};

Node* operator+(const Node& node1, const Node& node2) {
    int newData = node1.data + node2.data;
    return new Node(newData);
}

class DLL {
public:
    Node *head;
    DLL() {
        head = NULL;
    }

    void append(Node *newNode) {
        if (!head) {
            head = newNode;
        } else {
            Node *temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->prev = temp;
        }
    }

    void operator=(Node &temp) {
        head = &temp;
    }

    void operator+=(int val) {
        if (head) {
            head->data += val;
        }
        else
            head->data=0;
    }

    friend ostream& operator<<(ostream &out, DLL &obj);
};

ostream& operator<<(ostream &out, DLL &obj) {
    Node* temp = obj.head;
    while (temp) {
        out << temp->data << " ";
        temp = temp->next;
    }
    return out;
}

int main() {
    DLL firstnode;

    Node node1(10);
    Node node2(30);

    firstnode = node1;
    firstnode += 10;
    Node *n = node1 + node2;

    firstnode.append(&node2);
    firstnode.append(n);

    cout << "DoublyLinkedList: ";
    cout << firstnode << endl;

    delete n,firstnode;

    return 0;
}
