/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 18:57
 * update_at: 2026-10-06 18:57
 */

#include <cstdio>

const int MAXN = 30005; // 战舰编号 1..N，N <= 30000，多开几位防越界

int fa[MAXN];      // fa[i] 是 i 的父结点
int front_w[MAXN]; // front_w[i] 是 i 相对父结点排在前面的战舰数（只算到父结点这一段）
int size_w[MAXN];  // size_w[r] 是根 r 那一列的战舰总数，只有根上有效

int stk[MAXN]; // find_root 上溯时按顺序记下路径上的结点
int top;       // stk 的有效长度

// 返回 x 所在列的根（队首），同时把 x 到根的 front_w 累加好并做路径压缩。
// 必须迭代：M 指令能把列接成长链，递归有爆栈风险。
int find_root(int x) {
    int root = x;
    top = 0;
    while (fa[root] != root) { // 先向上走到根，沿路记下经过的结点
        stk[++top] = root;
        root = fa[root];
    }
    int depth = 0;
    for (int i = top; i >= 1; --i) { // 从靠近根的一端往回累加，得到每点的列内下标
        depth += front_w[stk[i]];
        front_w[stk[i]] = depth;
        fa[stk[i]] = root;
    }
    return root;
}

int main() {
    int T;
    scanf("%d", &T);

    for (int i = 1; i <= 30000; ++i) { // 初始每艘舰独占一列
        fa[i] = i;
        front_w[i] = 0;
        size_w[i] = 1;
    }

    char op[5];
    int x, y;
    for (int q = 1; q <= T; ++q) {
        scanf("%s %d %d", op, &x, &y);
        int rx = find_root(x);
        int ry = find_root(y);

        if (op[0] == 'M') {
            // 把 x 所在列整列接到 y 所在列尾部：x 列每艘舰的名次整体增加 y 列的长度
            if (rx != ry) { // 本就在同一列时是空操作，跳过以免把根挂到自己身上
                front_w[rx] = size_w[ry];
                size_w[ry] += size_w[rx];
                fa[rx] = ry;
            }
        } else if (rx != ry) {
            printf("-1\n");
        } else {
            // 同列：下标差的绝对值是间隔距离，扣掉端点之一就是中间夹着的战舰数
            int gap = front_w[x] - front_w[y];
            if (gap < 0) gap = -gap;
            if (gap == 0) printf("0\n"); // i == j 时差为 0，中间没有战舰
            else printf("%d\n", gap - 1);
        }
    }

    return 0;
}
