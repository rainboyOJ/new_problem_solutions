/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-21 09:53
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

int parent_array[MAXM * 4];
int size_array[MAXM * 4];

int find_root(int x) {
    if (parent_array[x] == x) {
        return x;
    }

    parent_array[x] = find_root(parent_array[x]);
    return parent_array[x];
}

void unite(int x, int y) {
    int root_x = find_root(x);
    int root_y = find_root(y);
    if (root_x == root_y) {
        return;
    }

    if (size_array[root_x] < size_array[root_y]) {
        swap(root_x, root_y);
    }

    parent_array[root_y] = root_x;
    size_array[root_x] += size_array[root_y];
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

        left--;
        int parity = (word == "odd");
        queries.push_back({left, right, parity});
        coordinates.push_back(left);
        coordinates.push_back(right);
    }

    sort(coordinates.begin(), coordinates.end());
    coordinates.erase(unique(coordinates.begin(), coordinates.end()), coordinates.end());

    int node_count = static_cast<int>(coordinates.size());
    for (int i = 0; i < 2 * node_count; i++) {
        parent_array[i] = i;
        size_array[i] = 1;
    }

    for (int i = 0; i < m; i++) {
        int x = lower_bound(coordinates.begin(), coordinates.end(), queries[i].left)
                - coordinates.begin();
        int y = lower_bound(coordinates.begin(), coordinates.end(), queries[i].right)
                - coordinates.begin();

        if (queries[i].parity == 0) {
            // 相等：x0 与 y0 相连，x1 与 y1 相连。
            unite(x, y);
            unite(x + node_count, y + node_count);
        } else {
            // 相反：x0 与 y1 相连，x1 与 y0 相连。
            unite(x, y + node_count);
            unite(x + node_count, y);
        }

        // 同一个前缀点的 0/1 两种角色不能属于同一集合。
        if (find_root(x) == find_root(x + node_count)
                || find_root(y) == find_root(y + node_count)) {
            cout << i << '\n';
            return 0;
        }
    }

    cout << m << '\n';
    return 0;
}
