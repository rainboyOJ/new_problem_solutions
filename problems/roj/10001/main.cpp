/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 21:36
 * update_at: 2026-10-04 21:36
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

int n;
int p[MAXN + 2]; // p[i] 表示格子 i 的弹力系数；p[n+1] 占位为 0

vector<int> casts; // 每次施法的格子编号

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    p[n + 1] = 0;

    int reach = 1;   // 不施法能到达的最右格子（棋子初始在格子 1）
    int cast_at = 1; // 把 reach 撑到当前值的格子，断档时应施法在它身上

    for (int i = 1; i <= n + 1; i++) {
        if (i > reach) {
            // 第一次走出可达范围：给 cast_at 施法恰好补上这一格
            casts.push_back(cast_at);
            reach = cast_at = i;
        }
        if (i <= n && i + p[i] > reach) {
            // 格子 i 能把右边界推得更远
            reach = i + p[i];
            cast_at = i;
        }
    }

    cout << (int)casts.size() << "\n";
    if (!casts.empty()) {
        for (size_t i = 0; i < casts.size(); i++) {
            if (i) cout << " ";
            cout << casts[i];
        }
        cout << "\n";
    }
    return 0;
}