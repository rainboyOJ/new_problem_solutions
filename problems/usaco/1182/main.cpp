/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 19:28
 * update_at: 2026-07-11 19:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int T;

ll solve_pair(ll a, ll b) {
    ll ans = (1LL << 62);

    for (int removed = 0; (b >> removed) > 0; removed++) {
        ll prefix = b >> removed;
        ll cur = a;
        ll steps = 0;

        // 固定除法次数后，S1 阶段是唯一的：奇数先 +1，再 /2。
        while (cur > prefix) {
            if (cur % 2 == 1) {
                cur++;
                steps++;
            }
            cur /= 2;
            steps++;
        }

        // 中间只需要补若干次 +1，让 cur 变成 prefix。
        steps += prefix - cur;

        // S3 阶段：removed 次 *2，加上恢复 b 的低 removed 位中所有 1 的代价。
        steps += removed;
        if (removed > 0) {
            ll mask = (1LL << removed) - 1;
            steps += __builtin_popcountll((unsigned long long)(b & mask));
        }

        ans = min(ans, steps);
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        ll a, b;
        cin >> a >> b;
        cout << solve_pair(a, b) << '\n';
    }

    return 0;
}
