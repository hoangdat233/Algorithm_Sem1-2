#include <iostream>
using namespace std;

struct Node {
    int id;
    int k;
    Node* left;
    Node* right;

    Node(int id, int k) : id(id), k(k), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int id, int k) {
    if (root == nullptr) {
        return new Node(id, k);
    }
    if (id < root->id) {
        root->left = insert(root->left, id, k);
    } else {
        root->right = insert(root->right, id, k);
    }
    return root;
}

bool check(Node* node, int& min_id) {
    if (node == nullptr) return false;

    int l_sum = 0, r_sum = 0;
    bool l_valid = check(node->left, min_id);
    bool r_valid = check(node->right, min_id);

    if (node->left != nullptr) l_sum = node->left->k;
    if (node->right != nullptr) r_sum = node->right->k;

    int total = l_sum + r_sum;

    if ((node->left != nullptr || node->right != nullptr) && node->k == total) {
        if (min_id == -1 || node->id < min_id) {
            min_id = node->id;
        }
    }

    return true;
}

int main() {
    int n;
    cin >> n;

    if (n == 0) {
        cout << "NO" << endl;
        return 0;
    }

    Node* root = nullptr;

    for (int i = 0; i < n; i++) {
        int id, k;
        cin >> id >> k;
        root = insert(root, id, k);
    }

    int min_id = -1;
    check(root, min_id);

    if (min_id == -1) {
        cout << "NO" << endl;
    } else {
        cout << min_id << endl;
    }

    return 0;
}