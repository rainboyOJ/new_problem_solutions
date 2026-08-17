/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:50
 */
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353LL;

struct GcdGroup {
    int value;          // 一组区间共同的 gcd
    long long sum_left; // 这些区间左端点之和，用于一次统计贡献
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<GcdGroup> groups;
    vector<GcdGroup> next_groups;
    groups.reserve(32);
    next_groups.reserve(32);

    long long answer = 0;
    for (int right = 1; right <= n; right++) {
        int current;
        cin >> current;
        next_groups.clear();

        // 以 right 结尾的新单点区间 [right, right]
        GcdGroup single;
        single.value = current;
        single.sum_left = right;
        next_groups.push_back(single);

        // 旧区间左端点不变，gcd 与当前元素取 gcd 后放入新分组
        for (int i = 0; i < (int)groups.size(); i++) {
            GcdGroup group;
            group.value = gcd(groups[i].value, current);
            group.sum_left = groups[i].sum_left;
            // 相邻且 gcd 相同的组合并，保证每组的 gcd 互不相同
            if (!next_groups.empty() && next_groups.back().value == group.value) {
                next_groups.back().sum_left += group.sum_left;
                next_groups.back().sum_left %= MOD;
            } else {
                next_groups.push_back(group);
            }
        }

        groups.swap(next_groups);
        // 一组所有区间贡献为 gcd * right * (左端点之和)，一次性累加
        for (int i = 0; i < (int)groups.size(); i++) {
            long long contribution = (long long)groups[i].value * groups[i].sum_left % MOD;
            contribution = contribution * right % MOD;
            answer += contribution;
            answer %= MOD;
        }
    }

    cout << answer << '\n';
    return 0;
}
