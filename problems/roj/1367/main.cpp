/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:14
 * update_at: 2026-10-12 14:37
 */
// main.cpp：树的存储（父亲孩子表示法的二叉树特化）+ 中序遍历计数。
//
// 一个结点的四个字段聚合成 struct：值、左儿子、右儿子、父亲。
// 对应文章《树的存储》模板里的 val[] / lch[] / rch[] / fa[] 四个全局数组，
// 这里按结点下标收进 node[u]，读入时顺手写 node[儿子].fa = 父亲，
// 于是"谁没当过儿子"不用另开数组，node[i].fa == 0 的点就是根。

#include <cstdio>

typedef long long ll;

const int maxn = 105; // 题面 n ≤ 100，按上界开

struct Node {
    ll val;   // 结点的值
    int lch;  // 左儿子编号，0 表示空
    int rch;  // 右儿子编号，0 表示空
    int fa;   // 父亲编号；fa == 0 表示这个点是根
};

Node node[maxn]; // node[u]：编号 u 的结点
int n;           // 结点个数
ll x;            // 要查找的结点值
int cnt;         // 中序访问计数器：第 cnt 个被访问的结点

// 初始化：把 0..n 全部清成 0，node[i].fa == 0 正好表示"根没有父亲"
// 模板签名保留，多组数据时必须调用
void init(int n) {
    for (int i = 0; i <= n; i++) {
        node[i] = Node{};
    }
}

// 根是唯一没当过儿子的点：读入时每个儿子都写了 fa，所以 fa == 0 的就是根
int find_root(int n) {
    for (int i = 1; i <= n; i++) {
        if (node[i].fa == 0) {
            return i;
        }
    }
    return 1; // 题面保证输入是一棵二叉树，走到这里说明输入不合法
}

// 中序遍历：左 -> 根 -> 右，一边数名次一边找值为 x 的结点
// 返回 true 表示子树里已经命中，调用方不要再往另一边走（替代 exit(0)）
bool inorder(int u) {
    if (u == 0) {
        return false;             // 0 表示空子树
    }
    if (inorder(node[u].lch)) {
        return true;              // 先走左子树
    }
    cnt++;                        // 到了根，这是第 cnt 个被访问的结点
    if (node[u].val == x) {
        printf("%d\n", cnt);
        return true;              // 命中，把"停"信号往上传
    }
    return inorder(node[u].rch);  // 最后走右子树
}

int main() {
    scanf("%d %lld", &n, &x);
    init(n);
    for (int i = 1; i <= n; i++) {
        int l, r;
        scanf("%lld %d %d", &node[i].val, &l, &r);
        node[i].lch = l;
        node[i].rch = r;
        // 孩子一登记，父亲也顺手记下：这一步就把 fa 填好了
        if (l != 0) {
            node[l].fa = i;
        }
        if (r != 0) {
            node[r].fa = i;
        }
    }

    inorder(find_root(n));
    return 0;
}
