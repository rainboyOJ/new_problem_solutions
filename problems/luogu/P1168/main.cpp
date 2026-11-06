/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-06 21:12
 * update_at: 2026-11-06 21:12
 */
// P1168 中位数：对顶堆
// low 是大根堆，存较小的一半；high 是小根堆，存较大的一半。
// 读完前 i 个数后若 i 是奇数，low 的堆顶就是前 i 个数的中位数。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

ll n;
ll a[MAXN]; // 输入序列

void read_input() {
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
    }
}

void solve() {
    priority_queue<ll> low;                                // 较小的一半，堆顶是这半边的最大值
    priority_queue<ll, vector<ll>, greater<ll>> high;       // 较大的一半，堆顶是这半边的最小值

    for (ll i = 1; i <= n; i++) {
        low.push(a[i]);

        // 保证 low 的最大值不大于 high 的最小值
        if (!high.empty() && low.top() > high.top()) {
            ll t = low.top();
            low.pop();
            high.push(t);
            low.push(high.top());
            high.pop();
        }

        // 保证 low 恰好比 high 多一个元素
        ll want = (i + 1) / 2;
        while ((ll)low.size() > want) {
            high.push(low.top());
            low.pop();
        }

        if (i % 2 == 1) {
            cout << low.top() << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
