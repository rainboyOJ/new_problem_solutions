/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:36
 * update_at: 2026-10-06 10:36
 */

#include <iostream>
using namespace std;

typedef long long ll;

const int LIMIT = 256 * 256; // 盒容量 ≤256，互质时最大凑不出的数 < 256*256

int n;
int b[15];        // 盒容量
bool reach[LIMIT + 1]; // reach[s] 表示 s 块能否凑出

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> b[i];

    // 所有盒容量的最大公约数 g > 1 时，非 g 倍数的块数永远买不到且无最大值
    ll g = b[1];
    for (int i = 2; i <= n; ++i) g = gcd(g, b[i]);
    if (g != 1) {
        cout << 0 << "\n";
        return 0;
    }

    // 完全背包可达性筛：s 能凑出 ⇔ 存在盒子 b，使 s-b 能凑出
    reach[0] = true;
    for (int s = 1; s <= LIMIT; ++s) {
        bool ok = false;
        for (int i = 1; i <= n; ++i) {
            if (b[i] <= s && reach[s - b[i]]) {
                ok = true;
                break;
            }
        }
        reach[s] = ok;
    }

    int ans = 0;
    for (int s = 1; s <= LIMIT; ++s)
        if (!reach[s]) ans = s; // 取最大不可达数

    cout << ans << "\n";
    return 0;
}
