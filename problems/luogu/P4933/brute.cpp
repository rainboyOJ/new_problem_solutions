/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-26 13:45
 * update_at: 2026-10-26 13:45
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 用 01 序列递归枚举所有下标子集，到叶子再检查选出的高度是否构成等差数列。
// 复杂度 O(2^n * n)，只适合 n <= 20 的数据。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 25; // 只能枚举到 n = 20 左右

int n;
int h[MAXN];      // h[i]: 第 i 座塔的高度, 下标从 1 开始
int choose[MAXN]; // choose[i]: 第 i 座塔留在地上为 1, 缩到地下为 0
ll ans;           // 美观方案数

// 检查当前 choose[1..n] 选出的高度是不是等差数列, 是则把答案加一。
void check_and_count() {
    int first = 0; // 选出的第一个下标
    int second = 0;
    int cnt = 0;   // 选出了几座塔
    for (int i = 1; i <= n; i++) {
        if (choose[i] == 0) {
            continue;
        }
        cnt++;
        if (cnt == 1) {
            first = i;
        } else if (cnt == 2) {
            second = i;
        }
    }
    if (cnt == 0) {
        return; // 一座都不留不算美观
    }
    if (cnt <= 2) {
        ans++;  // 只留一座或两座塔一定是等差数列
        return;
    }
    // 长度 >= 3 时, 相邻高度差是否全部相等就是判定标准
    int d = h[second] - h[first];
    int last = second;
    for (int i = second + 1; i <= n; i++) {
        if (choose[i] == 0) {
            continue;
        }
        if (h[i] - h[last] != d) {
            return;
        }
        last = i;
    }
    ans++;
}

// 这一层决定第 dep 座塔留不留下: 0 不留, 1 留下。
void dfs(int dep) {
    if (dep > n) {
        check_and_count();
        return;
    }
    for (int i = 0; i <= 1; i++) {
        choose[dep] = i;
        dfs(dep + 1);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &h[i]);
    }
    dfs(1);
    printf("%lld\n", ans);
    return 0;
}
