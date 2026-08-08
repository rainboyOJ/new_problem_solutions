#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;
const long long INF = (1LL << 60);

int n, m;
vector<pair<int, int> > roads[MAXN];
vector<int> depend[MAXN];
long long answer[MAXN];
long long road_arrive[MAXN];
long long shield_need[MAXN];
int remain_need[MAXN];
bool vis[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        roads[i].clear();
        depend[i].clear();
    }

    for (int i = 1; i <= m; i++) {
        int u, v, len;
        cin >> u >> v >> len;
        roads[u].push_back(make_pair(v, len));
    }

    for (int city = 1; city <= n; city++) {
        int k;
        cin >> k;
        remain_need[city] = k;
        for (int j = 1; j <= k; j++) {
            int generator_city;
            cin >> generator_city;
            depend[generator_city].push_back(city);
        }
    }

    for (int i = 1; i <= n; i++) {
        answer[i] = INF;
        road_arrive[i] = INF;
        shield_need[i] = 0;
        vis[i] = false;
    }

    answer[1] = 0;

    // 更直接的小数据写法：
    // 每次暴力找“当前最早可以被摧毁的那个城市”。
    for (int step = 1; step <= n; step++) {
        int choose = 0;
        for (int city = 1; city <= n; city++) {
            if (vis[city]) {
                continue;
            }
            if (city == 1) {
                choose = 1;
                break;
            }
            if (remain_need[city] != 0) {
                continue;
            }
            if (road_arrive[city] >= INF / 2) {
                continue;
            }
            long long cand = max(road_arrive[city], shield_need[city]);
            if (cand < answer[city]) {
                answer[city] = cand;
            }
            if (choose == 0 || answer[city] < answer[choose]) {
                choose = city;
            }
        }

        vis[choose] = true;

        for (size_t i = 0; i < roads[choose].size(); i++) {
            int v = roads[choose][i].first;
            long long nd = answer[choose] + roads[choose][i].second;
            if (nd < road_arrive[v]) {
                road_arrive[v] = nd;
            }
        }

        for (size_t i = 0; i < depend[choose].size(); i++) {
            int v = depend[choose][i];
            remain_need[v]--;
            if (answer[choose] > shield_need[v]) {
                shield_need[v] = answer[choose];
            }
        }
    }

    cout << answer[n] << '\n';

    return 0;
}
