#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;
const int MAXT = 25;

int n, m, target;
int a[MAXN];
int b[MAXN];
vector<pair<int, int>> plans;

void dfs_plan(int idx, int used, int gain) {
    if (used > target) {
        return;
    }
    if (idx > n) {
        plans.push_back(make_pair(used, gain));
        return;
    }

    int limit = target / max(1, a[idx]);
    for (int cnt = 0; cnt <= limit; cnt++) {
        long long next_used = 1LL * used + 1LL * cnt * a[idx];
        long long next_gain = 1LL * gain + 1LL * cnt * b[idx];
        if (next_used > target || next_gain > 1000000) {
            break;
        }
        dfs_plan(idx + 1, (int) next_used, (int) next_gain);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
    // 先枚举“一秒内可能建造出的所有苦工组合”，
    // 再按天做宽搜，状态是（当前资源，已有采集效率）。
    cin >> n >> m >> target;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
    }

    if (m >= target) {
        cout << 0 << '\n';
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        if (a[i] == 0 && b[i] > 0) {
            cout << 1 << '\n';
            return 0;
        }
    }

    dfs_plan(1, 0, 0);
    sort(plans.begin(), plans.end());
    plans.erase(unique(plans.begin(), plans.end()), plans.end());

    vector<vector<int>> vis(target, vector<int>(target + 1, 0));
    queue<tuple<int, int, int>> q;
    q.push(make_tuple(m, 0, 0));
    vis[m][0] = 1;

    while (!q.empty()) {
        int res = get<0>(q.front());
        int prod = get<1>(q.front());
        int day = get<2>(q.front());
        q.pop();

        for (size_t i = 0; i < plans.size(); i++) {
            int cost = plans[i].first;
            int add = plans[i].second;
            if (cost > res) {
                continue;
            }

            int next_prod = prod + add;
            if (next_prod > target) {
                next_prod = target;
            }

            long long next_res = 1LL * res - cost + prod + add;
            if (next_res >= target) {
                cout << day + 1 << '\n';
                return 0;
            }

            if (!vis[next_res][next_prod]) {
                vis[next_res][next_prod] = 1;
                q.push(make_tuple((int) next_res, next_prod, day + 1));
            }
        }
    }

    return 0;
}
