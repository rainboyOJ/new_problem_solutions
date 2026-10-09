/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 09:30
 * update_at: 2026-10-09 11:24
 */
#include <iostream>

using namespace std;

typedef long long ll;

const int MAXN = 200005;
const int MAXM = 200005;

// 主席树（可持久化线段树）维护数组 fa[]：第 p 个叶子表示元素 p 的父节点与深度
// 每次修改产生 O(log n) 个新结点，历史版本由根编号 rt[] 指向
//
// 空间估算：建树 O(n) 个结点；每个 1 操作产生 O(log n) ~ 18 个结点
// 最坏 m=200000 次合并 => 200000 * 18 = 3.6e6，加上建树与常数余量开 8.5e6
const int MAX_NODES = 8500000;

// 结点：一个对象一个 node[u]，不用平行数组
// val 的位域：低 20 位存 fa（n <= 200000 < 2^20），高 12 位存深度（<= 20 < 2^12）
struct Node {
    int left;  // 左儿子编号
    int right; // 右儿子编号
    int val;   // 叶子的值：fa | (dep << 20)
};
Node node[MAX_NODES];
int node_cnt = 0; // 已创建结点数，node_cnt 就是最后一个结点编号

int rt[MAXM]; // rt[i] = 第 i 次操作之后的版本根编号

// 新建一个结点，返回编号
int new_node(int left_son, int right_son, int value) {
    node_cnt++;
    node[node_cnt].left = left_son;
    node[node_cnt].right = right_son;
    node[node_cnt].val = value;
    return node_cnt;
}

// 建初始版本：叶子 i 的 fa = i，dep = 0
int build(int l, int r) {
    if (l == r) return new_node(0, 0, l);
    int mid = (l + r) >> 1;
    int left_son = build(l, mid);
    int right_son = build(mid + 1, r);
    return new_node(left_son, right_son, 0);
}

// 在版本 pre 的基础上把下标 idx 的叶子改成 fa|(dep<<20)，返回新版本根
int update(int pre, int l, int r, int idx, int fa, int dep) {
    if (l == r) return new_node(0, 0, fa | (dep << 20));
    int mid = (l + r) >> 1;
    int left_son = node[pre].left;
    int right_son = node[pre].right;
    if (idx <= mid) left_son = update(left_son, l, mid, idx, fa, dep);
    else right_son = update(right_son, mid + 1, r, idx, fa, dep);
    return new_node(left_son, right_son, 0);
}

// 查询版本 p 中下标 idx 的叶子值（fa|dep）
int query(int p, int l, int r, int idx) {
    if (l == r) return node[p].val;
    int mid = (l + r) >> 1;
    if (idx <= mid) return query(node[p].left, l, mid, idx);
    return query(node[p].right, mid + 1, r, idx);
}

const int FA_MASK = (1 << 20) - 1;

// 沿 fa 链找根，返回根叶子的值（含深度）
// 注意：这里绝不能路径压缩——可持久化结构下压缩会改写大量历史结点
int find_root(int p, int n, int x) {
    while (true) {
        int v = query(p, 1, n, x);
        int fa = v & FA_MASK;
        if (fa == x) return v;
        x = fa;
    }
}

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    rt[0] = build(1, n);

    int last_ans = 0; // 上一次询问的答案，用于强制在线异或解密
    for (int i = 1; i <= m; ++i) {
        int op;
        cin >> op;
        if (op == 1) {
            int a, b;
            cin >> a >> b;
            a ^= last_ans;
            b ^= last_ans;

            rt[i] = rt[i - 1]; // 未合并时版本不变
            int va = find_root(rt[i], n, a);
            int vb = find_root(rt[i], n, b);
            int root_a = va & FA_MASK;
            int root_b = vb & FA_MASK;
            if (root_a != root_b) {
                // 按秩（深度）合并，保证树深 O(log n)
                int dep_a = va >> 20;
                int dep_b = vb >> 20;
                if (dep_a < dep_b) {
                    rt[i] = update(rt[i - 1], 1, n, root_a, root_b, dep_a);
                } else if (dep_a > dep_b) {
                    rt[i] = update(rt[i - 1], 1, n, root_b, root_a, dep_b);
                } else {
                    int p = update(rt[i - 1], 1, n, root_a, root_b, dep_a);
                    rt[i] = update(p, 1, n, root_b, root_b, dep_b + 1);
                }
            }
        } else if (op == 2) {
            int k;
            cin >> k;
            k ^= last_ans;
            // 回到第 k 次操作之后的状态：第 0 次操作后就是初始状态
            rt[i] = rt[k];
        } else {
            int a, b;
            cin >> a >> b;
            a ^= last_ans;
            b ^= last_ans;
            int root_a = find_root(rt[i - 1], n, a) & FA_MASK;
            int root_b = find_root(rt[i - 1], n, b) & FA_MASK;
            int ans = (root_a == root_b) ? 1 : 0;
            cout << ans << "\n";
            last_ans = ans;
            rt[i] = rt[i - 1]; // 询问不改变状态
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
