#include <iostream>
#include "BST.h"

using namespace CustomBST;
using namespace std;

int main() {
    BST tree;
    
    cout << "1. Inserting elements:\n";
    tree += 50;
    tree += 30;
    tree += 70;
    tree += 20;
    tree += 40;
    cout << tree.toString() << "\n\n";

    cout << "2. Searching elements:\n";
    cout << "Contains 30? " << (tree[30] ? "Yes" : "No") << "\n";
    cout << "Contains 99? " << (tree[99] ? "Yes" : "No") << "\n\n";

    cout << "3. Updating element, changing 30 to 35:\n";
    tree *= make_pair(30, 35);
    cout << tree.toString() << "\n\n";

    cout << "4. Deleting element 70:\n";
    tree -= 70;
    cout << tree.toString() << "\n\n";

    cout << "5. Exception handling test:\n";
    try {
        cout << "Attempting to insert duplicate (50):\n";
        tree += 50;
    } catch (const DuplicateNodeException& e) {
        cout << "Caught custom exception: " << e.what() << "\n\n";
    }

    try {
        cout << "Attempting to delete non-existent (99):\n";
        tree -= 99;
    } catch (const std::invalid_argument& e) {
        cout << "Caught standard exception: " << e.what() << "\n";
    }
    cout << "\n";

    cout << "6. Clearing tree:\n";
    !tree;
    cout << tree.toString() << "\n";

    return 0;
}