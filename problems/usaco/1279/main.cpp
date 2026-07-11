/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 19:12
 * update_at: 2026-07-11 19:14
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1505;

int n, q;
char dirc[MAXN][MAXN]; // 内部格子的箭头方向
int cost[MAXN][MAXN];  // 边界饲料槽费用
ll cnt[MAXN][MAXN];    // cnt[i][j] 表示有多少头牛经过这个格子
ll answer;

void add_path(int x, int y, ll delta) {
    int i = x;
    int j = y;

    // 从 (x,y) 指向的下一个格子开始更新，(x,y) 本身经过数量不变。
    while (i <= n && j <= n) {
        if (dirc[i][j] == 'R') {
            j++;
        } else {
            i++;
        }

        cnt[i][j] += delta;
        if (i == n + 1 || j == n + 1) {
            answer += delta * cost[i][j];
        }
    }
}

void build_initial() {
    answer = 0;
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 1; j <= n + 1; j++) {
            if (i <= n && j <= n) {
                cnt[i][j]++;
                if (dirc[i][j] == 'R') {
                    cnt[i][j + 1] += cnt[i][j];
                } else {
                    cnt[i + 1][j] += cnt[i][j];
                }
            } else if (i != n + 1 || j != n + 1) {
                answer += cnt[i][j] * cost[i][j];
            }
        }
    }
}

void flip_cell(int x, int y) {
    ll cows = cnt[x][y];

    add_path(x, y, -cows);

    if (dirc[x][y] == 'R') {
        dirc[x][y] = 'D';
    } else {
        dirc[x][y] = 'R';
    }

    add_path(x, y, cows);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s >> cost[i][n + 1];
        for (int j = 1; j <= n; j++) {
            dirc[i][j] = s[j - 1];
        }
    }
    for (int j = 1; j <= n; j++) {
        cin >> cost[n + 1][j];
    }

    build_initial();

    cout << answer << '\n';
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        flip_cell(x, y);
        cout << answer << '\n';
    }

    return 0;
}
