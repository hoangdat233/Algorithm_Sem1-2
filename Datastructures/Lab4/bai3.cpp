#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    int size;  
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), size(1), left(nullptr), right(nullptr) {}
};

void update_size(TreeNode* node) {
    if (node) {
        node->size = 1;
        if (node->left) node->size += node->left->size;
        if (node->right) node->size += node->right->size;
    }
}

TreeNode* insert(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    if (val < root->val)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);
    update_size(root);
    return root;
}

TreeNode* findMin(TreeNode* node) {
    while (node->left) node = node->left;
    return node;
}

TreeNode* remove(TreeNode* root, int val) {
    if (!root) return nullptr;
    if (val < root->val) {
        root->left = remove(root->left, val);
    } else if (val > root->val) {
        root->right = remove(root->right, val);
    } else {
        if (!root->left) return root->right;
        if (!root->right) return root->left;
        TreeNode* minNode = findMin(root->right);
        root->val = minNode->val;
        root->right = remove(root->right, minNode->val);
    }
    update_size(root);
    return root;
}

int find_kth(TreeNode* root, int k) {
    int rightSize = root->right ? root->right->size : 0;
    if (k == rightSize + 1) return root->val;
    if (k <= rightSize) return find_kth(root->right, k);
    return find_kth(root->left, k - rightSize - 1);
}

int main() {
    int n;
    cin >> n;
    TreeNode* root = nullptr;
    vector<int> results;
    for (int i = 0; i < n; i++) {
        int command, k;
        cin >> command >> k;
        if (command == 1) {
            root = insert(root, k);
        } else if (command == -1) {
            root = remove(root, k);
        } else if (command == 0) {
            if (!root || root->size < k) {
                results.push_back(-1);
            } else {
                results.push_back(find_kth(root, k));
            }
        }
    }
    for (int res : results) {
        cout << res << endl;
    }
    return 0;
}
