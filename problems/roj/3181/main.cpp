/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 最优贸易：正图 SPFA 求最小买价，反图 SPFA 求最大卖价
#include <cstdio>
#include <vector>
using namespace std;

typedef long long ll;

const ll INF = 1LL << 60;

int n, m;
vector<int> xs, ys, zs; // 原始边表：zs = 1 单向，2 双向
vector<int> head, nxt, to;
vector<ll> price, best;
vector<char> inq;

// 链式前向星建图；z=2 的双向边在两个方向各挂一条
void build_graph() {
    int E = (int)xs.size();
    head.assign(n + 1, 0);
    nxt.assign(2 * E + 1, 0);
    to.assign(2 * E + 1, 0);
    int cnt = 1; // 边从 1 号开始编号，head 为 0 表示没有出边
    for (int i = 0; i < E; i++) {
        int u = xs[i], v = ys[i];
        to[cnt] = v; nxt[cnt] = head[u]; head[u] = cnt++;
        if (zs[i] == 2) {
            to[cnt] = u; nxt[cnt] = head[v]; head[v] = cnt++;
        }
    }
}

// 从 start 出发沿边传播路径上价格的极值；mode = 0 取 min（最小买价），1 取 max（最大卖价）
void spfa(int start, ll init, int mode) {
    best.assign(n + 1, init);
    inq.assign(n + 1, 0);
    best[start] = price[start];
    vector<int> q;
    q.push_back(start);
    inq[start] = 1;
    for (int h = 0; h < (int)q.size(); h++) {
        int u = q[h];
        inq[u] = 0;
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            ll nd = mode ? (best[u] > price[v] ? best[u] : price[v])
                         : (best[u] < price[v] ? best[u] : price[v]);
            bool better = mode ? (nd > best[v]) : (nd < best[v]);
            if (better) {
                best[v] = nd;
                if (!inq[v]) {
                    inq[v] = 1;
                    q.push_back(v);
                }
            }
        }
    }
}

int main() {
    if (scanf("%d %d", &n, &m) != 2) {
        return 0;
    }
    price.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &price[i]);
    }
    xs.assign(m, 0); ys.assign(m, 0); zs.assign(m, 0);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &xs[i], &ys[i], &zs[i]);
    }

    // 正图上从 1 做 min：mn[v] = 从 1 走到 v 的路上能买到的最低价
    build_graph();
    spfa(1, INF, 0);
    vector<ll> mn = best;

    // 反图上从 n 做 max：mx[v] = 从 v 走到 n 的路上能卖出的最高价
    for (int i = 0; i < m; i++) {
        int t = xs[i];
        xs[i] = ys[i];
        ys[i] = t;
    }
    build_graph();
    spfa(n, -INF, 1);
    vector<ll> mx = best;

    ll ans = 0; // 买卖都发生在 v：两头都可达才有定义
    bool found = false;
    for (int v = 1; v <= n; v++) {
        if (mn[v] != INF && mx[v] != -INF) {
            ll cand = mx[v] - mn[v];
            if (!found || cand > ans) {
                ans = cand;
                found = true;
            }
        }
    }
    if (!found) {
        ans = 0;
    }
    printf("%lld\n", ans);
    return 0;
}
