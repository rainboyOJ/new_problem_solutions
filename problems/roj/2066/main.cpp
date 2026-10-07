/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:43
 * update_at: 2026-10-06 10:43
 */
// main.cpp：完美的牛栏，二分图最大匹配，匈牙利算法（DFS 增广路）。
// 奶牛为左部点，牛栏为右部点；每个牛栏只容纳一头牛，即求最大匹配数。

#include <cstdio>

typedef long long ll;

const int MAXN = 205; // 最多奶牛数
const int MAXM = 205; // 最多牛栏数

int n, m; // n 头奶牛，m 个牛栏
// 邻接表（链式前向星）：edge_from 不需要，只存边指向的牛栏
int head[MAXN]; // head[cow] = 奶牛 cow 的第一条边编号
int nxt[MAXN * MAXM]; // 同一头奶牛的下一条边编号
int to[MAXN * MAXM];  // 该边指向的牛栏编号
int edge_cnt = 0;     // 边计数器

int match_stall[MAXM]; // match_stall[v] = 占用牛栏 v 的奶牛编号，0 表示空闲
bool visited[MAXM];    // visited[v] = 本轮增广中牛栏 v 是否被访问过

// 加一条边：奶牛 u 喜欢牛栏 v
void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 尝试为奶牛 cow 找增广路：能找到返回 true
bool find_path(int cow) {
    // 枚举奶牛 cow 喜欢的每个牛栏
    for (int e = head[cow]; e != 0; e = nxt[e]) {
        int stall = to[e];
        if (visited[stall])
            continue; // 本轮已访问过，跳过
        visited[stall] = true;
        // 牛栏空闲，或占用它的奶牛能腾挪到其它牛栏，则匹配成功
        if (match_stall[stall] == 0 || find_path(match_stall[stall])) {
            match_stall[stall] = cow;
            return true;
        }
    }
    return false;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        int s;
        scanf("%d", &s); // 第 i 头奶牛喜欢的牛栏数目
        for (int j = 1; j <= s; j++) {
            int stall;
            scanf("%d", &stall);
            add_edge(i, stall);
        }
    }

    int ans = 0; // 最大匹配数
    for (int cow = 1; cow <= n; cow++) {
        // 每轮增广前清空访问标记
        for (int v = 1; v <= m; v++)
            visited[v] = false;
        if (find_path(cow))
            ans++;
    }

    printf("%d\n", ans);
    return 0;
}
