/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:26
 * update_at: 2026-10-05 08:26
 */
// 软件包管理器：树链剖分 + 线段树（区间赋值 + 区间求和）
// install x：把根到 x 的路径拆成 O(log n) 段重链区间，每段用 段长-和 数出未安装个数后整体赋 1
// uninstall x：x 的子树在 DFS 序上恰好是连续区间 [pos[x], pos[x]+size[x]-1]，
//              用区间和数出已安装个数后整体赋 0

#include <cstdio>
#include <cstring>

typedef long long ll;

const int MAXN = 100005;

int n, qnum;
int fa[MAXN];        // fa[v]：v 的父节点（依赖的软件包）
int son[MAXN];       // son[v]：v 的重儿子（子树最大的儿子），没有则为 -1
int head[MAXN];      // head[v]：v 所在重链的链头
int pos[MAXN];       // pos[v]：v 在重链优先 DFS 序中的下标
int sz[MAXN];        // sz[v]：v 的子树大小
int chhead[MAXN];    // chhead[v]：v 的第一个孩子（孩子表链表头），-1 表示没有孩子
int chnext[MAXN];    // chnext[i]：孩子表中下一条边的下标，与 chhead 配对，节省建 vector
int ord[MAXN];       // 迭代版 DFS 的先序序列，ord[i] = 第 i 个访问的节点
int seq_cnt;

// 线段树：sum 为区间内已安装个数；lazy = -1 表示没有未下推的赋值标记，0/1 表示整段赋值
ll sum[4 * MAXN];
ll lazy[4 * MAXN];   // 标记用 ll，与 sum 同类型相乘，避免强制转换

// 建立孩子表：把 v 挂到 fa[v] 的孩子表头
void add_child(int v) {
    chnext[v] = chhead[fa[v]];
    chhead[fa[v]] = v;
}

// 迭代版 DFS：先序遍历求出 sz、son，顺带保证父亲先于儿子被访问
// 用 ord[] 数组手工模拟栈，避免深链时递归爆栈
void dfs_build() {
    seq_cnt = 0;
    ord[seq_cnt++] = 0;
    // 先序逆序处理即为自底向上：先算完所有孩子，再算父亲
    for (int i = 0; i < seq_cnt; ++i) {
        int v = ord[i];
        for (int c = chhead[v]; c != -1; c = chnext[c]) ord[seq_cnt++] = c;
    }
    // 此时 ord 已经完整，从后往前累加子树大小并挑重儿子
    for (int i = seq_cnt - 1; i >= 0; --i) {
        int v = ord[i];
        sz[v] = 1;
        int best = -1;
        for (int c = chhead[v]; c != -1; c = chnext[c]) {
            sz[v] += sz[c];
            if (best == -1 || sz[c] > sz[best]) best = c;
        }
        son[v] = best;
    }
}

// 重链优先的先序编号：重儿子接着当前链编，轻儿子自立新链
// 每条重链的编号连续，每个子树的编号区间 [pos, pos+sz-1] 也连续
int build_pos_cnt;
void dfs_split() {
    // 数组模拟栈：栈顶指针 tp，元素为待访问节点
    static int stk[MAXN];
    int tp = 0;
    stk[tp++] = 0;
    head[0] = 0;
    while (tp > 0) {
        int v = stk[--tp];
        pos[v] = build_pos_cnt++;
        // 先压轻儿子再压重儿子：重儿子最后压入 = 最先弹出，编号紧接父亲
        for (int c = chhead[v]; c != -1; c = chnext[c]) {
            if (c == son[v]) continue;
            head[c] = c; // 轻儿子自立链头
            stk[tp++] = c;
        }
        if (son[v] != -1) {
            head[son[v]] = head[v]; // 重儿子继承父亲的链头
            stk[tp++] = son[v];
        }
    }
}

// 左右孩子的和上推
void push_up(int i) {
    sum[i] = sum[i * 2] + sum[i * 2 + 1];
}

// 下推懒标记：把整段赋值标记传给两个孩子
void push_down(int i, int nl, int nr) {
    if (lazy[i] == -1) return;
    int mid = (nl + nr) / 2;
    lazy[i * 2] = lazy[i];
    sum[i * 2] = lazy[i] * (mid - nl + 1);
    lazy[i * 2 + 1] = lazy[i];
    sum[i * 2 + 1] = lazy[i] * (nr - mid);
    lazy[i] = -1;
}

void build_tree(int i, int nl, int nr) {
    lazy[i] = -1;
    sum[i] = 0;
    if (nl == nr) return;
    int mid = (nl + nr) / 2;
    build_tree(i * 2, nl, mid);
    build_tree(i * 2 + 1, mid + 1, nr);
}

// 把 [l,r] 整段赋值为 v，返回修改前的区间和（即被改变状态的节点数）
ll cover(int i, int nl, int nr, int l, int r, int v) {
    if (l <= nl && nr <= r) {
        ll before = sum[i];
        lazy[i] = v;
        sum[i] = (ll)v * (nr - nl + 1); // v 是 0/1，乘段长得到区间和
        return before;
    }
    push_down(i, nl, nr);
    int mid = (nl + nr) / 2;
    ll before = 0;
    if (l <= mid) before += cover(i * 2, nl, mid, l, r, v);
    if (r > mid) before += cover(i * 2 + 1, mid + 1, nr, l, r, v);
    push_up(i);
    return before;
}

int main() {
    scanf("%d", &n);
    memset(chhead, -1, sizeof(int) * n);
    fa[0] = -1;
    for (int v = 1; v < n; ++v) {
        scanf("%d", &fa[v]);
        add_child(v);
    }
    dfs_build();
    build_pos_cnt = 0;
    dfs_split();
    build_tree(1, 0, n - 1);

    scanf("%d", &qnum);
    char op[16];
    int x;
    for (int t = 0; t < qnum; ++t) {
        scanf("%s %d", op, &x);
        ll changed;
        if (op[0] == 'i') {
            // 安装：从 x 沿重链跳向根，每跳一段 [pos[head], pos[x]] 赋 1
            changed = 0;
            while (x != -1) {
                int h = head[x];
                // cover 返回修改前的和（已安装数），新增安装数 = 段长 - 和
                ll seg_len = pos[x] - pos[h] + 1;
                changed += seg_len - cover(1, 0, n - 1, pos[h], pos[x], 1);
                x = fa[h];
            }
        } else {
            // 卸载：整棵子树是连续区间 [pos[x], pos[x]+sz[x]-1]，赋 0
            changed = cover(1, 0, n - 1, pos[x], pos[x] + sz[x] - 1, 0);
        }
        printf("%lld\n", changed);
    }
    return 0;
}
