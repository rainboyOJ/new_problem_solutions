/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 17:32
 * update_at: 2026-07-11 17:33
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, k;
int have_metal[MAXN];       // 当前拥有的金属数量
int recipe_cnt[MAXN];       // recipe_cnt[x] 表示制造金属 x 需要几种原料金属
int ingredient[MAXN][MAXN]; // ingredient[x][i] 表示制造 x 的第 i 个原料

bool can_make(int x) {
    if (have_metal[x] > 0) {
        have_metal[x]--;
        return true;
    }

    if (recipe_cnt[x] == 0) {
        return false;
    }

    // 配方只依赖更小编号金属，所以递归不会成环。
    for (int i = 1; i <= recipe_cnt[x]; i++) {
        int y = ingredient[x][i];
        if (!can_make(y)) {
            return false;
        }
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> have_metal[i];
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

    int ans = 0;
    while (can_make(n)) {
        ans++;
    }

    cout << ans << '\n';

    return 0;
}
