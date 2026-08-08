#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;
const long long INF = (1LL << 60);

int n, m;
int t[MAXN];
map<pair<int, long long>, long long> memo;

long long dfs(int pos, long long last_depart) {
    if (pos > n) {
        return 0;
    }

    pair<int, long long> state = make_pair(pos, last_depart);
    map<pair<int, long long>, long long>::iterator it = memo.find(state);
    if (it != memo.end()) {
        return it->second;
    }

    long long best = INF;
    for (int j = pos; j <= n; j++) {
        long long depart_time = t[j];
        if (last_depart >= 0) {
            depart_time = max(depart_time, last_depart + m);
        }

        long long cost = 0;
        for (int k = pos; k <= j; k++) {
            cost += depart_time - t[k];
        }
        best = min(best, cost + dfs(j + 1, depart_time));
    }

    memo[state] = best;
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：直接枚举每一班车接走哪些连续同学。
    // 对一个固定分组，出发时刻就是“最后一位上车同学到达时刻”和“上一班返回时刻”两者的较大值。
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
    }

    sort(t + 1, t + n + 1);
    memo.clear();
    cout << dfs(1, -1) << '\n';
    return 0;
}
