/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 02:16
 * update_at: 2026-10-05 02:16
 */

#include <iostream>
using namespace std;

typedef long long ll; // 题目数据默认 long long

ll n;          // 整数个数
ll mn, mx;     // 当前最小值、最大值

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    cin >> mn;       // 第一个数同时作为最小、最大初值
    mx = mn;

    for (ll i = 2; i <= n; i++) {
        ll x;
        cin >> x;
        if (x < mn) mn = x; // 更新最小值
        if (x > mx) mx = x; // 更新最大值
    }

    cout << mx - mn << '\n';
    return 0;
}
