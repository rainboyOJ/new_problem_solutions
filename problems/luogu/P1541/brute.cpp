/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:27
 * update_at: 2026-11-11 00:27
 */
// brute.cpp：记忆化搜索实现基准
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int MAXN = 360;
const int MAXC = 42;

int a[MAXN];
int cnt[5];
int memo[MAXC][MAXC][MAXC][MAXC];

int dfs(int c1, int c2, int c3, int c4) {
    if (c1 == 0 && c2 == 0 && c3 == 0 && c4 == 0) return a[1];
    if (memo[c1][c2][c3][c4] != -1) return memo[c1][c2][c3][c4];

    int pos = 1 + c1 * 1 + c2 * 2 + c3 * 3 + c4 * 4;
    int max_prev = 0;

    if (c1 > 0) max_prev = max(max_prev, dfs(c1 - 1, c2, c3, c4));
    if (c2 > 0) max_prev = max(max_prev, dfs(c1, c2 - 1, c3, c4));
    if (c3 > 0) max_prev = max(max_prev, dfs(c1, c2, c3 - 1, c4));
    if (c4 > 0) max_prev = max(max_prev, dfs(c1, c2, c3, c4 - 1));

    return memo[c1][c2][c3][c4] = max_prev + a[pos];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    for (int i = 0; i < m; ++i) {
        int card;
        cin >> card;
        cnt[card]++;
    }

    memset(memo, -1, sizeof(memo));

    cout << dfs(cnt[1], cnt[2], cnt[3], cnt[4]) << "\n";

    return 0;
}
