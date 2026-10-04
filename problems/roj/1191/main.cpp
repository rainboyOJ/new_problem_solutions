/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:05
 * update_at: 2026-10-05 05:05
 */
// main.cpp：流感传染。逐天同步传播，用队列按天分层做多源 BFS。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

typedef long long ll;

ll n, m;
char grid[MAXN][MAXN]; // grid[i][j]：'#' 空房间，'.' 健康，'@' 已患病
queue<ll> infected;    // 队列里存患病格编号 r * n + c

// 上下左右四个邻居的方向。
const int dr[4] = {-1, 1, 0, 0};
const int dc[4] = {0, 0, -1, 1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    // 题面样例把一整行写成一个字符串（如 "....#"），评测数据把每格写成一个字符 token，
    // 两种排版都要能读：先看第一个网格 token 的长度就能区分。
    string token;
    cin >> token;
    if (token.size() == 1) {
        grid[0][0] = token[0];
        for (ll i = 1; i < n * n; i++) {
            cin >> token;
            grid[i / n][i % n] = token[0];
        }
    } else {
        for (ll j = 0; j < n; j++) grid[0][j] = token[j];
        for (ll i = 1; i < n; i++) {
            cin >> token;
            for (ll j = 0; j < n; j++) grid[i][j] = token[j];
        }
    }

    cin >> m;

    ll total = 0; // 当前患病人数
    for (ll r = 0; r < n; r++) {
        for (ll c = 0; c < n; c++) {
            if (grid[r][c] == '@') {
                infected.push(r * n + c);
                total++;
            }
        }
    }

    ll rounds = m - 1; // 第 1 天推进到第 m 天共 m-1 轮
    if (rounds > n * n) rounds = n * n; // 房间只有 n*n 间，更多轮数不会再有新患者

    while (rounds > 0 && !infected.empty()) {
        ll layer = infected.size(); // 定长快照：本轮出队的都是同一天的患者，保证同步传染
        for (ll k = 0; k < layer; k++) {
            ll cur = infected.front();
            infected.pop();
            ll r = cur / n;
            ll c = cur % n;

            for (int d = 0; d < 4; d++) {
                ll nr = r + dr[d];
                ll nc = c + dc[d];
                if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
                if (grid[nr][nc] == '.') {
                    grid[nr][nc] = '@'; // 入队即标记，每个格子最多入队一次
                    infected.push(nr * n + nc);
                    total++;
                }
            }
        }
        rounds--;
    }

    cout << total << endl;
    return 0;
}
