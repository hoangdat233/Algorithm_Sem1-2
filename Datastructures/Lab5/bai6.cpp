#include <iostream>

struct Node {
    long long data;
    Node* right;
    Node* left;
    int height;
    Node(long long key) : data(key), right(nullptr), left(nullptr), height(1) {}
};

int getHeight(Node* node) {
    return node ? node->height : 0;
}

int getBalance(Node* node) {
    return node ? getHeight(node->right) - getHeight(node->left) : 0;
}

void updateHeight(Node* node) {
    if (node)
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
}

Node* rotate(Node* root, bool left) {
    Node* newRoot = left ? root->right : root->left;
    Node* temp = left ? newRoot->left : newRoot->right;

    if (left) {
        newRoot->left = root;
        root->right = temp;
    } else {
        newRoot->right = root;
        root->left = temp;
    }

    updateHeight(root);
    updateHeight(newRoot);

    return newRoot;
}

Node* insert(Node* node, long long data, bool& duplicate) {
    if (!node) {
        duplicate = false;
        return new Node(data);
    }

    if (data < node->data)
        node->left = insert(node->left, data, duplicate);
    else if (data > node->data)
        node->right = insert(node->right, data, duplicate);
    else {
        duplicate = true;
        return node;
    }

    updateHeight(node);

    int balance = getBalance(node);
    if (balance > 1) {
        if (data < node->right->data)
            node->right = rotate(node->right, false);
        return rotate(node, true);
    } else if (balance < -1) {
        if (data > node->left->data)
            node->left = rotate(node->left, true);
        return rotate(node, false);
    }

    return node;
}

Node* maxValueNode(Node* node) {
    while (node->right)
        node = node->right;
    return node;
}

Node* deleteNode(Node* root, long long data, bool& deleted) {
    if (!root) {
        deleted = false;
        return nullptr;
    }

    if (data < root->data)
        root->left = deleteNode(root->left, data, deleted);
    else if (data > root->data)
        root->right = deleteNode(root->right, data, deleted);
    else {
        deleted = true;
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        } else {
            Node* temp = maxValueNode(root->left);
            root->data = temp->data;
            root->left = deleteNode(root->left, temp->data, deleted);
        }
    }

    if (!root)
        return nullptr;

    updateHeight(root);

    int balance = getBalance(root);
    if (balance > 1) {
        if (getBalance(root->right) < 0)
            root->right = rotate(root->right, false);
        return rotate(root, true);
    } else if (balance < -1) {
        if (getBalance(root->left) > 0)
            root->left = rotate(root->left, true);
        return rotate(root, false);
    }

    return root;
}

bool searchNode(Node* node, long long data) {
    while (node) {
        if (data == node->data)
            return true;
        node = (data < node->data) ? node->left : node->right;
    }
    return false;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    Node* node = nullptr;

    for (int i = 0; i < n; i++) {
        char op;
        long long x;
        std::cin >> op >> x;

        bool flag = false;
        if (op == 'A') {
            node = insert(node, x, flag);
            std::cout << (node ? getBalance(node) : 0) << '\n';
        } else if (op == 'D') {
            node = deleteNode(node, x, flag);
            std::cout << (node ? getBalance(node) : 0) << '\n';
        } else if (op == 'C') {
            std::cout << (searchNode(node, x) ? "Y" : "N") << '\n';
        }
    }

    return 0;
}
