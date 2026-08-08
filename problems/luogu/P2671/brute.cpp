// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;
const int MOD = 10007;

int n, m;
int number_val[MAXN];
int color_val[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> number_val[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> color_val[i];
    }

    int answer = 0;

    // 直接枚举左右端点 x,z。
    // 只要它们同颜色、并且中点 y 是整数，就会对应一个合法三元组。
    for (int x = 1; x <= n; x++) {
        for (int z = x + 1; z <= n; z++) {
            if (((x + z) & 1) != 0) continue;
            if (color_val[x] != color_val[z]) continue;

            int y = (x + z) / 2;
            if (!(x < y && y < z)) continue;

            int score = 1LL * (x + z) * (number_val[x] + number_val[z]) % MOD;
            answer += score;
            answer %= MOD;
        }
    }

    cout << answer % MOD << '\n';
    return 0;
}
