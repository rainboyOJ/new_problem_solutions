/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 12:16
 * update_at: 2026-10-06 12:16
 */

#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 1005;

ll f[MAXN];  // f[i] 表示从 i 出发（含 i 本身）能得到的数的个数
ll s[MAXN];  // s[i] = f[1] + f[2] + ... + f[i]，即 f 的前缀和

int main() {
    int n;
    cin >> n;

    // 递推：f[i] = 1 + (1..i/2 每个数左边拼上 i 之后各自的产物数)
    // 即 f[i] = 1 + s[i/2]，再用前缀和把转移降到 O(1)
    f[0] = 0;
    s[0] = 0;
    for (int i = 1; i <= n; i++) {
        f[i] = 1 + s[i / 2];
        s[i] = s[i - 1] + f[i];
    }

    cout << f[n] << endl;
    return 0;
}
