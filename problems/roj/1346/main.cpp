/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 11:15
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

const int maxn = 20005;
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

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    // 初始化：每个人自成一个集合
    init(n);
    // 读入 M 条亲戚关系，逐条合并
    for (int i = 1; i <= m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        unite(a, b);
    }
    int q;
    scanf("%d", &q);
    // 每次询问只需比较两人的代表元
    for (int i = 1; i <= q; i++) {
        int c, d;
        scanf("%d %d", &c, &d);
        if (same(c, d))
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
