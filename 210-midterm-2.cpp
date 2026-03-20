//*****************************************************************************
// COMSC-210 | Midterm 2 | Gabriel Marquez
// Description: this program simulates a line at a coffee shop. The simulation
// runs for 20 time periods (minutes) and displays the current line.
//*****************************************************************************

#include <iostream>
#include <vector> //to hold names
#include <fstream> //to read names from file
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;
const int TIME_PERIODS = 19; //first period of 20 adds 5 right away
const int NAME_MAX = 98; //to randomly select a name
const int FIRST_CUSTOMERS = 5; //for first customers

class DoublyLinkedList {
private:
    struct Node {
        string name;
        Node* prev;
        Node* next;
        Node(string customer, Node* p = nullptr, Node* n = nullptr) {
            name = customer; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void insert_after(string value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(string value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->name != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(string v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << "\t\t" << current->name << endl;
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->name << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    srand(time(0)); //for random numbers & probabilities
    vector<string> names;
    string custName;
    ifstream fin ("names.txt");
    if (fin.good( )) {
        while(fin >> custName) {
            names.push_back(custName); //read names into vector
        }
        fin.close( );         
    }
    else
    cout << "File not found. Check file name/directory and restart program\n";

    DoublyLinkedList list; //create doubly linked list object
    cout << "Store opens:" << endl;
    //take a random name from names & add to list
    for (int i = 0; i < FIRST_CUSTOMERS; ++i) {
        string customer = names[rand() % NAME_MAX];
        list.push_back(customer);
        cout << "\t" << customer << " joins the line." << endl;
    }
    cout << "\tResulting line:" << endl;
    list.print();

    //loop for next 19 minutes (20 total)
    for (int i = 0; i < TIME_PERIODS; i++) {
        cout << "Time step #" << i + 2 << ":" << endl;
        //customer joins the line (60%)
        int prob = rand() % 100 + 1; // returns random number 1-100
        if (prob <= 60) {
            string customer = names[rand() % NAME_MAX];
            list.push_back(customer);
            cout << "\t" << customer << " joins the line." << endl;
        }
        //
        if ()
    }

    return 0;
}