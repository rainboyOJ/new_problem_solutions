#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
const int MAXM = 25;
const long long NEG_INF = -(1LL << 60);

int n, m, cost1, cost2;
int mp[MAXM][MAXN];
long long dp[MAXN][MAXM][6];
bool vis[MAXN][MAXM][6];
int H, C;

// 记忆化搜索：
// dfs(x, y, used) 表示当前在 (x, y)，当前这次腾空过程已经用了 used 次跳跃，
// 从这里跑到终点线右侧的最大额外收益（包含当前位置收益，不含起点 (0,1)）。
long long dfs(int x, int y, int used) {
    if (x > n) {
        return 0;
    }
    if (mp[y][x] == -1) {
        return NEG_INF;
    }
    if (y == 1) {
        used = 0;
    }
    if (vis[x][y][used]) {
        return dp[x][y][used];
    }
    vis[x][y][used] = true;

    long long best = NEG_INF;

    if (y == 1) {
        // 在地面上可以继续向前跑一格。
        best = max(best, dfs(x + 1, 1, 0));
    }
    else {
        // 在空中可以继续下落一格；落地后连跳计数清零。
        if (y - 1 == 1) {
            best = max(best, dfs(x + 1, 1, 0));
        }
        else {
            best = max(best, dfs(x + 1, y - 1, used));
        }
    }

    // 如果当前还能继续跳一次，则尝试从当前位置起跳/连跳。
    if (used < C && y + H <= m) {
        long long extra = 0;
        bool ok = true;

        // 起跳/连跳过程中，会上升经过这些中间点。
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
            best = max(best, extra + dfs(x + H, y + H, used + 1));
        }
    }

    if (best == NEG_INF) {
        dp[x][y][used] = NEG_INF;
    }
    else {
        dp[x][y][used] = best + mp[y][x];
    }
    return dp[x][y][used];
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
            memset(vis, 0, sizeof(vis));

            long long ret = dfs(0, 1, 0);
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
