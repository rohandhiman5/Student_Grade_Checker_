#ifndef BTREE_HPP
#define BTREE_HPP

#include <iostream>
#include <vector>

// B-Tree Node Template
template <typename K, typename V>
class BTreeNode {
public:
    std::vector<K> keys;
    std::vector<V> values;
    std::vector<BTreeNode*> C;
    int t; // Minimum degree
    bool leaf;

    BTreeNode(int _t, bool _leaf) {
        t = _t;
        leaf = _leaf;
    }

    void insertNonFull(K k, V v) {
        int i = keys.size() - 1;
        if (leaf) {
            keys.push_back(k); // Make space
            values.push_back(v);
            while (i >= 0 && keys[i] > k) {
                keys[i + 1] = keys[i];
                values[i + 1] = values[i];
                i--;
            }
            keys[i + 1] = k;
            values[i + 1] = v;
        } else {
            while (i >= 0 && keys[i] > k)
                i--;
            if (C[i + 1]->keys.size() == 2 * t - 1) {
                splitChild(i + 1, C[i + 1]);
                if (keys[i + 1] < k)
                    i++;
            }
            C[i + 1]->insertNonFull(k, v);
        }
    }

    void splitChild(int i, BTreeNode* y) {
        BTreeNode* z = new BTreeNode(y->t, y->leaf);
        for (int j = 0; j < t - 1; j++) {
            z->keys.push_back(y->keys[j + t]);
            z->values.push_back(y->values[j + t]);
        }
        if (!y->leaf) {
            for (int j = 0; j < t; j++) {
                z->C.push_back(y->C[j + t]);
            }
            y->C.resize(t);
        }
        
        K upKey = y->keys[t - 1];
        V upVal = y->values[t - 1];
        y->keys.resize(t - 1);
        y->values.resize(t - 1);

        C.insert(C.begin() + i + 1, z);
        keys.insert(keys.begin() + i, upKey);
        values.insert(values.begin() + i, upVal);
    }

    void traverse(std::vector<V>& result) {
        int i;
        for (i = 0; i < keys.size(); i++) {
            if (!leaf)
                C[i]->traverse(result);
            result.push_back(values[i]);
        }
        if (!leaf)
            C[i]->traverse(result);
    }

    BTreeNode* search(K k, int& index) {
        int i = 0;
        while (i < keys.size() && k > keys[i])
            i++;
        if (i < keys.size() && keys[i] == k) {
            index = i;
            return this;
        }
        if (leaf)
            return nullptr;
        return C[i]->search(k, index);
    }
};

// B-Tree Class Template
template <typename K, typename V>
class BTree {
public:
    BTreeNode<K, V>* root;
    int t;

    BTree(int _t = 3) {
        root = nullptr;
        t = _t;
    }

    void traverse(std::vector<V>& result) {
        if (root != nullptr)
            root->traverse(result);
    }

    V* search(K k) {
        if (root == nullptr)
            return nullptr;
        int index;
        BTreeNode<K, V>* res = root->search(k, index);
        if (res != nullptr)
            return &res->values[index];
        return nullptr;
    }

    void insert(K k, V v) {
        if (root == nullptr) {
            root = new BTreeNode<K, V>(t, true);
            root->keys.push_back(k);
            root->values.push_back(v);
        } else {
            if (root->keys.size() == 2 * t - 1) {
                BTreeNode<K, V>* s = new BTreeNode<K, V>(t, false);
                s->C.push_back(root);
                s->splitChild(0, root);
                int i = 0;
                if (s->keys[0] < k)
                    i++;
                s->C[i]->insertNonFull(k, v);
                root = s;
            } else {
                root->insertNonFull(k, v);
            }
        }
    }
    
    // Clear tree to support rebuilding (e.g., for deletion)
    void clear() {
        // Simple clear for in-memory, memory management could be improved
        // but sufficient for a lightweight B-Tree wrapper.
        root = nullptr;
    }
};

#endif
