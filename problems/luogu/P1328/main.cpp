/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

// win[a][b] = 1 表示手势 a 能赢手势 b
int win[5][5] = {
    {0, 0, 1, 1, 0},
    {1, 0, 0, 1, 0},
    {0, 1, 0, 0, 1},
    {0, 0, 1, 0, 1},
    {1, 1, 0, 0, 0},
};

const int MAXLEN = 205;

int n, len_a, len_b;
int a[MAXLEN]; // A 的出拳周期
int b[MAXLEN]; // B 的出拳周期

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> len_a >> len_b;
    for (int i = 0; i < len_a; i++) cin >> a[i];
    for (int i = 0; i < len_b; i++) cin >> b[i];

    int score_a = 0, score_b = 0;

    // 模拟 n 轮
    for (int i = 0; i < n; i++) {
        int ga = a[i % len_a]; // 取模得到当前手势
        int gb = b[i % len_b];
        if (win[ga][gb])       // A 赢
            score_a++;
        else if (win[gb][ga])  // B 赢
            score_b++;
        // 平局不处理
    }

    cout << score_a << " " << score_b << "\n";

    return 0;
}
