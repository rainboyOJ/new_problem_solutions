/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 12:33
 * update_at: 2026-10-06 12:33
 */
#include <iostream>
#include <map>
#include <string>
using namespace std;

const int MAXN = 105;
const int NEG = -1000000000;

typedef long long ll;

ll n, v;
map<string, int> name_id; // 城市名 -> 自西向东的编号 0..n-1
int adj[MAXN][MAXN];      // 邻接矩阵，adj[i][j]=1 表示城市 i、j 之间有直达航线
int dp[MAXN][MAXN];       // dp[a][b]: 去程停在 a、回程停在 b 时覆盖的城市数(不计终点 n-1)

void read_input() {
    cin >> n >> v;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        name_id[s] = i;
    }
    for (int i = 0; i < v; i++) {
        string x, y;
        cin >> x >> y;
        int a = name_id[x];
        int b = name_id[y];
        adj[a][b] = 1;
        adj[b][a] = 1;
    }
}

void solve() {
    if (n == 1) {
        cout << 1 << '\n';
        return;
    }

    for (int a = 0; a < n; a++) {
        for (int b = 0; b < n; b++) {
            dp[a][b] = NEG;
        }
    }
    dp[0][0] = 0; // 两条链都还在起点 0，只计起点这一个城市

    for (int a = 0; a < n; a++) {
        for (int b = 0; b < n; b++) {
            int cur = dp[a][b];
            // 无效态；两条链在非起点处汇合；两条链都到达终点，均不再扩展
            if (cur < 0 || (a == b && a != 0) || (a == n - 1 && b == n - 1)) {
                continue;
            }
            int nxt = cur + 1;
            int far = a > b ? a : b; // 两条链端点中较大的编号
            // 去程前进：a -> c，c 必须比两条链的所有端点都大，避免重复覆盖
            for (int c = far + 1; c < n; c++) {
                if (adj[a][c] && nxt > dp[c][b]) {
                    dp[c][b] = nxt;
                }
            }
            // 回程前进：b -> c
            for (int c = b + 1; c < n; c++) {
                if (adj[b][c] && nxt > dp[c][a]) {
                    dp[c][a] = nxt;
                }
            }
        }
    }

    // 闭合：去程已到终点 n-1，回程停在 b 且 b 与终点相邻，补上终点这一个城市
    int best = 0;
    for (int b = 0; b < n - 1; b++) {
        if (dp[n - 1][b] >= 0 && adj[n - 1][b]) {
            if (dp[n - 1][b] + 1 > best) {
                best = dp[n - 1][b] + 1;
            }
        }
    }
    if (best < 1) {
        best = 1; // 一条路线都找不到时，题目规定输出 1
    }
    cout << best << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
