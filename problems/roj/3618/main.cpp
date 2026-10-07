/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 15:14
 * update_at: 2026-10-06 15:14
 */
// main.cpp：升级版石头剪刀布，按各自周期出拳，逐轮判胜并累计得分。
#include <iostream>

typedef long long ll;

const int MAXN = 205;

// 胜负表：beats[i][j] 为 1 表示手势 i 胜手势 j。
// 手势编号：0 剪刀，1 石头，2 布，3 蜥蜴人，4 斯波克。
int beats[5][5];

int seq_a[MAXN]; // 小 A 的出拳周期
int seq_b[MAXN]; // 小 B 的出拳周期

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // 五种手势各胜另外两种，共 10 对
    beats[0][2] = 1; beats[0][3] = 1; // 剪刀胜布、蜥蜴人
    beats[1][0] = 1; beats[1][3] = 1; // 石头胜剪刀、蜥蜴人
    beats[2][1] = 1; beats[2][4] = 1; // 布胜石头、斯波克
    beats[3][2] = 1; beats[3][4] = 1; // 蜥蜴人胜布、斯波克
    beats[4][0] = 1; beats[4][1] = 1; // 斯波克胜剪刀、石头

    ll n, len_a, len_b;
    std::cin >> n >> len_a >> len_b;

    for (ll i = 0; i < len_a; i++) {
        std::cin >> seq_a[i];
    }
    for (ll i = 0; i < len_b; i++) {
        std::cin >> seq_b[i];
    }

    ll score_a = 0;
    ll score_b = 0;
    for (ll r = 0; r < n; r++) {
        int hand_a = seq_a[r % len_a]; // 第 r 轮小 A 的手势
        int hand_b = seq_b[r % len_b]; // 第 r 轮小 B 的手势
        if (beats[hand_a][hand_b]) {
            score_a++;
        } else if (beats[hand_b][hand_a]) {
            score_b++;
        }
    }

    std::cout << score_a << ' ' << score_b << std::endl;
    return 0;
}
