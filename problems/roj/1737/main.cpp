/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 20:32
 * update_at: 2026-10-07 20:32
 */

// 一本通 1737《邮递员》正式解：
//   回路是闭合的，按环状顺序读它的边序列 e_1..e_m（succ(e_i) = e_{i+1}，下标模 m）。
//   每个片段 v1..vk 要求 succ((v_j,v_{j+1})) = (v_{j+1},v_{j+2})，于是片段把若干条边
//   "粘"成一串：每条边至多被逼出一个后继、一个前驱，被迫接两个就无解。
//   粘合关系是部分单射，必然分解成「链」和「环」：
//     · 环——它在 succ 里已经自成闭合块，而 succ 是覆盖全部 m 条边的唯一大环，
//       所以要么不存在环，要么这个环就吞掉全部边（此时回路被唯一确定，只需路口 1 在环上）；
//     · 链——整条链在回路里必须连着走，收缩成一条「超边」，只保留链首起点与链尾终点。
//   收缩后的多重图上存在经过每条超边一次的闭合路线 ⟺ 逐点入度=出度 且带边的点弱连通；
//   路线可以旋转到任意一个被访问到的点起头，所以还要保证路口 1 真的在路线上。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 50005;   // 岔路口数上限
const int MAXM = 200005;  // 街道数上限

struct Edge {
    int u;  // 街道起点
    int v;  // 街道终点
};

struct KeyedEdge {
    ll key;  // 街道 (a,b) 的唯一编码 a*(n+1)+b，用于二分查找
    int id;  // 街道编号
};

bool operator<(const KeyedEdge& x, const KeyedEdge& y) {
    return x.key < y.key;
}

Edge edge[MAXM];
KeyedEdge keyed[MAXM];

ll cntEdge;           // 街道条数 m，findEdge 的二分右界
int nxtEdge[MAXM];    // nxtEdge[i] = 被片段逼着紧接在街道 i 后面走的那条街道，-1 表示没有
int prvEdge[MAXM];    // prvEdge[i] = 被逼着紧排在街道 i 前面的那条街道，-1 表示没有
int stamp[MAXM];      // stamp[i] == 当前片段编号，说明街道 i 已在本片段里用过（同弧走两次无解）
int unitOfEdge[MAXM]; // 街道 i 归属的超边编号，-1 表示还没归属
int unitTail[MAXM];   // 超边的起点
int unitHead[MAXM];   // 超边的终点
int din[MAXN];        // 收缩图上每个点的入度
int dout[MAXN];       // 收缩图上每个点的出度
int deg1;             // 路口 1 在原图里的关联度数，为 0 时邮递员寸步难行
char vis[MAXN];       // 弱连通搜索的访问标记，只有 0/1，用 char 省内存

vector<int> adj[MAXN];  // 收缩图邻接表（无向，只用来判弱连通）

