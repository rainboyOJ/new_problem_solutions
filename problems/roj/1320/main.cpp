/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 09:17
 * update_at: 2026-10-05 09:17
 */
// main.cpp：均分纸牌，答案等于「偏差前缀和非零」的个数。
#include <iostream>
using namespace std;

const int MAXN = 105;

typedef long long ll;

ll n;
ll a[MAXN];    // a[i] 表示第 i 堆纸牌的初始张数
ll diff[MAXN]; // diff[i] = a[i] - 平均值，表示第 i 堆多出（正）或缺少（负）的张数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    ll sum = 0;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }

    ll avg = sum / n; // 纸牌总数保证是 n 的倍数

    // 每条相邻边界 i/i+1 上净流过的牌数被两端盈亏唯一确定，恰好等于偏差的前缀和；
    // 前缀和不为零就说明这条边界必须搬一次，所以答案就是非零前缀和的个数。
    ll prefix = 0;
    ll moves = 0;
    for (ll i = 1; i <= n - 1; i++) {
        diff[i] = a[i] - avg;
        prefix += diff[i];
        if (prefix != 0) {
            moves++;
        }
    }

    cout << moves << endl;
    return 0;
}
