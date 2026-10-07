/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 10:12
 * update_at: 2026-10-05 10:12
 */
// main.cpp：找树根和孩子。读入 m 条边 (x, y)，一次性写入父亲表和孩子表，
// 再分别回答「谁是根」和「谁的孩子最多」，最后升序输出。
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

const int MAXN = 1005; // 结点编号 <= 1000

ll n, m;
int parent[MAXN];              // parent[y] = y 的父亲，0 表示还没有人认领 y（即 y 是根）
vector<int> children[MAXN];    // children[x] = x 的全部孩子编号

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (ll i = 1; i <= m; i++) {
        ll x, y;
        cin >> x >> y;
        // 同一条边只解析一次，两端各写一张表：y 认下父亲，x 多一个孩子。
        parent[y] = x;
        children[x].push_back(y);
    }

    // 根是唯一没有父亲的结点。
    ll root = 0;
    for (ll v = 1; v <= n; v++) {
        if (parent[v] == 0) {
            root = v;
            break;
        }
    }

    // 孩子最多的结点，并列时取编号小者；编号递增扫描配合严格大于即可实现。
    ll busiest = 1;
    for (ll v = 1; v <= n; v++) {
        if (children[v].size() > children[busiest].size()) {
            busiest = v;
        }
    }

    cout << root << "\n";
    cout << busiest << "\n";

    // 孩子的输出要求按编号从小到大，输入不保证有序，必须显式排序。
    sort(children[busiest].begin(), children[busiest].end());
    for (size_t i = 0; i < children[busiest].size(); i++) {
        if (i > 0) {
            cout << " ";
        }
        cout << children[busiest][i];
    }
    cout << "\n";
    return 0;
}
