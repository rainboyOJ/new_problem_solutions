/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 19:46
 * update_at: 2026-10-08 19:46
 */
// ROJ 8012 国王的米粒：第 i 格放 2^(i-1) 粒米，求第 m 格到第 n 格的米粒总数。
// 等比数列求和：第 a 格到第 b 格（a <= b）共 2^b - 2^(a-1) 粒。
#include <iostream>
using namespace std;

typedef long long ll;

ll m, n; // 两个格子编号，1 <= m, n <= 30；题面没有保证 m <= n

void solve() {
    if (!(cin >> m >> n)) return;

    // 真实数据里存在 m > n（gwdml4 输入 30 25），交换后按小到大求和
    if (m > n) {
        ll tmp = m;
        m = n;
        n = tmp;
    }

    // 2^n - 2^(m-1)：n <= 30，用 1LL 保证移位不丢位数
    ll ans = (1LL << n) - (1LL << (m - 1));
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
