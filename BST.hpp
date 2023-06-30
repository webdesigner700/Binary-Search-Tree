#pragma once
#ifndef BST_ASSIGNMENT_HPP
#define BST_ASSIGNMENT_HPP

#include <iostream>
#include <algorithm>

template <typename T>
class BST
{
public:
    // We have a Node class with more features now
    // In addition to pointers to the left and right child,
    // there is also a pointer to the parent of Node.  
    // The parent of the root should always be nullptr
    // We also hava a height field to store the height of 
    // a node in the tree.
    class Node
    {
    public:
        T key;
        int height = 0;
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;
        // default constructor
        Node() {}
        // constructor that takes one or optionally 2 arguments
        // if only one argument is passed in the second argument 
        // defaults to nullptr
        Node(T k, Node* input_node = nullptr)
        {
            key = k;
            parent = input_node;
        }
    };

private:
    // The BST has two private variables, a pointer to the root
    // and an unsigned integer to hold its size
    // We make the style choice of indicating these are private 
    // data variables by having a trailing underscore in their names.
    Node* root_ = nullptr;
    unsigned int size_ = 0;


public:
    // Default constructor.  No action required on this one.
    BST();

    // Destructor.  We implement this for you.
    ~BST();

    //*** Methods for you to implement
    // insert
    // insert the key k into the BST while maintaining the BST property
    // Like std::set, if k is already in the tree then no action is taken
    // Update the size_ variable and heights of nodes accordingly
    //*** For you to implement
    void insert(T k);

    // successor
    // Return a pointer to the node containing the smallest key larger 
    // than k
    // Return nullptr if k is the largest key in the tree
    // Also return nullptr if k is not in the tree
    //*** For you to implement
    Node* successor(T k);

    // delete the minimum
    // Erase the minimum key in the tree
    // Take no action if tree is empty
    //*** For you to implement
    void delete_min();

    // erase
    // Locate the key k in the tree and remove it
    // If k is not in the tree you do not have to do anything
    // Update the size_ variable and heights of nodes accordingly
    //*** For you to implement
    void erase(T k);

    // Implement a right rotation about the node pointed to by 
    // node, as described in Lecture 8.6.  This will only be 
    // called when node has a left child.  
    // If left_child points to the left child of *node, 
    // then *left_child becomes the parent of *node, and the 
    // right subtree of *left_child becomes the left subtree of *node.  
    // Node heights should be properly updated after this operation.
    //*** For you to implement
    void rotate_right(Node* node);

    //*** End of methods for you to implement

    // Returns the number of keys in the tree
    // we implement this for you, but it is up to you to correctly
    // update the size_ variable
    unsigned size();

    // Prints out the keys in the tree via an in-order traversal
    // we implement this for you
    void print();

    void fix_height(Node* node);

    // Returns a pointer to the node containing the key k
    // We implement this for you
    Node* find(T k);

    // Creates a vector holding the keys in the tree by
    // doing an in-order traversal
    // We implement this for you, it is used in our testing.
    std::vector<T> make_vec();

    // The next two functions are to check your height values 
    // Please do not modify
    std::vector<int> your_postorder_heights();

    std::vector<int> real_postorder_heights();

    // get_root_value returns the value stored at the root
    // It used for testing purposes
    // No action needed on your part
    T get_root_value();

    // Return a pointer to the node containing the minimum key in the tree
    // We implement this for you
    Node* min();

    Node* max();

private:
    // We found it useful to have a "fix_height" function.
    // This assumes that the subtrees rooted at node's children have 
    // correct heights and then walks up the tree from node to the root 
    // correcting the heights.
    // You can imlement this, or correct the heights another way
    //void fix_height(Node* node);

    // The rest of these functions are already implemented

    // helper function for the destructor
    void delete_subtree(Node* node);

    // returns pointer to minimum node in subtree rooted by node
    // Assumes node is not nullptr
    Node* min(Node* node);

    // helper function for print
    void print(Node* node);

    // helper function for make_vec
    void make_vec(Node* node, std::vector<T>& vec);

    void your_postorder_heights(Node* node, std::vector<int>& vec);

    int real_postorder_heights(Node* node, std::vector<int>& vec);

};

// Default constructor
// You do not need to change this
template <typename T>
BST<T>::BST()
{
}

// Destructor
// We implement this for you
template <typename T>
BST<T>::~BST()
{
    delete_subtree(root_);
}

// helper function for destructor
template <typename T>
void BST<T>::delete_subtree(Node* node)
{
    if (node == nullptr)
    {
        return;
    }
    delete_subtree(node->left);
    delete_subtree(node->right);
    delete node;
}

