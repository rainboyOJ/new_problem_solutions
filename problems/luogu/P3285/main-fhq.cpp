/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-16 21:45
 * update_at: 2026-09-16 21:45
 *
 * P3285 [SCOI2014] 方伯伯的OJ
 *
 * 思路：FHQ-Treap 维护“区间节点” + 动态撕裂 + 父指针求排名
 *
 * n 高达 1e8，但操作只有 m <= 1e5 次，绝大多数用户的相对顺序永远不变。
 * 因此把连续的一段用户 [L,R] 打包成一个 Treap 节点（等价类思想）：
 *   - 节点的 size = 左子树 size + 右子树 size + (R - L + 1)
 *   - 初始整棵树只有一个节点 [1, n]
 *
 * map<int,int> mp 记录“每个区间的左端点 -> 该区间所在的 Treap 节点编号”。
 * 想定位用户 x 时：mp.upper_bound(x) 再 --it，就拿到包含 x 的那个区间。
 *
 * 当某次操作需要单独处理区间内部的一个点时，在 split 的递归下放过程中
 * 把这个区间节点“撕成”两个节点，这就是动态撕裂；新节点的优先级继承原节点，
 * 从而保证堆性质不被打乱。
 *
 * 每个节点还要维护父指针 fa，由 ID 反推排名时从节点往上爬：
 * 自己是父亲的右儿子时，父亲的左子树和父亲自身的区间都排在自己前面。
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005; // 初始 1 个节点 + 每次撕裂最多新增 1 个节点

int n, m;
int last_ans; // 上一次操作的输出，即题面中的 a

// ================= FHQ-Treap（区间节点版） =================

int root;                 // 当前树根
int L[MAXN], R[MAXN];     // 每个节点代表的用户编号区间 [L, R]
int ls[MAXN], rs[MAXN];   // 左右儿子
int sz[MAXN];             // 子树内用户总数（不是节点数）
int pri[MAXN];            // 随机优先级，大根堆
int fa[MAXN];             // 父指针，用于由节点反推排名
int tot;                  // 节点池大小

map<int, int> mp; // 区间左端点 -> 节点编号

// 建立编号为 id、代表区间 [l, r] 的新节点。
void new_node(int id, int l, int r) {
    L[id] = l;
    R[id] = r;
    ls[id] = rs[id] = fa[id] = 0;
    sz[id] = r - l + 1;
    pri[id] = rand();
}

// 用左右儿子信息更新自己的 size。
void push_up(int u) {
    sz[u] = sz[ls[u]] + sz[rs[u]] + (R[u] - L[u] + 1);
    // 同步父指针，保证爬树求排名时不会走错
    if (ls[u]) fa[ls[u]] = u;
    if (rs[u]) fa[rs[u]] = u;
}

/**
 * 按“用户数量”分裂：把树 u 切成 x（前 k 个用户）和 y（其余用户）。
 *
 * 与普通 FHQ-Treap 的区别：第 k 个用户可能落在某个区间节点 a 的内部，
 * 这时必须把这个节点撕成 [L,L+k-1] 和 [L+k,R] 两个节点。
 */
void split(int u, int k, int &x, int &y) {
    if (u == 0) {
        x = y = 0;
        return;
    }

    int left_sz = sz[ls[u]];      // 左子树里的用户数
    int len = R[u] - L[u] + 1;    // 自己这个区间的长度

    if (k < left_sz) {
        // 分界点在左子树内部，继续往左递归
        y = u;
        split(ls[u], k, x, ls[u]);
        push_up(y);
    } else if (k > left_sz + len) {
        // 分界点在右子树内部，继续往右递归
        x = u;
        split(rs[u], k - left_sz - len, rs[u], y);
        push_up(x);
    } else if (k == left_sz) {
        // 分界点刚好落在自己区间的左端之前：直接把左子树切出来
        x = ls[u];
        ls[u] = 0;
        if (x) fa[x] = 0;
        push_up(u);
        y = u;
    } else if (k == left_sz + len) {
        // 分界点刚好落在自己区间的右端之后：直接把右子树切出去
        y = rs[u];
        rs[u] = 0;
        if (y) fa[y] = 0;
        push_up(u);
        x = u;
    } else {
        // 核心：分界点落在这个区间内部，触发动态撕裂
        int kk = k - left_sz; // 这个区间要保留前 kk 个用户
        int v = ++tot;        // 新建节点，装下剩余的用户
        new_node(v, L[u] + kk, R[u]);
        pri[v] = pri[u];      // 继承优先级，保持堆性质

        // 原节点剩下的右子树归新节点，原节点被截断为 [L, L+kk-1]
        rs[v] = rs[u];
        if (rs[v]) fa[rs[v]] = v;
        R[u] = L[u] + kk - 1;
        rs[u] = 0;

        mp[L[v]] = v; // 新区间的左端点登记进 map

        x = u;
        y = v;
        push_up(x);
        push_up(y);
    }
}

