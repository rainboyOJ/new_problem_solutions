/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 08:30
 * update_at: 2026-10-09 09:10
 */
#include <iostream>
#include <string>
#include <queue>

using namespace std;
typedef long long ll;

const int MAXR = 55;    // 题面上限 r ≤ 50，留 5 格余量
const int MAXC = 55;    // 题面上限 c ≤ 50，留 5 格余量
const int MAXS = 10005; // |S| ≤ 10000，再加结尾换行符

ll r, c;                    // 键盘行数、列数
char grid[MAXR][MAXC];      // grid[i][j]：第 i 行第 j 列的按键字符，'*' 表示 Enter
char target[MAXS];          // target = S + '*'，即待打印文本末尾补一个换行符
ll target_len;              // target 的长度

struct Dir {
    ll dr;
    ll dc;
};

// 四个方向键：上、下、左、右
Dir dirs[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// next_pos[i][j][d]：从 (i, j) 按方向 d 跳一次后落到的位置，编码为 i * MAXC + j。
// 规则是「跳到该方向上第一个与 grid[i][j] 不同的格子」；若一路都相同或出界，
// 则原地不动，此时等于 i * MAXC + j。
ll next_pos[MAXR][MAXC][4];

// max_k[i][j]：到达格子 (i, j) 时，曾经达到过的最大已打印字符数。
// 若新状态的 k ≤ max_k[i][j]，说明之前用不多于它的步数到过这里且打印得更多，
// 后续要匹配的后缀被旧状态包含，当前状态严格劣，可直接剪枝。
ll max_k[MAXR][MAXC];

// BFS 状态：光标在 (r, c)，已经打印了 k 个字符，当前用了 dist 次按键
struct State {
    ll r;
    ll c;
    ll k;
    ll dist;
};

queue<State> q; // 用 std::queue 而非定长数组：峰值队列长度实测仅两千余，
                // 定长数组 rc(|S|+1) 会白占约 480MB，超过 128MB 的内存限制
void precompute() {
    for (ll i = 0; i < r; ++i) {
        for (ll j = 0; j < c; ++j) {
            for (ll d = 0; d < 4; ++d) {
                ll nr = i + dirs[d].dr;
                ll nc = j + dirs[d].dc;
                // 跳过所有与出发格同字符的格子，找第一个不同的
                while (nr >= 0 && nr < r && nc >= 0 && nc < c && grid[nr][nc] == grid[i][j]) {
                    nr += dirs[d].dr;
                    nc += dirs[d].dc;
                }
                if (nr >= 0 && nr < r && nc >= 0 && nc < c) {
                    next_pos[i][j][d] = nr * MAXC + nc;
                } else {
                    next_pos[i][j][d] = i * MAXC + j; // 没有不同字符可跳 ⇒ 原地不动
                }
            }
        }
    }
}

void solve() {
    if (!(cin >> r >> c)) return;
    for (ll i = 0; i < r; ++i) {
        cin >> grid[i];
    }
    string s;
    cin >> s;
    s += '*'; // 题面要求结尾打印换行符，键盘上的换行符就是 '*'

    target_len = s.length();
    for (ll i = 0; i < target_len; ++i) {
        target[i] = s[i];
    }

    precompute();

    for (ll i = 0; i < r; ++i) {
        for (ll j = 0; j < c; ++j) {
            max_k[i][j] = -1;
        }
    }

    // 起点：左上角，尚未打印任何字符
    State start;
    start.r = 0;
    start.c = 0;
    start.k = 0;
    start.dist = 0;
    q.push(start);
    max_k[0][0] = 0;

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        if (cur.k == target_len) { // 全部打印完毕（含结尾换行）
            cout << cur.dist << "\n";
            return;
        }

        // 按键一：选择键，打印当前字符（仅当与待打印字符相符）
        if (grid[cur.r][cur.c] == target[cur.k]) {
            ll nk = cur.k + 1;
            if (nk == target_len) {
                cout << cur.dist + 1 << "\n";
                return;
            }
            if (nk > max_k[cur.r][cur.c]) {
                max_k[cur.r][cur.c] = nk;
                State nxt;
                nxt.r = cur.r;
                nxt.c = cur.c;
                nxt.k = nk;
                nxt.dist = cur.dist + 1;
                q.push(nxt);
            }
        }

        // 按键二：四个方向键，跳到各自方向上的下一个不同字符
        for (ll d = 0; d < 4; ++d) {
            ll nxt_pos = next_pos[cur.r][cur.c][d];
            ll nr = nxt_pos / MAXC;
            ll nc = nxt_pos % MAXC;
            if (nr == cur.r && nc == cur.c) continue; // 无处可跳，按了也不动
            if (cur.k > max_k[nr][nc]) {
                max_k[nr][nc] = cur.k;
                State nxt;
                nxt.r = nr;
                nxt.c = nc;
                nxt.k = cur.k;
                nxt.dist = cur.dist + 1;
                q.push(nxt);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
