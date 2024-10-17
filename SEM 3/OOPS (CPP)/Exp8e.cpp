/*Give the definition of template class POLY which is to be implemented as a linked list using pointers where each node contains a coefficient, an exponent, and a pointer to the next node. Initialize an empty POLY object with no node. Also write code for inserting a node in the list in proper ordered position according to the exponent in the node to be inserted.*/
#include <iostream>
using namespace std;

template <class T>
class POLY {
    struct Node {
        T coeff;
        T exp;
        Node *next;
    };
    Node *head;
public:
    POLY() {
        head = NULL;
    }

    void insert(T coeff, T exp) {
        Node *newNode = new Node;
        newNode->coeff = coeff;
        newNode->exp = exp;
        newNode->next = NULL;

        if (head == NULL || head->exp < exp) {
            newNode->next = head;
            head = newNode;
        } else {
            Node *temp = head;
            Node *prev = NULL;
            while (temp != NULL && temp->exp >= exp) {
                if (temp->exp == exp) {
                    temp->coeff += coeff;
                    return;
                }
                prev = temp;
                temp = temp->next;
                
            }
            newNode->next = temp;
            prev->next = newNode;
        }
    }
    void display() {
        Node *temp = head;
        if (temp == NULL) {
            cout << "Polynomial is empty." << endl;
            return;
        }
        while (temp != NULL) {
            cout << temp->coeff << "x^" << temp->exp;
            if (temp->next != NULL) {
                cout << " + ";
            }
            temp = temp->next;
        }
        cout << endl;
    }
    friend POLY operator+(POLY &p1, POLY &p2) {
        POLY p3;
        Node *temp1 = p1.head;
        Node *temp2 = p2.head;
        while (temp1 != NULL && temp2 != NULL) {
            if (temp1->exp == temp2->exp) {
                p3.insert(temp1->coeff + temp2->coeff, temp1->exp);
                temp1 = temp1->next;
                temp2 = temp2->next;
            } else if (temp1->exp > temp2->exp) {
                p3.insert(temp1->coeff, temp1->exp);
                temp1 = temp1->next;
            } else {
                p3.insert(temp2->coeff, temp2->exp);
                temp2 = temp2->next;
            }
        }
        while (temp1 != NULL) {
            p3.insert(temp1->coeff, temp1->exp);
            temp1 = temp1->next;
        }
        while (temp2 != NULL) {
            p3.insert(temp2->coeff, temp2->exp);
            temp2 = temp2->next;
        }
        return p3;
    }
};

int main() {
    POLY<float> p1, p2, p3;
    int choice;
    float coeff, exp;

    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Insert a term into Polynomial 1\n";
        cout << "2. Insert a term into Polynomial 2\n";
        cout << "3. Display Polynomial 1\n";
        cout << "4. Display Polynomial 2\n";
        cout << "5. Add the two polynomials\n";
        cout << "6. Display the result of addition\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter coefficient and exponent for Polynomial 1: ";
            cin >> coeff >> exp;
            p1.insert(coeff, exp);
            break;

        case 2:
            cout << "Enter coefficient and exponent for Polynomial 2: ";
            cin >> coeff >> exp;
            p2.insert(coeff, exp);
            break;

        case 3:
            cout << "Polynomial 1: ";
            p1.display();
            break;

        case 4:
            cout << "Polynomial 2: ";
            p2.display();
            break;

        case 5:
            p3 = p1 + p2;
            cout << "Polynomials added successfully!\n";
            break;

        case 6:
            cout << "Resulting Polynomial: ";
            p3.display();
            break;

        case 7:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 7);

    return 0;
}
