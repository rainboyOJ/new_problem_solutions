/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 17:29
 * update_at: 2026-10-07 17:33
 */
// main.cpp：棋盘问题，无限棋盘上按 n 个向量走，BFS 求最少步数。
// 与 main.py 同一算法：只保留「贴着起点-终点连线」的走廊内状态（宽度为单步最大长度），
// 另加起终点附近的小球兜底，用手写开散列判重。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXM = 1000000;   // 走廊内的状态数上界（实测最大约 41 万）
const int PRIME = 999983;   // 开散列取模用的质数

int vecx[12], vecy[12];     // 可走的 n 个向量
int n;                      // 向量个数
ll sx, sy, tx, ty;          // 起点与终点坐标
ll D;                       // 单步最大长度的平方 max(x^2 + y^2)
ll A, B, C;                 // 起点-终点连线方程 A*x + B*y + C = 0

struct Entry {              // 散列桶里的一个状态：坐标 + 同桶下一条链
    int x, y, nxt;
};
Entry table[MAXM];
int head[PRIME];            // 每个桶的链表头
int idx;                    // 已插入的状态数

static inline ll sqr(ll v) { return v * v; }

static inline int hashxy(ll x, ll y) {
    ll h = ((x << 16) ^ y) % PRIME;
    if (h < 0) h += PRIME;
    return (int)h;
}

// 插入状态，返回 false 表示此前已经访问过
static inline bool insert_state(ll x, ll y) {
    int h = hashxy(x, y);
    for (int e = head[h]; e != -1; e = table[e].nxt) {
        if (table[e].x == x && table[e].y == y) return false;
    }
    table[idx].x = (int)x;
    table[idx].y = (int)y;
    table[idx].nxt = head[h];
    head[h] = idx++;
    return true;
}

// 点 (x,y) 是否值得扩展：靠近起终点，或落在连线走廊内且投影不越过头尾
static inline bool useful(ll x, ll y) {
    if (sqr(x - sx) + sqr(y - sy) <= D) return true;
    if (sqr(x - tx) + sqr(y - ty) <= D) return true;
    if ((tx - sx) * (x - sx) + (ty - sy) * (y - sy) < 0) return false;   // 落到起点身后
    if ((sx - tx) * (x - tx) + (sy - ty) * (y - ty) < 0) return false;   // 越过了终点
    return sqr(A * x + B * y + C) <= D * (sqr(A) + sqr(B));              // 到连线距离 <= sqrt(D)
}

// 按层 BFS，第一次弹出终点时的层号就是答案；不可达返回 -1
static int bfs() {
    memset(head, -1, sizeof(head));
    idx = 0;
    queue<pair<int, int>> q;
    q.push({(int)sx, (int)sy});
    insert_state(sx, sy);
    int step = 0;
    while (!q.empty()) {
        int cnt = (int)q.size();
        while (cnt--) {
            int cx = q.front().first, cy = q.front().second;
            q.pop();
            if (cx == tx && cy == ty) return step;
            for (int i = 0; i < n; i++) {
                int nx = cx + vecx[i], ny = cy + vecy[i];
                if (useful(nx, ny) && insert_state(nx, ny)) q.push({nx, ny});
            }
        }
        step++;
    }
    return -1;
}

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        scanf("%lld %lld %lld %lld", &sx, &sy, &tx, &ty);
        scanf("%d", &n);
        D = 0;
        bool allPos = true;                  // 题面保证分量 > 0，这里仍留一手兼容负数
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &vecx[i], &vecy[i]);
            D = max(D, sqr(vecx[i]) + sqr(vecy[i]));
            if (vecx[i] < 0 || vecy[i] < 0) allPos = false;
        }
        A = ty - sy;
        B = sx - tx;
        C = sy * tx - sx * ty;
        if (allPos && (tx < sx || ty < sy)) {   // 分量非负时坐标只增不减
            puts("IMPOSSIBLE");
            continue;
        }
        int ans = bfs();
        if (ans < 0) puts("IMPOSSIBLE");
        else printf("%d\n", ans);
    }
    return 0;
}
