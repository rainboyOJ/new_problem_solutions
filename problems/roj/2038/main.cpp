/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:01
 * update_at: 2026-10-06 10:01
 */
#include <cmath>
#include <cstdio>

typedef long long ll;

const int MAXN = 155;
const double INF = 1e18; // 距离哨兵：表示两点当前不连通

int n;                   // 牧区数量
ll px[MAXN], py[MAXN];   // 每个牧区的坐标
bool linked[MAXN][MAXN]; // 原图邻接矩阵，1 表示两点直接相连
double dis[MAXN][MAXN];  // dis[i][j] Floyd 后为块内最短路，不连通时仍为 INF
int comp[MAXN];          // comp[i] = 牧区 i 所在牧场的编号（取块内最小编号）
double ecc[MAXN];        // ecc[i] = 牧区 i 到本块内最远点的距离
double diam[MAXN];       // diam[c] = 编号为 c 的牧场的直径

// 两个牧区之间的欧几里得距离。
double euclid(int a, int b) {
    double dx = px[a] - px[b];
    double dy = py[a] - py[b];
    return sqrt(dx * dx + dy * dy);
}

// 全图跑一遍 Floyd：块内得到全源最短路，块间距离保持 INF。
void floyd() {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (dis[i][k] >= INF) continue; // i 与 k 不连通，k 不能作中转点
            for (int j = 0; j < n; j++) {
                double via = dis[i][k] + dis[k][j];
                if (via < dis[i][j]) dis[i][j] = via;
            }
        }
    }
}

int stk[MAXN]; // 连通块染色用的手写栈

// 给每个牧区染上所在牧场的编号，块内最小点标号作为该块编号。
void find_components() {
    for (int i = 0; i < n; i++) comp[i] = -1;
    for (int s = 0; s < n; s++) {
        if (comp[s] != -1) continue;
        comp[s] = s;
        int top = 0;
        stk[top++] = s;
        while (top > 0) {
            int u = stk[--top];
            for (int v = 0; v < n; v++) {
                if (linked[u][v] && comp[v] == -1) {
                    comp[v] = s;
                    stk[top++] = v;
                }
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &px[i], &py[i]);
    }

    // 矩阵行可能带行内空格或 CRLF 行尾：把所有剩余 token 拼成 0/1 串，再按每行 n 个切开。
    char cells[MAXN * MAXN + 10];
    char token[MAXN * MAXN + 10];
    int len = 0;
    while (scanf("%s", token) == 1) {
        for (int t = 0; token[t] != '\0'; t++) {
            if (len < MAXN * MAXN) cells[len++] = token[t];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            linked[i][j] = (cells[i * n + j] == '1');
        }
    }

    // 初始距离矩阵：对角线 0，有边用欧氏距离，无边用 INF。
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) dis[i][j] = 0;
            else if (linked[i][j]) dis[i][j] = euclid(i, j);
            else dis[i][j] = INF;
        }
    }

    floyd();

    // 偏心距：每个点到本块内最远点的距离。
    for (int i = 0; i < n; i++) {
        double best = 0;
        for (int j = 0; j < n; j++) {
            if (dis[i][j] < INF && dis[i][j] > best) best = dis[i][j];
        }
        ecc[i] = best;
    }

    find_components();

    // 每个牧场的直径 = 块内偏心距的最大值。
    for (int i = 0; i < n; i++) diam[i] = 0;
    for (int i = 0; i < n; i++) {
        if (ecc[i] > diam[comp[i]]) diam[comp[i]] = ecc[i];
    }

    // 枚举跨牧场点对 (i, j)：新边权是两点间欧氏距离（不是 dis[i][j]，跨块时它是 INF）。
    double best_link = INF;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (comp[i] == comp[j]) continue;
            double cand = ecc[i] + euclid(i, j) + ecc[j];
            if (cand < best_link) best_link = cand;
        }
    }

    // 新直径还要与原有各牧场直径取 max：连边只增不减，两个“团块”型牧场不会被压细。
    double ans = best_link;
    for (int i = 0; i < n; i++) {
        if (comp[i] == i && diam[i] > ans) ans = diam[i];
    }

    printf("%.6f\n", ans);
    return 0;
}
