/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 09:20
 */
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353LL;

struct GcdGroup {
    int value;
    long long sum_left;
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

        GcdGroup single;
        single.value = current;
        single.sum_left = right;
        next_groups.push_back(single);

        for (int i = 0; i < (int)groups.size(); i++) {
            GcdGroup group;
            group.value = gcd(groups[i].value, current);
            group.sum_left = groups[i].sum_left;
            if (!next_groups.empty() && next_groups.back().value == group.value) {
                next_groups.back().sum_left += group.sum_left;
                next_groups.back().sum_left %= MOD;
            } else {
                next_groups.push_back(group);
            }
        }

        groups.swap(next_groups);
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
