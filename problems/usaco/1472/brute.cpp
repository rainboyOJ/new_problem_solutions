/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 20:40
 * update_at: 2026-07-11 20:41
 */
// brute.cpp：小数据暴力解，枚举行排列和列排列并检查是否能重命名成输入表。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 8;
const int MAXV = 20;

int n;
int a[MAXN][MAXN];
int p[MAXN], q[MAXN];
int best[MAXN][MAXN];
bool has_best;

bool is_valid() {
    int label[MAXV];
    for (int i = 0; i < MAXV; i++) label[i] = -1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x = p[i] + q[j];
            if (label[x] == -1) {
                label[x] = a[i][j];
            } else if (label[x] != a[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool candidate_is_better() {
    if (!has_best) return true;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x = p[i] + q[j];
            if (x < best[i][j]) return true;
            if (x > best[i][j]) return false;
        }
    }
    return false;
}

void save_candidate() {
    has_best = true;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            best[i][j] = p[i] + q[j];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        p[i] = i;
        q[i] = i;
    }

    do {
        for (int i = 1; i <= n; i++) q[i] = i;
        do {
            if (is_valid() && candidate_is_better()) {
                save_candidate();
            }
        } while (next_permutation(q + 1, q + n + 1));
    } while (next_permutation(p + 1, p + n + 1));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j > 1) cout << ' ';
            cout << best[i][j];
        }
        cout << '\n';
    }

    return 0;
}
