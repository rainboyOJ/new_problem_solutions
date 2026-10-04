/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:33
 * update_at: 2026-10-05 00:33
 */

// 食物链：带权并查集（种类并查集）
// 每只动物相对父亲记录一个模 3 关系：0 同类、1 吃父亲、2 被父亲吃。
// 三类动物的环形食物链正好对应模 3 加法，于是「同类 / x 吃 y」统一成一次减法判断。

#include <cstdio>

typedef long long ll;

const int MAXN = 50005;  // n <= 50000

int fa[MAXN];    // fa[x]：x 的父亲，自成一集时指向自己
int rel[MAXN];   // rel[x]：x 相对父亲的关系（0 同类，1 x 吃父亲，2 父亲吃 x）
int siz[MAXN];   // siz[根]：集合大小，按大小合并以控制树高

// 查根并把 x 到根的路径压缩；返回根，同时让 rel[x] 变成 x 相对根的关系。
// 注意顺序：先递归让父亲指向根、父亲的关系更新到位，再累加 rel[x]。
int find(int x) {
    if (fa[x] == x) {
        return x;
    }
    int root = find(fa[x]);
    rel[x] = (rel[x] + rel[fa[x]]) % 3;  // x 到根 = x 到父亲 + 父亲到根
    fa[x] = root;
    return root;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        rel[i] = 0;
        siz[i] = 1;
    }

    int lie_count = 0;  // 假话总数
    for (int t = 0; t < k; t++) {
        int d, x, y;
        scanf("%d %d %d", &d, &x, &y);

        // 越界，或者说出「x 吃 x」，直接是假话
        if (x > n || y > n || (d == 2 && x == y)) {
            lie_count++;
            continue;
        }

        int rootx = find(x);
        int rx = rel[x];  // x 相对根的关系
        int rooty = find(y);
        int ry = rel[y];  // y 相对根的关系

        if (rootx != rooty) {
            // 两棵树还没连通，这句话必为真，用它把两棵树合并。
            // 合并的目标是让 (rx' - ry') mod 3 == d-1（同类为 0，x 吃 y 为 1）。
            if (siz[rootx] < siz[rooty]) {
                // 把 rootx 挂到 rooty 下，此时 x 到新根为 rx + rel[rootx]
                fa[rootx] = rooty;
                rel[rootx] = ((d - 1 + ry - rx) % 3 + 3) % 3;
                siz[rooty] += siz[rootx];
            } else {
                // 把 rooty 挂到 rootx 下，此时 y 到新根为 ry + rel[rooty]
                fa[rooty] = rootx;
                rel[rooty] = ((rx - ry - (d - 1)) % 3 + 3) % 3;
                siz[rootx] += siz[rooty];
            }
        } else {
            // 已同根：真实关系为 (rx - ry) mod 3，与话意不符则是假话
            int truth = ((rx - ry) % 3 + 3) % 3;
            if (truth != d - 1) {
                lie_count++;
            }
        }
    }

    printf("%d\n", lie_count);
    return 0;
}
