/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 06:12
 * update_at: 2026-10-05 06:12
 */
// main.cpp：接水问题，用最小堆维护各龙头累计接水量。
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

typedef long long ll;

// 小根堆：存放每个正在供水的龙头的累计接水量，堆顶就是最早空出来的龙头
priority_queue<ll, vector<ll>, greater<ll> > loads;

int main() {
    ll n, m;
    scanf("%lld %lld", &n, &m);
    ll ans = 0;
    for (ll i = 1; i <= n; i++) {
        ll w;
        scanf("%lld", &w);
        if (i <= m) {
            // 开始时前 m 名同学各占一个龙头（n < m 时只占 n 个龙头）
            loads.push(w);
        } else {
            // 队首同学接到"最早空出的龙头"上：换掉堆顶的累计量
            ll t = loads.top();
            loads.pop();
            loads.push(t + w);
        }
    }
    // 龙头不空转，总时间就是各龙头累计接水量的最大值
    while (!loads.empty()) {
        ans = max(ans, loads.top());
        loads.pop();
    }
    printf("%lld\n", ans);
    return 0;
}
