/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:05
 * update_at: 2026-10-05 00:05
 */
#include <iostream>
using namespace std;

typedef long long ll;

ll n, m;      // 序列长度与指定数字
ll x;         // 当前读入的数
ll cnt;       // 与 m 相同的数的个数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 读取序列长度和指定数字
    cin >> n >> m;

    // 线性扫描序列，统计等于 m 的数的个数
    for (ll i = 1; i <= n; ++i) {
        cin >> x;
        if (x == m) {
            ++cnt;
        }
    }

    // 输出结果
    cout << cnt << "\n";
    return 0;
}
