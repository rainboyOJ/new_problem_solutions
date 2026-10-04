/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:11
 * update_at: 2026-10-05 05:11
 */
// main.cpp：判断整除。2^n 种符号方案只有 k 个余数状态，保留「可达余数集合」逐个数字推进。
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 10005;
const int MAXK = 105;

ll n, k;
ll a[MAXN];        // a[i] 已归约到 [0, k)，加号减号只关心余数
char reach[MAXK];  // reach[r] = 1 表示处理完当前前缀后余数 r 可达
char nxt[MAXK];    // 加入 a[i] 之后的可达余数集合

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] %= k; // 只看余数：s * a 与 s * (a mod k) 模 k 同余
    }

    reach[0] = 1; // 空序列的和为 0

    for (ll i = 1; i <= n; i++) {
        for (ll r = 0; r < k; r++) nxt[r] = 0;
        for (ll r = 0; r < k; r++) {
            if (!reach[r]) continue;
            nxt[(r + a[i]) % k] = 1;          // 第 i 个数前放 +
            nxt[(r - a[i] + k) % k] = 1;      // 第 i 个数前放 -
        }
        for (ll r = 0; r < k; r++) reach[r] = nxt[r];
    }

    if (reach[0])
        cout << "YES" << "\n";
    else
        cout << "NO" << "\n";

    return 0;
}
