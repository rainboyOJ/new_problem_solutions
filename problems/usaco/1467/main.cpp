/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 12:25
 * update_at: 2026-07-11 12:27
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n, a, b;
char color[MAXN][MAXN];
bool has_star[MAXN][MAXN]; // has_star[i][j] 表示初始照片中这个位置有星星

void clear_case() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            has_star[i][j] = false;
        }
    }
}

bool has_source(int r, int c) {
    return r - b >= 1 && c - a >= 1;
}

int solve_one() {
    cin >> n >> a >> b;
    clear_case();

    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for (int j = 1; j <= n; j++) {
            color[i][j] = s[j - 1];
        }
    }

    bool ok = true;

    // 黑色像素表示前后两张照片这里都有星星。
    // 因此当前位置必须有初始星星，且它的来源位置也必须有初始星星并移动过来。
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (color[i][j] == 'B') {
                has_star[i][j] = true;
                if (!has_source(i, j)) {
                    ok = false;
                } else {
                    has_star[i - b][j - a] = true;
                }
            }
        }
    }

    if (!ok) {
        return -1;
    }

    // 白色不能有初始星星；灰色必须恰好由当前位置或来源位置贡献一颗星星。
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (color[i][j] == 'W') {
                if (has_star[i][j]) {
                    return -1;
                }
            } else if (color[i][j] == 'G') {
                if (has_star[i][j]) {
                    continue;
                }
                if (has_source(i, j) && has_star[i - b][j - a]) {
                    continue;
                }
                has_star[i][j] = true;
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (has_star[i][j]) {
                ans++;
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        cout << solve_one() << '\n';
    }

    return 0;
}
