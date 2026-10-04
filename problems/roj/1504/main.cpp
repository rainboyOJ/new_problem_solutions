/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:12
 * update_at: 2026-10-05 05:12
 */

// 1504 Word Rings：首尾两位字母缩点 + 0/1 分数规划 + DFS-SPFA 判正权环。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXV = 676;        // 顶点：26*26 = 676 个两位字母组合
const int MAXE = 460000;     // 边：去重后最多 676*676 ≈ 4.6e5 条
const double EPS = 1e-9;

int n;
char s[1005];

// 链式前向星存图
int head[MAXV], nxt[MAXE], to[MAXE], edge_cnt = 0;
double w[MAXE]; // 边权：字符串长度减去二分的 mid，读入时存原始长度

// DFS-SPFA 判正环需要的全局状态
double dist[MAXV];
bool in_stack[MAXV]; // 该点是否在当前递归栈上

// 把字符串的两位字母映射成 0..675 的顶点编号
// pos 取 0 表示前两位，取 len-2 表示末两位
int encode_pair(int pos) {
    return (s[pos] - 'a') * 26 + (s[pos + 1] - 'a');
}

// 加一条 u -> v、原始长度为 len 的有向边（判环时实际边权为 len - mid）
void add_edge(int u, int v, double len) {
    edge_cnt++;
    to[edge_cnt] = v;
    w[edge_cnt] = len;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 一组数据的建图：读入 n 个字符串，重边只保留最长的一条
// 返回边数；若所有串长度都小于 2 则返回 0（无法构成环）
int build_graph() {
    edge_cnt = 0;
    memset(head, 0, sizeof(head));
    // best[u][v]：当前 (u,v) 之间最长串的长度，0 表示还没有边
    static int best[MAXV][MAXV];
    memset(best, 0, sizeof(best));

    for (int i = 1; i <= n; i++) {
        scanf("%s", s);
        int len = strlen(s);
        if (len < 2) continue; // 长度小于 2 的串没有首尾两位字母，无法参与连接
        int u = encode_pair(0);
        int v = encode_pair(len - 2);
        if (len > best[u][v]) best[u][v] = len;
    }

    for (int u = 0; u < MAXV; u++) {
        for (int v = 0; v < MAXV; v++) {
            if (best[u][v] > 0) add_edge(u, v, best[u][v]);
        }
    }
    return edge_cnt;
}

// DFS 版 SPFA：从 u 出发找权值和大于 0 的环
// 命中正在递归栈上的点（in_stack[v] == true）说明闭合出一个正权环
// 找到正环立即层层返回 true，在"存在正环"的判定下效率很高
bool dfs_spfa(int u, double mid) {
    in_stack[u] = true;
    for (int i = head[u]; i != 0; i = nxt[i]) {
        int v = to[i];
        if (dist[u] + w[i] - mid > dist[v] + EPS) {
            if (in_stack[v]) return true; // 回到栈上的点，存在正权环
            dist[v] = dist[u] + w[i] - mid;
            if (dfs_spfa(v, mid)) return true;
        }
    }
    in_stack[u] = false;
    return false;
}

// 判定：把每条边权改成 len - mid 后，图中是否存在正权环
bool has_positive_cycle(double mid) {
    for (int i = 0; i < MAXV; i++) dist[i] = 0.0;
    memset(in_stack, false, sizeof(in_stack));
    // dist 全部初始化为 0 等价于从超级源点出发，任何点都可能属于某个正环
    for (int u = 0; u < MAXV; u++) {
        if (dfs_spfa(u, mid)) return true;
    }
    return false;
}

// 输出平均长度：按原题惯例直接截断两位小数
void print_answer(double ans) {
    int t = (int)(ans * 100 + EPS); // 截断而非四舍五入，如 65/3 输出 21.66
    printf("%d.%02d\n", t / 100, t % 100);
}

// 处理一组数据
bool solve_one() {
    scanf("%d", &n);
    if (n == 0) return false;

    int m = build_graph();
    if (m == 0) {
        printf("No solution\n");
        return true;
    }

    // mid = 0 时所有边权为正，不存在正环就说明原图根本没有环
    if (!has_positive_cycle(0.0)) {
        printf("No solution\n");
        return true;
    }

    // 二分平均长度：mid 判出正环说明平均值可以更大
    double low = 0.0, high = 1000.0;
    for (int iter = 1; iter <= 50; iter++) {
        double mid = (low + high) / 2;
        if (has_positive_cycle(mid)) low = mid;
        else high = mid;
    }
    print_answer(low);
    return true;
}

int main() {
    while (solve_one()) {
    }
    return 0;
}
