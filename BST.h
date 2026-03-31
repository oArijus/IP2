#ifndef BST_H
#define BST_H

#include <string>
#include <stdexcept>
#include <utility>

// Abstract Data Type for a Binary Search Tree.

namespace custom_bst {

    // Exception thrown when an operation attempts to insert a value that already exists.
    class DuplicateNodeException : public std::logic_error {
    public:
        explicit DuplicateNodeException(const std::string& message) : std::logic_error(message) {
        }
    };

    // BST class implementing a Binary Search Tree set.
    class BST {
    public:
        // Constructors and Destructor
        BST();
        ~BST();
        BST(const BST& other);                // Copy Constructor 
        BST& operator=(const BST& other);     // Assignment Operator
        
        // CRUD Operators
 
        // Create (Insert)
        BST& operator+=(int value);
        
        // Read (Search)
        bool operator[](int value) const;
        
        // Update (Edit)
        BST& operator*=(const std::pair<int, int>& old_new_values);

        // Delete (Remove)
        BST& operator-=(int value);

        // Clears all elements from the tree and resets size to 0.
        void operator!();

        // Comparisons
        bool operator==(const BST& other) const;
        bool operator!=(const BST& other) const;
        bool operator<(const BST& other) const;
        bool operator<=(const BST& other) const;
        bool operator>(const BST& other) const;
        bool operator>=(const BST& other) const;

        // Returns a string containing size and a list of elements.
        std::string toString() const;

        // Returns the total count of nodes in the tree.
        int size() const;

    private:
        // Pointer to Implementation class.
        class BSTImpl;
        BSTImpl* pimpl;
    };
} 

#endif 