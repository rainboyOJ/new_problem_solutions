/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-06-19 18:47
 * update_at: 2026-10-26 12:48
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 直接搜索所有合法的合并顺序：每一步枚举"相邻且相等"的位置，把它俩合成 x+1，
// 然后递归继续，取所有分支里的最大值。
// 分支数随层数指数增长，所以只适合 n <= 20 量级的小数据。
#include <bits/stdc++.h>
using namespace std;

// 在当前序列 v 上枚举所有可合并的一对，递归取最优。
vector<int> cur;
int best;

void dfs(const vector<int> &v) {
    for (int x : v) {
        if (x > best) {
            best = x;
        }
    }

    for (int i = 0; i + 1 < (int)v.size(); i++) {
        if (v[i] != v[i + 1]) {
            continue;
        }
        // 这一层选择：合并位置 i 和 i+1。
        vector<int> next = v;
        next[i] = next[i] + 1;
        next.erase(next.begin() + i + 1);
        dfs(next);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    cur.resize(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &cur[i]);
    }
    best = 0;
    dfs(cur);
    printf("%d\n", best);
    return 0;
}
