/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 16:30
 * update_at: 2026-10-06 16:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1005; // 题目测试数据 n 不大，状态表开到 1000 足够

// memo[r][c] 表示把 r 拆成若干不超过 c 的正整数之和的方案数；-1 表示未计算
ll memo[MAXN][MAXN];

// parts(r, c)：把 r 拆成若干不超过 c 的正整数之和的方案数
ll parts(int r, int c) {
    if (r == 0) return 1; // 已经拼完，空拆分算一种
    if (c <= 0) return 0; // 还有剩余但上限为 0，无法拆分
    ll &res = memo[r][c];
    if (res != -1) return res;
    res = 0;
    int up = min(r, c);
    for (int x = 1; x <= up; x++) {
        // 首段取 x，下一段上限收紧为 x
        res += parts(r - x, x);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    // 只清理实际需要使用的状态范围
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            memo[i][j] = -1;
        }
    }

    cout << parts(n, n) << "\n";
    return 0;
}
