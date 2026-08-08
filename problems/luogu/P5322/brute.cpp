#include <bits/stdc++.h>
using namespace std;

static int s, n, m;
static vector<vector<int>> enemy;
static vector<int> choice;
static int best = 0;

static int score_for_castle(int castle, int x) {
    int cnt = 0;
    for (int i = 1; i <= s; ++i) {
        if (x > 2 * enemy[i][castle]) {
            ++cnt;
        }
    }
    return cnt * castle;
}

static void dfs(int castle, int used, int sum_score) {
    if (castle > n) {
        best = max(best, sum_score);
        return;
    }

    // 不给这座城堡派兵。
    dfs(castle + 1, used, sum_score);

    // 枚举给这座城堡派多少兵。
    for (int x = 1; x + used <= m; ++x) {
        choice[castle] = x;
        dfs(castle + 1, used + x, sum_score + score_for_castle(castle, x));
        choice[castle] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s >> n >> m;
    enemy.assign(s + 1, vector<int>(n + 1));
    for (int i = 1; i <= s; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> enemy[i][j];
        }
    }

    choice.assign(n + 1, 0);
    dfs(1, 0, 0);
    cout << best << '\n';
    return 0;
}
