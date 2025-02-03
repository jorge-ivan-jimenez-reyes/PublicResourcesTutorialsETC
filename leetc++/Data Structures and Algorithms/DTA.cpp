//
// Created by Jorge Ivan Jimenez Reyes  on 02/02/25.
//

//lINKED List
//like a chain of people holding hands
//Each person (node) only nows two thingss
//Their own number data
//Who thweir are holdng hands pointer
#include <iostream>
using namespace std;

//Creating a node Structure
struct Node {
    int data;//the data stored in the node
    Node* next;// Pointer to the next node
};

//Fuction to print the linked list

void printList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << "->";
        temp = temp->next;
    }
    cout << "NULL" << endl;// indicates the end of the list
}

int main() {
    //Creating nodes
    Node* first = new Node();
    Node* second = new Node();
    Node* third = new Node();
    //Asgning values
    first->data = 1;
    first->next = second;//Linking first node to second node

    second->data = 2;
    second->next = third;//linking second node to third node

    third->data = 3;
    third->next = nullptr;//last node points to null

    //printing the list
    printList(first);
    return 0;
}

//Arra vs Linked _List https://www.youtube.com/watch?v=B31LgI4Y4DQ&t=13191s

