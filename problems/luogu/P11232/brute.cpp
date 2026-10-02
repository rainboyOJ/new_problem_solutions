/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:42
 * update_at: 2026-10-01 22:42
 */
// brute.cpp：小数据暴力解，逐车逐测速仪判断超速，再枚举测速仪子集求最少保留台数。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 20;   // 暴力只服务小数据，m 也不能大（要枚举 2^m 个子集）

int T;
int n, m;
ll L, V;                      // L 道路长度，V 限速
ll d[MAXN], v[MAXN], a[MAXN]; // 每辆车的驶入位置、初速度、加速度
ll p[MAXN];                   // 测速仪位置
vector<int> cover[MAXN];      // cover[i]：能测出第 i 辆车超速的测速仪下标

// 判断第 id 辆车在位置 pos 处是否超速，比较速度平方即可。
bool is_speeding(ll id, ll pos) {
    ll speed_square = v[id] * v[id] + 2 * a[id] * (pos - d[id]);
    return speed_square > V * V;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        cin >> n >> m >> L >> V;

        for (int i = 1; i <= n; i++) {
            cin >> d[i] >> v[i] >> a[i];
            cover[i].clear();
        }
        for (int j = 1; j <= m; j++) {
            cin >> p[j];
        }

        // 先逐车找出所有能测出它超速的测速仪。
        int speeding_cars = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (p[j] < d[i]) {
                    continue;   // 车还没驶入道路
                }
                if (is_speeding(i, p[j])) {
                    cover[i].push_back(j);
                }
            }
            if (!cover[i].empty()) {
                speeding_cars++;
            }
        }

        // 枚举保留哪些测速仪，找出能覆盖全部超速车的最少台数。
        int best_keep = m;
        int total = 1 << m;

        for (int mask = 0; mask < total; mask++) {
            bool ok = true;

            for (int i = 1; i <= n && ok; i++) {
                if (cover[i].empty()) {
                    continue;
                }

                bool caught = false;
                int cnt = cover[i].size();
                for (int k = 0; k < cnt; k++) {
                    int sensor = cover[i][k] - 1;
                    if (mask & (1 << sensor)) {
                        caught = true;
                        break;
                    }
                }
                if (!caught) {
                    ok = false;
                }
            }

            if (ok) {
                int keep = 0;
                for (int j = 0; j < m; j++) {
                    if (mask & (1 << j)) {
                        keep++;
                    }
                }
                best_keep = min(best_keep, keep);
            }
        }

        cout << speeding_cars << ' ' << m - best_keep << '\n';
    }

    return 0;
}
