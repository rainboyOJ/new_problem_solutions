/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-26 13:36
 * update_at: 2026-10-26 16:36
 */
// main.cpp: 正式主解. dp[i][j] = 前 i 束花放入前 j 个花瓶的最大美学值.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 105;      // F, V 都不超过 100
const ll NEG = -(1LL << 60);  // 负无穷哨兵: 美学值最小为 -50*100, 远大于 NEG

ll F, V;                     // F 束花, V 个花瓶
ll a[MAXN][MAXN];            // a[i][j]: 花束 i 放入花瓶 j 的美学值
ll dp[MAXN][MAXN];           // dp[i][j]: 前 i 束花放入前 j 个花瓶的最大美学值
ll path[MAXN];               // path[t]: 还原方案时从后往前记录的花瓶编号

void read_data() {
    cin >> F >> V;
    for (int i = 1; i <= F; i++) {
        for (int j = 1; j <= V; j++) {
            cin >> a[i][j];
        }
    }
}

void solve() {
    // 初始化: 0 束花放入任意多个花瓶美学值为 0; 其余状态置为负无穷.
    for (int i = 0; i <= F; i++) {
        for (int j = 0; j <= V; j++) {
            dp[i][j] = NEG;
        }
    }
    for (int j = 0; j <= V; j++) {
        dp[0][j] = 0;
    }

    // 转移: 花束 i 不放花瓶 j -> dp[i][j-1]; 放 -> dp[i-1][j-1] + a[i][j].
    for (int i = 1; i <= F; i++) {
        for (int j = i; j <= V; j++) {
            ll not_use = dp[i][j - 1];
            ll use = dp[i - 1][j - 1] + a[i][j];
            dp[i][j] = max(not_use, use);
        }
    }

    cout << dp[F][V] << "\n";

    // 方案还原: 从 (F, V) 反推. 若 dp[i][j] == dp[i][j-1], 说明最优解没用花瓶 j,
    // 左移; 否则花束 i 一定放在花瓶 j, 记录后向左上角走一步.
    ll i = F;
    ll j = V;
    ll cnt = 0;
    while (i > 0) {
        if (j > i && dp[i][j] == dp[i][j - 1]) {
            j--;
        } else {
            path[++cnt] = j;
            i--;
            j--;
        }
    }

    // path 是逆序记录的, 倒序输出得到递增序列.
    for (int k = cnt; k >= 1; k--) {
        cout << path[k] << (k == 1 ? '\n' : ' ');
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_data();
    solve();

    return 0;
}
