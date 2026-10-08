/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 16:15
 * update_at: 2026-10-08 16:15
 */
// ROJ 1384 珍珠(bead)：Floyd-Warshall 求传递闭包，统计有多少颗珍珠不可能是中位数。
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 105;
bool reach[MAXN][MAXN]; // reach[i][j] = true 表示确定珍珠 i 比珍珠 j 重（含传递推出的关系）

void solve() {
    ll n, m;
    if (!(cin >> n >> m)) return;

    for (ll k = 0; k < m; ++k) {
        ll x, y;
        cin >> x >> y;
        reach[x][y] = true; // 直接给出的关系：x 比 y 重
    }

    // 传递闭包：若 i 比 k 重且 k 比 j 重，则 i 比 j 重
    for (ll k = 1; k <= n; ++k)
        for (ll i = 1; i <= n; ++i)
            for (ll j = 1; j <= n; ++j)
                if (reach[i][k] && reach[k][j]) reach[i][j] = true;

    ll half = n / 2; // n 为奇数，中位数必须恰好有 n/2 颗比它重的珍珠
    ll not_middle = 0;
    for (ll i = 1; i <= n; ++i) {
        ll heavier = 0; // 确定比珍珠 i 重的珍珠数
        ll lighter = 0; // 确定比珍珠 i 轻的珍珠数
        for (ll j = 1; j <= n; ++j) {
            if (reach[j][i]) heavier++;
            if (reach[i][j]) lighter++;
        }
        if (heavier > half || lighter > half) not_middle++;
    }
    cout << not_middle << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
