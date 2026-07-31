/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 17:07
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;

int n, m;
int left_x[MAXN], bottom_y[MAXN], right_x[MAXN], top_y[MAXN];
int level[MAXN];

bool contains(int id, int x, int y) {
    return left_x[id] <= x && x <= right_x[id] && bottom_y[id] <= y && y <= top_y[id];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> left_x[i] >> bottom_y[i] >> right_x[i] >> top_y[i];
        level[i] = i;
    }

    int top_level = n;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;

        int chosen = 0;
        for (int id = 1; id <= n; id++) {
            if (contains(id, x, y) && (chosen == 0 || level[id] > level[chosen])) {
                chosen = id;
            }
        }

        if (chosen == 0) {
            cout << "IGNORED\n";
        } else {
            cout << chosen << '\n';
            top_level++;
            level[chosen] = top_level;
        }
    }

    return 0;
}
