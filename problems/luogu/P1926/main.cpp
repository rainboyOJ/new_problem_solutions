#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k, r;
    cin >> n >> m >> k >> r;

    vector<int> like(n + 1), homework_time(m + 1), homework_score(m + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> like[i];
    }
    for (int i = 1; i <= m; ++i) {
        cin >> homework_time[i];
    }
    for (int i = 1; i <= m; ++i) {
        cin >> homework_score[i];
    }

    vector<int> dp(k + 1, INF);
    dp[0] = 0;
    for (int i = 1; i <= m; ++i) {
        for (int score = k; score >= 0; --score) {
            if (dp[score] == INF) {
                continue;
            }
            int next_score = min(k, score + homework_score[i]);
            dp[next_score] = min(dp[next_score], dp[score] + homework_time[i]);
        }
    }

    int left_time = r - dp[k];
    sort(like.begin() + 1, like.end());

    int answer = 0;
    for (int i = 1; i <= n; ++i) {
        if (left_time >= like[i]) {
            left_time -= like[i];
            ++answer;
        }
    }

    cout << answer << '\n';
    return 0;
}
