#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解。
// 对一个周期内的“必染色类型”建状态图，
// 判断是否存在无限染色方案，使得同色连续段长度始终小于 k。

int T;
long long p1, p2, k;

struct State {
    int pos;
    int last_color; // 0 红, 1 蓝, 2 表示还没有上一段颜色
    int run_len;
};

vector<int> type_list;
vector<State> states;
vector<vector<int> > graph, rev_graph, comps;
vector<int> vis, order, comp, has_cycle, reached;

long long gcd_value(long long a, long long b) {
    while (b != 0) {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a;
}

long long lcm_value(long long a, long long b) {
    return a / gcd_value(a, b) * b;
}

int get_idx(const vector<vector<int> > &id, int pos, int last_color, int run_len) {
    return id[pos][last_color * (int)k + run_len];
}

void dfs1(int u) {
    vis[u] = 1;
    for (int v : graph[u]) {
        if (!vis[v]) {
            dfs1(v);
        }
    }
    order.push_back(u);
}

void dfs2(int u, int cid) {
    comp[u] = cid;
    comps[cid].push_back(u);
    for (int v : rev_graph[u]) {
        if (comp[v] == -1) {
            dfs2(v, cid);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;

    while (T--) {
        cin >> p1 >> p2 >> k;

        if (k == 1) {
            cout << "No\n";
            continue;
        }

        type_list.clear();
        states.clear();
        graph.clear();
        rev_graph.clear();
        comps.clear();
        vis.clear();
        order.clear();
        comp.clear();
        has_cycle.clear();
        reached.clear();

        long long g = gcd_value(p1, p2);
        long long a = p1 / g;
        long long b = p2 / g;

        long long L = lcm_value(a, b);

        for (long long x = 0; x < L; x++) {
            bool red = (x % a == 0);
            bool blue = (x % b == 0);

            if (!red && !blue) {
                continue;
            }

            if (red && blue) {
                type_list.push_back(2); // 公共点，可以染红或染蓝
            } else if (red) {
                type_list.push_back(0);
            } else {
                type_list.push_back(1);
            }
        }

        int m = type_list.size();
        vector<vector<int> > id(m, vector<int>(3 * (int)k, -1));

        for (int pos = 0; pos < m; pos++) {
            for (int last_color = 0; last_color < 3; last_color++) {
                for (int run_len = 0; run_len < k; run_len++) {
                    int cur_id = states.size();
                    id[pos][last_color * (int)k + run_len] = cur_id;
                    states.push_back({pos, last_color, run_len});
                }
            }
        }

        graph.assign(states.size(), vector<int>());
        rev_graph.assign(states.size(), vector<int>());

        for (int i = 0; i < (int)states.size(); i++) {
            int pos = states[i].pos;
            int last_color = states[i].last_color;
            int run_len = states[i].run_len;

            vector<int> colors;
            if (type_list[pos] == 2) {
                colors.push_back(0);
                colors.push_back(1);
            } else {
                colors.push_back(type_list[pos]);
            }

            for (int color : colors) {
                int next_run = (last_color == color ? run_len + 1 : 1);
                if (next_run >= k) {
                    continue;
                }

                int next_pos = (pos + 1) % m;
                int to = get_idx(id, next_pos, color, next_run);
                graph[i].push_back(to);
                rev_graph[to].push_back(i);
            }
        }

        vis.assign(states.size(), 0);
        for (int i = 0; i < (int)states.size(); i++) {
            if (!vis[i]) {
                dfs1(i);
            }
        }

        comp.assign(states.size(), -1);
        int comp_cnt = 0;
        for (int i = (int)order.size() - 1; i >= 0; i--) {
            int u = order[i];
            if (comp[u] == -1) {
                comps.push_back(vector<int>());
                dfs2(u, comp_cnt);
                comp_cnt++;
            }
        }

        has_cycle.assign(comp_cnt, 0);
        for (int i = 0; i < comp_cnt; i++) {
            if ((int)comps[i].size() > 1) {
                has_cycle[i] = 1;
                continue;
            }
            int u = comps[i][0];
            for (int v : graph[u]) {
                if (v == u) {
                    has_cycle[i] = 1;
                }
            }
        }

        queue<int> q;
        reached.assign(states.size(), 0);

        vector<int> first_colors;
        if (type_list[0] == 2) {
            first_colors.push_back(0);
            first_colors.push_back(1);
        } else {
            first_colors.push_back(type_list[0]);
        }

        bool ok = false;
        for (int color : first_colors) {
            int start = get_idx(id, 1 % m, color, 1);
            if (!reached[start]) {
                reached[start] = 1;
                q.push(start);
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            if (has_cycle[comp[u]]) {
                ok = true;
                break;
            }

            for (int v : graph[u]) {
                if (!reached[v]) {
                    reached[v] = 1;
                    q.push(v);
                }
            }
        }

        if (ok) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }

    return 0;
}
