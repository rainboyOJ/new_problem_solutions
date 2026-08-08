#include <bits/stdc++.h>
using namespace std;

// brute.cpp：逐层爬父亲回答 K 级祖先，只适合小数据对拍。

typedef unsigned int ui;

const int MAXN = 2005;

int n, q;
ui seed_value;
int parent_node[MAXN];
int depth_node[MAXN];
vector<int> children[MAXN];
int root_node;

ui get(ui x) {
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    seed_value = x;
    return seed_value;
}

void dfs_depth(int u) {
    for (int i = 0; i < (int)children[u].size(); i++) {
        int v = children[u][i];
        depth_node[v] = depth_node[u] + 1;
        dfs_depth(v);
    }
}

int kth_ancestor_brute(int x, int k) {
    while (k > 0) {
        x = parent_node[x];
        k--;
    }
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q >> seed_value;
    for (int i = 1; i <= n; i++) {
        cin >> parent_node[i];
        if (parent_node[i] == 0) {
            root_node = i;
        } else {
            children[parent_node[i]].push_back(i);
        }
    }

    depth_node[root_node] = 1;
    dfs_depth(root_node);

    int last_answer = 0;
    unsigned long long final_answer = 0;
    for (int i = 1; i <= q; i++) {
        int x = (int)(((get(seed_value) ^ (ui)last_answer) % (ui)n) + 1);
        int k = (int)((get(seed_value) ^ (ui)last_answer) % (ui)depth_node[x]);
        int current_answer = kth_ancestor_brute(x, k);
        last_answer = current_answer;
        final_answer ^= 1ULL * (unsigned int)i * (unsigned int)current_answer;
    }

    cout << final_answer << '\n';

    return 0;
}
