/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-15 22:15
 * update_at: 2026-09-15 22:15
 *
 * brute.cpp：小数据暴力解，直接向右、向左扫到最近的被摧毁房子。
 * 用来帮助理解题意，并和 main 系列对拍。
 */
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;

int n, m;
bool destroyed[maxn];
int stk[maxn], top_;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        string op;
        cin >> op;
        if (op == "D") {
            int x;
            cin >> x;
            destroyed[x] = true;
            stk[++top_] = x;
        } else if (op == "R") {
            destroyed[stk[top_--]] = false;
        } else {
            int x;
            cin >> x;
            if (destroyed[x]) {
                cout << 0 << "\n";
                continue;
            }
            // 向左找最近的断点（0 号虚拟断点兜底）
            int l = x;
            while (l >= 1 && !destroyed[l]) --l;
            // 向右找最近的断点（n+1 号虚拟断点兜底）
            int r = x;
            while (r <= n && !destroyed[r]) ++r;
            cout << r - l - 1 << "\n";
        }
    }

    return 0;
}
