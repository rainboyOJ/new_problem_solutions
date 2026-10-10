/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 方块堆叠方案计数：记忆化搜索，最高的人必须站在某一排最左的空位。
#include <cstdio>
#include <vector>
#include <map>

typedef long long ll;

std::map<std::vector<int>, ll> memo;
std::vector<int> caps;
ll K;

// 已放好 rows[i] 个人的状态下，继续放完所有人（当前最高者）的方案数
ll count_ways(std::vector<int> rows) {
    if (rows == caps) return 1; // 所有位置都放满，剩下的恰好填满
    std::map<std::vector<int>, ll>::iterator it = memo.find(rows);
    if (it != memo.end()) return it->second;

    ll sum = 0;
    for (ll i = 0; i < K; i++) {
        // 第 i 排未满，且它前面一排（更靠后）已放人数更多，保证列不悬空
        if (rows[i] < caps[i] && (i == 0 || rows[i - 1] > rows[i])) {
            rows[i]++;
            sum += count_ways(rows);
            rows[i]--;
        }
    }
    memo[rows] = sum;
    return sum;
}

int main() {
    ll k;
    while (scanf("%lld", &k) == 1) {
        if (k == 0) break;
        caps.assign(k, 0);
        for (ll i = 0; i < k; i++) {
            scanf("%d", &caps[i]);
        }
        K = k;
        memo.clear();
        std::vector<int> rows(k, 0);
        printf("%lld\n", count_ways(rows));
    }
    return 0;
}
