/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:12
 * update_at: 2026-10-05 02:40
 */
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 105; // n,m ≤ 100，留 5 余量

ll n, m;                // 原矩阵行数 n、列数 m
ll a[MAXN][MAXN];       // a[i][j] = 原矩阵第 i 行第 j 列的元素

void solve() {
    // 外层枚举输出行 j（即原矩阵的第 j 列），共 m 行
    for (ll j = 1; j <= m; j++) {
        for (ll i = 1; i <= n; i++) {
            if (i > 1) cout << ' ';
            cout << a[i][j];
        }
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    solve();

    return 0;
}
