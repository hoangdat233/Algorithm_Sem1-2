#include <iostream>
#include <stack>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int x) : val(x), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int val) {
    if (!root) return new Node(val);
    if (val < root->val) root->left = insert(root->left, val);
    else if (val > root->val) root->right = insert(root->right, val);
    return root;
}

Node* erase(Node* root, int val) {
    if (!root) return nullptr;
    if (val < root->val) root->left = erase(root->left, val);
    else if (val > root->val) root->right = erase(root->right, val);
    else {
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = root->right;
        while (temp && temp->left) temp = temp->left;
        root->val = temp->val;
        root->right = erase(root->right, temp->val);
    }
    return root;
}

void inorder(Node* root, stack<Node*>& s) {
    while (root) {
        s.push(root);
        root = root->left;
    }
}

void transfer_tasks(Node*& src, Node*& dest) {
    stack<Node*> stack_src, stack_dest;

    inorder(src, stack_src); 
    inorder(dest, stack_dest); 

    while (!stack_src.empty() || !stack_dest.empty()) {
        if (stack_src.empty()) {
            Node* node = stack_dest.top();
            stack_dest.pop();
            dest = insert(dest, node->val);
            inorder(node->right, stack_dest);
        } else if (stack_dest.empty()) {
            Node* node = stack_src.top();
            stack_src.pop();
            dest = insert(dest, node->val);
            inorder(node->right, stack_src);
        } else {
            Node* node_src = stack_src.top();
            Node* node_dest = stack_dest.top();

            if (node_src->val <= node_dest->val) {
                stack_src.pop();
                dest = insert(dest, node_src->val);
                inorder(node_src->right, stack_src);
            } else {
                stack_dest.pop();
                dest = insert(dest, node_dest->val);
                inorder(node_dest->right, stack_dest);
            }
        }
    }
}

void clearTree(Node*& root) {
    if (!root) return;
    clearTree(root->left);
    clearTree(root->right);
    delete root;
    root = nullptr;
}

void inorder_print(Node* root, bool& isFirst) {
    if (!root) return;
    inorder_print(root->left, isFirst);
    if (!isFirst) cout << " ";
    cout << root->val;
    isFirst = false;
    inorder_print(root->right, isFirst);
}

int main() {
    int n;
    cin >> n;
    Node* tasks_nikolai = nullptr;
    Node* tasks_stepan = nullptr;
    
    while (n--) {
        int op, id, task;
        cin >> op;

        if (op == 0) {  
            cin >> id >> task;
            if (id == 0) {
                tasks_nikolai = insert(tasks_nikolai, task);
            } else if (id == 1) {
                tasks_stepan = insert(tasks_stepan, task);
            }
        } else if (op == 1) { 
            cin >> id >> task;
            if (id == 0) {
                tasks_nikolai = erase(tasks_nikolai, task);
            } else if (id == 1) {
                tasks_stepan = erase(tasks_stepan, task);
            }
        } else if (op == 2) {  
            transfer_tasks(tasks_stepan, tasks_nikolai); 
            clearTree(tasks_stepan);  
            
            bool isFirst = true;
            if (tasks_nikolai) {
                inorder_print(tasks_nikolai, isFirst); 
                cout << endl;
            }
        }
    }

    clearTree(tasks_nikolai);
    clearTree(tasks_stepan);
    return 0;
}
