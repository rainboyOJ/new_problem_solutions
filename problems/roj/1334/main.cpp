/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 10:10
 * update_at: 2026-10-05 10:11
 */
#include <iostream>
#include <queue>
using namespace std;

typedef long long ll;

queue<ll> q; // 当前仍在圈内的人，队头为正在报数的人

int main() {
    ll n, m;
    cin >> n >> m;
    for (ll i = 1; i <= n; ++i) q.push(i); // 初始围圈顺序 1~n

    ll cnt = 0; // 当前已报数到第几个
    while (!q.empty()) {
        ll x = q.front();
        q.pop();
        ++cnt;
        if (cnt == m) { // 正好数到第 m 个人，出列输出
            cout << x;
            cnt = 0;
            if (!q.empty()) cout << ' ';
        } else { // 未数到 m，回到队尾等待下一轮
            q.push(x);
        }
    }
    cout << '\n';
    return 0;
}
