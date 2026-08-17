/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:41
 */
#include <bits/stdc++.h>
using namespace std;

// 判断数字 number 是否应该跳过：是 7 的倍数，或十进制表示中含有数字 7。
bool should_skip(int number) {
    if (number % 7 == 0) return true;
    while (number > 0) {
        if (number % 10 == 7) return true;
        number /= 10;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int skipped[4] = {};  // 甲乙丙丁四人各自跳过的次数
    int said_count = 0;   // 已经真正报出的数字个数
    for (int number = 1; said_count < n; number++) {
        int player = (number - 1) % 4; // 当前数字轮到谁
        if (should_skip(number)) {
            skipped[player]++;
        } else {
            said_count++;
        }
    }
    for (int i = 0; i < 4; i++) cout << skipped[i] << '\n';

    return 0;
}