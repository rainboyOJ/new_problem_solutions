/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-03 12:04
 * update_at: 2026-10-03 12:04
 */
// brute.cpp：小数据暴力解（仅用于理解题意与对拍，不做任何优化）。
// 直接搜索操作序列：状态就是当前的 (a, t) 两个数列，每一步尝试操作一或操作二。
//
// 剪枝依据：a 只会变大，t 在操作一之后也只会变大（新 t_i = t_i + t_{n+1-i} >= t_i），
// 所以只要某一刻出现 a_i + t_i > b_i，以后永远补不回来，可以立刻停止这条分支。
// 因此搜索树是有限的。本文件只在 t_i、b_i 都很小的数据上使用。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1005;

int n;
int a[maxn]; // 当前的 a
int t[maxn]; // 当前的 t
int b[maxn]; // 目标的 b

bool dfs() {
    // 已经达到目标
    bool same = true;
    for (int i = 1; i <= n; i++) {
        if (a[i] != b[i]) same = false;
    }
    if (same) return true;

    // 如果现在这个 t 都已经加不动，以后的 t 只会更大，更不可能加
    for (int i = 1; i <= n; i++) {
        if (a[i] + t[i] > b[i]) return false;
    }

    // 选择一：执行操作二，a += t
    for (int i = 1; i <= n; i++) a[i] += t[i];
    if (dfs()) return true;
    for (int i = 1; i <= n; i++) a[i] -= t[i];

    // 选择二：执行操作一，t 与自己的倒序相加。
    // 用本层的局部数组保存 t，避免不同递归层互相覆盖。
    int save_t[maxn];
    for (int i = 1; i <= n; i++) save_t[i] = t[i];
    for (int i = 1; i <= n; i++) t[i] = save_t[i] + save_t[n + 1 - i];
    if (dfs()) return true;
    for (int i = 1; i <= n; i++) t[i] = save_t[i];

    return false;
}

void read_data() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> t[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
        for (int i = 1; i <= n; i++) a[i] = 0;
        if (dfs()) cout << "Yes\n";
        else cout << "No\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    read_data();

    return 0;
}
