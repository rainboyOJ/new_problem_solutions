/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 文艺平衡树扩展（ADD / REVERSE / REVOLVE / INSERT / DELETE / MIN）：Splay 维护区间。
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>

typedef long long ll;

const ll INF = 1000000000000000000LL;

struct Node {
    int ch[2];   // 左 / 右孩子
    int fa;      // 父亲
    ll val;      // 节点自身的值
    ll mn;       // 子树最小值
    ll add;      // 子树整体加法的懒标记
    char rev;    // 子树待翻转的懒标记
    int siz;     // 子树大小
};

std::vector<Node> nd;

ll cnt = 0;  // 已用节点数
ll root = 0; // 根
std::vector<ll> A;

// 分配一个值为 v、父亲为 par 的新节点
ll new_node(ll v, ll par) {
    cnt++;
    nd[cnt].ch[0] = nd[cnt].ch[1] = 0;
    nd[cnt].fa = (int)par;
    nd[cnt].val = nd[cnt].mn = v;
    nd[cnt].add = 0;
    nd[cnt].rev = 0;
    nd[cnt].siz = 1;
    return cnt;
}

// 由左右孩子重算 x 的子树大小与最小值
void pull(ll x) {
    ll l = nd[x].ch[0], r = nd[x].ch[1];
    nd[x].siz = nd[l].siz + nd[r].siz + 1;
    ll m = nd[x].val;
    if (nd[l].mn < m) m = nd[l].mn;
    if (nd[r].mn < m) m = nd[r].mn;
    nd[x].mn = m;
}

// 从 x 往上逐层重算聚合值，直到根
void pull_up(ll x) {
    while (x) {
        pull(x);
        x = nd[x].fa;
    }
}

// 把 x 的懒标记下传一层：整子树加 add、整子树翻转
void push(ll x) {
    if (nd[x].add) {
        ll d = nd[x].add;
        nd[x].add = 0;
        for (int s = 0; s < 2; s++) {
            ll y = nd[x].ch[s];
            if (y) {
                nd[y].val += d;
                nd[y].mn += d;
                nd[y].add += d;
            }
        }
    }
    if (nd[x].rev) {
        nd[x].rev = 0;
        ll l = nd[x].ch[0], r = nd[x].ch[1];
        nd[x].ch[0] = (int)r;
        nd[x].ch[1] = (int)l;
        if (l) nd[l].rev ^= 1;
        if (r) nd[r].rev ^= 1;
    }
}

std::vector<ll> pathbuf;

// 把根到 x 路径上的懒标记自上而下清空
void push_path(ll x) {
    pathbuf.clear();
    while (x) {
        pathbuf.push_back(x);
        x = nd[x].fa;
    }
    for (size_t i = pathbuf.size(); i-- > 0;) {
        push(pathbuf[i]);
    }
}

// 把 x 上旋一层（路径上的懒标记已被 push_path 清空）
void rotate(ll x) {
    ll y = nd[x].fa;
    ll z = nd[y].fa;
    int side = (nd[y].ch[1] == (int)x) ? 1 : 0; // x 是 y 的哪一侧孩子
    ll w = nd[x].ch[side ^ 1];
    if (w) nd[w].fa = (int)y;
    nd[y].ch[side] = (int)w;
    nd[x].ch[side ^ 1] = (int)y;
    nd[y].fa = (int)x;
    nd[x].fa = (int)z;
    if (z) nd[z].ch[nd[z].ch[1] == (int)y ? 1 : 0] = (int)x;
    pull(y);
}

// 把 x 转成 goal 的孩子（goal=0 表示转成根）
void splay_to(ll x, ll goal) {
    push_path(x);
    while (nd[x].fa != goal) {
        ll y = nd[x].fa;
        ll z = nd[y].fa;
        if (z != goal && ((nd[z].ch[1] == (int)y) == (nd[y].ch[1] == (int)x))) {
            rotate(y); // 一字型先转父亲，避免退化成链
        }
        if (nd[x].fa != goal) rotate(x);
    }
    if (!goal) root = x; // 转到根后同步全局根指针
    pull(x);
    pull_up(nd[x].fa);
}

// 从 start 出发找中序第 k 个元素（沿途把懒标记下传）
ll kth(ll start, ll k) {
    ll x = start;
    while (true) {
        push(x);
        ll left = nd[nd[x].ch[0]].siz;
        if (k == left + 1) return x;
        if (k <= left) {
            x = nd[x].ch[0];
        } else {
            k -= left + 1;
            x = nd[x].ch[1];
        }
    }
}

