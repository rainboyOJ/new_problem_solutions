/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 10:12
 * update_at: 2026-10-12 14:56
 */
// main.cpp：用父亲孩子表示法存树，找根和孩子最多的结点，孩子升序输出。
//
// 每条边 (x, y) 只解析一次：y 认下父亲 x，x 多一个孩子 y。
// 结点的两个字段聚合成 struct：父亲、孩子列表。
// 根是唯一没当过孩子的点（fa == 0）；孩子最多的结点按"编号递增扫描 + 严格大于"取，
// 并列时自然留下编号小的那个。

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

const int maxn = 1005; // 题面结点编号 x,y <= 1000，按上界开

struct Node {
    int fa;            // 父亲编号，fa == 0 表示还没有人认领它（即根）
    vector<int> child; // 全部孩子编号，输入不保证有序
};

Node node[maxn]; // node[u]：编号 u 的结点
ll n, m;         // 结点个数、边数

// 读入 m 条边：每条边一次写两处，y 认下父亲，x 多一个孩子
void read_input() {
    cin >> n >> m;
    for (ll i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        node[y].fa = x;
        node[x].child.push_back(y);
    }
}

// 根是唯一没当过孩子的点：读入时每个孩子都写了 fa，所以 fa == 0 的就是根
ll find_root() {
    for (ll v = 1; v <= n; v++) {
        if (node[v].fa == 0) {
            return v;
        }
    }
    return 0; // 题面保证输入是一棵树，走到这里说明输入不合法
}

// 孩子最多的结点，并列取编号小者：
// 编号递增扫描配合严格大于，先扫到的小编号一定留得住
ll find_busiest() {
    ll best = 1;
    for (ll v = 1; v <= n; v++) {
        if (node[v].child.size() > node[best].child.size()) {
            best = v;
        }
    }
    return best;
}

void solve() {
    read_input();
    ll root = find_root();
    ll busiest = find_busiest();

    cout << root << "\n";
    cout << busiest << "\n";

    // 孩子的输出要求按编号从小到大，输入不保证有序，必须显式排序
    sort(node[busiest].child.begin(), node[busiest].child.end());
    for (size_t i = 0; i < node[busiest].child.size(); i++) {
        if (i > 0) {
            cout << " ";
        }
        cout << node[busiest].child[i];
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}
