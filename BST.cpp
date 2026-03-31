#include "BST.h"
#include <sstream>
#include <vector>

namespace custom_bst {

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
            if (!node) return nullptr;
            Node* newNode = new Node(node->data);
            newNode->left = copyTree(node->left);
            newNode->right = copyTree(node->right);
            return newNode;
        }

        Node* insert(Node* node, int value) {
            if (!node) {
                node_count++;
                return new Node(value);
            }
            if (value < node->data) {
                node->left = insert(node->left, value);
            }
            else if (value > node->data) {
                node->right = insert(node->right, value);
            }
            else {
                throw DuplicateNodeException("Value " + std::to_string(value) + " already exists in BST.");
            }
            return node;
        }

        Node* findMin(Node* node) const {
            while (node && node->left) node = node->left;
            return node;
        }

        Node* remove(Node* node, int value) {
            if (!node) throw std::invalid_argument("Value not found for deletion.");

            if (value < node->data) {
                node->left = remove(node->left, value);
            }
            else if (value > node->data) {
                node->right = remove(node->right, value);
            }
            else {
                if (!node->left) {
                    Node* temp = node->right;
                    delete node;
                    node_count--;
                    return temp;
                }
                else if (!node->right) {
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

        void inOrder(Node* node, std::vector<int>& elements) const {
            if (node) {
                inOrder(node->left, elements);
                elements.push_back(node->data);
                inOrder(node->right, elements);
            }
        }

    public:
        BSTImpl() : root(nullptr), node_count(0) {
        }
        
        ~BSTImpl() {
            destroyTree(root);
        }
        
        BSTImpl(const BSTImpl& other) : root(nullptr), node_count(other.node_count) {
            root = copyTree(other.root);
        }

        void add(int value) {
            root = insert(root, value);
        }
        
        void removeVal(int value) {
            root = remove(root, value);
        }

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

        int size() const {
            return node_count;
        }

        std::vector<int> getElements() const {
            std::vector<int> elements;
            inOrder(root, elements);
            return elements;
        }
    };

    BST::BST() : pimpl(new BSTImpl()) {
    }

    BST::~BST() {
        delete pimpl;
    }

    BST::BST(const BST& other) : pimpl(new BSTImpl(*other.pimpl)) {
    }

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
            throw std::invalid_argument("Old value not found for update.");
        }
        if (pimpl->search(old_new.second) && old_new.first != old_new.second) {
            throw DuplicateNodeException("New value already exists in BST.");
        }
        pimpl->removeVal(old_new.first);
        pimpl->add(old_new.second);
        return *this;
    }

    bool BST::operator[](int value) const {
        return pimpl->search(value);
    }

    void BST::operator!() {
        pimpl->clear();
    }

    std::string BST::toString() const {
        std::vector<int> elems = pimpl->getElements();
        std::ostringstream oss;
        oss << "BST [Size: " << elems.size() << "] Elements: { ";
        for (size_t i = 0; i < elems.size(); ++i) {
            oss << elems[i] << (i < elems.size() - 1 ? ", " : "");
        }
        oss << " }";
        return oss.str();
    }

    int BST::size() const {
        return pimpl->size();
    }

    bool BST::operator==(const BST& other) const {
        return pimpl->getElements() == other.pimpl->getElements();
    }

    bool BST::operator!=(const BST& other) const {
        return !(*this == other);
    }
    
    bool BST::operator<(const BST& other) const {
        return pimpl->getElements() < other.pimpl->getElements();
    }
    bool BST::operator<=(const BST& other) const {
        return (*this < other) || (*this == other);
    }
    bool BST::operator>(const BST& other) const {
        return !(*this <= other);
    }
    bool BST::operator>=(const BST& other) const {
        return !(*this < other);
    }

}