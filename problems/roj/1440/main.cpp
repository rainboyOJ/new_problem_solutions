/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:47
 * update_at: 2026-10-05 23:48
 */
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 205; // n 最大值
const int MAXK = 10;  // k 最大值

ll f[MAXN][MAXK]; // f[i][j]：把 i 分成 j 份（不减、每份≥1）的方案数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    // 边界：拆成 1 份只有 1 种；i < j 时不够分，保持 0
    for (int i = 1; i <= n; i++) f[i][1] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 2; j <= k && j <= i; j++) {
            // 末份为 1：去掉它；末份≥2：每份减 1
            // 注意 i - j 可能为 0，f[0][*] 保持 0 即可
            f[i][j] = f[i - 1][j - 1] + f[i - j][j];
        }
    }

    cout << f[n][k] << '\n';
    return 0;
}
