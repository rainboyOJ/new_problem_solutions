/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:11
 * update_at: 2026-10-05 04:11
 */
#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long ll;

const int MAXE = 100005; // 边数上限
const int MAXN = 50005;  // 点数上限

struct Edge {
    int u;
    int v;
    int w;
};

int n, m;
ll need; // 生成树中必须包含的白边条数

Edge whites[MAXE]; // 白边列表，按边权升序
Edge blacks[MAXE]; // 黑边列表，按边权升序
int white_num;     // 白边条数
int black_num;     // 黑边条数

int fa[MAXN]; // 并查集父节点

// 边按权值升序，用于提前把白边、黑边各自排好序
bool cmp_edge(const Edge &a, const Edge &b) {
    return a.w < b.w;
}

// 并查集查找，带路径压缩
int find_root(int x) {
    while (fa[x] != x) {
        fa[x] = fa[fa[x]];
        x = fa[x];
    }
    return x;
}

// 给每条白边额外附加权值 bonus 后跑一次无约束 Kruskal。
// 白边、黑边两组已各自有序，用双指针归并成整体有序，单次只需 O(E)。
// 返回选入的白边条数，adjusted_weight 带回调整后的生成树总权值。
int kruskal(ll bonus, ll &adjusted_weight) {
    for (int i = 0; i < n; i++) {
        fa[i] = i;
    }
    int chosen = 0;     // 已选入生成树的边数
    int white_used = 0; // 已选入的白边条数
    ll total = 0;       // 调整后的生成树总权值
    int wi = 0;         // 白边指针
    int bi = 0;         // 黑边指针

    while (chosen < n - 1 && (wi < white_num || bi < black_num)) {
        // 白边用尽时只能取黑边；白边权值不超过黑边时取白边
        // 权值相同时固定优先取白边，保证二分的单调性
        bool take_white = true;
        if (wi >= white_num) {
            take_white = false;
        } else if (bi < black_num && blacks[bi].w < whites[wi].w + bonus) {
            take_white = false;
        }

        int u, v;
        ll w;
        if (take_white) {
            u = whites[wi].u;
            v = whites[wi].v;
            w = whites[wi].w + bonus;
            wi++;
        } else {
            u = blacks[bi].u;
            v = blacks[bi].v;
            w = blacks[bi].w;
            bi++;
        }

        int ru = find_root(u);
        int rv = find_root(v);
        if (ru == rv) {
            continue; // 两端已连通，这条边舍弃
        }
        fa[ru] = rv;
        total += w;
        chosen++;
        if (take_white) {
            white_used++;
        }
    }

    adjusted_weight = total;
    return white_used;
}

int main() {
    scanf("%d %d %lld", &n, &m, &need);

    white_num = 0;
    black_num = 0;
    for (int i = 0; i < m; i++) {
        int s, t, c, col;
        scanf("%d %d %d %d", &s, &t, &c, &col);
        if (col == 0) {
            whites[white_num].u = s;
            whites[white_num].v = t;
            whites[white_num].w = c;
            white_num++;
        } else {
            blacks[black_num].u = s;
            blacks[black_num].v = t;
            blacks[black_num].w = c;
            black_num++;
        }
    }

    // 白边权值只比黑边大/小有限范围，一次排序后二分内部无需再排序
    sort(whites, whites + white_num, cmp_edge);
    sort(blacks, blacks + black_num, cmp_edge);

    // WQS 二分：找“选出的白边条数 >= need”的最大附加权值 best_bonus
    int low = -105;
    int high = 105;
    int best_bonus = 0;
    ll dummy = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int cnt = kruskal(mid, dummy);
        if (cnt >= need) {
            best_bonus = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    // 用 best_bonus 再跑一次，截距还原出恰好 need 条白边的最小权值和
    ll adjusted = 0;
    kruskal(best_bonus, adjusted);
    ll ans = adjusted - need * best_bonus;
    printf("%lld\n", ans);

    return 0;
}
