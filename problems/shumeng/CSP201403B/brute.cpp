/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 17:07
 */
// brute.cpp：小数据暴力解，显式维护从底到顶的窗口顺序。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;

int n, m;
int left_x[MAXN], bottom_y[MAXN], right_x[MAXN], top_y[MAXN];
int order[MAXN];

bool contains(int id, int x, int y) {
    return left_x[id] <= x && x <= right_x[id] && bottom_y[id] <= y && y <= top_y[id];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> left_x[i] >> bottom_y[i] >> right_x[i] >> top_y[i];
        order[i] = i;
    }

    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;

        int position = 0;
        for (int j = n; j >= 1; j--) {
            if (contains(order[j], x, y)) {
                position = j;
                break;
            }
        }

        if (position == 0) {
            cout << "IGNORED\n";
            continue;
        }

        int chosen = order[position];
        cout << chosen << '\n';
        for (int j = position; j < n; j++) {
            order[j] = order[j + 1];
        }
        order[n] = chosen;
    }

    return 0;
}
