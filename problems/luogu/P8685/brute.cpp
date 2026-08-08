#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;
const int MAXT = 55;

int n, m, T;
int cnt[MAXT][MAXN];
int score[MAXN];
bool in_cache[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> T;
    for (int i = 1; i <= m; i++) {
        int t, id;
        cin >> t >> id;
        cnt[t][id]++;
    }

    // 朴素模拟每一个时刻、每一家店。
    for (int t = 1; t <= T; t++) {
        for (int id = 1; id <= n; id++) {
            if (cnt[t][id] == 0) {
                score[id] = max(0, score[id] - 1);
            }
            else {
                score[id] += cnt[t][id] * 2;
            }

            if (score[id] > 5) {
                in_cache[id] = true;
            }
            else if (score[id] <= 3) {
                in_cache[id] = false;
            }
        }
    }

    int ans = 0;
    for (int id = 1; id <= n; id++) {
        if (in_cache[id]) {
            ans++;
        }
    }

    cout << ans << '\n';
    return 0;
}
