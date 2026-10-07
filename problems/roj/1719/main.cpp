/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 18:50
 * update_at: 2026-10-07 18:50
 */
// main.cpp：过河（一本通 · 高手训练 1719）。
// 可行走集合 = 直线 y=0、直线 y=W 与买下的若干圆盘（含边界与内部）。
// 圆心必须放在某个木桩上，圆盘可以伸出河面（y<0 或 y>W）。
// 两圆盘能互相走到 ⇔ 圆心距 d <= r1 + r2（相切/相交即可）；
// 圆盘触底 ⇔ Y <= R，触顶 ⇔ W - Y <= R。
// 于是问题化成"点权（圆盘价格）最短路"：节点 = (木桩, 圆盘种类)，节点权 = 圆盘价格，
// 所有触底的圆盘是源点（以 0 为初始代价），任意触顶的圆盘是终点。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 255;      // 木桩数量上限，题面 N <= 250
const int MAXM = 255;      // 圆盘种类上限，题面 M <= 250
const ll INF = 4000000000000000000LL;   // 最短路无穷大，远大于任何可行花费（<= 250 * 10^6）

// 一根木桩：圆心只能放在这里，坐标 (x, y)
struct Pile {
    ll x;
    ll y;
};

// 一种圆盘：半径 r、单价 c
struct Disk {
    ll r;
    ll c;
};

// 堆中元素：停在木桩 pile 上、用的是第 disk 种圆盘时的总花费 cost
struct State {
    ll cost;
    ll pile;
    ll disk;
    // priority_queue 默认大根堆，这里反向比较，得到按 cost 的小根堆
    bool operator<(const State &other) const { return cost > other.cost; }
};

int pileCnt;                // 木桩数 N
int diskTypeCnt;            // 读入的圆盘种类数 M
ll riverW;                  // 河的宽度 W
ll typeCnt;                 // 压缩后保留下来的圆盘种类数（Pareto 前沿长度），也当"种类下标"的上界用
Pile pile[MAXN];            // 木桩
Disk disk[MAXM];            // 保留的圆盘，半径升序、价格随之严格升序
ll pileDist[MAXN][MAXN];    // pileDist[i][k] = 木桩 i 与木桩 k 的圆心距向上取整（整数比较，免浮点误差）
ll dist[MAXN][MAXM];        // dist[i][a]：从地面一路走到"停在木桩 i 上的第 a 种圆盘"的最小花费
ll frontier[MAXN];          // 木桩 k 上下标 >= frontier[k] 的圆盘已定最短路，[0, frontier[k]) 还待松弛

priority_queue<State> pq;   // 堆优化 Dijkstra 的优先队列

// 返回最小的整数 r >= 0 使 r*r >= s，即 ceil(sqrt(s))；圆心距全程用整数表示
ll ceil_sqrt(ll s) {
    if (s <= 0) return 0;
    ll r = sqrtl(s);        // 先取浮点近似，下面两个 while 把它修正成精确的整数开方
    while (r > 0 && (r - 1) * (r - 1) >= s) r--;
    while (r * r < s) r++;
    return r;
}

// 读入 M 种圆盘并压缩成 Pareto 前沿：半径升序、价格严格升序。
// "半径更大且价格不更高"的种类可以完全替代另一种（够得更远、还更便宜），故只保留不被支配的。
void read_disks() {
    map<ll, ll> cheapest;   // 半径 -> 该半径下的最低价格，只为同半径去重
    for (int i = 0; i < diskTypeCnt; i++) {
        ll radius, cost;
        scanf("%lld %lld", &radius, &cost);
        map<ll, ll>::iterator it = cheapest.find(radius);
        if (it == cheapest.end() || cost < it->second) cheapest[radius] = cost;
    }
    typeCnt = 0;
    ll floor = INF;         // 已保留种类（半径都比当前这个大）中的最低价格
    for (map<ll, ll>::reverse_iterator it = cheapest.rbegin(); it != cheapest.rend(); ++it) {
        if (it->second < floor) {   // 半径更小却更便宜，才没被"更大更便宜的盘"支配
            disk[typeCnt].r = it->first;
            disk[typeCnt].c = it->second;
            typeCnt++;
            floor = it->second;
        }
    }
    reverse(disk, disk + typeCnt);  // 翻成半径升序，价格随之升序
}

// 二分出第一个半径 >= need 的种类下标：半径表升序，故"半径够用"的种类恰好是一段后缀
ll lower_bound_radius(ll need) {
    ll lo = 0, hi = typeCnt;    // 答案落在 [lo, hi]，hi 表示"没有种类够用"
    while (lo < hi) {
        ll mid = (lo + hi) / 2;
        if (disk[mid].r >= need) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

// 用花费 base 一次性松弛木桩 k 上尚未定最短路的圆盘 [idx, frontier[k])。
// 每次出堆的 base 单调不减，而松弛结果 base + c 对 base 单调，
// 所以每个 (木桩, 圆盘) 状态第一次被覆盖时拿到的就是它的最终最短路。
void relax_pile(ll k, ll idx, ll base) {
    for (ll t = idx; t < frontier[k]; t++) {
        dist[k][t] = base + disk[t].c;
        State cur;
        cur.cost = dist[k][t];
        cur.pile = k;
        cur.disk = t;
        pq.push(cur);
    }
    frontier[k] = idx;
}

int main() {
    int testCnt;
    if (scanf("%d", &testCnt) != 1) return 0;

    while (testCnt--) {
        scanf("%d %d %lld", &pileCnt, &diskTypeCnt, &riverW);
        for (int i = 0; i < pileCnt; i++) scanf("%lld %lld", &pile[i].x, &pile[i].y);
        read_disks();

        // 圆心距预处理：ceil(两点欧氏距离)。d <= r1 + r2 等价于 ceil(d) <= r1 + r2
        for (int i = 0; i < pileCnt; i++) {
            for (int k = 0; k < pileCnt; k++) {
                ll dx = pile[i].x - pile[k].x;
                ll dy = pile[i].y - pile[k].y;
                pileDist[i][k] = ceil_sqrt(dx * dx + dy * dy);
            }
        }

        while (!pq.empty()) pq.pop();
        for (int k = 0; k < pileCnt; k++) {
            frontier[k] = typeCnt;                  // 一开始所有圆盘都没定最短路
            for (ll t = 0; t < typeCnt; t++) dist[k][t] = INF;
        }

        // 源点：能触底的圆盘（Y_k <= R），代价就是这块圆盘的价格
        for (int k = 0; k < pileCnt; k++) relax_pile(k, lower_bound_radius(pile[k].y), 0);

        ll ans = -1;
        while (!pq.empty()) {
            State cur = pq.top();
            pq.pop();
            if (cur.cost != dist[cur.pile][cur.disk]) continue;
            if (disk[cur.disk].r >= riverW - pile[cur.pile].y) {   // 这块圆盘触顶了
                ans = cur.cost;
                break;                                             // 出堆顺序单调不减，首次触顶即最优
            }
            for (int k = 0; k < pileCnt; k++) {
                if (frontier[k] == 0) continue;                    // 木桩 k 上已无可松弛的圆盘
                // 从当前圆盘跳到木桩 k：需要半径 >= 圆心距 - R_cur，仍是一段后缀
                ll idx = lower_bound_radius(pileDist[cur.pile][k] - disk[cur.disk].r);
                if (idx < frontier[k]) relax_pile(k, idx, cur.cost);
            }
        }

        if (ans < 0) printf("impossible\n");
        else printf("%lld\n", ans);
    }
    return 0;
}
