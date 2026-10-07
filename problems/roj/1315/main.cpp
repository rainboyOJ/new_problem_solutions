/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 13:25
 * update_at: 2026-10-04 13:25
 */

#include <iostream>
using namespace std;

typedef long long ll;

// n 个不同元素划分成 k 个非空无标号集合的方案数 = 第二类 Stirling 数 S(n,k)
// 递推：S(n,k) = S(n-1,k-1) + k * S(n-1,k)
// 边界：S(i,1)=1, S(i,i)=1, S(i,j)=0(>= i 越界或 j==0)
// 用一维数组滚动：外层 i 从 2..n，内层 j 从大到小更新，保留上一行 S(i-1,j-1) 的值。
const int MAXN = 35;
ll dp[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, k;
    cin >> n >> k;

    if (k == 0 || k > n) {
        cout << 0 << "\n";
        return 0;
    }

    // 初值 S(1,1)=1
    dp[1] = 1;
    for (ll j = 2; j <= k; j++) dp[j] = 0;

    for (ll i = 2; i <= n; i++) {
        ll upper = min(i, k);
        // j 从大到小：dp[j-1] 仍是上一行 S(i-1,j-1) 的值
        for (ll j = upper; j >= 1; j--) {
            ll single = (j == i) ? 1 : dp[j - 1];   // 第 i 个元素单独成一盒
            ll into_old = (j == 1) ? 1 : dp[j];     // 第 i 个元素放进已有的某一盒
            dp[j] = single + j * into_old;          // 按 64 位有符号 long long 自然溢出
        }
    }

    cout << dp[k] << "\n";
    return 0;
}