// 逐字符快读：最坏一份输入接近 6MB、上百万个整数，格式化读入太慢
ll readInt() {
    int c = getchar();
    while (c != -1 && c <= ' ') c = getchar();
    if (c == -1) return -1;
    ll x = 0;
    while (c > ' ') {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    return x;
}

// 在按 key 排好序的街道表里二分查找编码为 key 的街道，找不到返回 -1
int findEdge(ll key) {
    int lo = 0, hi = (int)cntEdge - 1, res = -1;
    while (lo <= hi) {
        int mid = (lo + hi) >> 1;
        if (keyed[mid].key == key) {
            res = keyed[mid].id;
            break;
        }
        if (keyed[mid].key < key) lo = mid + 1;
        else hi = mid - 1;
    }
    return res;
}

int main() {
    // nxtEdge / prvEdge / unitOfEdge 用 -1 当"不存在"的哨兵，
    // 全局数组默认全是 0，必须先整体置成 -1
    memset(nxtEdge, -1, sizeof(nxtEdge));
    memset(prvEdge, -1, sizeof(prvEdge));
    memset(unitOfEdge, -1, sizeof(unitOfEdge));

    ll n = readInt();
    ll m = readInt();
    cntEdge = m;
    for (ll i = 0; i < m; i++) {
        ll a = readInt();
        ll b = readInt();
        edge[i].u = a;  // a,b ≤ n ≤ 50000
        edge[i].v = b;
        if (a == 1 || b == 1) deg1++;
        keyed[i].key = a * (n + 1) + b;  // 数据保证 (a,b) 只出现一次，编码不冲突
        keyed[i].id = i;
    }
    sort(keyed, keyed + m);

    ll t = readInt();  // 片段数
    for (ll f = 1; f <= t; f++) {
        ll k = readInt();
        if (k < 1) continue;
        ll prevVertex = readInt();
        int prevEdgeId = -1;
        for (ll i = 1; i < k; i++) {
            ll cur = readInt();
            int e = findEdge(prevVertex * (n + 1) + cur);  // 片段要求走的这条街道
            if (e == -1) {                                 // 片段引用了不存在的街道
                printf("NIE\n");
                return 0;
            }
            if (stamp[e] == f) {  // 同一条街道在一个片段里要走两次，回路做不到
                printf("NIE\n");
                return 0;
            }
            stamp[e] = f;
            if (prevEdgeId != -1) {
                // 街道 prevEdgeId 后面被迫接两条不同的街道，或街道 e 前面被迫接两条
                bool conflict = (nxtEdge[prevEdgeId] != -1 && nxtEdge[prevEdgeId] != e) ||
                                (prvEdge[e] != -1 && prvEdge[e] != prevEdgeId);
                if (conflict) {
                    printf("NIE\n");
                    return 0;
                }
                nxtEdge[prevEdgeId] = e;
                prvEdge[e] = prevEdgeId;
            }
            prevEdgeId = e;
            prevVertex = cur;
        }
    }

    // 分解粘合关系：先从每条"没有被逼出前驱"的街道出发走完整条链
    int unitCnt = 0;
    for (int i = 0; i < (int)m; i++) {
        if (prvEdge[i] != -1 || unitOfEdge[i] != -1) continue;
        int e = i;
        while (true) {
            unitOfEdge[e] = unitCnt;
            if (nxtEdge[e] == -1) break;
            e = nxtEdge[e];
        }
        unitTail[unitCnt] = edge[i].u;  // 链首所在点给一条出边
        unitHead[unitCnt] = edge[e].v;  // 链尾所在点给一条入边，这一对端点就是收缩出的超边
        unitCnt++;
    }

    // 剩下的街道每条都被逼出了后继，它们的 nxt 构成闭合轨道（succ 的闭合块）。
    // succ 必须是覆盖全部 m 条边的单环，所以闭合轨道只能有一条且吞掉全部边；
    // 存在两条轨道、或轨道之外还有链时，轨道会在自己的边集内绕圈，接不上其余街道。
    int orbitCnt = 0, orbitEdges = 0;
    for (int i = 0; i < (int)m; i++) {
        if (unitOfEdge[i] != -1) continue;
        orbitCnt++;
        if (orbitCnt > 1) {  // 已经出现第二条轨道，拼不成一条回路
            printf("NIE\n");
            return 0;
        }
        int e = i;
        while (true) {
            unitOfEdge[e] = unitCnt;
            orbitEdges++;
            e = nxtEdge[e];
            if (e == -1 || e == i) break;
        }
        unitCnt++;
    }
    if (orbitCnt > 0) {
        // 整张图就是这一条闭合回路，回路已被唯一确定：路口 1 在这条回路上即可起头
        printf(orbitEdges == (int)m && deg1 > 0 ? "TAK\n" : "NIE\n");
        return 0;
    }

    // 全是链：收缩成超边后，只给两端点加度数（链中间被穿过的点进一次出一次，天然平衡）
    for (int i = 0; i < unitCnt; i++) {
        int a = unitTail[i], b = unitHead[i];
        dout[a]++;
        din[b]++;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int v = 1; v <= (int)n; v++) {
        if (din[v] != dout[v]) {  // 有向图存在欧拉回路的必要条件
            printf("NIE\n");
            return 0;
        }
    }

    // 弱连通：带边的点要落在同一个连通块里，否则那些街道接不进同一条回路
    static int que[MAXN];
    int qh = 0, qt = 0;
    int start = 1;
    for (int v = 1; v <= (int)n; v++)
        if (din[v] > 0 || dout[v] > 0) { start = v; break; }
    vis[start] = 1;
    que[qt++] = start;
    while (qh < qt) {
        int u = que[qh++];
        for (size_t j = 0; j < adj[u].size(); j++) {
            int w = adj[u][j];
            if (!vis[w]) {
                vis[w] = 1;
                que[qt++] = w;
            }
        }
    }
    for (int v = 1; v <= (int)n; v++) {
        if ((din[v] > 0 || dout[v] > 0) && !vis[v]) {
            printf("NIE\n");
            return 0;
        }
    }
    // 路线可以旋转到任意一个被访问过的点起头，所以只要路口 1 关联着街道就一定能从 1 出发
    printf(deg1 > 0 || m == 0 ? "TAK\n" : "NIE\n");
    return 0;
}
