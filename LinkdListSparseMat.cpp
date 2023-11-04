#include <iostream>

// Define a class for representing individual matrix elements
class Element {
public:
    int r;      // Represents the row index of an element
    int c;      // Represents the column index of an element
    int val;    // Stores the value of an element

    Element(int row, int col, int value) : r(row), c(col), val(value) {}
};

// Create a class for linked list nodes to store matrix elements
class ListNode {
public:
    Element data;    // Contains data for a matrix element
    ListNode* next;  // Points to the next node in the linked list

    ListNode(int row, int col, int value) : data(row, col, value), next(nullptr) {}
};

// Implement a class to represent a sparse matrix
class SparseMatrix {
private:
    ListNode* head;  // Points to the first node in the linked list
    int numRows, numCols;  // Indicates the number of rows and columns in the matrix

public:
    SparseMatrix(int m, int n) : head(nullptr), numRows(m), numCols(n) {}

    // Method for inserting a new element into the sparse matrix
    void InsertElement(int row, int col, int value) {
        if (row < 0 || row >= numRows || col < 0 || col >= numCols) {
            // Handle situations with invalid matrix indices
            std::cerr << "Invalid matrix indices." << std::endl;
            return;
        }

        ListNode* newNode = new ListNode(row, col, value);
        if (!head) {
            // If the list is empty, set the new node as the head
            head = newNode;
            return;
        }

        ListNode* current = head;
        ListNode* previous = nullptr;

        // Locate the appropriate position to insert the new node in the linked list
        while (current && (current->data.r < row || (current->data.r == row && current->data.c < col))) {
            previous = current;
            current = current->next;
        }

        if (previous) {
            previous->next = newNode;
        } else {
            // Insert the new node at the beginning of the list
            head = newNode;
        }

        newNode->next = current;
    }

    // Method for displaying the sparse matrix
    void DisplayMatrix() {
        ListNode* current = head;
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                if (current && current->data.r == i && current->data.c == j) {
                    // Output the value of a non-zero element at this position
                    std::cout << current->data.val << " ";
                    current = current->next;
                } else {
                    // Output 0 if no element is found at this position
                    std::cout << "0 ";
                }
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    int numRows, numCols;
    std::cout << "Enter the number of rows and columns: ";
    std::cin >> numRows >> numCols;

    SparseMatrix matrix(numRows, numCols);

    int row, col, value;

    while (true) {
        std::cout << "Enter row, column, and value (or -1 to exit): ";
        std::cin >> row;
        if (row == -1)
            break;

        std::cin >> col >> value;
        matrix.InsertElement(row, col, value);
    }

    std::cout << "Sparse Matrix:" << std::endl;
    matrix.DisplayMatrix();

    return 0;
}
