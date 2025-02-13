#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int findIndex(const vector<int>& inorder, int start, int end, int rootValue) {
    for (int i = start; i <= end; i++) {
        if (inorder[i] == rootValue) {
            return i;
        }
    }
    return -1;
}

Node* Build_BST(const vector<int>& inorder, const vector<int>& preorder, int start, int end, int& preIndex) {
    if (start > end) {
        return NULL;
    }
    
    int rootValue = preorder[preIndex++];
    Node* newNode = createNode(rootValue);

    if (start == end) {
        return newNode;
    }
    int inIndex = findIndex(inorder, start, end, rootValue);
    if (inIndex == -1) {
        return NULL;
    }
    newNode->left = Build_BST(inorder, preorder, start, inIndex - 1, preIndex);
    newNode->right = Build_BST(inorder, preorder, inIndex + 1, end, preIndex);
    return newNode;
}

int checkPostorder(Node* root, const vector<int>& postorder, int& index) {
    if (root == NULL) {
        return index;
    }
    index = checkPostorder(root->left, postorder, index);
    index = checkPostorder(root->right, postorder, index);
    if (root->data == postorder[index]) {
        index++;
    } else {
        return -1;
    }
    return index;
}

int main() {
    int n;
    cin >> n;
    vector<int> inorder(n), preorder(n), postorder(n);
    for (int i = 0; i < n; i++) {
        cin >> preorder[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> inorder[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> postorder[i];
    }
    int preIndex = 0;
    Node* root = Build_BST(inorder, preorder, 0, n - 1, preIndex);

    if (root == NULL) {
        cout << "NO";
        return 0;
    }
    int postIndex = 0;
    int res = checkPostorder(root, postorder, postIndex);
    if (res == n) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}
