/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:49
 * update_at: 2026-10-01 22:49
 */
// brute.cpp：小数据搜索所有攻击顺序，用来帮助理解题意并辅助对拍。
// 状态压缩：alive 表示哪些怪兽还在场上，used 表示哪些怪兽已发起过攻击。
// 只适合 n ≤ 10 的对拍场景。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 12;

ll n;
int r[MAXN];
map<ll, int> memo; // 记忆化：(alive, used) -> 最少剩余怪兽数

// 统计二进制中 1 的个数（n ≤ 12，直接数）。
int count_bits(int x) {
    int cnt = 0;
    while (x > 0) {
        cnt += x & 1;
        x >>= 1;
    }
    return cnt;
}

// dfs(alive, used)：返回在当前状态下游戏结束时最少剩余怪兽数。
int dfs(int alive, int used) {
    ll key = ((ll)alive << n) | used;
    auto it = memo.find(key);
    if (it != memo.end()) {
        return it->second;
    }

    // 判断是否还有怪兽可以发起攻击（在场且未攻击过）。
    int can_attack = 0;
    for (int i = 0; i < n; i++) {
        if ((alive & (1 << i)) && !(used & (1 << i))) {
            can_attack = 1;
        }
    }

    if (!can_attack) {
        int ret = count_bits(alive);
        memo[key] = ret;
        return ret;
    }

    int ans = count_bits(alive);

    // 枚举所有合法的攻击者-目标对。
    for (int i = 0; i < n; i++) {
        if (!(alive & (1 << i)) || (used & (1 << i))) {
            continue;
        }

        for (int j = 0; j < n; j++) {
            if (i == j || !(alive & (1 << j))) {
                continue;
            }

            int next_alive = alive;
            int next_used = used | (1 << i);
            if (r[i] > r[j]) {
                next_alive &= ~(1 << j); // 击杀目标
            }

            ans = min(ans, dfs(next_alive, next_used));
        }
    }

    memo[key] = ans;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (ll i = 0; i < n; i++) {
        cin >> r[i];
    }

    memo.clear();
    cout << dfs((1 << n) - 1, 0) << '\n';

    return 0;
}
