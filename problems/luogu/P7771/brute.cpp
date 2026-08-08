// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;
const int MAXM = 20;

int n, m;
int eu[MAXM], ev[MAXM];
vector<int> out_edges[MAXN];
bool used[MAXM];
vector<int> cur_path, best_path;

bool better(const vector<int> &a, const vector<int> &b) {
    if (b.empty()) {
        return true;
    }
    for (int i = 0; i < (int) a.size(); i++) {
        if (a[i] != b[i]) {
            return a[i] < b[i];
        }
    }
    return false;
}

void dfs(int u, int used_cnt) {
    if (used_cnt == m) {
        if (better(cur_path, best_path)) {
            best_path = cur_path;
        }
        return;
    }

    for (int id : out_edges[u]) {
        if (used[id]) {
            continue;
        }
        used[id] = true;
        cur_path.push_back(ev[id]);
        dfs(ev[id], used_cnt + 1);
        cur_path.pop_back();
        used[id] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        out_edges[i].clear();
    }

    for (int i = 1; i <= m; i++) {
        cin >> eu[i] >> ev[i];
        out_edges[eu[i]].push_back(i);
        used[i] = false;
    }

    for (int i = 1; i <= n; i++) {
        sort(out_edges[i].begin(), out_edges[i].end(), [&](int x, int y) {
            if (ev[x] != ev[y]) {
                return ev[x] < ev[y];
            }
            return x < y;
        });
    }

    best_path.clear();
    for (int start = 1; start <= n; start++) {
        cur_path.clear();
        cur_path.push_back(start);
        dfs(start, 0);
    }

    if (best_path.empty()) {
        cout << "No\n";
    } else {
        for (int i = 0; i < (int) best_path.size(); i++) {
            if (i) {
                cout << ' ';
            }
            cout << best_path[i];
        }
        cout << '\n';
    }

    return 0;
}
