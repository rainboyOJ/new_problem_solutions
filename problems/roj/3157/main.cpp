/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <cstdio>
#include <algorithm>
#include <deque>
using namespace std;

typedef long long ll;

const int MAXN = 16005;
const int MAXM = 105;

struct Painter {
    ll limit; // L：最多连续粉刷的木板数
    ll price; // P：每块木板的报酬
    ll must;  // S：必须覆盖的木板位置
};

ll n, m;
Painter painter[MAXM]; // 全部工匠，按 S 升序排列后依次加入 DP
ll best[MAXN];         // best[j]：已加入的工匠在「前 j 块木板」上能拿到的最大报酬
ll cur[MAXN];          // 加入当前工匠后的新报酬表

bool cmp_must(const Painter &a, const Painter &b) { return a.must < b.must; }

// 让一个工匠（必刷 must、一次最多刷 limit 块、每块 price）加入后，更新报酬表。
// 新表先继承 best（这个工匠不刷，或刷的段不含第 j 块）；另一种情况是他刷的段右端正好是 j，
// 左端为 k，需满足 k <= must（段要盖住必刷的那块）和 k >= j-limit+1（长度受限），
// 收益 best[k-1] + (j-k+1)*price = price*j + (best[m] - price*m)，其中 m = k-1。
// m 的窗口是 [j-limit, must-1]，j 增大时窗口右端固定、左端右移，用单调队列维护窗口最值。
void add_painter(const Painter &p) {
    for (ll j = 0; j <= n; j++) cur[j] = best[j];
    deque<pair<ll, ll> > win; // (best[m] - price*m, m)，值从队首到队尾单调递减
    for (ll t = 0; t < p.must; t++) {
        ll value = best[t] - p.price * t;
        while (!win.empty() && win.back().first <= value) win.pop_back();
        win.push_back(make_pair(value, t));
    }
    for (ll j = p.must; j <= n; j++) {
        while (!win.empty() && win.front().second < j - p.limit) win.pop_front();
        if (!win.empty()) {
            ll brushed = win.front().first + p.price * j; // 这个工匠刷 [k, j] 的收益
            if (brushed > cur[j]) cur[j] = brushed;
        }
        if (cur[j - 1] > cur[j]) cur[j] = cur[j - 1]; // 「前 j 块」可退化成「前 j-1 块」
    }
    for (ll j = 0; j <= n; j++) best[j] = cur[j];
}

int main() {
    scanf("%lld%lld", &n, &m);
    for (ll i = 0; i < m; i++)
        scanf("%lld%lld%lld", &painter[i].limit, &painter[i].price, &painter[i].must);
    // 按 S 排序后，每个工匠刷的段都排在后面工匠要盖住的 S 之前，逐行 DP 才成立
    sort(painter, painter + m, cmp_must);
    for (ll i = 0; i < m; i++) add_painter(painter[i]);
    printf("%lld\n", best[n]);
    return 0;
}