//*** For you to implement
template <typename T>
void BST<T>::insert(T k)
{
    // You can mostly follow your solution from Week 9 lab here
    // Add functionality to set the parent pointer of the new node created
    // ++size_;
    // Also remember to correct the heights on the path from the newly
    // inserted node to the root.
    // fix_height(start_fix);

    // node will iterate down through the tree starting from the root
    Node* node = root_;
    // prev_node will hold node's parent
    Node* prev_node = node;
    bool went_right;

    if (node == nullptr)
    {
        root_ = new Node(k);
        ++size_;
        return;
    }

    while (node != nullptr)
    {
        prev_node = node;

        if (k < node->key)
        {
            node = node->left;
            went_right = false;
        }
        else if (k > node->key)
        {
            node = node->right;
            went_right = true;
        }
        // item already in set
        else
        {
            return;
        }
    }
    // new node is either left or right child of prev_node

    if (went_right)
    {
        prev_node->right = new Node(k, prev_node);
        fix_height(prev_node->right);
        ++size_;
    }
    else
    {
        prev_node->left = new Node(k, prev_node);
        fix_height(prev_node->left);
        ++size_;
    }

    //now the height has to be changed 

}

//*** For you to implement
template <typename T>
typename BST<T>::Node* BST<T>::successor(T k)
{
    // successor
    // Return a pointer to the node containing the smallest key larger 
    // than k
    // Return nullptr if k is the largest key in the tree
    // Also return nullptr if k is not in the tree

    // There are two cases here.  
    // If the node containing k has a right child, then 
    // the successor will be the minimum node in its right subtree
    // Otherwise, the successor will be the first node with a key 
    // bigger than k on the path from the node with key k to the root.
    // In other words, it is the node where we last took a left turn when 
    // searching for the key k.

    // dummy return value so compiler does not complain


    Node* node = find(k);
    Node* successor;

    //return nullptr if k is the largest key in the tree

    if (node == nullptr) { // this is the case where k is not in the tree
        return nullptr;
    }
    else if (node == max()) { // this is the case when k is the larghest key in the BST 
        return nullptr;
    }
    else if (node->right != nullptr) { // if the right node is there, check the right subtree

        node = node->right;

        while (node->left != nullptr) {
            node = node->left;
        }
    }
    else { // this is the case when there is no right child

        Node* temp = node;

        while (temp->parent != nullptr) {

            temp = temp->parent;

            if (temp->key > node->key) {
                node = temp;
                break;
            }
        }
    }

    return node;
}

//*** For you to implement
template <typename T>
void BST<T>::delete_min()
{

    // delete the minimum
    // Erase the minimum key in the tree
    // Take no action if tree is empty
    //*** For you to implement

    // if tree is empty just return.
    //Node* min_node = min();
    // Now update pointers to remove min_node from the tree

    //delete min_node;
    //--size_;
    //fix_height(start_fix);

    if (root_ == nullptr) { // if the root does not exsist
        return;
    }
    else if (size_ == 1) { // the case when only the root exists
        root_ = nullptr;
        --size_;
        return;
    }
    else { // the case when the size of the BST is more than 1
        Node* min_node = min();

        if (min_node == root_) { // the case when there is no left subtree
            root_ = min_node->right;
            root_->parent = nullptr;
            --size_;
            fix_height(root_);
        }
        else { // the case when there is a left subtree

            Node* min_parent = min_node->parent;

            if (min_node->right != nullptr) { // the case when the min_node parent has a right subchild

                min_parent->left = min_node->right;
                min_node->right->parent = min_parent;
                --size_;
                fix_height(min_parent->left);
            }
            else { // the case when the min node does not have a child
                min_node->parent = nullptr;
                min_parent->left = nullptr;
                --size_;
                fix_height(min_parent);
            }
        }
    }
}

