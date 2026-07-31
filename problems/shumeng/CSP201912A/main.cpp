/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 20:09
 */
#include <bits/stdc++.h>
using namespace std;

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
    int skipped[4] = {};
    int said_count = 0;
    for (int number = 1; said_count < n; number++) {
        int player = (number - 1) % 4;
        if (should_skip(number)) {
            skipped[player]++;
        } else {
            said_count++;
        }
    }
    for (int i = 0; i < 4; i++) cout << skipped[i] << '\n';

    return 0;
}
