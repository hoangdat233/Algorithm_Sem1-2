#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int data) : data(data), left(nullptr), right(nullptr) {}
};

typedef Node* node;

bool Check(node root, int target) {
    while (root != nullptr) {
        if (root->data == target) return true;
        root = (target < root->data) ? root->left : root->right;
    }
    return false;
}
node successor(node curr) {
    curr = curr->right;
    while (curr != nullptr && curr->left != nullptr) {
        curr = curr->left;
    }
    return curr;
}

node insert(node root, int data) {
    if (root == nullptr) return new Node(data);
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}

node erase(node root, int target) {
    if (root == nullptr) return root;
    if (target < root->data) {
        root->left = erase(root->left, target);
    } else if (target > root->data) {
        root->right = erase(root->right, target);
    } else {
        if (root->left == nullptr) {
            node temp = root->right;
            delete root;
            return temp;
        }
        if (root->right == nullptr) {
            node temp = root->left;
            delete root;
            return temp;
        }
        node succ = successor(root);
        root->data = succ->data;
        root->right = erase(root->right, succ->data);
    }
    return root;
}

node mingreater(node root, int x) {
    node min = nullptr;
    while (root) {
        if (root->data > x) {
            min = root;
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return min;
}


node maxless(node root, int x) {
    node max = nullptr;
    while (root) {
        if (root->data < x) {
            max = root;
            root = root->right;
        } else {
            root = root->left;
        }
    }
    return max;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    node root = nullptr;
    int op, x;

    while (std::cin >> op >> x) {
        switch(op) {
            case 0:
                root = insert(root, x);
                break;
            case 1:
                root = erase(root, x);
                break;
            case 2:
                std::cout << (Check(root, x) ? "true" : "false") << '\n';
                break;
            case 3: {
                node res = mingreater(root, x);
                if (res) {
                    std::cout << res->data << '\n';
                } else {
                    std::cout << "none" << '\n';
                }
                break;
            }
            case 4: {
                node res = maxless(root, x);
                if (res) {
                    std::cout << res->data << '\n';
                } else {
                    std::cout << "none" << '\n';
                }
                break;
            }
        }
    }
    return 0;
}
