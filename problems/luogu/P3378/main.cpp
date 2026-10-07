/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 09:38
 * update_at: 2026-10-07 09:38
 */
// 【模板】堆：用 priority_queue 维护可重小根堆，push/top/pop 分别对应插入、查最小值、删除最小值。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

priority_queue<ll, vector<ll>, greater<ll> > pq; // 小根堆：堆顶始终是当前最小值，重复元素各占一个位置

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;

    // 依次处理 n 次操作：1 插入、2 输出最小值、3 删除最小值。
    for (ll i = 0; i < n; i++) {
        ll op;
        cin >> op;

        if (op == 1) {
            ll x;
            cin >> x;
            pq.push(x);
        } else if (op == 2) {
            cout << pq.top() << '\n';
        } else {
            pq.pop();
        }
    }

    return 0;
}
