/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 17:32
 * update_at: 2026-07-11 17:33
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 12;

int n, k;
int start_have[MAXN];
int recipe_cnt[MAXN];
int ingredient[MAXN][MAXN];
int best_answer;

bool recipe_available(int target, int have[]) {
    if (recipe_cnt[target] == 0) {
        return false;
    }
    for (int i = 1; i <= recipe_cnt[target]; i++) {
        int y = ingredient[target][i];
        if (have[y] <= 0) {
            return false;
        }
    }
    return true;
}

void apply_recipe(int target, int have[], int delta) {
    for (int i = 1; i <= recipe_cnt[target]; i++) {
        int y = ingredient[target][i];
        have[y] -= delta;
    }
    have[target] += delta;
}

// 枚举下一步执行哪个当前可用配方。
void dfs_convert(int have[]) {
    if (have[n] > best_answer) {
        best_answer = have[n];
    }

    for (int target = 1; target <= n; target++) {
        if (!recipe_available(target, have)) {
            continue;
        }

        apply_recipe(target, have, 1);
        dfs_convert(have);
        apply_recipe(target, have, -1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> start_have[i];
    }

    cin >> k;
    for (int i = 1; i <= k; i++) {
        int target, m;
        cin >> target >> m;
        recipe_cnt[target] = m;
        for (int j = 1; j <= m; j++) {
            cin >> ingredient[target][j];
        }
    }

    best_answer = start_have[n];
    int have[MAXN];
    for (int i = 1; i <= n; i++) {
        have[i] = start_have[i];
    }

    dfs_convert(have);

    cout << best_answer << '\n';

    return 0;
}
