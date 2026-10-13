/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:20
 * update_at: 2026-10-13 22:34
 */

#include <cstdio>
#include <algorithm>

using namespace std;

// 并查集竞赛精简版（不用 struct）：路径压缩 + 按大小合并
// 口诀：find 找根压到底，unite 小树挂大树
// 易错点：init 别只写 fa[i] = i，sz[i] 也要置 1；合并后 sz 只在新根上有效
// 和别的模板一起用时 maxn 只留一份

const int maxn = 4015;   // 视数据范围调整为 2*最大n+5，本题 n <= 2005
int fa[maxn], sz[maxn];  // sz[x] 仅在根上有效

void init(int n) {
    for (int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1;
}

// 查 x 的根，顺手把整条链压到根上
int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

bool same(int x, int y) { return find(x) == find(y); }

// 小树挂大树，返回是否真的发生了合并
bool unite(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx == fy) return false;
    if (sz[fx] < sz[fy]) swap(fx, fy);
    fa[fy] = fx;
    sz[fx] += sz[fy];
    return true;
}

// 扩展域并查集：节点 1..n 为自身（朋友域），n+1..2n 为敌对域
int n, m, ans;
bool root_seen[maxn];  // root_seen[r] 表示代表元 r 是否已经统计过

int main() {
    scanf("%d %d", &n, &m);

    // 初始化：每个人有自身域 x 和敌对域 x+n
    init(2 * n);

    for (int i = 1; i <= m; ++i) {
        int p, x, y;
        scanf("%d %d %d", &p, &x, &y);
        if (p == 0) {
            // 朋友：朋友的朋友是朋友，直接合并自身域
            unite(x, y);
        } else {
            // 敌人：x 与 y 的敌对域合并，y 与 x 的敌对域合并
            // 这样“敌人的敌人”会通过共同的敌对域节点自动连通
            unite(x, y + n);
            unite(y, x + n);
        }
    }

    // 统计 1..n 中不同 find(i) 的个数，就是最大团伙数
    // 注意：代表元可能落在敌对域（合并方向导致），所以要按根去重
    for (int i = 1; i <= n; ++i) {
        int r = find(i);
        if (!root_seen[r]) {
            root_seen[r] = true;
            ans = ans + 1;
        }
    }
    printf("%d\n", ans);

    return 0;
}
