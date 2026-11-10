/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 08:11
 * update_at: 2026-11-10 08:32
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 使用 01 序列递归枚举所有可能的子集，叶子节点检查是否完整覆盖 [1, T]，求最少选中数量。
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 25;
const ll INF = 1e9;

ll n, t;

struct Segment {
    ll l;
    ll r;
};

Segment seg[MAXN];
int choose[MAXN]; // 01 序列：choose[i] = 1 表示选择第 i 头奶牛
ll ans = INF;

// 检查当前选择是否覆盖了 [1, T] 上的每一个整数点
bool check() {
    for (ll point = 1; point <= t; point++) {
        bool covered = false;
        for (ll i = 0; i < n; i++) {
            if (choose[i] && seg[i].l <= point && point <= seg[i].r) {
                covered = true;
                break;
            }
        }
        if (!covered) return false;
    }
    return true;
}

// 01 序列递归枚举
void dfs_choose(int dep) {
    if (dep == n) {
        if (check()) {
            ll cnt = 0;
            for (ll i = 0; i < n; i++) {
                if (choose[i]) cnt++;
            }
            ans = min(ans, cnt);
        }
        return;
    }

    // 不选第 dep 头
    choose[dep] = 0;
    dfs_choose(dep + 1);

    // 选第 dep 头
    choose[dep] = 1;
    dfs_choose(dep + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> t)) return 0;

    for (ll i = 0; i < n; i++) {
        cin >> seg[i].l >> seg[i].r;
    }

    dfs_choose(0);

    if (ans >= INF) {
        cout << -1 << "\n";
    } else {
        cout << ans << "\n";
    }

    return 0;
}