//*** For you to implement
template <typename T>
void BST<T>::erase(T k)
{

    // erase
    // Locate the key k in the tree and remove it
    // If k is not in the tree you do not have to do anything
    // Update the size_ variable and heights of nodes accordingly
    //*** For you to implement


    // Step 1: locate node holding key k
    // simply return if k is not in tree
    // let node_to_remove be a pointer to the node to be removed


    Node* node_to_remove = find(k);

    if (node_to_remove == nullptr) {
        return;
    }

    Node* node_parent;

    Node* node_child;

    Node* node_successor;

    Node* successor_parent;

    Node* successor_child;

    Node* left_child;

    Node* right_child;

    if (node_to_remove != root_) {
        node_parent = node_to_remove->parent;
    }
    else {
        node_parent = nullptr;
    }


    //Case 1 : node_to_remove has no children

    if (node_to_remove->left == nullptr && node_to_remove->right == nullptr) {

        if (node_to_remove != root_) { //node_to_remove is not the root

            if (node_parent->left == node_to_remove) {
                node_to_remove->parent = nullptr;
                node_parent->left = nullptr;
                --size_;
                fix_height(node_parent);
            }
            else if (node_parent->right == node_to_remove) { //node_parent right child is node_to_remove
                node_to_remove->parent = nullptr;
                node_parent->right = nullptr;
                --size_;
                fix_height(node_parent);
            }
        }
        else {
            root_ = nullptr;
            --size_;
            // when the root gets deleted the height does not need to be fixed
        }
    }
    else if (node_to_remove->left != nullptr && node_to_remove->right != nullptr) {

        // the case when the node_to_remove has both children

        left_child = node_to_remove->left;
        right_child = node_to_remove->right;

        node_successor = successor(node_to_remove->key);

        // add the case when node to remove is thr root node 

        successor_parent = node_successor->parent;

        if (node_successor->right != nullptr) {

            successor_child = node_successor->right;
        }
        else {
            successor_child = nullptr;
        }

        // this is the subcase where successor is not teh right child of node_to_remove

        if (node_successor != node_to_remove->right) {

            // this is the first case where successor has a right child
            // make parent of successor point to right child of successor
            if (node_successor->right != nullptr) {

                node_successor->parent = nullptr;
                successor_parent->left = nullptr;
                node_successor->right = nullptr;
                successor_child->parent = nullptr;

                successor_parent->left = successor_child;
                successor_child->parent = successor_parent;

                fix_height(successor_child);
            }
            else { // this is the case where node successor does not have a right child

                node_successor->parent = nullptr;
                successor_parent->left = nullptr;

                fix_height(successor_parent);
            }

            //make parent of node_to_remove point to successor 
            if (node_to_remove != root_) { // the case when node_to_remove is not the root

                if (node_parent->left == node_to_remove) {

                    node_parent->left = nullptr;
                    node_to_remove->parent = nullptr;
                    node_to_remove->left = nullptr;
                    left_child->parent = nullptr;
                    node_to_remove->right = nullptr;
                    right_child->parent = nullptr;

                    node_parent->left = node_successor;
                    node_successor->parent = node_parent;

                }
                else if (node_parent->right == node_to_remove) {

                    node_parent->right = nullptr;
                    node_to_remove->parent = nullptr;
                    node_to_remove->left = nullptr;
                    left_child->parent = nullptr;
                    node_to_remove->right = nullptr;
                    right_child->parent = nullptr;

                    node_parent->right = node_successor;
                    node_successor->parent = node_parent;

                }

                //update children of successor with children of node_to_remove

                node_successor->left = left_child;
                left_child->parent = node_to_remove;
                node_successor->right = right_child;
                right_child->parent = node_to_remove;

                fix_height(node_successor);
                --size_;
            }
            else {
                // this is the case where node_to_remove is the root

                node_to_remove->left = nullptr;
                left_child->parent = nullptr;
                node_to_remove->right = nullptr;
                right_child->parent = nullptr;

                node_successor->left = left_child;
                left_child->parent = node_successor;

                node_successor->right = right_child;
                right_child->parent = node_successor;

                node_successor->parent = nullptr;

                root_ = node_successor;
                fix_height(node_successor);
                --size_;
            }

        }

        // this is the subcase where the successor is the right child 

        else if (node_successor == node_to_remove->right) { // this is for the special case when the successor is the right child 

            if (node_to_remove != root_) {

                //make parent of node_to_remove point to successor 
                if (node_parent->left == node_to_remove) {

                    node_to_remove->left = nullptr;
                    node_to_remove->right = nullptr;
                    node_to_remove->parent = nullptr;

                    node_parent->left = right_child;
                    right_child->parent = node_parent;

                    right_child->left = left_child;
                    left_child->parent = right_child;

                }
                else if (node_parent->right == node_to_remove) {

                    node_to_remove->left = nullptr;
                    node_to_remove->right = nullptr;
                    node_to_remove->parent = nullptr;

                    node_parent->right = right_child;
                    right_child->parent = node_parent;

                    right_child->left = left_child;
                    left_child->parent = right_child;
                }

                fix_height(right_child);
                --size_;

            }
            else {

                //make successor the root here as it shoudl replace node_to_remove
                //let right child be where it is

                right_child->parent = nullptr;
                left_child->parent = nullptr;
                right_child->left = left_child;
                left_child->parent = right_child;
                node_to_remove->left = nullptr;
                node_to_remove->right = nullptr;
                root_ = right_child;
                fix_height(right_child);
                --size_;

            }

        }
    }
    else {
        // The case when the node_to_remove has a single child

        if (node_to_remove != root_) {

            // the child takes the place of the node to delete 

            if (node_to_remove->left != nullptr) {
                node_child = node_to_remove->left;
                node_to_remove->left = nullptr;
                if (node_parent->left == node_to_remove) {
                    node_parent->left = node_child;
                }
                else if (node_parent->right == node_to_remove) {
                    node_parent->right = node_child;
                }
                node_child->parent = node_parent;
                node_to_remove->parent = nullptr;
                --size_;
                fix_height(node_child);
            }
            else if (node_to_remove->right != nullptr) {
                node_child = node_to_remove->right;
                node_to_remove->right = nullptr;
                if (node_parent->left == node_to_remove) {
                    node_parent->left = node_child;
                }
                else if (node_parent->right == node_to_remove) {
                    node_parent->right = node_child;
                }
                node_child->parent = node_parent;
                node_to_remove->parent = nullptr;
                --size_;
                fix_height(node_child);
            }
        }
        else { // the case when the node_to_remove is the root and it has one child 
            if (node_to_remove->left != nullptr) {
                node_child = node_to_remove->left;
                node_to_remove->left = nullptr;
                node_child->parent = nullptr;
                root_ = node_child;
                --size_;
                fix_height(root_);
            }
            else if (node_to_remove->right != nullptr) {
                node_child = node_to_remove->right;
                node_to_remove->right = nullptr;
                node_child->parent = nullptr;
                root_ = node_child;
                --size_;
                fix_height(root_);
            }
        }
    }






    // Step 2: find a node, replacement, to replace node_to_remove
    // We break this down into 3 cases
    // Case 1: node_to_remove has no right child 
    // Case 2: node_to_remove has no left child 
    // Case 3: node_to_remove has both children


    //for case 3, find successor s of key to remove


    // Case 4: node_to_remove has no children - got code for this
    // in this case replacement is successor of node_to_remove
    // There is a further instance of Case 3 that needs special handling.
    // This is where replacement is the right child of node_to_remove.

    // Once pointers have been correctly adjusted then don't forget to:
    // delete node_to_remove;
    // --size_;
    // fix the heights from the bottom-most node affected by the changes
    //fix_height(start_fix);


}

