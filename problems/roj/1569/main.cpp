/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:20
 * update_at: 2026-10-04 22:20
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 405; // 2n + 5，环拆成链后长度翻倍

typedef long long ll;

ll n, m;      // n 堆石子；m = 2n 为拆环成链后的总长
ll a[MAXN];   // 拆环后的石子序列：原序列接一份在后面
ll pre[MAXN]; // pre[k] = 前 k 堆石子之和，O(1) 取区间和
ll f[MAXN][MAXN]; // f[i][j]：把区间 [i,j] 合并成一堆的最小得分
ll g[MAXN][MAXN]; // g[i][j]：把区间 [i,j] 合并成一堆的最大得分
ll BIG;       // 最小值表的哨兵，任何合法得分都达不到

// 读入并把环拆成两倍长的链。
void read_input() {
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (ll i = 1; i <= n; i++) {
        a[i + n] = a[i]; // 复制一份接到末尾，破环成链
    }
    m = 2 * n;
}

void solve() {
    // 前缀和：sum(i,j) = pre[j] - pre[i-1]
    pre[0] = 0;
    for (ll i = 1; i <= m; i++) {
        pre[i] = pre[i - 1] + a[i];
    }

    // 哨兵：任何方案得分不超过 n 倍石子总和（每次得分 <= 总和，共 n-1 次）
    BIG = pre[n] * n + 1;

    // 长度 1 的区间 f = g = 0（全局数组默认即 0）
    // 按区间长度从小到大递推：长度 L 只依赖更短的子区间
    for (ll len = 2; len <= n; len++) {
        for (ll i = 1; i + len - 1 <= m; i++) {
            ll j = i + len - 1;
            ll sum_ij = pre[j] - pre[i - 1]; // 最后一次合并必得整段和，与断点无关
            ll best_min = BIG;
            ll best_max = -1;
            // 枚举断点：左段 [i,k]、右段 [k+1,j] 先各自合成一堆
            for (ll k = i; k < j; k++) {
                ll s_min = f[i][k] + f[k + 1][j];
                ll s_max = g[i][k] + g[k + 1][j];
                if (s_min < best_min) best_min = s_min;
                if (s_max > best_max) best_max = s_max;
            }
            f[i][j] = best_min + sum_ij;
            g[i][j] = best_max + sum_ij;
        }
    }

    // 每个长度为 n 的窗口 [r, r+n-1] 对应一种断环方式，枚举所有起点取最值
    ll ans_min = BIG;
    ll ans_max = -1;
    for (ll r = 1; r <= n; r++) {
        if (f[r][r + n - 1] < ans_min) ans_min = f[r][r + n - 1];
        if (g[r][r + n - 1] > ans_max) ans_max = g[r][r + n - 1];
    }

    cout << ans_min << "\n";
    cout << ans_max << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
