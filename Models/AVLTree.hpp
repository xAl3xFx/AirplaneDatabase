//
// Created by Alex on 25.12.2019.
//

#ifndef AIRPLANEDATABASE_AVLTREE_HPP
#define AIRPLANEDATABASE_AVLTREE_HPP
#include<iostream>
#include "Plane.hpp"

using namespace std;

class BST
{
    struct node
    {
        Plane* data;
        node* left;
        node* right;
        int height;
    };

    node* root;

    void makeEmpty(node* t)
    {
        if(t == NULL)
            return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }

    node* insert(Plane *x, node* t)
    {
        if(t == NULL)
        {
            t = new node;
            t->data = x;
            t->height = 0;
            t->left = t->right = NULL;
        }
        else if(x->getId() < t->data->getId())
        {
            t->left = insert(x, t->left);
            if(height(t->left) - height(t->right) == 2)
            {
                if(x->getId() < t->left->data->getId())
                    t = singleRightRotate(t);
                else
                    t = doubleRightRotate(t);
            }
        }
        else if(x->getId() > t->data->getId())
        {
            t->right = insert(x, t->right);
            if(height(t->right) - height(t->left) == 2)
            {
                if(x->getId() > t->right->data->getId())
                    t = singleLeftRotate(t);
                else
                    t = doubleLeftRotate(t);
            }
        }

        t->height = max(height(t->left), height(t->right))+1;
        return t;
    }

    node* singleRightRotate(node* &t)
    {
        if (t->left != NULL) {
            node* u = t->left;
            t->left = u->right;
            u->right = t;
            t->height = max(height(t->left), height(t->right)) + 1;
            u->height = max(height(u->left), t->height) + 1;
            return u;
        }
        return t;
    }
    node* singleLeftRotate(node* &t)
    {
        if (t->right != NULL) {
            node* u = t->right;
            t->right = u->left;
            u->left = t;
            t->height = max(height(t->left), height(t->right)) + 1;
            u->height = max(height(t->right), t->height) + 1;
            return u;
        }
        return t;
    }

    node* doubleLeftRotate(node* &t)
    {
        t->right = singleRightRotate(t->right);
        return singleLeftRotate(t);
    }

    node* doubleRightRotate(node* &t)
    {
        t->left = singleLeftRotate(t->left);
        return singleRightRotate(t);
    }

    node* findMin(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    node* findMax(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }

    Plane* findById(long long id, node *t)
    {
        if(t == NULL)
        {
            return NULL;
        }
        else if(id < t->data->getId())
        {
            return findById(id, t->left);
        }
        else if(t->data->getId() < id)
        {
            return findById(id, t->right);
        }
        else
        {
            return t->data;
        }
    }

    node* remove(Plane x, node* t)
    {
        node* temp;

        // Element not found
        if(t == NULL)
            return NULL;

            // Searching for element
        else if(x.getId() < t->data->getId())
            t->left = remove(x, t->left);
        else if(x.getId() > t->data->getId())
            t->right = remove(x, t->right);

            // Element found
            // With 2 children
        else if(t->left && t->right)
        {
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(*t->data, t->right);
        }
            // With one or zero child
        else
        {
            temp = t;
            if(t->left == NULL)
                t = t->right;
            else if(t->right == NULL)
                t = t->left;
            delete temp;
        }
        if(t == NULL)
            return t;

        t->height = max(height(t->left), height(t->right))+1;

        // If node is unbalanced
        // If left node is deleted, right case
        if(height(t->left) - height(t->right) == -2)
        {
            // right right case
            if(height(t->right->right) - height(t->right->left) == 1)
                return singleLeftRotate(t);
                // right left case
            else
                return doubleLeftRotate(t);
        }
            // If right node is deleted, left case
        else if(height(t->right) - height(t->left) == 2)
        {
            // left left case
            if(height(t->left->left) - height(t->left->right) == 1){
                return singleRightRotate(t);
            }
                // left right case
            else
                return doubleRightRotate(t);
        }
        return t;
    }

    int height(node* t)
    {
        return (t == NULL ? -1 : t->height);
    }

    int getBalance(node* t)
    {
        if(t == NULL)
            return 0;
        else
            return height(t->left) - height(t->right);
    }

    void inorder(node* t)
    {
        if(t == NULL)
            return;
        inorder(t->left);
        //cout << t->data << " ";
        cout << "Not implemented";
        inorder(t->right);
    }

public:
    BST()
    {
        root = NULL;
    }

    void insert(Plane *x)
    {
        root = insert(x, root);
    }

    void remove(Plane x)
    {
        root = remove(x, root);
    }

    void display()
    {
        inorder(root);
        cout << endl;
    }

    Plane* find(long long id){
        return findById(id, root);
    }

};

#endif //AIRPLANEDATABASE_AVLTREE_HPP
