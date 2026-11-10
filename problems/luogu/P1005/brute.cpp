/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 22:50
 * update_at: 2026-11-10 22:50
 */

// brute.cpp：小数据暴力解，采用递归搜索枚举每一步取首还是取尾，用于对拍验证
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

using int128 = __int128;

const int MAXM = 85;
int a[MAXM];
int128 pow2[MAXM];

void print_int128(int128 x) {
    if (x == 0) {
        cout << 0;
        return;
    }
    string s;
    while (x > 0) {
        s.push_back('0' + (x % 10));
        x /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s;
}

// 递归搜索第 step 轮，当前剩余区间为 [L, R]
int128 dfs(int L, int R, int step) {
    if (L == R) {
        return static_cast<int128>(a[L]) * pow2[step];
    }
    int128 choose_left = static_cast<int128>(a[L]) * pow2[step] + dfs(L + 1, R, step + 1);
    int128 choose_right = static_cast<int128>(a[R]) * pow2[step] + dfs(L, R - 1, step + 1);
    return max(choose_left, choose_right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    pow2[0] = 1;
    for (int i = 1; i <= m; ++i) {
        pow2[i] = pow2[i - 1] * 2;
    }

    int128 total_score = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[j];
        }
        total_score += dfs(1, m, 1);
    }

    print_int128(total_score);
    cout << "\n";

    return 0;
}
