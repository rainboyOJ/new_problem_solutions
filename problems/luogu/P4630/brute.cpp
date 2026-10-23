/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 12:51
 * update_at: 2026-10-23 13:50
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 枚举所有 (s,c,f) 三元组，DFS 搜索是否存在 s -> c -> f 的简单路径。
// 仅适用于 n <= 10 左右的稀疏图；稠密图或 n 较大时会指数爆炸。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 15;

int n, m;
vector<int> g[MAXN];
bool vis[MAXN];
bool found_path;

ll count_good_triples() {
    ll res = 0;
    for (int s = 1; s <= n; ++s) {
        for (int c = 1; c <= n; ++c) {
            if (c == s) continue;
            for (int f = 1; f <= n; ++f) {
                if (f == s || f == c) continue;
                // 检查是否存在简单路径 s -> c -> f ，使用连续 visited 的两阶段搜索
                memset(vis, 0, sizeof(vis));
                found_path = false;
                function<void(int)> go_to_c = [&](int u) {
                    if (found_path) return;
                    if (u == c) {
                        function<void(int)> go_to_f = [&](int v) {
                            if (found_path) return;
                            if (v == f) {
                                found_path = true;
                                return;
                            }
                            for (int w : g[v]) {
                                if (!vis[w]) {
                                    vis[w] = true;
                                    go_to_f(w);
                                    if (found_path) return;
                                    vis[w] = false;
                                }
                            }
                        };
                        vis[c] = true;
                        go_to_f(c);
                        return;
                    }
                    for (int v : g[u]) {
                        if (!vis[v]) {
                            vis[v] = true;
                            go_to_c(v);
                            if (found_path) return;
                            vis[v] = false;
                        }
                    }
                };
                vis[s] = true;
                go_to_c(s);
                if (found_path) ++res;
            }
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) g[i].clear();
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    ll ans = count_good_triples();
    cout << ans << '\n';
    return 0;
}
