/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 11:32
 * update_at: 2026-10-06 11:32
 */
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef long long ll;

int n;
ll total; // 最小总代价

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    priority_queue<ll, vector<ll>, greater<ll> > pq; // 小根堆维护当前各堆重量
    for (int i = 1; i <= n; ++i) {
        ll x;
        cin >> x;
        pq.push(x);
    }

    // 每次取出最小的两堆合并，代价累加；共 n-1 次合并
    for (int i = 1; i <= n - 1; ++i) {
        ll a = pq.top(); pq.pop();
        ll b = pq.top(); pq.pop();
        ll c = a + b;
        total += c;
        pq.push(c);
    }

    cout << total << "\n";
    return 0;
}
