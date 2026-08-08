// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 12;

int case_id, T;
int n, k;
pair<int, int> edge_list[MAXN];
int key_edge[MAXN];
bool adjacent_edge[MAXN][MAXN];
set<vector<pair<int, int> > > all_trees;

void dfs_line_graph(int root, int current, int visited_mask, vector<int> parent_stack, vector<pair<int, int> > tree_edges) {
    bool moved = false;
    for (int i = 1; i < n; i++) {
        if ((visited_mask & (1 << (i - 1))) || !adjacent_edge[current][i]) {
            continue;
        }
        moved = true;
        vector<pair<int, int> > next_edges = tree_edges;
        int a = current, b = i;
        if (a > b) {
            swap(a, b);
        }
        next_edges.push_back(make_pair(a, b));

        vector<int> next_stack = parent_stack;
        next_stack.push_back(current);
        dfs_line_graph(root, i, visited_mask | (1 << (i - 1)), next_stack, next_edges);
    }

    if (moved) {
        return;
    }

    if (current == root) {
        if (visited_mask == (1 << (n - 1)) - 1) {
            sort(tree_edges.begin(), tree_edges.end());
            all_trees.insert(tree_edges);
        }
    } else {
        int parent = parent_stack.back();
        parent_stack.pop_back();
        dfs_line_graph(root, parent, visited_mask, parent_stack, tree_edges);
    }
}

bool share_endpoint(pair<int, int> a, pair<int, int> b) {
    return a.first == b.first || a.first == b.second || a.second == b.first || a.second == b.second;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> case_id >> T;
    while (T--) {
        cin >> n >> k;
        for (int i = 1; i < n; i++) {
            cin >> edge_list[i].first >> edge_list[i].second;
        }
        for (int i = 1; i <= k; i++) {
            cin >> key_edge[i];
        }

        for (int i = 1; i < n; i++) {
            for (int j = 1; j < n; j++) {
                adjacent_edge[i][j] = (i != j && share_endpoint(edge_list[i], edge_list[j]));
            }
        }

        all_trees.clear();
        for (int i = 1; i <= k; i++) {
            vector<int> empty_stack;
            vector<pair<int, int> > empty_edges;
            int root = key_edge[i];
            dfs_line_graph(root, root, 1 << (root - 1), empty_stack, empty_edges);
        }

        cout << all_trees.size() << '\n';
    }

    return 0;
}
