// brute.cpp：小数据暴力搜索，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30;
const int MAXM = 10;
const long long NEG_INF = -(1LL << 60);

int n, m, cost1, cost2;
int mp[MAXM][MAXN];
int H, C;

long long brute_dfs(int x, int y, int used) {
    if (x > n) {
        return 0;
    }
    if (mp[y][x] == -1) {
        return NEG_INF;
    }
    if (y == 1) {
        used = 0;
    }

    long long best = NEG_INF;

    if (y == 1) {
        best = max(best, brute_dfs(x + 1, 1, 0));
    }
    else {
        if (y - 1 == 1) {
            best = max(best, brute_dfs(x + 1, 1, 0));
        }
        else {
            best = max(best, brute_dfs(x + 1, y - 1, used));
        }
    }

    if (used < C && y + H <= m) {
        long long extra = 0;
        bool ok = true;
        for (int i = 1; i < H; i++) {
            int nx = x + i;
            int ny = y + i;
            if (nx > n) {
                break;
            }
            if (mp[ny][nx] == -1) {
                ok = false;
                break;
            }
            extra += mp[ny][nx];
        }
        if (ok) {
            best = max(best, extra + brute_dfs(x + H, y + H, used + 1));
        }
    }

    if (best == NEG_INF) {
        return NEG_INF;
    }
    return best + mp[y][x];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> cost1 >> cost2;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> mp[i][j];
        }
    }

    long long best_score = NEG_INF;
    int best_c = -1;
    int best_h = -1;

    for (int c = 1; c <= 5; c++) {
        for (int h = 1; c * h < m; h++) {
            C = c;
            H = h;

            long long ret = brute_dfs(0, 1, 0);
            if (ret == NEG_INF) {
                continue;
            }

            long long score = ret - 1LL * cost1 * (h - 1) - 1LL * cost2 * (c - 1);

            if (score > best_score ||
                (score == best_score && (c < best_c || (c == best_c && h < best_h)))) {
                best_score = score;
                best_c = c;
                best_h = h;
            }
        }
    }

    if (best_c == -1) {
        cout << "mission failed\n";
    }
    else {
        cout << best_score << ' ' << best_c << ' ' << best_h << '\n';
    }

    return 0;
}
