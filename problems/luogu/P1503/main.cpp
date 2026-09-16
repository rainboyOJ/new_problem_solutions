/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-15 22:15
 * update_at: 2026-09-15 22:15
 *
 * P1503 鬼子进村
 * 解法：把被摧毁的房子看作“断点”，用 FHQ-Treap 维护断点集合。
 *       查询 x 时，找到左侧最近的断点 L 和右侧最近的断点 R，
 *       能到达的房子数就是 R - L - 1。
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

// 增加虚拟边界 0 和 n+1，它们永远是被摧毁的
const int maxn = 5e5 + 5;

// ==================== FHQ-Treap 模板（按值分裂） ====================
template<typename T = long long, int N = 500005>
struct FHQ {
    int root;

    struct Node {
        int l, r;
        int size, fix;
        T val;
    };
    Node tr[N];
    int tr_idx = 0;
    int get() { return ++tr_idx; }

    std::mt19937 rnd;

    FHQ() {
        rnd.seed(233);
        init();
    }

    void init() {
        root = 0;
        tr_idx = 0;
        tr[0].l = tr[0].r = tr[0].size = 0;
        tr[0].val = 0;
    }

    int new_node(T v) {
        int id = get();
        tr[id].l = tr[id].r = 0;
        tr[id].size = 1;
        tr[id].fix = rnd();
        tr[id].val = v;
        return id;
    }

    void push_up(int u) {
        tr[u].size = tr[tr[u].l].size + tr[tr[u].r].size + 1;
    }

    // 把树 u 分成 x(<=v) 和 y(>v)
    void split(int u, int v, int &x, int &y) {
        if (!u) { x = y = 0; return; }
        if (tr[u].val <= v) {
            x = u;
            split(tr[u].r, v, tr[u].r, y);
        } else {
            y = u;
            split(tr[u].l, v, x, tr[u].l);
        }
        push_up(u);
    }

    int merge(int x, int y) {
        if (!x || !y) return x + y;
        if (tr[x].fix > tr[y].fix) {
            tr[x].r = merge(tr[x].r, y);
            push_up(x);
            return x;
        } else {
            tr[y].l = merge(x, tr[y].l);
            push_up(y);
            return y;
        }
    }

    // 集合中是否存在值 v
    bool contains(T v) {
        int u = root;
        while (u) {
            if (tr[u].val == v) return true;
            u = (v < tr[u].val) ? tr[u].l : tr[u].r;
        }
        return false;
    }

    // 插入 v，已存在则不重复插入（与 std::set 语义一致）
    void insert(T v) {
        if (contains(v)) return;
        int x, y;
        split(root, v, x, y);
        root = merge(merge(x, new_node(v)), y);
    }

    // 删除所有值为 v 的节点（与 std::set::erase 语义一致）
    void del(T v) {
        int x, y, z;
        split(root, v, x, z);
        split(x, v - 1, x, y);
        // y 中全是值为 v 的节点，直接整棵树丢弃
        root = merge(x, z);
    }

    // 查询第一个 > v 的值，找不到返回 INF_MAX
    T upper_bound(T v) {
        T ans = numeric_limits<T>::max();
        int u = root;
        while (u) {
            if (tr[u].val > v) {
                ans = tr[u].val;
                u = tr[u].l;
            } else {
                u = tr[u].r;
            }
        }
        return ans;
    }

    // 查询第一个 < v 的值，找不到返回 INF_MIN
    T lower_bound(T v) {
        T ans = numeric_limits<T>::min();
        int u = root;
        while (u) {
            if (tr[u].val < v) {
                ans = tr[u].val;
                u = tr[u].r;
            } else {
                u = tr[u].l;
            }
        }
        return ans;
    }
};
// ==================== FHQ-Treap 模板结束 ====================

int n, m;
bool destroyed[maxn]; // destroyed[i] 表示 i 号房子当前是否被摧毁
int stk[maxn], top_;  // 记录摧毁历史，R 操作按后进先出恢复
FHQ<int, maxn> fhq;

void read_data() {
    cin >> n >> m;
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0);
    read_data();

    // 虚拟边界：0 和 n+1 永远是被摧毁的
    fhq.insert(0);
    fhq.insert(n + 1);

    for (int i = 1; i <= m; ++i) {
        string op;
        cin >> op;
        if (op == "D") {
            int x;
            cin >> x;
            destroyed[x] = true;
            fhq.insert(x);
            stk[++top_] = x;
        } else if (op == "R") {
            int x = stk[top_--];
            destroyed[x] = false;
            fhq.del(x);
        } else { // Q
            int x;
            cin >> x;
            if (destroyed[x]) {
                cout << 0 << "\n";
            } else {
                int R = fhq.upper_bound(x);
                int L = fhq.lower_bound(x);
                cout << R - L - 1 << "\n";
            }
        }
    }

    return 0;
}
