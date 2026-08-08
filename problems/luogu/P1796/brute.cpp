#include <bits/stdc++.h>
using namespace std;

// brute.cpp：暴力枚举从第 0 层走到第 N 层的所有路径，只适合小数据对拍。

const int MAXN = 105;
const int MAXK = 105;
const long long INF = (1LL << 60);

int n;
int cnt[MAXN];
vector<pair<int, int> > pre[MAXN][MAXK];

// dfs(level, planet) 表示暴力枚举所有路径，求到达这一点的最小花费。
long long dfs(int level, int planet) {
    if (level == 0) {
        return 0;
    }

    long long best = INF;

    for (int i = 0; i < (int)pre[level][planet].size(); i++) {
        int from = pre[level][planet][i].first;
        int cost = pre[level][planet][i].second;
        best = min(best, dfs(level - 1, from) + cost);
    }

    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cnt[0] = 1;

    for (int level = 1; level <= n; level++) {
        cin >> cnt[level];
        for (int planet = 1; planet <= cnt[level]; planet++) {
            while (true) {
                int from;
                cin >> from;
                if (from == 0) {
                    break;
                }

                int cost;
                cin >> cost;
                pre[level][planet].push_back(make_pair(from, cost));
            }
        }
    }

    long long ans = INF;
    for (int planet = 1; planet <= cnt[n]; planet++) {
        ans = min(ans, dfs(n, planet));
    }

    cout << ans << '\n';
    return 0;
}
