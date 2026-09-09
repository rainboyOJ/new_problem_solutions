/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-28 21:28
 * update_at: 2026-08-28 21:28
 */
// brute.cpp：小数据暴力解，枚举所有“摆放方式”并逐字符检查。
// 摆放方式 = (起点, 第一段方向, 拐点位置 k, 第二段方向)，
// 直线看成拐点不存在，L 形看成第一段 k 个字母后转 90 度。
// 复杂度较高（O(R*C*8*L*L)），只适合小数据验证与对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXRC = 105;

string w;                 // 要找的单词 W
int R, C;                 // 网格行数、列数
char g[MAXRC][MAXRC];     // 网格
int ans = 0;

// 8 个方向：0 上，1 右上，2 右，3 右下，4 下，5 左下，6 左，7 左上
int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

// 从 (x,y) 出发，第一段沿方向 d1 放 len1 个字母，第二段沿方向 d2 放剩余字母，
// 逐字符检查整条路径上的字母是否恰好等于 w。
bool check_path(int x, int y, int d1, int len1, int d2) {
    int L = (int)w.size();
    // 第一段：第 0..len1-1 个字母
    for (int t = 0; t < len1; t++) {
        int nx = x + dx[d1] * t;
        int ny = y + dy[d1] * t;
        if (nx < 0 || nx >= R || ny < 0 || ny >= C || g[nx][ny] != w[t]) {
            return false;
        }
    }
    // 第二段：拐点在 (x + dx[d1]*(len1-1), y + dy[d1]*(len1-1))，之后沿 d2 走
    for (int t = len1; t < L; t++) {
        int nx = x + dx[d1] * (len1 - 1) + dx[d2] * (t - len1 + 1);
        int ny = y + dy[d1] * (len1 - 1) + dy[d2] * (t - len1 + 1);
        if (nx < 0 || nx >= R || ny < 0 || ny >= C || g[nx][ny] != w[t]) {
            return false;
        }
    }
    return true;
}

void solve() {
    int L = (int)w.size();
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (g[i][j] != w[0]) {
                continue;
            }
            for (int d1 = 0; d1 < 8; d1++) {
                // 直线：整条路径沿 d1，相当于第一段长度为 L、没有第二段
                if (check_path(i, j, d1, L, d1)) {
                    ans++;
                }
                // L 形：第一段 k 个字母（2 <= k <= L-1），然后向两个垂直方向拐
                for (int k = 2; k <= L - 1; k++) {
                    for (int d2 = 2; d2 <= 6; d2 += 4) {   // 两个垂直方向
                        int nd2 = (d1 + d2) % 8;
                        if (check_path(i, j, d1, k, nd2)) {
                            ans++;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> w >> R >> C;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> g[i][j];
        }
    }

    solve();
    cout << ans << '\n';
    return 0;
}
