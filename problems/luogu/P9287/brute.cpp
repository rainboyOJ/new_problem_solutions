#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解。
// 直接搜索所有可能的感染过程，收集所有终局，再统计稳定 / 可行病毒。
const int MAXN = 8;

int n, p;
int a[MAXN][MAXN];
int rk[MAXN][MAXN];

vector<vector<int>> states;
map<vector<int>, int> id_of;
queue<int> que;
vector<vector<int>> terminal_states;

int get_id(const vector<int> &state) {
    map<vector<int>, int>::iterator it = id_of.find(state);
    if (it != id_of.end()) {
        return it->second;
    }
    int id = (int)states.size();
    states.push_back(state);
    id_of[state] = id;
    que.push(id);
    return id;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int k = 1; k <= n; k++) {
            cin >> a[i][k];
            rk[i][a[i][k]] = k;
        }
    }
    cin >> p;

    vector<int> start(n + 1);
    for (int i = 1; i <= n; i++) {
        start[i] = i;
    }
    get_id(start);

    while (!que.empty()) {
        int id = que.front();
        que.pop();

        vector<int> cur = states[id];
        bool moved = false;

        for (int from = 1; from <= n; from++) {
            int virus = cur[from];
            for (int to = 1; to <= n; to++) {
                if (from == to) {
                    continue;
                }
                if (rk[to][virus] < rk[to][cur[to]]) {
                    moved = true;
                    vector<int> nxt = cur;
                    nxt[to] = virus;
                    get_id(nxt);
                }
            }
        }

        if (!moved) {
            terminal_states.push_back(cur);
        }
    }

    vector<int> feasible(n + 1, 0);
    vector<int> stable(n + 1, 1);

    for (int idx = 0; idx < (int)terminal_states.size(); idx++) {
        vector<int> used(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            used[terminal_states[idx][i]] = 1;
        }
        for (int v = 1; v <= n; v++) {
            if (used[v]) {
                feasible[v] = 1;
            } else {
                stable[v] = 0;
            }
        }
    }

    vector<int> ans;
    if (p == 1) {
        for (int v = 1; v <= n; v++) {
            if (stable[v]) {
                ans.push_back(v);
            }
        }
    } else {
        for (int v = 1; v <= n; v++) {
            if (feasible[v]) {
                ans.push_back(v);
            }
        }
    }

    cout << ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); i++) {
        if (i) {
            cout << ' ';
        }
        cout << ans[i];
    }
    cout << '\n';

    return 0;
}
