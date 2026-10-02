/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-06-20 07:35
 * update_at: 2026-10-01 20:09
 */
// brute.cpp：小数据暴力解，逐行枚举"不选"或"选某一种食材"，
// 到叶子节点检查是否存在某种食材严格超过一半。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 15;
const int MAXM = 15;
const ll MOD = 998244353LL;

int n, m;
int a[MAXN][MAXM]; // 输入矩阵
int cnt[MAXM];     // cnt[j]：当前方案中食材 j 被选了多少次
ll ans;

// 模意义下加法
void add_mod(ll &x, ll y) {
    x += y;
    if (x >= MOD) {
        x -= MOD;
    }
}

// 检查当前方案是否合法：没有任何食材严格超过一半
bool check(int chosen) {
    for (int j = 1; j <= m; j++) {
        if (cnt[j] * 2 > chosen) {
            return false;
        }
    }
    return true;
}

// 逐行枚举：第 row 行要么不选，要么选食材 j（j 从 1 到 m）
void dfs(int row, int chosen, ll ways) {
    if (row > n) {
        if (chosen == 0) {
            return;
        }

        if (check(chosen)) {
            add_mod(ans, ways);
        }
        return;
    }

    // 不选第 row 行
    dfs(row + 1, chosen, ways);

    // 选第 row 行的食材 j
    for (int j = 1; j <= m; j++) {
        if (a[row][j] == 0) {
            continue;
        }

        cnt[j]++;
        dfs(row + 1, chosen + 1, ways * a[row][j] % MOD);
        cnt[j]--;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    dfs(1, 0, 1);
    cout << ans << '\n';

    return 0;
}
