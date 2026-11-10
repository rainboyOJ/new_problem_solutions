/**
 * Problem: luogu P1982 - [NOIP 2013 普及组] 小朋友的数字
 * Author: rainboy
 * Date: 2026-11-11 00:35
 * Description: 前缀最大子段和 + __int128 跟踪与取模
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using int128 = __int128_t;

const int MAXN = 1000005;

int n;
long long p_ll;
long long a_input[MAXN];
int128 f[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> p_ll)) return 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a_input[i];
    }

    int128 p = p_ll;

    // 1. 特征值
    int128 cur_seg = a_input[1];
    f[1] = a_input[1];
    for (int i = 2; i <= n; ++i) {
        int128 val = a_input[i];
        cur_seg = max(cur_seg + val, val);
        f[i] = max(f[i - 1], cur_seg);
    }

    // 2. 分数计算
    int128 g1 = f[1];
    int128 max_score = g1;

    if (n >= 2) {
        int128 cur_g = g1 + f[1];
        max_score = max(max_score, cur_g);

        bool overflow_p = false;
        int128 mod_g = cur_g;

        if (cur_g > p) {
            overflow_p = true;
            mod_g = cur_g % p;
        }

        for (int i = 3; i <= n; ++i) {
            int128 add = max(static_cast<int128>(0), f[i - 1]);
            if (!overflow_p) {
                cur_g += add;
                max_score = max(max_score, cur_g);
                if (cur_g > p || (add > 0 && cur_g > max_score)) {
                    overflow_p = true;
                    mod_g = cur_g % p;
                }
            } else {
                mod_g = (mod_g + add % p) % p;
            }
        }

        if (overflow_p) {
            long long ans = (mod_g % p + p) % p;
            cout << ans << "\n";
            return 0;
        }
    }

    if (max_score < 0) {
        long long ans = -((-max_score) % p);
        cout << ans << "\n";
    } else {
        long long ans = max_score % p;
        cout << ans << "\n";
    }

    return 0;
}
