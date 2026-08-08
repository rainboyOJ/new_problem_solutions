#include <bits/stdc++.h>
using namespace std;

// brute.cpp：枚举田忌马匹的出场顺序，与齐王固定顺序逐一比较，求最大得分。

const int MAXN = 12;

int n;
int tian[MAXN], king[MAXN];
bool used[MAXN];
int order_arr[MAXN];
int ans = -1000000000;

void dfs(int pos, int score) {
    if (pos > n) {
        ans = max(ans, score);
        return;
    }

    for (int i = 1; i <= n; i++) {
        if (used[i]) {
            continue;
        }
        used[i] = true;

        int next_score = score;
        if (tian[i] > king[pos]) {
            next_score += 200;
        }
        else if (tian[i] < king[pos]) {
            next_score -= 200;
        }

        order_arr[pos] = tian[i];
        dfs(pos + 1, next_score);
        used[i] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> tian[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> king[i];
    }

    sort(king + 1, king + n + 1, greater<int>());
    dfs(1, 0);

    cout << ans << '\n';
    return 0;
}
