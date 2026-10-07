/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:15
 * update_at: 2026-10-06 14:15
 */

// main.cpp：把奶牛看成 SPF 轴上的区间、防晒霜看成带重数的点，求最大匹配数。
// 做法：防晒霜按 SPF 升序发放，用小根堆维护待选奶牛，优先满足 maxSPF 最小（最快过期）的奶牛。

#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>

typedef long long ll;

const int MAXN = 2505;

int C, L;
std::pair<ll, ll> cow[MAXN];   // cow[i] = {minSPF, maxSPF}，按 minSPF 升序排序
std::pair<ll, ll> bottle[MAXN]; // bottle[j] = {SPF, cover}，按 SPF 升序排序

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> C >> L;
    for (int i = 0; i < C; i++)
        std::cin >> cow[i].first >> cow[i].second;
    for (int j = 0; j < L; j++)
        std::cin >> bottle[j].first >> bottle[j].second;

    // 奶牛按 minSPF 升序：扫到 SPF=s 时，minSPF<=s 的奶牛刚好全部解锁
    std::sort(cow, cow + C);
    // 防晒霜按 SPF 升序依次发放
    std::sort(bottle, bottle + L);

    // 小根堆存待选奶牛的 maxSPF：堆顶是可行集合最小（最急）的那头
    std::priority_queue<ll, std::vector<ll>, std::greater<ll> > pending;
    int next_cow = 0; // 下一头等待入堆的奶牛下标，只前进不后退
    ll ans = 0;

    for (int j = 0; j < L; j++) {
        ll spf = bottle[j].first;
        ll cover = bottle[j].second;

        // 把 minSPF <= s 的奶牛压入堆，每头牛只入堆一次
        while (next_cow < C && cow[next_cow].first <= spf) {
            pending.push(cow[next_cow].second);
            next_cow++;
        }
        // 先清掉已经过期的奶牛：maxSPF < s 连这瓶都接受不了，以后更没机会
        while (!pending.empty() && pending.top() < spf)
            pending.pop();
        // 每瓶优先发给最急（maxSPF 最小）的奶牛
        while (cover > 0 && !pending.empty()) {
            pending.pop();
            cover--;
            ans++;
        }
    }

    std::cout << ans << std::endl;
    return 0;
}
