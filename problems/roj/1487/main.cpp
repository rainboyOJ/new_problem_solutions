// 北极通讯网络（一本通 3.1 例 2）
// Kruskal 最小生成树：k 台卫星设备相当于把树中最大的 max(k-1,0) 条边
// 用卫星链路替代，剩下的最大边权就是无线电收发机需要的最小 d。
#include <cstdio>
#include <cmath>
#include <algorithm>

const int MAXN = 505;
const int MAXE = MAXN * MAXN / 2;

typedef long long ll;

int n, k;
int x[MAXN], y[MAXN];
int fa[MAXN];

struct Edge {
    double w; // 边权（欧氏距离）
    int u, v; // 端点
};

Edge eg[MAXE]; // 全部点对的边
int ecnt;      // 边数

// 边权升序比较（供 sort 使用，不用 lambda）
bool cmp_edge(const Edge &a, const Edge &b) {
    return a.w < b.w;
}

// 并查集：查找根
int find(int a) {
    while (fa[a] != a) {
        fa[a] = fa[fa[a]]; // 路径压缩
        a = fa[a];
    }
    return a;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d %d", &x[i], &y[i]);

    // 卫星设备足够时 d 可以为 0
    if (k >= n) {
        printf("0.00\n");
        return 0;
    }

    // 构造全部点对的边
    ecnt = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) {
            double dx = x[i] - x[j];
            double dy = y[i] - y[j];
            eg[++ecnt].w = sqrt(dx * dx + dy * dy);
            eg[ecnt].u = i;
            eg[ecnt].v = j;
        }

    // 按边权升序排序（Kruskal）
    std::sort(eg + 1, eg + ecnt + 1, cmp_edge);

    for (int i = 1; i <= n; i++)
        fa[i] = i;

    // 生成树的边权从小到大依次存入 tw
    double tw[MAXN]; // 生成树各边权值
    int tcnt = 0;
    for (int i = 1; i <= ecnt && tcnt < n - 1; i++) {
        int fu = find(eg[i].u);
        int fv = find(eg[i].v);
        if (fu != fv) {
            fa[fu] = fv;
            tw[++tcnt] = eg[i].w;
        }
    }

    // 去掉最大的 max(k-1,0) 条边后，剩余最大边即答案
    int remove_cnt = k - 1;
    if (remove_cnt < 0) remove_cnt = 0;
    double ans = 0.0;
    if (remove_cnt < tcnt)
        ans = tw[tcnt - remove_cnt];
    printf("%.2f\n", ans);
    return 0;
}
