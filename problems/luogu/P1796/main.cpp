#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL << 60);

int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    // 第 0 层只有一个起点星球，编号视为 1，初始花费为 0。
    vector<long long> prev(2, 0);

    for (int level = 1; level <= n; level++) {
        int k;
        cin >> k;

        vector<long long> cur(k + 1, INF);

        for (int planet = 1; planet <= k; planet++) {
            while (true) {
                int from;
                cin >> from;
                if (from == 0) {
                    break;
                }

                long long cost;
                cin >> cost;

                // 当前层的星球只会从上一层的某个星球转移过来。
                if (prev[from] < INF / 2) {
                    cur[planet] = min(cur[planet], prev[from] + cost);
                }
            }
        }

        prev = cur;
    }

    long long ans = INF;
    for (int i = 1; i < (int)prev.size(); i++) {
        ans = min(ans, prev[i]);
    }

    cout << ans << '\n';
    return 0;
}
