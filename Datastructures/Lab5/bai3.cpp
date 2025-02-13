#include <iostream>
#include <vector>
#include <queue>

struct Node {
    int key;
    int l; // left
    int r; // right
    int h; // height
};

std::vector<Node> tree;

int getH(int v) {
    return v == -1 ? 0 : tree[v].h;
}

void updateH(int v) {
    int hl = getH(tree[v].l);
    int hr = getH(tree[v].r);
    tree[v].h = (hl > hr ? hl : hr) + 1;
}

int rotateL(int v) {
    int u = tree[v].r;
    tree[v].r = tree[u].l;
    tree[u].l = v;
    updateH(v);
    updateH(u);
    return u;
}

int rotateR(int v) {
    int u = tree[v].l;
    tree[v].l = tree[u].r;
    tree[u].r = v;
    updateH(v);
    updateH(u);
    return u;
}

int getBal(int v) {
    updateH(v);
    int b = getH(tree[v].r) - getH(tree[v].l);
    if (b == 2) {
        if (getH(tree[tree[v].r].r) < getH(tree[tree[v].r].l)) {
            tree[v].r = rotateR(tree[v].r);
        }
        return rotateL(v);
    }
    if (b == -2) {
        if (getH(tree[tree[v].l].l) < getH(tree[tree[v].l].r)) {
            tree[v].l = rotateL(tree[v].l);
        }
        return rotateR(v);
    }
    return v;
}

int insert(int root, int key) {
    std::vector<int> path;
    int cur = root;
    int par = -1;

    while (cur != -1) {
        path.push_back(cur);
        par = cur;
        if (key < tree[cur].key) {
            cur = tree[cur].l;
        } else {
            cur = tree[cur].r;
        }
    }

    Node newNode = {key, -1, -1, 1};
    tree.push_back(newNode);
    int newIdx = tree.size() - 1;

    if (par == -1) {
        root = newIdx;
    } else if (key < tree[par].key) {
        tree[par].l = newIdx;
    } else {
        tree[par].r = newIdx;
    }

    for (int i = path.size() - 1; i >= 0; --i) {
        int node = path[i];
        node = getBal(node);

        if (i > 0) {
            int prev = path[i - 1];
            if (tree[prev].l == path[i]) {
                tree[prev].l = node;
            } else {
                tree[prev].r = node;
            }
        } else {
            root = node;
        }
    }

    return root;
}

std::vector<Node> rebuild(int root, std::vector<int>& idxMap) {
    std::vector<Node> newTree;
    std::queue<int> q;
    int idx = 0;
    q.push(root);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (v == -1 || idxMap[v] != -1) continue;
        idxMap[v] = idx++;
        newTree.push_back(tree[v]);
        q.push(tree[v].l);
        q.push(tree[v].r);
    }

    return newTree;
}

void print(const std::vector<Node>& newTree, const std::vector<int>& idxMap) {
    std::cout << newTree.size() << '\n';
    for (int i = 0; i < newTree.size(); i++) {
        int l = newTree[i].l == -1 ? 0 : idxMap[newTree[i].l] + 1;
        int r = newTree[i].r == -1 ? 0 : idxMap[newTree[i].r] + 1;
        std::cout << newTree[i].key << " " << l << " " << r << '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;

    int root = -1;
    if (n > 0) {
        tree.resize(n);
        for (int i = 0; i < n; ++i) {
            int key, l, r;
            std::cin >> key >> l >> r;
            tree[i] = {key, l - 1, r - 1, 1};
        }
        root = 0;

        for (int i = n - 1; i >= 0; --i) {
            updateH(i);
        }
    }

    int x;
    std::cin >> x;

    root = insert(root, x);

    std::vector<int> idxMap(tree.size(), -1);
    std::vector<Node> newTree = rebuild(root, idxMap);

    print(newTree, idxMap);

    return 0;
}
