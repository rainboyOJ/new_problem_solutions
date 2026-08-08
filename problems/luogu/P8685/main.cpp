#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;
const int MAXM = 100000 + 5;

struct Order {
    int t;
    int id;
};

int n, m, T;
Order ord[MAXM];
int score[MAXN];
int last_time[MAXN];
bool in_cache[MAXN];

bool cmp_order(const Order &a, const Order &b) {
    if (a.t != b.t) {
        return a.t < b.t;
    }
    return a.id < b.id;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> T;
    for (int i = 1; i <= m; i++) {
        cin >> ord[i].t >> ord[i].id;
    }

    sort(ord + 1, ord + m + 1, cmp_order);

    int i = 1;
    while (i <= m) {
        int t = ord[i].t;
        int id = ord[i].id;
        int cnt = 0;

        while (i <= m && ord[i].t == t && ord[i].id == id) {
            cnt++;
            i++;
        }

        // 中间这些时刻该店没有订单，优先级会持续下降。
        score[id] = max(0, score[id] - (t - last_time[id] - 1));
        if (score[id] <= 3) {
            in_cache[id] = false;
        }

        score[id] += cnt * 2;
        if (score[id] > 5) {
            in_cache[id] = true;
        }

        last_time[id] = t;
    }

    int ans = 0;
    for (int id = 1; id <= n; id++) {
        score[id] = max(0, score[id] - (T - last_time[id]));
        if (score[id] <= 3) {
            in_cache[id] = false;
        }
        if (in_cache[id]) {
            ans++;
        }
    }

    cout << ans << '\n';
    return 0;
}
