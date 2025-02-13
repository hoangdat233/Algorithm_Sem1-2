#include <iostream>
#include <string>

struct TreeNode {
    int key;
    int studentMask;
    TreeNode* left;
    TreeNode* right;
    int height;
    TreeNode(int value) {
        key = value;
        left = right = nullptr;
        height = 1;
        studentMask = 0;
    }
};

int calculateHeight(TreeNode* node) {
    return node ? node->height : 0;
}

int maxValue(int a, int b) {
    return (a > b) ? a : b;
}

int calculateBalance(TreeNode* node) {
    return node ? calculateHeight(node->right) - calculateHeight(node->left) : 0;
}

TreeNode* rotateRight(TreeNode* node) {
    TreeNode* newRoot = node->left;
    TreeNode* temp = newRoot->right;
    newRoot->right = node;
    node->left = temp;
    node->height = maxValue(calculateHeight(node->left), calculateHeight(node->right)) + 1;
    newRoot->height = maxValue(calculateHeight(newRoot->left), calculateHeight(newRoot->right)) + 1;
    return newRoot;
}

TreeNode* rotateLeft(TreeNode* node) {
    TreeNode* newRoot = node->right;
    TreeNode* temp = newRoot->left;
    newRoot->left = node;
    node->right = temp;
    node->height = maxValue(calculateHeight(node->left), calculateHeight(node->right)) + 1;
    newRoot->height = maxValue(calculateHeight(newRoot->left), calculateHeight(newRoot->right)) + 1;
    return newRoot;
}

TreeNode* insertIntoTree(TreeNode* root, int key, int student, bool& isDuplicate) {
    if (!root) {
        isDuplicate = false;
        TreeNode* newNode = new TreeNode(key);
        newNode->studentMask |= (1 << (student - 1));
        return newNode;
    }
    if (key < root->key) {
        root->left = insertIntoTree(root->left, key, student, isDuplicate);
    } else if (key > root->key) {
        root->right = insertIntoTree(root->right, key, student, isDuplicate);
    } else {
        isDuplicate = true;
        root->studentMask |= (1 << (student - 1));
        return root;
    }

    root->height = maxValue(calculateHeight(root->left), calculateHeight(root->right)) + 1;
    int balance = calculateBalance(root);

    if (balance > 1 && key > root->right->key)
        return rotateLeft(root);
    if (balance > 1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    if (balance < -1 && key < root->left->key)
        return rotateRight(root);
    if (balance < -1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    return root;
}

long long convertStringToKey(const std::string& input) {
    long long key = 0;
    for (char c : input) {
        if (c >= '0' && c <= '9') key = key * 62 + (c - '0');
        else if (c >= 'A' && c <= 'Z') key = key * 62 + (10 + c - 'A');
        else if (c >= 'a' && c <= 'z') key = key * 62 + (36 + c - 'a');
    }
    return key;
}

int countSetBits(int x) {
    int count = 0;
    while (x) {
        x &= (x - 1); 
        ++count;
    }
    return count;
}

void calculateScores(TreeNode* root, int& score1, int& score2, int& score3) {
    if (!root) return;
    calculateScores(root->left, score1, score2, score3);

    int bitCount = countSetBits(root->studentMask);
    if (bitCount == 1) {
        if (root->studentMask & 1) score1 += 3;
        else if (root->studentMask & 2) score2 += 3;
        else if (root->studentMask & 4) score3 += 3;
    } else if (bitCount == 2) {
        if ((root->studentMask & 1) && (root->studentMask & 2)) {
            score1 += 1;
            score2 += 1;
        }
        if ((root->studentMask & 1) && (root->studentMask & 4)) {
            score1 += 1;
            score3 += 1;
        }
        if ((root->studentMask & 2) && (root->studentMask & 4)) {
            score2 += 1;
            score3 += 1;
        }
    }

    calculateScores(root->right, score1, score2, score3);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    TreeNode* root = nullptr;

    for (int student = 1; student <= 3; ++student) {
        for (int i = 0; i < n; ++i) {
            std::string filename;
            std::cin >> filename;
            long long key = convertStringToKey(filename);
            bool isDuplicate = false;
            root = insertIntoTree(root, key, student, isDuplicate);
        }
    }

    int score1 = 0, score2 = 0, score3 = 0;
    calculateScores(root, score1, score2, score3);
    std::cout << score1 << " " << score2 << " " << score3;
    return 0;
}
