/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-08-17 23:10
 */
// brute.cpp：把元素建成冲突图，回溯求最少染色数，适合小数据验证。
#include <bits/stdc++.h>
using namespace std;

int element_count;
int best_color;
vector<int> order_vertices;
vector<int> vertex_color;
vector<int> conflict_mask;
vector<int> vertex_degree;

bool degree_compare(int x, int y) {
    return vertex_degree[x] > vertex_degree[y];
}

void color_dfs(int position, int used_color) {
    if (used_color >= best_color) {
        return;
    }
    if (position == element_count) {
        best_color = used_color;
        return;
    }
    int u = order_vertices[position];
    int forbidden = 0;
    for (int i = 0; i < position; i++) {
        int v = order_vertices[i];
        if ((conflict_mask[u] >> v) & 1) {
            forbidden |= 1 << vertex_color[v];
        }
    }
    for (int color = 0; color < used_color; color++) {
        if (((forbidden >> color) & 1) == 0) {
            vertex_color[u] = color;
            color_dfs(position + 1, used_color);
        }
    }
    vertex_color[u] = used_color;
    color_dfs(position + 1, used_color + 1);
    vertex_color[u] = -1;
}

int repair_cost(const vector<int> &values, int w) {
    element_count = (int)values.size();
    if (element_count == 0) {
        return 0;
    }
    if (w >= (1 << 30)) {
        return element_count;
    }
    conflict_mask.assign(element_count, 0);
    vertex_degree.assign(element_count, 0);
    for (int i = 0; i < element_count; i++) {
        for (int j = 0; j < i; j++) {
            if ((values[i] ^ values[j]) < w) {
                conflict_mask[i] |= 1 << j;
                conflict_mask[j] |= 1 << i;
                vertex_degree[i]++;
                vertex_degree[j]++;
            }
        }
    }
    order_vertices.resize(element_count);
    for (int i = 0; i < element_count; i++) {
        order_vertices[i] = i;
    }
    sort(order_vertices.begin(), order_vertices.end(), degree_compare);
    vertex_color.assign(element_count, -1);
    best_color = element_count;
    color_dfs(0, 0);
    return best_color;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, w;
    cin >> n >> w;
    vector<vector<int> > packets(n + 1);
    for (int i = 1; i <= n; i++) {
        int count;
        cin >> count;
        packets[i].resize(count);
        for (int j = 0; j < count; j++) {
            cin >> packets[i][j];
        }
    }
    int q;
    cin >> q;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int u, x;
            cin >> u >> x;
            packets[u].push_back(x);
        } else if (type == 2) {
            int u, v;
            cin >> u >> v;
            packets[u].insert(packets[u].end(),
                              packets[v].begin(), packets[v].end());
            packets[v].clear();
        } else {
            long long answer = 0;
            for (int i = 1; i <= n; i++) {
                answer += repair_cost(packets[i], w);
            }
            cout << answer << '\n';
        }
    }
    return 0;
}
