/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 18:13
 * update_at: 2026-10-07 18:13
 */
// ROJ 1715《公交旅行》
//
// 题意：n 个站台、m 条环形公交线路。第 i 条线路长 t_i，0 时刻第 i 辆车在 s_i[1]，
//   之后每时刻开到线路里的下一站，到终点后下一时刻回到起点（位置按 (j+1) mod t_i 循环）。
//   0 时刻我在站台 1，与某辆车同处一站即可上车、任意时刻可下车，上下车不耗时，
//   一次只能坐一辆车但可换乘。求最早到达站台 2..n 的时刻，不可达输出 -1。
//
// 建模：线路 i 的车只在时刻 T ≡ j (mod t_i) 出现在站台 s_i[j]（下标 0 起）。
//   若我在 d 时刻位于站台 s_i[j]，最早可于 T = d + ((j - d) mod t_i) 上车，
//   T+1 时刻到达 s_i[(j+1) mod t_i]。由于"早到不会更差"（多等不花代价），
//   在站台图上跑 Dijkstra 即可，边权在松弛时实时计算、不必显式建图。
//
// 复杂度：时间 O(Σt_i · log n)，空间 O(n + Σt_i)。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

static const ll INF = (ll)4e18;  // 大于任何可能到达时刻

// ---------- 快速读入 ----------
static char ibuf[1 << 22];
static int ilen = 0, ipos = 0;

static inline int gc() {
    if (ipos == ilen) {
        ilen = (int)fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen == 0) return -1;
    }
    return ibuf[ipos++];
}

static inline int readInt() {
    int c = gc();
    while (c != -1 && (c < '0' || c > '9')) c = gc();
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return x;
}

int n, m;                    // 站台数、线路数
vector<int> per;             // per[i] = t_i，线路 i 的周期（也是线路长度）
vector<int> off;             // off[i] = 线路 i 在 pool 中的起始下标
vector<int> pool;            // 所有线路的站台顺序拼接

vector<int> head;            // 站台 v 的邻接表起点（CSR）
vector<int> entR, entP;      // 每个 (线路号, 线路内位置) 条目

vector<ll> dist;             // dist[v] = 最早到达站台 v 的时刻
vector<char> done;

// 把站台 v 上出现的所有 (线路号, 位置) 建成 CSR 邻接表
void buildAt() {
    head.assign(n + 2, 0);
    for (size_t k = 0; k < pool.size(); k++) head[pool[k] + 1]++;
    for (int v = 1; v <= n; v++) head[v + 1] += head[v];
    vector<int> cur(head.begin(), head.end());
    entR.assign(pool.size(), 0);
    entP.assign(pool.size(), 0);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < per[i]; j++) {
            int v = pool[off[i] + j];
            int slot = cur[v]++;
            entR[slot] = i;
            entP[slot] = j;
        }
    }
}

// 站台图上的 Dijkstra：边权（等车 + 坐一站）在松弛时按相位实时算
void dijkstra() {
    dist.assign(n + 1, INF);
    done.assign(n + 1, 0);
    dist[1] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > pq;
    pq.push(make_pair((ll)0, 1));
    while (!pq.empty()) {
        pair<ll, int> top = pq.top();
        pq.pop();
        ll d = top.first;
        int v = top.second;
        if (done[v]) continue;
        done[v] = 1;
        for (int k = head[v]; k < head[v + 1]; k++) {
            int r = entR[k], p = entP[k];
            int t = per[r];
            ll board = d + (ll)((p - d) % t + t) % t;  // 等到相位 p 的最早时刻
            int nxt = pool[off[r] + (p + 1) % t];      // 再坐一站到的地方
            if (board + 1 < dist[nxt]) {
                dist[nxt] = board + 1;
                pq.push(make_pair(dist[nxt], nxt));
            }
        }
    }
}

int main() {
    n = readInt();
    m = readInt();
    per.resize(m);
    off.resize(m);
    pool.reserve(2 << 18);
    for (int i = 0; i < m; i++) {
        int ti = readInt();
        per[i] = ti;
        off[i] = (int)pool.size();
        for (int j = 0; j < ti; j++) pool.push_back(readInt());
    }
    buildAt();
    dijkstra();
    // 输出站台 2..n 的最早到达时刻，不可达输出 -1
    for (int v = 2; v <= n; v++) {
        if (v > 2) putchar(' ');
        if (dist[v] >= INF) fputs("-1", stdout);
        else printf("%lld", dist[v]);
    }
    putchar('\n');
    return 0;
}
