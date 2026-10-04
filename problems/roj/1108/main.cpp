/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 01:40
 * update_at: 2026-10-05 01:40
 */

#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 1005; // n 最大 1000

ll a[MAXN]; // 第一个向量的 n 个分量
ll b[MAXN]; // 第二个向量的 n 个分量

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    ll ans = 0; // 点积结果
    for (int i = 1; i <= n; i++) ans += a[i] * b[i];

    cout << ans << "\n";
    return 0;
}