// 合并两棵树，要求 x 中所有用户都排在 y 之前。
int merge(int x, int y) {
    if (x == 0 || y == 0) return x + y;

    if (pri[x] > pri[y]) {
        rs[x] = merge(rs[x], y);
        push_up(x);
        return x;
    } else {
        ls[y] = merge(x, ls[y]);
        push_up(y);
        return y;
    }
}

// 分裂后把两棵新根的父指针清空。
void split_root(int k, int &x, int &y) {
    split(root, k, x, y);
    if (x) fa[x] = 0;
    if (y) fa[y] = 0;
}

/**
 * 由用户编号 x 求它当前的绝对排名。
 *
 * mp 里存的是区间左端点，upper_bound(x) 找到第一个左端点大于 x 的区间，
 * 再回退一步就是包含 x 的那个区间。
 */
int get_rank(int x) {
    auto it = mp.upper_bound(x);
    --it;
    int u = it->second;
    int l = it->first;

    // 节点内部的偏移 + 左子树的人数
    int rank = sz[ls[u]] + (x - l + 1);

    // 沿父指针往上爬：自己是右儿子时，父亲整体都在自己前面
    while (fa[u] != 0) {
        int p = fa[u];
        if (rs[p] == u) {
            rank += sz[ls[p]] + (R[p] - L[p] + 1);
        }
        u = p;
    }
    return rank;
}

/**
 * 把当前排名为 k 的那个用户单独切出来。
 * 返回 x（它前面的人）、mid（只有这一个用户）、y（它后面的人）。
 * 因为 split 带动态撕裂，mid 保证是一个长度为 1 的节点。
 */
void cut_one(int k, int &x, int &mid, int &y) {
    int t1, t2;
    split_root(k - 1, x, t1);
    split(t1, 1, mid, y);
    if (mid) fa[mid] = 0;
    if (y) fa[y] = 0;
}

// ================= 主流程 =================

void solve() {
    // 初始只有一个区间节点 [1, n]
    tot = 1;
    new_node(1, 1, n);
    mp[1] = 1;
    root = 1;
    fa[root] = 0;

    // 哨兵：保证 upper_bound(x) 一定能 --it（x = n 时也安全）
    mp[n + 1] = 0;

    last_ans = 0;

    for (int i = 1; i <= m; i++) {
        int opt;
        cin >> opt;

        if (opt == 1) {
            int x, y;
            cin >> x >> y;
            x -= last_ans;
            y -= last_ans;

            int rank = get_rank(x);

            int t1, mid, t2;
            cut_one(rank, t1, mid, t2);

            // 排名不变，只把编号从 x 改成 y
            mp.erase(L[mid]);
            L[mid] = R[mid] = y;
            mp[y] = mid;

            root = merge(merge(t1, mid), t2);

            last_ans = rank;
            cout << rank << "\n";
        } else if (opt == 2) {
            int x;
            cin >> x;
            x -= last_ans;

            int rank = get_rank(x);

            int t1, mid, t2;
            cut_one(rank, t1, mid, t2);

            // 放到最前面
            root = merge(mid, merge(t1, t2));

            last_ans = rank;
            cout << rank << "\n";
        } else if (opt == 3) {
            int x;
            cin >> x;
            x -= last_ans;

            int rank = get_rank(x);

            int t1, mid, t2;
            cut_one(rank, t1, mid, t2);

            // 放到最后面
            root = merge(merge(t1, t2), mid);

            last_ans = rank;
            cout << rank << "\n";
        } else {
            int k;
            cin >> k;
            k -= last_ans;

            int t1, mid, t2;
            cut_one(k, t1, mid, t2);

            // mid 是长度 1 的区间，它的左端点就是答案
            int ans = L[mid];

            root = merge(merge(t1, mid), t2);

            last_ans = ans;
            cout << ans << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    srand(233); // 固定种子，方便本地对拍复现
    cin >> n >> m;
    solve();

    return 0;
}
