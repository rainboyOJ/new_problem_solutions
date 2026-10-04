/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 06:19
 * update_at: 2026-10-05 06:19
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005; // 点数上限
const int MAXM = 200005; // 边数上限

int t, n, m;
int head[MAXN];   // 链式前向星头指针，head[u] 为 0 表示没有出边
int nxt[MAXM * 2];
int to_[MAXM * 2];
int eid[MAXM * 2]; // eid[i] 为第 i 条弧对应的边的带符号编号：无向图反向弧为负，有向图为正
bool used[MAXM];   // used[i] 表示第 i 条边是否已被走过
int cur[MAXN];     // cur[u] 当前弧优化：记录 u 下一条要尝试的弧下标

int ans[MAXM];  // 逆序记录的回路边编号
int ans_cnt = 0;

// 加一条 u -> v、边号为 e 的弧
void add_edge(int u, int v, int e) {
    static int cnt = 0;
    cnt++;
    to_[cnt] = v;
    nxt[cnt] = head[u];
    eid[cnt] = e;
    head[u] = cnt;
}

// 非递归 Hierholzer：当前弧推进，退栈时后序记录进入的边，得到逆序回路
void hierholzer(int start) {
    static int stk_u[MAXN * 2]; // 栈里存点
    static int stk_e[MAXM];     // 栈里存进入该点用的边
    int top_u = 0, top_e = 0;

    for (int i = 1; i <= n; i++) cur[i] = head[i];
    stk_u[++top_u] = start;

    while (top_u > 0) {
        int u = stk_u[top_u];
        int e = cur[u];
        if (e != 0) {
            // 该弧对应的边还没走过才走：无向图时双向各占一条弧，用 used[|eid|] 去重
            int id = eid[e];
            int pos = id < 0 ? -id : id;
            cur[u] = nxt[e];
            if (used[pos]) continue;
            used[pos] = true;
            stk_u[++top_u] = to_[e];
            stk_e[++top_e] = id;
        } else {
            top_u--;
            if (top_e > 0) {
                ans_cnt++;
                ans[ans_cnt] = stk_e[top_e];
                top_e--;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        if (t == 1) {
            add_edge(u, v, i);
            add_edge(v, u, -i); // 无向图：反向弧记为负号
        } else {
            add_edge(u, v, i);
        }
    }

    // m == 0 时：没有边，显然可以"一笔画"，输出空方案
    if (m == 0) {
        cout << "YES" << '\n' << '\n';
        return 0;
    }

    // 度数条件：无向图所有点度数为偶数，有向图每点入度等于出度
    bool ok = true;
    if (t == 1) {
        static int deg[MAXN]; // deg[v] 为 v 的度数
        for (int i = 1; i <= n; i++) deg[i] = 0;
        for (int u = 1; u <= n; u++) {
            for (int e = head[u]; e != 0; e = nxt[e]) {
                if (eid[e] > 0) { // 只数正向弧，每条无向边恰好一条，避免双向重复计数
                    deg[u]++;
                    deg[to_[e]]++;
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            if (deg[i] % 2 != 0) ok = false;
        }
    } else {
        static int outd[MAXN], ind[MAXN]; // 出度与入度
        for (int i = 1; i <= n; i++) outd[i] = ind[i] = 0;
        for (int u = 1; u <= n; u++) {
            for (int e = head[u]; e != 0; e = nxt[e]) {
                outd[u]++;
                ind[to_[e]]++;
            }
        }
        for (int i = 1; i <= n; i++) {
            if (ind[i] != outd[i]) ok = false;
        }
    }
    if (!ok) {
        cout << "NO" << '\n';
        return 0;
    }

    // 从任意一个有边的点出发
    int start = 1;
    for (int i = 1; i <= n; i++) {
        if (head[i] != 0) {
            start = i;
            break;
        }
    }
    hierholzer(start);

    // 走过的边数不足 m：图里有边的部分不连通
    if (ans_cnt != m) {
        cout << "NO" << '\n';
        return 0;
    }

    cout << "YES" << '\n';
    // ans 里是逆序回路，倒序输出即为正序
    for (int i = m; i >= 1; i--) {
        cout << ans[i] << (i == 1 ? '\n' : ' ');
    }
    return 0;
}
