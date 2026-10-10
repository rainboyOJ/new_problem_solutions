/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 22:57
 * update_at: 2026-10-08 22:57
 */

#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 1005;

// a[1..n]：题面的输入序列。用 ll 存：题面值域上界 2^32-1 超过 INT_MAX，int 会溢出。
ll a[MAXN];

// 读入 n 个数存入 a[1..n]，打擂台求最大值所在位置（1-based）。
void solve() {
    ll n;
    cin >> n;

    for (ll i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    ll max_pos = 1; // 当前最大值所在位置，从 a[1] 起打擂台
    for (ll i = 2; i <= n; ++i) {
        // 只有严格大于才更新位置，故并列最大值保留第一次出现的位置
        if (a[i] > a[max_pos]) {
            max_pos = i;
        }
    }

    cout << max_pos << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}
