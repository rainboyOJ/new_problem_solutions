/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 观光旅游：01 分数规划 + SPFA 判负环
#include <cstdio>
#include <vector>
using namespace std;

typedef long long ll;

int L, P;
vector<ll> fun;      // fun[i]：景点 i 的乐趣值
vector<int> eu, ev, et;
vector<vector<int> > out_edges; // out_edges[u]：u 的出边编号，按输入顺序
vector<double> dis;
vector<int> relax;
vector<char> inq;

// 图（边权为 mid*t - f）中是否存在负环
bool has_neg_cycle(double mid) {
    // 超级源点连向所有点：dis 初始全 0，所有点一开始都在队列里
    dis.assign(L + 1, 0.0);
    relax.assign(L + 1, 0);
    inq.assign(L + 1, 1);
    vector<int> q;
    for (int i = 1; i <= L; i++) {
        q.push_back(i);
    }
    for (int qh = 0; qh < (int)q.size(); qh++) {
        int u = q[qh];
        inq[u] = 0;
        for (int t = 0; t < (int)out_edges[u].size(); t++) {
            int e = out_edges[u][t];
            int v = ev[e];
            double nd = dis[u] + (mid * et[e] - fun[v]); // 点权 f 记在边的终点上
            if (nd < dis[v]) {
                dis[v] = nd;
                relax[v]++;
                if (relax[v] >= L) { // 一个点被松弛 n 次 ⇒ 存在负环
                    return true;
                }
                if (!inq[v]) {
                    inq[v] = 1;
                    q.push_back(v);
                }
            }
        }
    }
    return false;
}

int main() {
    if (scanf("%d %d", &L, &P) != 2) {
        return 0;
    }
    fun.assign(L + 1, 0);
    for (int i = 1; i <= L; i++) {
        scanf("%lld", &fun[i]);
    }
    eu.assign(P, 0); ev.assign(P, 0); et.assign(P, 0);
    out_edges.assign(L + 1, vector<int>());
    for (int i = 0; i < P; i++) {
        scanf("%d %d %d", &eu[i], &ev[i], &et[i]);
        out_edges[eu[i]].push_back(i);
    }

    // 二分比值 mid：有负环 ⇔ 存在环的 Σf/Σt > mid
    double lo = 0.0, hi = 1000.0;
    for (int it = 0; it < 30; it++) {
        double mid = (lo + hi) / 2;
        if (has_neg_cycle(mid)) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    printf("%.2f\n", hi);
    return 0;
}
