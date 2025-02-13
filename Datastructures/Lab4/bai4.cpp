#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
};

Node* createNode(int val) {
    Node* node = new Node();
    node->val = val;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

void insert(Node* root, int val) {
    if (val == root->val) {
        return; 
    }
    if (val < root->val) {
        if (root->left) {
            insert(root->left, val);
        } else {
            root->left = createNode(val);
        }
    } else {
        if (root->right) {
            insert(root->right, val);
        } else {
            root->right = createNode(val);
        }
    }
}

vector<int> Rmost_level(Node* root) {
    vector<int> res;
    if (!root) return res;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int levelsize = q.size();
        int Rmost = 0;

        for (int i = 0; i < levelsize; i++) {
            Node* node = q.front();
            q.pop();
            Rmost = node->val;
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        res.push_back(Rmost);
    }
    return res;
}

int main() {
    int n;
    cin >> n;

    Node* root = nullptr;
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        if (!root) {
            root = createNode(val);
        } else {
            insert(root, val);
        }
    }
    vector<int> res = Rmost_level(root);
    for (int val : res) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}
