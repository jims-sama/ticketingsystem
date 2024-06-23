#include <iostream>
#include <stack>

using namespace std;

class TicketCounter {
private:
    stack<int> stackNewestOnTop; // Stack to hold the newest elements
    stack<int> stackOldestOnTop; // Stack to hold the oldest elements

    // Transfer elements from stackNewestOnTop to stackOldestOnTop
    void shiftStacks() {
        if (stackOldestOnTop.empty()) {
            while (!stackNewestOnTop.empty()) {
                stackOldestOnTop.push(stackNewestOnTop.top());
                stackNewestOnTop.pop();
            }
        }
    }

public:
    // Enqueue a new customer
    void enqueue(int customerNumber) {
        stackNewestOnTop.push(customerNumber);
        cout << "Customer " << customerNumber << " arrives (enqueue): Added ticket number " << customerNumber << endl;
    }

    // Dequeue and serve the next customer
    void dequeue() {
        if (isEmpty()) {
            cout << "No customers in queue." << endl;
            return;
        }
        shiftStacks();
        int nextTicket = stackOldestOnTop.top();
        stackOldestOnTop.pop();
        cout << "Now serving ticket number " << nextTicket << endl;
    }

    // Get the ticket number of the next customer without dequeueing
    int peek() {
        if (isEmpty()) {
            cout << "No customers in queue." << endl;
            return -1; // Indicate an error
        }
        shiftStacks();
        return stackOldestOnTop.top();
    }

    // Display the current queue status
    void display() {
        if (isEmpty()) {
            cout << "Queue status: []" << endl;
            return;
        }
        cout << "Queue status: [";

        stack<int> tempStackNewest = stackNewestOnTop;
        stack<int> tempStackOldest = stackOldestOnTop;

        // First, display elements in stackOldestOnTop
        stack<int> displayStack;
        while (!tempStackOldest.empty()) {
            displayStack.push(tempStackOldest.top());
            tempStackOldest.pop();
        }
        while (!displayStack.empty()) {
            cout << displayStack.top();
            displayStack.pop();
            if (!tempStackOldest.empty() || !tempStackNewest.empty()) {
                cout << ", ";
            }
        }

        // Then, display elements in stackNewestOnTop (in reverse order)
        stack<int> reversedStackNewest;
        while (!tempStackNewest.empty()) {
            reversedStackNewest.push(tempStackNewest.top());
            tempStackNewest.pop();
        }
        while (!reversedStackNewest.empty()) {
            cout << reversedStackNewest.top();
            reversedStackNewest.pop();
            if (!reversedStackNewest.empty()) {
                cout << ", ";
            }
        }

        cout << "]" << endl;
    }

    // Check if the queue is empty
    bool isEmpty() {
        return stackNewestOnTop.empty() && stackOldestOnTop.empty();
    }
};

int main() {
    TicketCounter counter;
    int choice;
    int customerNumber = 1; // Initial customer number

    do {
        cout << "\nTicket Counter Menu:\n";
        cout << "1. Enqueue a customer\n";
        cout << "2. Dequeue and serve a customer\n";
        cout << "3. Peek at the next customer\n";
        cout << "4. Display queue status\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                counter.enqueue(customerNumber++);
                break;
            case 2:
                counter.dequeue();
                break;
            case 3: {
                int nextCustomer = counter.peek();
                if (nextCustomer != -1) {
                    cout << "Next customer to be served has ticket number " << nextCustomer << endl;
                }
                break;
            }
            case 4:
                counter.display();
                break;
            case 5:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 5);

    return 0;
}

