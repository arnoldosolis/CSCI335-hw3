#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include "sequence_map.h"
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
//--------------------Functions Added------------------------
// void printValue( )     --> Prints value of node
// void countNodes( )     --> Counts the nodes in a tree
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
public:
    AvlTree() : root{nullptr}
    {
    }

    AvlTree(const AvlTree &rhs) : root{nullptr}
    {
        root = clone(rhs.root);
    }

    AvlTree(AvlTree &&rhs) : root{rhs.root}
    {
        rhs.root = nullptr;
    }

    ~AvlTree()
    {
        makeEmpty();
    }

    /**
     * Deep copy.
     */
    AvlTree &operator=(const AvlTree &rhs)
    {
        AvlTree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    /**
     * Move.
     */
    AvlTree &operator=(AvlTree &&rhs)
    {
        std::swap(root, rhs.root);
        return *this;
    }

    /*
        getter function for removed_node
    */
    int getRemovedNodeCalls()
    {
        // returns removed nodes
        return removed_node;
    }

    /*
        getter function for total_recursive_calls
    */
    int getTotalRecursiveCalls()
    {
        // returns total recursive calls
        return total_recursive_calls;
    }

    /*
        Returns the number of strings found in tree from sequences.txt
    */
    void stringsFound(AvlTree &a_tree)
    {
        // stores all strings from seqeunces 
        std::string seq_lines;
        // counter for strings found
        float numOfStringsFound = 0;
        // counter for calls
        float containCalls = 0;
        // Initializes ifstream object to open file
        std::ifstream seqtxt("sequences.txt");
        // reads in file
        while (getline(seqtxt, seq_lines))
        {
            // creates sequence map object
            SequenceMap seq(seq_lines, "");
            // if the strin contains sequence
            if (a_tree.contains(seq, containCalls))
            {
                // increase counter 
                numOfStringsFound++;
            }
        }
        // calculates the average number of recursion calls
        float avg = containCalls / numOfStringsFound;
        // prints the number of strings found
        std::cout << "4a: " << numOfStringsFound << std::endl;
        // prints the average number of recursion calls
        std::cout << "4b: " << avg << std::endl;
    }

    /*
        Prints the value of the current node
    */
    void printValue(const Comparable &x) const
    {
        // recursive function
        printValue(x, root);
    }

    /*
        Counts the nodes in the tree
    */
    int countNodes() const
    {
        return countNodes(root);
    }

    /*
        Calculates depth of tree
    */
    float depthOfTree()
    {
        float depth = 0;
        return depthOfTree(root, depth);
    }

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable &findMin() const
    {
        if (isEmpty())
            throw UnderflowException{};
        return findMin(root)->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable &findMax() const
    {
        if (isEmpty())
            throw UnderflowException{};
        return findMax(root)->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains(const Comparable &x, float &containCalls) const
    {
        containCalls++;
        return contains(x, root, containCalls);
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree() const
    {
        if (isEmpty())
            cout << "Empty tree" << endl;
        else
            printTree(root);
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty()
    {
        makeEmpty(root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const Comparable &x)
    {
        insert(x, root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(Comparable &&x)
    {
        insert(std::move(x), root);
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(const Comparable &x)
    {
        remove(x, root);
    }
private:
    struct AvlNode
    {
        Comparable element;
        AvlNode *left;
        AvlNode *right;
        int height;

        AvlNode(const Comparable &ele, AvlNode *lt, AvlNode *rt, int h = 0)
            : element{ele}, left{lt}, right{rt}, height{h} {}

        AvlNode(Comparable &&ele, AvlNode *lt, AvlNode *rt, int h = 0)
            : element{std::move(ele)}, left{lt}, right{rt}, height{h} {}
    };

    AvlNode *root;
    // Internal counter
    int removed_node = 0;
    // Internal counter
    int total_recursive_calls = 0;
    
    /*
        Note: This code was taken from the book, specifically from contains()
        Internal method that computes depth of tree.
    */
    float depthOfTree(AvlNode *node, float depth) const
    {
        // if node doesnt exist
        if (node == nullptr)
        {
            // return 0
            return 0;
        }
        else
        {
            // recursively counts
            return depth + depthOfTree(node->left, depth + 1) + depthOfTree(node->right, depth + 1);
        }
    }

    /*
        Note: This code was taken from the book, specifically from contains()
        Internal method that counts nodes in the tree
    */
    int countNodes(AvlNode *node) const
    {
        // If the node doesnt exist
        if (node == nullptr)
        {
            // return 0
            return 0;
        }
        // else if the node on both sides do not exist return 1
        else if (node->left == nullptr && node->right == nullptr)
        {
            return 1;
        }
        else
        {
            // recursively counts
            return (countNodes(node->left) + countNodes(node->right) + 1);
        }
    }

    /*
        Note: This code was taken from the book, specifically from contains()
        Internal method for printValue() that gets the value of the current node
    */
    void printValue(const Comparable &x, AvlNode *node) const
    {
        // If the node doesnt exist
        if (node == nullptr)
        {
            // print not found
            std::cout << "Not Found";
        }
        // if node exists
        else if (node->element < x)
        {
            // recursively calls printValue()
            printValue(x, node->right);
        }
        // if node exists
        else if (x < node->element)
        {
            // recursively calls printValue()
            printValue(x, node->left);
        }
        else
        {
            // prints out element at node
            std::cout << node->element;
        }
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(const Comparable &x, AvlNode *&t)
    {
        if (t == nullptr)
            t = new AvlNode{x, nullptr, nullptr};
        else if (x < t->element)
            insert(x, t->left);
        else if (t->element < x)
            insert(x, t->right);
        else
            t->element.Merge(x); // for duplicates

        balance(t);
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(Comparable &&x, AvlNode *&t)
    {
        if (t == nullptr)
            t = new AvlNode{std::move(x), nullptr, nullptr};
        else if (x < t->element)
            insert(std::move(x), t->left);
        else if (t->element < x)
            insert(std::move(x), t->right);
        else
            t->element.Merge(x); // for duplicates

        balance(t);
    }
    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove(const Comparable &x, AvlNode *&t)
    {
        // counter for recursive calls
        total_recursive_calls++;
        if (t == nullptr)
        {
            return; // Item not found; do nothing
        }
        if (x < t->element)
        {
            remove(x, t->left);
        }
        else if (t->element < x)
        {
            remove(x, t->right);
        }
        else if (t->left != nullptr && t->right != nullptr) // Two children
        {
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else
        {
            AvlNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
            // Counter for nodes removed
            removed_node++;
        }
        
        balance(t);
    }

    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
    void balance(AvlNode *&t)
    {
        if (t == nullptr)
            return;

        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
        {
            if (height(t->left->left) >= height(t->left->right))
                rotateWithLeftChild(t);
            else
                doubleWithLeftChild(t);
        }
        else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
        {
            if (height(t->right->right) >= height(t->right->left))
                rotateWithRightChild(t);
            else
                doubleWithRightChild(t);
        }
        t->height = max(height(t->left), height(t->right)) + 1;
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode *findMin(AvlNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        if (t->left == nullptr)
            return t;
        return findMin(t->left);
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AvlNode *findMax(AvlNode *t) const
    {
        if (t != nullptr)
            while (t->right != nullptr)
                t = t->right;
        return t;
    }

    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains(const Comparable &x, AvlNode *t, float &containCalls) const
    {
        if (t == nullptr)
        {
            return false;   
        }   
        else if (x < t->element)
        {
            containCalls++;
            return contains(x, t->left, containCalls);
        }
        else if (t->element < x)
        {
            containCalls++;
            return contains(x, t->right, containCalls);
        }
        else
        {
            return true; // Match
        }
    }
    /****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, AvlNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty(AvlNode *&t)
    {
        if (t != nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree(AvlNode *t) const
    {
        if (t != nullptr)
        {
            printTree(t->left);
            cout << t->element << endl;
            printTree(t->right);
        }
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode *clone(AvlNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        else
            return new AvlNode{t->element, clone(t->left), clone(t->right), t->height};
    }

    // Avl manipulations
    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height(AvlNode *t) const
    {
        return t == nullptr ? -1 : t->height;
    }

    int max(int lhs, int rhs) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild(AvlNode *&k2)
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild(AvlNode *&k1)
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->right), k1->height) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild(AvlNode *&k3)
    {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild(AvlNode *&k1)
    {
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }
};

#endif
