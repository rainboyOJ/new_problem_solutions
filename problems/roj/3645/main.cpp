/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 15:50
 * update_at: 2026-10-06 15:50
 */
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 1005; // 图书数量上限

ll code[MAXN];      // 升序排序后的图书编码
ll pow10[10];       // pow10[k] = 10^k，用来截取末 k 位

int main() {
    pow10[0] = 1;
    for (int k = 1; k <= 8; k++) {
        pow10[k] = pow10[k - 1] * 10;
    }

    ll n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> code[i];
    }
    sort(code, code + n); // 排序后「第一个命中」就是最小的编码

    for (int i = 0; i < q; i++) {
        ll len, need;
        cin >> len >> need;
        ll ans = -1;
        for (int j = 0; j < n; j++) {
            // 编码末 len 位等于需求码，即对 10^len 取模相等
            if (code[j] % pow10[len] == need) {
                ans = code[j];
                break;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
