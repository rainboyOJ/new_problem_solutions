/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:55
 * update_at: 2026-11-11 00:55
 */

// brute.cpp：暴力搜索所有可能的划分方案
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;
int n, m;
int a[105];
int cur_min = INF, cur_max = -1;

inline int mod10(int val) {
    return ((val % 10) + 10) % 10;
}

// 递归切分：当前起点 s，已切出 cnt 段，当前处理到 idx，累乘值为 prod
void dfs(int s, int idx, int cnt, int prod) {
    if (cnt == m - 1) {
        // 最后一段从 idx 到 s + n - 1
        int sum = 0;
        for (int i = idx; i <= s + n - 1; ++i) sum += a[i];
        int total = prod * mod10(sum);
        cur_min = min(cur_min, total);
        cur_max = max(cur_max, total);
        return;
    }

    // 枚举这一段的结束位置
    int cur_sum = 0;
    for (int next_end = idx; next_end <= s + n - 1 - (m - 1 - cnt); ++next_end) {
        cur_sum += a[next_end];
        dfs(s, next_end + 1, cnt + 1, prod * mod10(cur_sum));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m)) return 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i + n] = a[i];
    }

    for (int s = 1; s <= n; ++s) {
        dfs(s, s, 0, 1);
    }

    cout << cur_min << "\n" << cur_max << "\n";
    return 0;
}
