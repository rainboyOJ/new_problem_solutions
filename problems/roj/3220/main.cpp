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

const ll FAR = 1000000000000000000LL;

int cost[105][105];   // 小人 -> 房子的曼哈顿距离

ll pot_l[105];        // 左部顶标
ll pot_r[105];        // 右部顶标
int match_r[105];     // match_r[j] = 配到房子 j 的小人，0 表示空房
int prev_[105];       // 交错树上房子 j 的前驱房子
ll slack[105];
bool used[105];

// 匈牙利（KM）求 n×n 最小权完美匹配
ll min_cost_perfect_matching(int n) {
    for (int i = 0; i <= n; i++) { pot_l[i] = 0; pot_r[i] = 0; }
    for (int i = 0; i <= n; i++) match_r[i] = 0;

    for (int i = 1; i <= n; i++) {
        match_r[0] = i;
        for (int j = 0; j <= n; j++) slack[j] = FAR;
        for (int j = 0; j <= n; j++) used[j] = false;
        int j0 = 0;
        while (true) {
            used[j0] = true;
            int u = match_r[j0];
            ll delta = FAR;
            int j1 = 0;
            for (int j = 1; j <= n; j++) {
                if (!used[j]) {
                    ll gap = (ll)cost[u - 1][j - 1] - pot_l[u] - pot_r[j];
                    if (gap < slack[j]) {
                        slack[j] = gap;
                        prev_[j] = j0;
                    }
                    if (slack[j] < delta) {
                        delta = slack[j];
                        j1 = j;
                    }
                }
            }
            for (int j = 0; j <= n; j++) {
                if (used[j]) {
                    pot_l[match_r[j]] += delta;
                    pot_r[j] -= delta;
                } else {
                    slack[j] -= delta;
                }
            }
            j0 = j1;
            if (match_r[j0] == 0) break;
        }
        while (j0) {
            match_r[j0] = match_r[prev_[j0]];
            j0 = prev_[j0];
        }
    }

    ll total = 0;
    for (int j = 1; j <= n; j++)
        total += (ll)cost[match_r[j] - 1][j - 1];
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (true) {
        cin >> n >> m;
        if (n == 0 && m == 0) break;
        vector<string> grid(n);
        for (int i = 0; i < n; i++) cin >> grid[i];

        vector<pair<int, int> > people, houses;
        for (int r = 0; r < n; r++)
            for (int c = 0; c < m; c++) {
                if (grid[r][c] == 'm') people.push_back(make_pair(r, c));
                else if (grid[r][c] == 'H') houses.push_back(make_pair(r, c));
            }
        int cnt = (int)people.size();
        for (int i = 0; i < cnt; i++)
            for (int j = 0; j < cnt; j++)
                cost[i][j] = abs(people[i].first - houses[j].first)
                           + abs(people[i].second - houses[j].second);
        cout << min_cost_perfect_matching(cnt) << "\n";
    }
    return 0;
}