// 把 A 的区间 [x, y] 切成一颗完整子树，返回 (a, 子树根)
void segment(ll x, ll y, ll& a, ll& key) {
    a = kth(root, x);
    splay_to(a, 0);
    ll b = kth(a, y + 2); // a 在根上用全局位置：A[y] 在 y+1，后继在 y+2
    splay_to(b, a);
    key = nd[b].ch[0];
}

// 翻转 A 的区间 [x, y]
void reverse_seg(ll x, ll y) {
    if (x >= y) return;
    ll a, key;
    segment(x, y, a, key);
    nd[key].rev ^= 1;
    pull_up(a);
}

// 区间右轮换 t 次：尾部 t 个移到前面，等价于三次翻转
void revolve(ll x, ll y, ll t) {
    t %= (y - x + 1);
    if (t) {
        reverse_seg(x, y - t);
        reverse_seg(y - t + 1, y);
        reverse_seg(x, y);
    }
}

// 把 A[lo..hi] 建成尽量平衡的子树，返回子树根
ll build(ll lo, ll hi, ll par) {
    if (lo > hi) return 0;
    ll mid = (lo + hi) >> 1;
    ll x = new_node(A[mid], par);
    nd[x].ch[0] = (int)build(lo, mid - 1, x);
    nd[x].ch[1] = (int)build(mid + 1, hi, x);
    pull(x);
    return x;
}

int main() {
    ll n;
    if (scanf("%lld", &n) != 1) return 0;
    A.assign(n, 0);
    for (ll i = 0; i < n; i++) {
        scanf("%lld", &A[i]);
    }
    ll m;
    scanf("%lld", &m);

    ll cap = n + m + 5; // 左右哨兵 2 个 + 原序列 n 个 + 每次 INSERT 最多新增 1 个
    nd.assign(2 * cap + 10, Node());
    nd[0].mn = INF; // 空节点不能把子树最小值拉成 0

    A.push_back(INF); // 右哨兵并进建树列表
    ll head = new_node(INF, 0); // 左哨兵：树中第 1 个位置
    ll mid_root = build(0, n, head);
    nd[head].ch[1] = (int)mid_root;
    pull(head);
    root = head;

    std::vector<char> opname(16);
    for (ll q = 0; q < m; q++) {
        char buf[16];
        scanf("%s", buf);
        std::string op(buf);
        if (op == "ADD") {
            ll x, y, d;
            scanf("%lld %lld %lld", &x, &y, &d);
            ll a, key;
            segment(x, y, a, key);
            // 懒标记只打在子树根上：子树自身的最小值立即修正
            nd[key].val += d;
            nd[key].mn += d;
            nd[key].add += d;
            pull_up(a);
        } else if (op == "REVERSE") {
            ll x, y;
            scanf("%lld %lld", &x, &y);
            reverse_seg(x, y);
        } else if (op == "REVOLVE") {
            ll x, y, t;
            scanf("%lld %lld %lld", &x, &y, &t);
            revolve(x, y, t);
        } else if (op == "INSERT") {
            ll x, p;
            scanf("%lld %lld", &x, &p);
            ll a = kth(root, x + 1); // A 的第 x 个元素
            splay_to(a, 0);
            ll b = kth(a, x + 2);    // 全局位置：A[x] 在 x+1，后继在 x+2
            splay_to(b, a);
            ll c = new_node(p, b);
            nd[b].ch[0] = (int)c;    // 此刻 b 的左子树恰好为空
            pull(b);
            pull_up(a);
        } else if (op == "DELETE") {
            ll x;
            scanf("%lld", &x);
            ll a = kth(root, x);     // 树中第 x 个 = A 的第 x-1 个（可能是左哨兵）
            splay_to(a, 0);
            ll b = kth(a, x + 2);    // 全局位置：A[x] 在 x+1，后继在 x+2
            splay_to(b, a);
            nd[b].ch[0] = 0;         // 此刻 b 的左子树恰好只有 A[x]
            pull(b);
            pull_up(a);
        } else { // MIN
            ll x, y;
            scanf("%lld %lld", &x, &y);
            ll a, key;
            segment(x, y, a, key);
            printf("%lld\n", nd[key].mn);
        }
    }
    return 0;
}
