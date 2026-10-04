/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:07
 * update_at: 2026-10-02 15:07
 */
// brute.cpp：最朴素的模拟。每个队列用一个 deque 维护，队尾 push、队首 pop，
// 每次操作结束后扫一遍所有队列统计不同权值种数。小数据对拍用。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 200005;

int n, m;
int a[maxn];
deque<int> q[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int t = 1; t <= m; t++) {
        int l, r, x;
        cin >> l >> r >> x;

        // 对区间内每个队列执行 push，并一直 pop 直到 size <= a_i
        for (int i = l; i <= r; i++) {
            q[i].push_back(x);
            while ((int)q[i].size() > a[i]) q[i].pop_front();
        }

        // 统计当前所有队列里出现过的不同权值个数
        set<int> kinds;
        for (int i = 1; i <= n; i++) {
            for (size_t k = 0; k < q[i].size(); k++) kinds.insert(q[i][k]);
        }
        cout << kinds.size() << "\n";
    }

    return 0;
}
