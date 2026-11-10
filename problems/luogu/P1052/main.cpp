/**
 * Problem: luogu P1052 - [NOIP 2005 提高组] 过河
 * Author: rainboy
 * Date: 2026-11-11 00:15
 * Description: 步长周期模数间距压缩 + 线性 DP
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;
const int MOD_BASE = 2520; // lcm(1..10) = 2520，完全覆盖所有可能周期步长
const int MAX_POS = 300000;

int L, S, T, M;
int orig_stone[105];
int comp_stone[105];
bool has_stone[MAX_POS];
int f[MAX_POS];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> L >> S >> T >> M)) return 0;
    for (int i = 1; i <= M; ++i) {
        cin >> orig_stone[i];
    }

    // 特殊情况：步长固定为 S
    if (S == T) {
        int ans = 0;
        for (int i = 1; i <= M; ++i) {
            if (orig_stone[i] % S == 0) {
                ans++;
            }
        }
        cout << ans << "\n";
        return 0;
    }

    // S < T：间距压缩
    sort(orig_stone + 1, orig_stone + M + 1);
    orig_stone[0] = 0;
    orig_stone[M + 1] = L;

    comp_stone[0] = 0;
    for (int i = 1; i <= M + 1; ++i) {
        int delta = orig_stone[i] - orig_stone[i - 1];
        if (delta > 90) {
            delta = (delta % 90) + 90;
        }
        comp_stone[i] = comp_stone[i - 1] + delta;
        if (i <= M) {
            has_stone[comp_stone[i]] = true;
        }
    }

    int comp_L = comp_stone[M + 1];

    for (int i = 1; i <= comp_L + T; ++i) {
        f[i] = INF;
    }
    f[0] = 0;

    for (int i = 1; i <= comp_L + T; ++i) {
        for (int j = S; j <= T; ++j) {
            if (i >= j && f[i - j] != INF) {
                f[i] = min(f[i], f[i - j] + (has_stone[i] ? 1 : 0));
            }
        }
    }

    int ans = INF;
    for (int i = comp_L; i < comp_L + T; ++i) {
        ans = min(ans, f[i]);
    }

    cout << ans << "\n";

    return 0;
}
