#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;

    Node(int value) : data(value), left(NULL), right(NULL) {}
};

typedef Node* node;

node insert(node root, int value)
{
    if (root == NULL)
    {
        return new Node(value);
    }

    if (value < root->data)
    {
        root->left = insert(root->left, value);
    }
    else if (value > root->data)
    {
        root->right = insert(root->right, value);
    }
    return root;
}

void inorder(node root)
{
    if (root == NULL)
    {
        return;
    }
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

int main(){
    int n;
    cin >> n;
    node root = NULL;
    for (int i = 0; i < n; i++)
    {
        int value;
        cin >> value;
        root = insert(root, value);
    }
    inorder(root);
    return 0;
}