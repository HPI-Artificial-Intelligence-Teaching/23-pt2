#ifndef __TRIE_H__
#define __TRIE_H__

#include <array>
#include <functional>
#include <map>

#include "st.h"

std::string repeat_string(const std::string &input, int n) {
    std::string result;
    for (int i = 0; i < n; i++) {
        result += input;
    }
    return result;
}

template <std::size_t N>
std::array<char, N> strtoarr(const std::string &s) {
    assert(s.size() == N);
    std::array<char, N> arr;
    for (int i = 0; i < N; i++) {
        arr[i] = (char)s[i];
    }
    return (arr);
}

// Implements the class for a symbol table based on (un-balanced) binary search
// trees
template <typename Key, typename Value, size_t U>
class Trie {
    struct Node {
        Key key;
        Value val;
        int size;
        bool is_word;
        std::array<Node *, U> children;

        std::string print(const int level = 1,
                          const bool print_empty = false) const {
            std::string s = "";
            s += repeat_string(".  ", level - 1) + "|- " + key +
                 (is_word ? "." : "") + "\n";
            for (int i = 0; i < U; i++) {
                if (children[i]) {
                    s += children[i]->print(level + 1, print_empty);
                } else {
                    if (print_empty) {
                        s += repeat_string(".  ", level) + "_" + "\n";
                    }
                }
            }
            return s;
        }

        friend std::ostream &operator<<(std::ostream &os, const Node &n) {
            os << std::endl << n.print() << std::endl;
            return os;
        }

        // constructor with values
        Node(const Key &k, const Value &v, const int s)
            : key(k), val(v), size(s), is_word(false), children() {}
    };
    Node *root;  // root of the search forest
    std::array<Key, U> alphabet;

    friend std::ostream &operator<<(std::ostream &os,
                                    const Trie<Key, Value, U> &kt) {
        if (kt.root) {
            os << std::endl;
            for (auto &kv : kt.root->children) {
                if (kv) {
                    os << kv->print() << std::endl;
                }
            }
        } else {
            os << "Empty Trie" << std::endl;
        }
        return os;
    }

    int c_map(const Key &k) const {
        for (int i = 0; i < U; i++) {
            if (alphabet[i] == k) {
                return i;
            }
        }
        throw std::invalid_argument("Key not in alphabet");
    }

    // copys an existing tree pointed to by n
    const Node *deep_copy_tree(const Node *n) const {
        if (n) {
            auto node = new Node(n->key, n->val, n->size);
            node->depth = n->depth;
            node->is_word = n->is_word;
            node->children = new std::array<Node *, U>();
            for (int i = 0; i < U; i++) {
                node->children[i] = deep_copy_tree(n->children[i]);
            }
            return (node);
        }
        return (nullptr);
    }

    // frees the tree pointed to by n
    void free_tree(const Node *n) const {
        if (n) {
            for (int i = 0; i < U; i++) {
                free_tree(n->children[i]);
            }
            delete n;
        }
        return;
    }

   public:
    // default constructor
    template <std::size_t N>
    Trie(const std::array<Key, N> &a) {
        this->root = nullptr;
        for (int i = 0; i < N; i++) {
            alphabet[i] = a[i];
        }
    }

    // copy constructor
    Trie(const Trie &bst) { root = deep_copy_tree(bst.root); }

    // move constructor
    Trie(Trie &&bst) : root(bst.root) { bst.root = nullptr; }

    // copy assignment
    Trie &operator=(const Trie &bst) {
        // free the existing tree
        free_tree(root);
        // copy the tree
        root = deep_copy_tree(bst.root);
        return (*this);
    }

    // move assignment
    Trie &operator=(Trie &&bst) {
        // free the existing tree
        free_tree(root);

        root = bst.root;
        bst.root = nullptr;
        return (*this);
    }

    // destructor
    ~Trie() { free_tree(root); }

    // put a key-value pair into the table
    template <std::size_t N>
    void add(const std::array<Key, N> &k) {
        if (root == nullptr) {
            root = new Node(k[0], 0, 1);  // a bit hacky but whatever, it at
                                          // least guarantees a valid root
        }
        Node *current = root;
        for (int i = 0; i < N; i++) {
            auto idx = c_map(k[i]);
            if (current->children[idx] == nullptr) {
                current->children[idx] = new Node(k[i], 0, 1);
            }
            current = current->children[idx];
        }
        current->is_word = true;
    }

    template <std::size_t N>
    bool contains(const std::array<Key, N> &k) {
        if (root == nullptr) {
            return false;
        }
        Node *current = root;
        for (size_t i = 0; i < N; i++) {
            try {
                auto idx = c_map(k[i]);
                if (current->children[idx] == nullptr) {
                    return false;
                }
                current = current->children[idx];
            } catch (std::invalid_argument &e) {
                return false;
            }
        }
        return true;
    }

    template <std::size_t N>
    bool observed(const std::array<Key, N> &k) {
        if (root == nullptr) {
            return false;
        }
        Node *current = root;
        for (size_t i = 0; i < N; i++) {
            try {
                auto idx = c_map(k[i]);
                if (current->children[idx] == nullptr) {
                    return false;
                }
                current = current->children[idx];
            } catch (std::invalid_argument &e) {
                return false;
            }
        }
        return current->is_word;
    }
};

#endif