//*** For you to implement
template <typename T>
void BST<T>::rotate_right(Node* node)
{
    // Assumptions: node is not nullptr and must have a left child

    // There are 3 pairs (parent and child) of pointers to change
    // 1) node's left child becomes move_up_node's right child
    // 2) node's original parent becomes move_up_node's parent
    // 3) move_up_node's right child becomes node

    // Correct height of ancestors of node 
    // fix_height(node);

    Node* move_up_node = node->left; // move_up_node is the left child of node

    Node* move_up_right; //move_up-rught is possibly the right child of move_up_node

    Node* move_up_left;

    Node* node_parent; //node_parent is the parent of node

    if (move_up_node->right != nullptr) {
        move_up_right = move_up_node->right;
    }
    else {
        move_up_right = nullptr;
    }

    if (node->parent != nullptr) {
        node_parent = node->parent;
    }
    else {
        node_parent = nullptr;
    }



    if (node != root_) { // case when node is not the root //1



        if (node_parent->left == node) {

            //something is wrong hre i think

            node_parent->left = move_up_node;
            move_up_node->parent = node_parent;
            move_up_node->right = node;
            node->parent = move_up_node;
            if (move_up_right != nullptr) {
                node->left = move_up_right;
                move_up_right->parent = node;
                fix_height(move_up_right);
            }
            else {
                node->left = nullptr;
                fix_height(node);
            }
        }
        else {

            node_parent->right = move_up_node;
            move_up_node->parent = node_parent;
            move_up_node->right = node;
            node->parent = move_up_node;
            if (move_up_right != nullptr) {
                node->left = move_up_right;
                move_up_right->parent = node;
                fix_height(move_up_right);
            }
            else {
                node->left = nullptr;
                fix_height(node);
            }
        }

    }
    else { // this case is when node is a root and it does not have a parent //2

        node->left = nullptr;


        if (move_up_right == nullptr) {

            move_up_node->right = node;
            move_up_node->parent = nullptr;
            node->parent = move_up_node;
            root_ = move_up_node;
            fix_height(node);
        }
        else {

            move_up_node->right = node;
            node->parent = move_up_node;
            move_up_node->parent = nullptr;
            root_ = move_up_node;
            node->left = move_up_right;
            move_up_right->parent = node;
            fix_height(move_up_right);
        }



    }
}

