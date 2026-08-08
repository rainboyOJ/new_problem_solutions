/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-16 17:48
 * update_at: 2026-07-21 09:53
 */
#include <bits/stdc++.h>
using namespace std;

struct Query {
    int left;
    int right;
    int parity; // even = 0, odd = 1
};

const int MAXM = 5005;

int parent_array[MAXM * 2];
int size_array[MAXM * 2];
int xor_to_parent[MAXM * 2];

// xor_to_parent[x] 表示 value[x] XOR value[parent[x]]。
int find_root(int x) {
    if (parent_array[x] == x) {
        return x;
    }

    int old_parent = parent_array[x];
    parent_array[x] = find_root(old_parent);
    xor_to_parent[x] ^= xor_to_parent[old_parent];
    return parent_array[x];
}

// 约束为 value[x] XOR value[y] = expected。
// 返回 false 表示这条约束和之前的约束矛盾。
bool unite(int x, int y, int expected) {
    int root_x = find_root(x);
    int root_y = find_root(y);

    if (root_x == root_y) {
        return (xor_to_parent[x] ^ xor_to_parent[y]) == expected;
    }

    // value[root_x] XOR value[root_y]
    int relation = xor_to_parent[x] ^ xor_to_parent[y] ^ expected;

    if (size_array[root_x] < size_array[root_y]) {
        swap(root_x, root_y);
    }

    parent_array[root_y] = root_x;
    xor_to_parent[root_y] = relation;
    size_array[root_x] += size_array[root_y];
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Query> queries;
    vector<int> coordinates;
    queries.reserve(m);
    coordinates.reserve(2 * m);

    for (int i = 0; i < m; i++) {
        int left, right;
        string word;
        cin >> left >> right >> word;

        // 区间 [left, right] 对应前缀点 left-1 和 right。
        left--;
        int parity = (word == "odd");
        queries.push_back({left, right, parity});
        coordinates.push_back(left);
        coordinates.push_back(right);
    }

    sort(coordinates.begin(), coordinates.end());
    coordinates.erase(unique(coordinates.begin(), coordinates.end()), coordinates.end());

    int node_count = static_cast<int>(coordinates.size());
    for (int i = 0; i < node_count; i++) {
        parent_array[i] = i;
        size_array[i] = 1;
        xor_to_parent[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int x = lower_bound(coordinates.begin(), coordinates.end(), queries[i].left)
                - coordinates.begin();
        int y = lower_bound(coordinates.begin(), coordinates.end(), queries[i].right)
                - coordinates.begin();

        if (!unite(x, y, queries[i].parity)) {
            cout << i << '\n';
            return 0;
        }
    }

    cout << m << '\n';
    return 0;
}
