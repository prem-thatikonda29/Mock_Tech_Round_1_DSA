#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* next;
};

// Creating a new node
Node* createNode(int data) {
    Node* newNode = new Node();
    if (!newNode) {
        cout << "Memory error\n";
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Inserting a new node at the end
void insertNode(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* lastNode = *head;
    while (lastNode->next) {
        lastNode = lastNode->next;
    }
    lastNode->next = newNode;
}

// Printing the linked list
void printList(Node* head) {
    while (head) {
        if(head->next == NULL){
            cout << head->data << " -> NULL";
        }
        else{
            cout << head->data << " -> ";
        }
        head = head->next;
    }
    cout << endl;
}

// Detect cycle
bool detectCycle(Node* head) {
    if (head == NULL || head->next == NULL) {
        return false;
    }
    Node* slow = head;
    Node* fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }
    return false;
}

// Removing the cycle
void removeCycle(Node* head) {
    if (head == NULL || head->next == NULL) {
        return;
    }
    Node* slow = head;
    Node* fast = head;

    // Detect cycle and find meeting point
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            break;
        }
    }

    // Check if a cycle exists
    if (slow == fast) {
        slow = head;
        if (slow == fast) {
            while (fast->next != slow) {
                fast = fast->next;
            }
        } else {
            // Move both pointers until they meet at the start of the cycle
            while (slow->next != fast->next) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        // Break the cycle
        fast->next = NULL;
    }
}


// Reverse linked list
Node* reverseList(Node* head) {
    Node* prev = NULL;
    Node* current = head;
    Node* next = NULL;
    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

// Free linked list memory
void freeList(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// Main function
int main() {
    Node* head = NULL;
    insertNode(&head, 1);
    insertNode(&head, 2);
    insertNode(&head, 3);
    insertNode(&head, 4);
    insertNode(&head, 5);

    // head->next->next->next->next->next = head->next->next;

    cout << "Original Linked List: ";
    head = reverseList(head);
    cout << "Reversed Linked List: ";
    printList(head);

    if(detectCycle(head)){
        cout << "Cycle detected in the linked list" << endl;
    }
    else{
        cout << "No cycle detected in the linked list" << endl;
        removeCycle(head);
        cout << "Cycle removed from the linked list" << endl;
        // printList(head);
    }

    // Free allocated memory
    freeList(head);

    return 0;
}