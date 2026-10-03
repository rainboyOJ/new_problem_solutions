/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-03 11:01
 * update_at: 2026-10-03 11:01
 */
// brute.cpp：小数据暴力解，直接枚举所有子段求异或和，用来对拍 main.cpp。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 5;

int n;
int a[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // 枚举左端点 L，向右扩展右端点 R，边走边维护当前子段的异或和
    ll ans = 0;
    for (int L = 1; L <= n; L++) {
        int now = 0;
        for (int R = L; R <= n; R++) {
            now ^= a[R];   // [L, R] 的异或和
            ans += now;
        }
    }

    cout << ans << "\n";
    return 0;
}
