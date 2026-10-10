/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Item { int v, p, q; };
Item items[65];

// 组：主件 (v, v*p) 在首位，其后是附件
vector<vector<pair<int, int> > > groups;
vector<pair<int, int> > opts[65];   // 每组的全部购买方案

// 生成一组的所有方案（必含主件，附件任选子集）
void build_options(int gi) {
    vector<pair<int, int> >& g = groups[gi];
    int main_v = g[0].first, main_s = g[0].second;
    int na = (int)g.size() - 1;
    opts[gi].clear();
    // 枚举附件子集
    for (int mask = 0; mask < (1 << na); mask++) {
        int cost = main_v, gain = main_s;
        for (int i = 0; i < na; i++)
            if (mask & (1 << i)) {
                cost += g[1 + i].first;
                gain += g[1 + i].second;
            }
        opts[gi].push_back(make_pair(cost, gain));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int budget, m;
    cin >> budget >> m;
    for (int i = 1; i <= m; i++)
        cin >> items[i].v >> items[i].p >> items[i].q;

    // 分组：主件自开一组，附件挂到 q 指向的主件组尾
    int group_id[65];
    memset(group_id, 0, sizeof(group_id));
    for (int i = 1; i <= m; i++) {
        if (items[i].q == 0) {
            group_id[i] = (int)groups.size();
            groups.push_back(vector<pair<int, int> >());
            groups.back().push_back(make_pair(items[i].v, items[i].v * items[i].p));
        }
    }
    for (int i = 1; i <= m; i++) {
        if (items[i].q != 0) {
            int gid = group_id[items[i].q];
            groups[gid].push_back(make_pair(items[i].v, items[i].v * items[i].p));
        }
    }
    int G = (int)groups.size();
    for (int i = 0; i < G; i++) build_options(i);

    // 分组背包
    vector<int> dp(budget + 1, 0);
    for (int i = 0; i < G; i++) {
        for (int j = budget; j >= 0; j--) {
            for (size_t k = 0; k < opts[i].size(); k++) {
                int cost = opts[i][k].first, gain = opts[i][k].second;
                if (cost <= j && dp[j - cost] + gain > dp[j])
                    dp[j] = dp[j - cost] + gain;
            }
        }
    }
    int ans = 0;
    for (int j = 0; j <= budget; j++) ans = max(ans, dp[j]);
    cout << ans << "\n";
    return 0;
}
