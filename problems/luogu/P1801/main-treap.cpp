#include <bits/stdc++.h>
using namespace std;

struct Treap {
    struct Node {
        int child[2] = {0, 0};
        int value = 0;
        int priority = 0;
        int count = 0;
        int size = 0;
    };

    vector<Node> tree;
    int root = 0;
    mt19937 rng;

    Treap(int max_nodes = 0) : rng(712367821) {
        tree.reserve(max_nodes + 1);
        tree.push_back(Node()); // node 0 is the null sentinel.
    }

    int new_node(int value) {
        tree.push_back(Node());
        int id = (int)tree.size() - 1;
        tree[id].value = value;
        tree[id].priority = (int)rng();
        tree[id].count = 1;
        tree[id].size = 1;
        return id;
    }

    int node_size(int u) const {
        return u == 0 ? 0 : tree[u].size;
    }

    void pushup(int u) {
        tree[u].size = node_size(tree[u].child[0]) +
                       node_size(tree[u].child[1]) +
                       tree[u].count;
    }

    // direction=0: lift left child by right rotation.
    // direction=1: lift right child by left rotation.
    void rotate(int &u, int direction) {
        int v = tree[u].child[direction];
        tree[u].child[direction] = tree[v].child[direction ^ 1];
        tree[v].child[direction ^ 1] = u;
        pushup(u);
        pushup(v);
        u = v;
    }

    void insert(int &u, int value) {
        if (u == 0) {
            u = new_node(value);
            return;
        }
        if (tree[u].value == value) {
            tree[u].count++;
            pushup(u);
            return;
        }

        int direction = value > tree[u].value;
        insert(tree[u].child[direction], value);
        if (tree[tree[u].child[direction]].priority < tree[u].priority) {
            rotate(u, direction);
        }
        pushup(u);
    }

    void insert(int value) {
        insert(root, value);
    }

    // Rank is 1-based: the smallest value has rank 1.
    int rank_of(int value) const {
        int u = root;
        int rank = 1;
        while (u != 0) {
            if (value <= tree[u].value) {
                u = tree[u].child[0];
            } else {
                rank += node_size(tree[u].child[0]) + tree[u].count;
                u = tree[u].child[1];
            }
        }
        return rank;
    }

    int kth(int k) const {
        int u = root;
        while (u != 0) {
            int left_size = node_size(tree[u].child[0]);
            if (k <= left_size) {
                u = tree[u].child[0];
            } else if (k <= left_size + tree[u].count) {
                return tree[u].value;
            } else {
                k -= left_size + tree[u].count;
                u = tree[u].child[1];
            }
        }
        return -1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    vector<int> a(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }
    vector<int> u(n);
    for (int i = 0; i < n; i++) {
        cin >> u[i];
    }

    Treap treap(m + 5);
    int inserted = 0;
    int rank = 1; // 第 i 次 GET 输出第 i 小
    for (int q : u) {
        for (int i = inserted; i < q; i++) {
            treap.insert(a[i]);
        }
        inserted = q;
        cout << treap.kth(rank) << '\n';
        rank++;
    }

    return 0;
}
