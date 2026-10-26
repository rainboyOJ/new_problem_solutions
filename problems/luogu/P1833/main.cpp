/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-26 13:27
 * update_at: 2026-10-26 16:36
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXT = 1005;

ll n, limit_time;
ll dp[MAXT]; // dp[j] 表示总耗时不超过 j 分钟时的最大美学值

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll start_hour, start_minute, end_hour, end_minute;
    char colon;
    cin >> start_hour >> colon >> start_minute;
    cin >> end_hour >> colon >> end_minute;
    cin >> n;

    limit_time = (end_hour * 60 + end_minute) - (start_hour * 60 + start_minute);

    for (int i = 1; i <= n; i++) {
        ll tree_time, beauty, count_limit;
        cin >> tree_time >> beauty >> count_limit;

        if (count_limit == 0) {
            // 完全背包正序：当前容量可读到本轮刚更新的状态，因此同一棵树可重复选择。
            for (int j = tree_time; j <= limit_time; j++) {
                dp[j] = max(dp[j], dp[j - tree_time] + beauty);
            }
            continue;
        }

        // 二进制分组把有限次数拆成若干个 0/1 物品，每组只能选一次。
        ll group_size = 1;
        while (count_limit > 0) {
            ll use_count = min(group_size, count_limit);
            ll group_time = use_count * tree_time;
            ll group_beauty = use_count * beauty;

            // 0/1 背包倒序：来源状态尚未被当前组更新，保证本组最多选一次。
            for (int j = limit_time; j >= group_time; j--) {
                dp[j] = max(dp[j], dp[j - group_time] + group_beauty);
            }

            count_limit -= use_count;
            group_size <<= 1;
        }
    }

    cout << dp[limit_time] << '\n';
    return 0;
}
