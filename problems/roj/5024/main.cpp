/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 22:23
 * update_at: 2026-10-08 22:23
 */
#include <iostream>

using namespace std;

typedef long long ll;

ll m;            // 目标值：求最小的 n 使 1 + 1/2 + ... + 1/n >= m
double sum_h;    // 当前调和级数部分和 H_n
ll n;            // 当前已经累加到的项数（也是分母）

void solve() {
    // 逐项累加，直到部分和达到 m；退出时 n 就是最小的合法项数。
    // 注意必须做实数除法：写成 1 / n 会按整数截断成 0，循环永不结束。
    // m <= 11 时 n 最大 33617，double 的累积误差（~1e-10）远小于
    // H_n 跨过整数 m 时的最小间隙（~1e-5），比较不会误判。
    while (sum_h < m) {
        n++;
        sum_h += 1.0 / n;
    }
    cout << n << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (cin >> m) {
        solve();
    }
    return 0;
}
