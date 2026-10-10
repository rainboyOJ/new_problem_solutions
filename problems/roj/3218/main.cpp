/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 13:40
 * update_at: 2026-10-09 14:16
 */
// 3218「Team Them Up!」将他们分好队
// 两个人能同队 ⟺ 两人【互相】认识（题面明说「A 认识 B 不代表 B 认识 A」）。
// 把「不能同队」的两人在【补图】里连一条边，则每支队伍都是补图的独立集，
// 合法分队 ⟺ 补图的二分染色；出现奇环 ⟺ 无解。
// 每个连通块的两个色类必须整块地归到同一队，于是用背包 DP 让两队人数尽量接近。

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const ll MAXN = 105;       // N ≤ 100，留一点余量

ll N;                      // 人数
bool know[MAXN][MAXN];     // know[i][j]：i 认识 j（单向关系，别当成对称）
bool differ[MAXN][MAXN];   // differ[i][j]：i 与 j 不能同队，即补图里的边

struct Block {
    vector<ll> side[2];    // 该连通块在补图中两侧的成员编号
    ll cnt[2];             // 两侧各有多少人（存一份，输出时不必再取 size()）
};
Block block[MAXN];         // block[1..C] 各连通块；补图中的孤立点自成一块
ll C;                      // 连通块个数

ll color[MAXN];            // color[u]：u 在补图中的颜色（0/1），-1 表示尚未染色

struct DpLayer {
    bool reach[MAXN];      // reach[j]：处理到这一层时队 1 人数恰为 j 是否可达
    ll from[MAXN];         // from[j]：达到 reach[j] 时本层这一块给队 1 的是哪一侧
};
DpLayer dp[MAXN];          // dp[i] 表示处理完前 i 个连通块的背包层

// 在补图上从 u 开始染色（c 为 u 的颜色）；发现奇环返回 false
bool dfs_color(ll u, ll c) {
    color[u] = c;
    block[C].side[c].push_back(u);
    block[C].cnt[c]++;
    for (ll v = 1; v <= N; v++) {
        if (!differ[u][v]) continue;
        if (color[v] == -1) {
            if (!dfs_color(v, c ^ 1)) return false;
        } else if (color[v] == c) {
            return false;   // 同色相邻 ⇒ 奇环 ⇒ 无解
        }
    }
    return true;
}

// 读入：第一行 N，随后 N 行是若干整数，以 0 结尾
void read_input() {
    for (ll i = 1; i <= N; i++) {
        ll x;
        while (cin >> x && x != 0) know[i][x] = true;
    }
}

// 建补图：不完全互识的两人不能同队
void build_differ_graph() {
    for (ll i = 1; i <= N; i++) {
        for (ll j = 1; j <= N; j++) {
            if (i != j && !(know[i][j] && know[j][i])) differ[i][j] = true;
        }
    }
}

// 补图二分染色，把每个连通块拆成两侧；奇环返回 false
bool build_blocks() {
    for (ll i = 1; i <= N; i++) color[i] = -1;
    for (ll i = 1; i <= N; i++) {
        if (color[i] != -1) continue;
        C++;
        if (!dfs_color(i, 0)) return false;
    }
    return true;
}

// 背包：每块把某一侧整块给队 1，求两队人数差最小的分配，并回退出两队成员
bool pick_teams(vector<ll> &team1, vector<ll> &team2) {
    dp[0].reach[0] = true;
    for (ll i = 1; i <= C; i++) {
        ll w0 = block[i].cnt[0];
        ll w1 = block[i].cnt[1];
        for (ll j = 0; j <= N; j++) {
            if (!dp[i - 1].reach[j]) continue;
            if (j + w0 <= N) {
                dp[i].reach[j + w0] = true;
                dp[i].from[j + w0] = 0;
            }
            if (j + w1 <= N) {
                dp[i].reach[j + w1] = true;
                dp[i].from[j + w1] = 1;
            }
        }
    }

    ll best = -1;
    ll best_diff = N + 1;
    for (ll j = 1; j < N; j++) {   // 两队各至少 1 人 ⇒ 队 1 人数只能是 1..N-1
        if (!dp[C].reach[j]) continue;
        ll diff = 2 * j - N;
        if (diff < 0) diff = -diff;
        if (diff < best_diff) {
            best_diff = diff;
            best = j;
        }
    }
    if (best < 0) return false;

    for (ll i = C; i >= 1; i--) {
        ll side = dp[i].from[best];
        for (ll u : block[i].side[side]) team1.push_back(u);
        for (ll u : block[i].side[side ^ 1]) team2.push_back(u);
        best -= block[i].cnt[side];
    }
    // 真实数据里同一队的成员按编号升序给出，逐字节比对要求保持一致
    sort(team1.begin(), team1.end());
    sort(team2.begin(), team2.end());
    return true;
}

void print_teams(const vector<ll> &team1, const vector<ll> &team2) {
    cout << team1.size();
    for (ll u : team1) cout << " " << u;
    cout << "\n";
    cout << team2.size();
    for (ll u : team2) cout << " " << u;
    cout << "\n";
}

void solve() {
    if (!(cin >> N)) return;

    read_input();
    build_differ_graph();

    if (!build_blocks()) {
        cout << "No solution\n";
        return;
    }

    vector<ll> team1;
    vector<ll> team2;
    if (!pick_teams(team1, team2)) {
        cout << "No solution\n";
        return;
    }

    print_teams(team1, team2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
