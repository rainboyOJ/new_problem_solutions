/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-07 11:21
 * update_at: 2026-11-07 11:21
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 做法：01 序列枚举隔板
//   b[i] = 1 表示在 i 和 i+1 之间切一刀 (1 <= i <= n-1)
//   共 2^(n-1) 种划分，逐一检查每段和是否等于 K
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 25;
int n;
ll K;
ll a[maxn];

int b[maxn];   // b[i]=1 表示 i 与 i+1 之间放隔板
int ans = 0;

// 检查当前隔板方案是否合法
bool check() {
    ll sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += a[i];
        bool cut = (i == n) || (b[i] == 1);
        if (cut) {
            if (sum == K) return false; // 出现和为 K 的段
            sum = 0;
        }
    }
    return true;
}

// 01 序列，枚举隔板的所有可能情况
void dfs(int dep) {
    if (dep == n) {                 // 前 n-1 个位置都决定了
        if (check()) ans++;
        return;
    }
    for (int i = 0; i <= 1; ++i) {  // i: 0 不切, 1 切
        b[dep] = i;
        dfs(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> K;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    if (n == 1) {
        // 只有一种划分：整段
        cout << (a[1] == K ? 0 : 1) << "\n";
        return 0;
    }

    dfs(1);                         // 枚举 b[1..n-1]
    cout << ans % 998244353 << "\n";
    return 0;
}
