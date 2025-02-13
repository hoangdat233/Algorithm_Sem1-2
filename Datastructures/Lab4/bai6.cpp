#include <iostream>
#include <stack>
#include <string>
 
using namespace std;
 
struct Node {
    int value;
    Node* left;
    Node* right;
    Node* parent;
    int maxVal;
    int minVal;
    int sum;
    Node(int val) : value(val), left(nullptr), right(nullptr), parent(nullptr), maxVal(val), minVal(val), sum(val) {}
};
 
void updateSubtree(Node* root) {
    if (!root) return;
 
    root->sum = root->value;
    root->maxVal = root->value;
    root->minVal = root->value;
 
    bool isBST = true;
 
    if (root->left) {
        updateSubtree(root->left);
        if (root->left->sum == -1e9 || root->left->maxVal >= root->value) {
            isBST = false;
        } else {
            root->sum += root->left->sum;
            root->minVal = min(root->minVal, root->left->minVal);
        }
    }

    if (root->right) {
        updateSubtree(root->right);
        if (root->right->sum == -1e9 || root->right->minVal <= root->value) {
            isBST = false;
        } else {
            root->sum += root->right->sum;
            root->maxVal = max(root->maxVal, root->right->maxVal);
        }
    }
 
    if (!isBST) {
        root->sum = -1e9;
    }
}
 
int findMaxsum(Node* root) {
    if (!root) return 0;
    updateSubtree(root);
 
    stack<Node*> nodes;
    nodes.push(root);
    int maxSum = 0;
 
    while (!nodes.empty()) {
        Node* node = nodes.top();
        nodes.pop();
        if (node->sum != -1e9) {
            maxSum = max(maxSum, node->sum);
        }
        if (node->left) nodes.push(node->left);
        if (node->right) nodes.push(node->right);
    }
    return maxSum;
}

void DeleteTree(Node* root) {
    stack<Node*> nodes;
    nodes.push(root);
    while (!nodes.empty()) {
        Node* node = nodes.top();
        nodes.pop();
        if (node->left) nodes.push(node->left);
        if (node->right) nodes.push(node->right);
        delete node;
    }
}

int main() {
    string input;
    getline(cin, input);
 
    Node* root = nullptr;
    Node* cur = nullptr;
    stack<Node*> nodeStack;
 
    int index = 0;
 
    for (int i = 0; i < (int)input.size(); ++i) {
        char cmd = input[i];
        if (cmd == 'l' || cmd == 'r') {
            if (!nodeStack.empty()) {
                cur = nodeStack.top();
            }
            index++;
            Node* newNode = new Node(0);
            newNode->parent = cur;
            if (cmd == 'l') {
                cur->left = newNode;
            } else {
                cur->right = newNode;
            }
            nodeStack.push(newNode);
            cur = newNode;
        } else if (cmd == 'u') {
            if (!nodeStack.empty()) {
                nodeStack.pop();
                if (!nodeStack.empty()) {
                    cur = nodeStack.top();
                }
            }
        } else if (isdigit(cmd) || cmd == '-' || cmd == '+') {
            int value = 0;
            int sign = 1;
            if (cmd == '-') {
                sign = -1;
                ++i;
            } else if (cmd == '+') {
                ++i;
            }
 
            while (i < input.size() && isdigit(input[i])) {
                value = value * 10 + (input[i] - '0');
                ++i;
            }
            --i;
            value *= sign;
 
            if (cur) {
                cur->value = value;
                cur->sum = value;
                cur->maxVal = value;
                cur->minVal = value;
            } else {
                root = new Node(value);
                nodeStack.push(root);
                cur = root;
            }
        }
    }
 
    int maxSum = findMaxsum(root);
    cout << maxSum << endl;
    DeleteTree(root);
    
    return 0;
}