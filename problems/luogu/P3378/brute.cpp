/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-16 23:26
 * update_at: 2026-10-07 10:18
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 用一个 vector 存下所有元素，每次查询或删除时线性扫描找最小值。
vector<ll> heap_data;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;

    for (ll i = 0; i < n; i++) {
        ll op;
        cin >> op;

        if (op == 1) {
            ll x;
            cin >> x;
            heap_data.push_back(x);
        } else {
            // 线性找出当前最小值所在的位置
            ll pos = 0;
            for (ll j = 1; j < (ll)heap_data.size(); j++) {
                if (heap_data[j] < heap_data[pos]) {
                    pos = j;
                }
            }

            if (op == 2) {
                cout << heap_data[pos] << '\n';
            } else {
                // 删除最小值：用最后一个元素覆盖它再缩短，等价于 erase
                heap_data[pos] = heap_data[heap_data.size() - 1];
                heap_data.pop_back();
            }
        }
    }

    return 0;
}
