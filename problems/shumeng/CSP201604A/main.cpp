/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:48
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n;
int sales[MAXN]; // 每天的销售量

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> sales[i];
    }

    int answer = 0;
    // 第 i 天是折点，当且仅当前一段与后一段的增减方向相反。
    // 相邻两天的销量保证不同，因此两个差值乘积为负就说明方向相反。
    for (int i = 2; i <= n - 1; i++) {
        int diff1 = sales[i] - sales[i - 1];
        int diff2 = sales[i + 1] - sales[i];
        if (diff1 * diff2 < 0) {
            answer++;
        }
    }
    cout << answer << '\n';
    return 0;
}