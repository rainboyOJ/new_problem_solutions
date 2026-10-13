/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 11:16
 * update_at: 2026-10-13 22:33
 */

#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

// 并查集竞赛精简版（不用 struct）：路径压缩 + 按大小合并
// 口诀：find 找根压到底，unite 小树挂大树
// 易错点：init 别只写 fa[i] = i，sz[i] 也要置 1；合并后 sz 只在新根上有效
// 和别的模板一起用时 maxn 只留一份

const int maxn = 205 * 205;
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

int n, m;
int W;                           // 点阵实际宽度，含虚拟外圈

int main() {
    scanf("%d %d", &n, &m);
    W = n + 1;                     // 真实数据里有 x=n 向下 / y=n 向右的越界边，多开一圈
    init(W * W);                   // 编号空间为 W*W，留出越界边所在的一圈

    for (int i = 1; i <= m; ++i) {
        int x, y;
        char dir[2];
        scanf("%d %d %1s", &x, &y, dir); // 读入一个非空白字符
        int u = (x - 1) * W + y;         // 点 (x, y) 的编号，1-based
        int v;
        if (dir[0] == 'D') v = u + W;     // 向下连到下一行同列
        else v = u + 1;                   // 'R'，向右连到同一行下一列

        if (!unite(u, v)) {            // 两端已在同一块，加这条边必成环
            printf("%d\n", i);
            return 0;
        }
    }

    printf("draw\n");
    return 0;
}
