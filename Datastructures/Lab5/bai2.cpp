#include <iostream>
#include <vector>
#include <stack>
#include <queue>

struct Node {
    int key;
    int left;
    int right;
};

std::vector<Node> tree;
std::vector<int> h;

void calcH(int root) {
    std::stack<int> s;
    std::vector<bool> vis(tree.size(), false);
    s.push(root);

    while (!s.empty()) {
        int cur = s.top();
        if (cur == -1) {
            s.pop();
            continue;
        }

        if (vis[cur]) {
            s.pop();
            int hl = tree[cur].left == -1 ? 0 : h[tree[cur].left];
            int hr = tree[cur].right == -1 ? 0 : h[tree[cur].right];
            h[cur] = std::max(hl, hr) + 1;
        } else {
            vis[cur] = true;
            s.push(cur);
            if (tree[cur].right != -1) s.push(tree[cur].right);
            if (tree[cur].left != -1) s.push(tree[cur].left);
        }
    }
}

int rotRL(int root) {
    int r = tree[root].right;
    int rl = tree[r].left;

    int rll = tree[rl].left;
    int rlr = tree[rl].right;

    tree[rl].left = root;
    tree[rl].right = r;

    tree[root].right = rll;
    tree[r].left = rlr;

    return rl;
}

int rotR(int root) {
    int r = tree[root].right;
    int rl = tree[r].left;

    tree[r].left = root;
    tree[root].right = rl;

    return r;
}

int balance(int root) {
    int hl = tree[root].left == -1 ? 0 : h[tree[root].left];
    int hr = tree[root].right == -1 ? 0 : h[tree[root].right];
    int bal = hr - hl;

    if (bal > 1) {
        int rc = tree[root].right;
        int hrl = tree[rc].left == -1 ? 0 : h[tree[rc].left];
        int hrr = tree[rc].right == -1 ? 0 : h[tree[rc].right];
        int balR = hrr - hrl;

        if (balR < 0) {
            return rotRL(root);
        } else {
            return rotR(root);
        }
    }
    return root;
}

std::vector<Node> rebuild(int root, std::vector<int> &idx) {
    std::vector<Node> newTree;
    std::queue<int> q;
    int cnt = 0;
    q.push(root);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        if (cur == -1 || idx[cur] != -1) continue;
        idx[cur] = cnt++;
        newTree.push_back(tree[cur]);
        q.push(tree[cur].left);
        q.push(tree[cur].right);
    }

    return newTree;
}

void print(const std::vector<Node> &newTree, const std::vector<int> &idx, int n) {
    std::cout << n << std::endl;
    for (int i = 0; i < n; i++) {
        int l = newTree[i].left == -1 ? 0 : idx[newTree[i].left] + 1;
        int r = newTree[i].right == -1 ? 0 : idx[newTree[i].right] + 1;
        std::cout << newTree[i].key << " " << l << " " << r << std::endl;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;

    tree.resize(n);
    h.resize(n, 0);

    for (int i = 0; i < n; i++) {
        int key, left, right;
        std::cin >> key >> left >> right;
        tree[i].key = key;
        tree[i].left = left ? left - 1 : -1;
        tree[i].right = right ? right - 1 : -1;
    }

    int root = 0;

    calcH(root);

    root = balance(root);

    std::vector<int> idx(tree.size(), -1);
    std::vector<Node> newTree = rebuild(root, idx);

    print(newTree, idx, n);

    return 0;
}
