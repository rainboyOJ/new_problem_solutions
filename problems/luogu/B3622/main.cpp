/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-06 21:12
 * update_at: 2026-11-06 21:12
 */
// B3622 枚举子集（递归实现指数型枚举）
// 第 i 位同学先试 "N"（不参加）再试 "Y"（参加），这样输出顺序天然是字典序。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n;
char buf[15]; // 当前方案，buf[1..n] 存 N/Y

void dfs(ll i) {
    if (i == n + 1) {
        for (ll k = 1; k <= n; k++) {
            cout << buf[k];
        }
        cout << '\n';
        return;
    }
    buf[i] = 'N';
    dfs(i + 1);
    buf[i] = 'Y';
    dfs(i + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    dfs(1);

    return 0;
}
