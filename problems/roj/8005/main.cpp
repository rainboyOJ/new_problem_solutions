/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 16:42
 * update_at: 2026-10-06 16:43
 */
#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;

const ll MOD = 100000; // 结果只保留最低 5 位

ll n;
ll f[100005]; // f[i] 表示首项为 i 的合法数列个数
ll s[100005]; // s[i] 表示 f[1..i] 的前缀和

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;

    f[1] = 1; // 数列 [1] 自身合法
    s[1] = 1;
    for (ll i = 2; i <= n; i++) {
        // 数列 [i] 自身贡献 1；后面可以接首项为 1..i/2 的任意合法数列
        f[i] = (1 + s[i / 2]) % MOD;
        s[i] = (s[i - 1] + f[i]) % MOD;
    }

    cout << f[n] << "\n";
    return 0;
}
