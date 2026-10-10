/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 07:39
 * update_at: 2026-10-08 07:39
 */
// main.cpp：查找文献。有向图 X->Y 表示文章 X 引用了文章 Y，
// 从 1 号文章出发，出边按编号升序排序后分别做 DFS / BFS，只输出可达文章。
// DFS 用显式栈模拟递归先序，链状图深度 1e5 也不会爆系统栈。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005; // 文章编号上限 1e5，开 1e5+5 够用

int n, m;              // 文章数、引用关系数（值域 <= 1e6，int 足够）
vector<int> g[MAXN];   // 邻接表：g[u] 存 u 的参考文献（读数后统一升序排序）
int ans[MAXN];         // 遍历序列（最多 n 个数）
bool vis[MAXN];        // 访问标记；DFS 与 BFS 各自重算一次，必须清零复用

// 显式栈的一帧：结点 u，以及"下一个待扩展的出边下标"
struct Frame {
    int u;
    int idx;
};
Frame stk[MAXN]; // 栈深最多 n（链状图）

// 打印一个序列，数字间单空格，行末不加多余空格
void print_seq(int cnt) {
    for (int i = 0; i < cnt; i++) {
        printf("%d%c", ans[i], i + 1 == cnt ? '\n' : ' ');
    }
}

// 从 1 号文章出发的先序 DFS：显式栈严格对应递归写法（访问即输出，回溯靠弹栈）
int dfs() {
    for (int i = 1; i <= n; i++) vis[i] = false;
    int cnt = 0;
    int top = 0;
    vis[1] = true;
    ans[cnt++] = 1;
    stk[top].u = 1;
    stk[top].idx = 0;
    top++;
    while (top > 0) {
        int u = stk[top - 1].u;
        if (stk[top - 1].idx < (int)g[u].size()) {
            int v = g[u][stk[top - 1].idx];
            stk[top - 1].idx++;
            if (!vis[v]) { // 未看过才递归进去，看过就换下一条出边
                vis[v] = true;
                ans[cnt++] = v;
                stk[top].u = v;
                stk[top].idx = 0;
                top++;
            }
        } else {
            top--; // 出边走完，回溯
        }
    }
    return cnt;
}

// 从 1 号文章出发的 BFS：入队时判重，保证每个点只入队一次
int bfs() {
    for (int i = 1; i <= n; i++) vis[i] = false;
    int cnt = 0;
    queue<int> q;
    vis[1] = true;
    q.push(1);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ans[cnt++] = u;
        int sz = g[u].size();
        for (int i = 0; i < sz; i++) {
            int v = g[u][i];
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
    return cnt;
}

int main() {
    if (scanf("%d %d", &n, &m) != 2) return 0;
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        g[x].push_back(y);
    }
    // 题面：能看的文章很多时先看编号较小的那篇 -> 出边升序排序
    for (int i = 1; i <= n; i++) {
        sort(g[i].begin(), g[i].end());
    }

    print_seq(dfs());
    print_seq(bfs());

    return 0;
}
