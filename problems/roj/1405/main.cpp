/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:02
 * update_at: 2026-10-05 23:02
 */
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXS = 10005;

bool is_comp[MAXS]; // is_comp[x] = true 表示 x 是合数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int S;
    if (!(cin >> S)) return 0;

    // 埃氏筛标记合数
    for (int i = 2; i * i <= S; ++i) {
        if (!is_comp[i]) {
            for (int j = i * i; j <= S; j += i) {
                is_comp[j] = true;
            }
        }
    }

    // 从 S/2 向下枚举较小质数 p，首个满足 p 与 S-p 均为质数的即最优
    int ans = 0;
    for (int p = S / 2; p >= 2; --p) {
        if (!is_comp[p] && !is_comp[S - p]) {
            ans = p * (S - p);
            break;
        }
    }

    cout << ans << "\n";
    return 0;
}
