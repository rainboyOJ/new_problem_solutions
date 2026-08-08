/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    int N; // 一年存的总钱数
    cin >> N;
    // 代数化简后：N = 364 * X + 1092 * K
    // 要输出最大的 X，所以从 100 倒着枚举
    for (int x = 100; x >= 0; x--) {
        int rest = N - 364 * x;
        // 剩下的钱要能被 1092 整除，且 K > 0
        if (rest > 0 && rest % 1092 == 0) {
            int k = rest / 1092;
            cout << x << endl << k << endl;
            break;
        }
    }
    return 0;
}