// The rest of the functions below are already implemented

// returns a pointer to the minimum node
template <typename T>
typename BST<T>::Node* BST<T>::min()
{
    if (root_ == nullptr)
    {
        return root_;
    }
    else
    {
        return min(root_);
    }
}

// returns pointer to minimum node in the subtree rooted by node
// Assumes node is not nullptr
template <typename T>
typename BST<T>::Node* BST<T>::min(Node* node)
{
    while (node->left != nullptr)
    {
        node = node->left;
    }
    return node;
}

template <typename T>
typename BST<T>::Node* BST<T>::max() {

    Node* node = root_;
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}

// returns a pointer to node with key k
template <typename T>
typename BST<T>::Node* BST<T>::find(T k)
{
    Node* node = root_;
    while (node != nullptr && node->key != k)
    {
        node = k < node->key ? node->left : node->right;
    }
    return node;
}

template <typename T>
unsigned BST<T>::size()
{
    return size_;
}

// prints out the keys in the tree using in-order traversal
template <typename T>
void BST<T>::print()
{
    print(root_);
}

// you can modify what is printed out to suit your needs
template <typename T>
void BST<T>::print(Node* node)
{
    if (node == nullptr)
    {
        return;
    }
    print(node->left);
    std::cout << node->key << " height " << node->height << '\n';
    print(node->right);
}

// This is used in our testing, please do not modify
template <typename T>
typename std::vector<T> BST<T>::make_vec()
{
    std::vector<T> vec;
    vec.reserve(size_);
    make_vec(root_, vec);
    return vec;
}

// This is used for our testing, please do not modify
template <typename T>
void BST<T>::make_vec(Node* node, std::vector<T>& vec)
{
    if (node == nullptr)
    {
        return;
    }
    make_vec(node->left, vec);
    vec.push_back(node->key);
    make_vec(node->right, vec);

}

// This is used for our testing, please do not modify
template <typename T>
void BST<T>::your_postorder_heights(Node* node, std::vector<int>& vec)
{
    if (node == nullptr)
    {
        return;
    }
    your_postorder_heights(node->left, vec);
    your_postorder_heights(node->right, vec);
    vec.push_back(node->height);
}

// This is used for our testing, please do not modify
template <typename T>
int BST<T>::real_postorder_heights(Node* node, std::vector<int>& vec)
{
    if (node == nullptr)
    {
        return -1;
    }
    int left_height = real_postorder_heights(node->left, vec);
    int right_height = real_postorder_heights(node->right, vec);
    int node_height = 1 + std::max(left_height, right_height);
    vec.push_back(node_height);
    return node_height;
}

// This is used for our testing, please do not modify
template <typename T>
typename std::vector<int> BST<T>::your_postorder_heights()
{
    std::vector<int> vec;
    vec.reserve(size_);
    your_postorder_heights(root_, vec);
    return vec;
}

// This is used for our testing, please do not modify
template <typename T>
typename std::vector<int> BST<T>::real_postorder_heights()
{
    std::vector<int> vec;
    vec.reserve(size_);
    real_postorder_heights(root_, vec);
    return vec;
}


template <typename T>
void BST<T>::fix_height(Node* node) {

    while (node->parent != nullptr || node == root_) {

        //if both children exsist, th emaximum height is incremented by 1 for the parent

        if (node->left == nullptr && node->right == nullptr) {
            node->height = 0;
        }
        else if (node->left != nullptr && node->right != nullptr) {

            if (node->left->height > node->right->height) {
                node->height = node->left->height + 1;
            }
            else {
                node->height = node->right->height + 1;
            }
        }
        else if (node->left != nullptr && node->right == nullptr) {

            node->height = node->left->height + 1;
        }
        else if (node->left == nullptr && node->right != nullptr) {

            node->height = node->right->height + 1;
        }

        if (node != root_) {
            node = node->parent;
        }
        else {
            break;
        }

    }
}

// This is used for our testing, please do not modify
template <typename T>
T BST<T>::get_root_value()
{
    if (root_ == nullptr)
    {
        //std::cout << "Calling get_root_value on empty tree\n";
        T dummy{};
        return dummy;
    }
    else
    {
        return root_->key;
    }
}

#endif

