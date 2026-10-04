/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:23
 * update_at: 2026-10-02 15:23
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 做法：答案只依赖字符之间的相对大小，所以最优解一定可以只使用 1..n 这些字符。
//       枚举所有 s[1..n]（按字典序升序），第一个满足 p 的即为字典序最小的答案。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;

int n;
int p[MAXN];    // 输入的 p_i
int cur[MAXN];  // 当前枚举的串
int ans[MAXN];  // 找到的答案
bool found;

// 计算当前串 cur 的 p 数组，与输入比较
bool check() {
    for (int j = 1; j <= n; ++j) {
        // 在 s[1..j] 的所有后缀中找字典序最小者（后缀长度互不相同，最小值唯一）
        int best = 1;
        for (int x = 2; x <= j; ++x) {
            // 比较 s[x..j] 与 s[best..j]
            int i = x, k = best;
            while (i <= j && k <= j && cur[i] == cur[k]) {
                ++i;
                ++k;
            }
            if (k > j) {
                // s[best..j] 是 s[x..j] 的前缀，更短的后缀字典序更小
                continue;
            }
            if (i > j) {
                // s[x..j] 是 s[best..j] 的前缀，更小
                best = x;
                continue;
            }
            if (cur[i] < cur[k]) best = x;
        }
        if (best != p[j]) return false;
    }
    return true;
}

// 按字典序枚举所有串
void dfs(int dep) {
    if (found) return;
    if (dep > n) {
        if (check()) {
            found = true;
            for (int i = 1; i <= n; ++i) ans[i] = cur[i];
        }
        return;
    }
    for (int c = 1; c <= n && !found; ++c) {
        cur[dep] = c;
        dfs(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> p[i];

        found = false;
        dfs(1);

        if (!found) {
            cout << -1 << "\n";
        } else {
            for (int i = 1; i <= n; ++i) cout << ans[i] << " \n"[i == n];
        }
    }
    return 0;
}
