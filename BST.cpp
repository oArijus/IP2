#include "BST.h"
#include <sstream>

namespace CustomBST {

    DuplicateNodeException::DuplicateNodeException(const std::string& message) : std::logic_error(message){
    }

    class BST::BSTImpl {
    private:
        struct Node {
            int data;
            Node* left;
            Node* right;
            Node(int val) : data(val), left(nullptr), right(nullptr) {}
        };
        
        Node* root;
        int node_count;

        void destroyTree(Node* node) {
            if (node) {
                destroyTree(node->left);
                destroyTree(node->right);
                delete node;
            }
        }

        Node* copyTree(const Node* node) {
            if (!node) {
                return nullptr;
            }
            Node* newNode = new Node(node->data);
            newNode->left = copyTree(node->left);
            newNode->right = copyTree(node->right);
            return newNode;
        }

        Node* insert(Node* node, int value) {
            if (!node) {
                return new Node(value);
            }
            if (value < node->data) {
                node->left = insert(node->left, value);
            } else if (value > node->data) {
                node->right = insert(node->right, value);
            } else {
                throw DuplicateNodeException("Value " + std::to_string(value) + " exists.");
            }
            return node;
        }

        Node* findMin(Node* node) const {
            if (node == nullptr) {
                return nullptr;
            }
            while (node->left) {
                node = node->left;
            }
            return node;
        }

        Node* remove(Node* node, int value) {
            if (!node) {
                throw std::invalid_argument("Value not found.");
            }

            if (value < node->data) {
                node->left = remove(node->left, value);
            } else if (value > node->data) {
                node->right = remove(node->right, value);
            } else {
                if (!node->left) {
                    Node* temp = node->right;
                    delete node;
                    node_count--;
                    return temp;
                } else if (!node->right) {
                    Node* temp = node->left;
                    delete node;
                    node_count--;
                    return temp;
                }
                Node* temp = findMin(node->right);
                node->data = temp->data;
                node->right = remove(node->right, temp->data);
            }
            return node;
        }

        void fillArray(Node* node, int* arr, int& index) const {
            if (node) {
                fillArray(node->left, arr, index);
                arr[index++] = node->data;
                fillArray(node->right, arr, index);
            }
        }

    public:
        BSTImpl() : root(nullptr), node_count(0) {}
        ~BSTImpl() { destroyTree(root); }
        BSTImpl(const BSTImpl& other) : root(nullptr), node_count(other.node_count) {
            root = copyTree(other.root);
        }

        void add(int value) { root = insert(root, value); }
        void removeVal(int value) { root = remove(root, value); }

        bool search(int value) const {
            Node* current = root;
            while (current) {
                if (value == current->data) return true;
                if (value < current->data) current = current->left;
                else current = current->right;
            }
            return false;
        }

        void clear() {
            destroyTree(root);
            root = nullptr;
            node_count = 0;
        }

        int size() const { return node_count; }

        int compare(const BSTImpl& other) const {
            if (node_count != other.node_count) {
                return (node_count < other.node_count) ? -1 : 1;
            }
            if (node_count == 0) return 0;

            int* thisArr = new int[node_count];
            int* otherArr = new int[other.node_count];
            int i1 = 0, i2 = 0;

            fillArray(root, thisArr, i1);
            fillArray(other.root, otherArr, i2);

            int result = 0;
            for (int i = 0; i < node_count; ++i) {
                if (thisArr[i] < otherArr[i]) {
                    result = -1;
                    break;
                }
                if (thisArr[i] > otherArr[i]) {
                    result = 1;
                    break;
                }
            }

            delete[] thisArr;
            delete[] otherArr;
            return result;
        }

        std::string elementsToString() const {
            if (node_count == 0) return "";
            int* arr = new int[node_count];
            int idx = 0;
            fillArray(root, arr, idx);
            std::ostringstream oss;
            for (int i = 0; i < node_count; ++i) {
                oss << arr[i] << (i < node_count - 1 ? ", " : "");
            }
            delete[] arr;
            return oss.str();
        }
    };

    BST::BST() : pimpl(new BSTImpl()) {}
    BST::~BST() { delete pimpl; }
    BST::BST(const BST& other) : pimpl(new BSTImpl(*other.pimpl)) {}

    BST& BST::operator=(const BST& other) {
        if (this != &other) {
            delete pimpl;
            pimpl = new BSTImpl(*other.pimpl);
        }
        return *this;
    }

    BST& BST::operator+=(int value) {
        pimpl->add(value);
        return *this;
    }

    BST& BST::operator-=(int value) {
        pimpl->removeVal(value);
        return *this;
    }

    BST& BST::operator*=(const std::pair<int, int>& old_new) {
        if (!pimpl->search(old_new.first)) {
            throw std::invalid_argument("Old value not found.");
        }
        if (pimpl->search(old_new.second) && old_new.first != old_new.second) {
            throw DuplicateNodeException("New value already exists.");
        }
        pimpl->removeVal(old_new.first);
        pimpl->add(old_new.second);
        return *this;
    }

    bool BST::operator[](int value) const { return pimpl->search(value); }
    void BST::operator!() { pimpl->clear(); }
    int BST::size() const { return pimpl->size(); }

    std::string BST::toString() const {
        return "BST [Size: " + std::to_string(pimpl->size()) + "] Elements: { " + pimpl->elementsToString() + " }";
    }

    bool BST::operator==(const BST& other) const { return pimpl->compare(*other.pimpl) == 0; }
    bool BST::operator!=(const BST& other) const { return pimpl->compare(*other.pimpl) != 0; }
    bool BST::operator<(const BST& other) const { return pimpl->compare(*other.pimpl) < 0; }
    bool BST::operator<=(const BST& other) const { return pimpl->compare(*other.pimpl) <= 0; }
    bool BST::operator>(const BST& other) const { return pimpl->compare(*other.pimpl) > 0; }
    bool BST::operator>=(const BST& other) const { return pimpl->compare(*other.pimpl) >= 0; }
}