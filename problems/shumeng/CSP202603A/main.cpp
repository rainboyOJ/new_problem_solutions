/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-07-31 16:22
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int answer = 0;
    for (int i = 0; i < n; i++) {
        unsigned int value;
        cin >> value;
        int ones = 0;
        int zeros = 0;
        while (value > 0) {
            if (value & 1U) ones++;
            else zeros++;
            value >>= 1;
        }
        if (ones == zeros) answer++;
    }
    cout << answer << '\n';
    return 0;
}
