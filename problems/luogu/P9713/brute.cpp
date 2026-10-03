/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:23
 * update_at: 2026-10-02 15:23
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 写法就是题面的逐字翻译：开一个三维的“还在不在”标记，每次操作把符合条件的方块一个个删掉，
// 每删掉一个就让剩余个数减一，然后输出剩余个数。
// 复杂度是 O(a * b * c * m)，只在对拍用的小数据上运行。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll a, b, c;
int m;

// 把三维坐标压成一维下标，省内存也省事：idx = ((x-1)*b + (y-1))*c + (z-1)
vector<char> alive;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b >> c >> m;

    ll total = a * b * c;
    alive.assign((size_t)total, 1); // 1 表示这个单位立方体还在

    for (int t = 1; t <= m; ++t) {
        int op;
        ll k;
        cin >> op >> k;

        // 一次操作：把所有满足“第 op 维坐标 <= k”的方块切掉
        for (ll x = 1; x <= a; ++x) {
            for (ll y = 1; y <= b; ++y) {
                for (ll z = 1; z <= c; ++z) {
                    size_t idx = (size_t)(((x - 1) * b + (y - 1)) * c + (z - 1));
                    if (alive[idx] == 0) {
                        continue; // 已经被前面的操作切掉了
                    }
                    ll pos;
                    if (op == 1) {
                        pos = x;
                    } else if (op == 2) {
                        pos = y;
                    } else {
                        pos = z;
                    }
                    if (pos <= k) {
                        alive[idx] = 0;
                        total--;
                    }
                }
            }
        }
        cout << total << "\n";
    }

    return 0;
}
