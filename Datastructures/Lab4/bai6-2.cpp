#include <iostream>
#include <climits>

struct Node {
    long long val;
    Node* left;
    Node* right;
    Node* parent;
    Node(long long v) : val(v), left(nullptr), right(nullptr), parent(nullptr) {}
};

struct BSTInfo {
    bool isBST;
    long long minVal;
    long long maxVal;
    long long sum;
};

long long min(long long a, long long b) {
    return a < b ? a : b;
}

long long max(long long a, long long b) {
    return a > b ? a : b;
}

BSTInfo findMaxBST(Node* node, long long &maxSum) {
    if (!node) {
        return {true, LLONG_MAX, LLONG_MIN, 0};  
    }
    BSTInfo left = findMaxBST(node->left, maxSum);
    BSTInfo right = findMaxBST(node->right, maxSum);
    bool isBST = left.isBST && right.isBST && (node->left == nullptr || node->val > left.maxVal) && (node->right == nullptr || node->val < right.minVal);

    long long subtreeSum = node->val + left.sum + right.sum;
    if (isBST) {
        maxSum = std::max(maxSum, subtreeSum);
    }

    BSTInfo cur;
    cur.isBST = isBST;
    cur.minVal = isBST ? std::min(node->val, left.minVal) : LLONG_MIN;
    cur.maxVal = isBST ? std::max(node->val, right.maxVal) : LLONG_MAX;
    cur.sum = isBST ? subtreeSum : 0;
    return cur;
}

int main() {
    char cmd;
    long long rootVal;
    std::cin >> rootVal;
    Node* root = new Node(rootVal);
    Node* curr = root;
    long long val;
    while (std::cin >> cmd) {
        if (cmd == 'l') {
            std::cin >> val;
            Node* newNode = new Node(val);
            newNode->parent = curr;
            curr->left = newNode;
            curr = newNode;
        } else if (cmd == 'r') {
            std::cin >> val;
            Node* newNode = new Node(val);
            newNode->parent = curr;
            curr->right = newNode;
            curr = newNode;
        } else if (cmd == 'u') {
            curr = curr->parent;
        }
    }
    long long maxSum = 0; 
    findMaxBST(root, maxSum);
    std::cout << maxSum << std::endl;

    return 0;
}
