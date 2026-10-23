/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 23:05
 * update_at: 2026-10-23 23:32
 */
// brute.cpp：小数据暴力染色检验。
// 复杂度为 O(3^n * n)，搜索空间随节点数指数爆炸，只适合 n <= 15 的小数据验证与对拍。
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

typedef long long ll;

const int maxn = 50;

int ls[maxn];
int rs[maxn];
int node_cnt = 0;
string s;
int pos_idx = 0;

int color[maxn]; // 0: 绿, 1: 红, 2: 蓝
int ans_max = -1;
int ans_min = 1e9;

int build_tree() {
    int u = ++node_cnt;
    char type = s[pos_idx++];
    if (type == '0') {
        ls[u] = 0;
        rs[u] = 0;
    } else if (type == '1') {
        ls[u] = build_tree();
        rs[u] = 0;
    } else if (type == '2') {
        ls[u] = build_tree();
        rs[u] = build_tree();
    }
    return u;
}

// 检查染色合法性
bool check(int u) {
    if (u == 0) return true;
    int l = ls[u];
    int r = rs[u];
    if (l != 0) {
        if (color[u] == color[l]) return false;
        if (!check(l)) return false;
    }
    if (r != 0) {
        if (color[u] == color[r]) return false;
        if (!check(r)) return false;
    }
    if (l != 0 && r != 0) {
        if (color[l] == color[r]) return false;
    }
    return true;
}

// 暴力枚举每个节点的颜色
void dfs(int u) {
    if (u > node_cnt) {
        if (check(1)) {
            int green_cnt = 0;
            for (int i = 1; i <= node_cnt; ++i) {
                if (color[i] == 0) {
                    green_cnt++;
                }
            }
            ans_max = max(ans_max, green_cnt);
            ans_min = min(ans_min, green_cnt);
        }
        return;
    }

    for (int c = 0; c < 3; ++c) {
        color[u] = c;
        dfs(u + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> s)) return 0;

    build_tree();
    dfs(1);

    cout << ans_max << " " << ans_min << "\n";

    return 0;
}
