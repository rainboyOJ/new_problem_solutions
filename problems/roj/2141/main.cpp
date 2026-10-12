/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 07:52
 * update_at: 2026-10-12 14:56
 */
// main.cpp：父亲孩子表示法建公司继承树，BFS 序自底向上累加子树大小，每人输出 sz-1。
//
// 员工的三个字段聚合成 struct：直接上司、全部直接下属、子树大小。
// 上司编号不保证小于本人编号，不能按编号倒着扫；必须先从根 1 求 BFS 序
// （父亲一定先于孩子入队），再逆序累加，孩子就一定先算完。
// 子树大小最大是 n = 2*10^5，用 int 足够，不必上 ll。

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

const int maxn = 200005; // 题面 n <= 2*10^5，按上界开

struct Node {
    int boss;          // 直接上司编号，总经理 1 的上司记为 0
    vector<int> child; // 全部直接下属编号
    int sz;            // 以 u 为根的子树大小（含本人），最大 n，int 足够
};

Node node[maxn];  // node[u]：员工 u
int order[maxn];  // BFS 序：父亲一定排在孩子之前
int order_cnt;    // BFS 序里的员工个数，order[0..order_cnt-1]
ll n;             // 员工数量

// 读入：员工 2..n 各报一个直接上司，同时登记到上司的下属表里
void read_input() {
    cin >> n;
    for (ll i = 2; i <= n; i++) {
        cin >> node[i].boss;
        node[node[i].boss].child.push_back(i); // 建边：上司 -> 直接下属
    }
}

// 从总经理 1 出发求 BFS 序：入队时父亲一定先于孩子，可以当拓扑序用
void build_order() {
    int head = 0, tail = 0;
    order[tail++] = 1;
    while (head < tail) {
        int u = order[head++];
        for (size_t i = 0; i < node[u].child.size(); i++) {
            order[tail++] = node[u].child[i];
        }
    }
    order_cnt = tail;
}

// 逆着 BFS 序自底向上累加：孩子先算完，再把自己整棵子树的大小报给上司
void calc_subtree_size() {
    build_order();
    for (ll i = 1; i <= n; i++) {
        node[i].sz = 1; // 先假设每人只有自己
    }
    for (int i = order_cnt - 1; i >= 0; i--) {
        int u = order[i];
        if (u != 1) { // 根没有上司可上报
            node[node[u].boss].sz += node[u].sz;
        }
    }
}

void solve() {
    read_input();
    calc_subtree_size();

    // 员工 u 的下属人数 = 子树大小 - 1（去掉本人）
    for (ll i = 1; i <= n; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << node[i].sz - 1;
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}
