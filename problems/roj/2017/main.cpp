/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:32
 * update_at: 2026-10-06 09:32
 */
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXR = 1005;

ll prev_row[MAXR]; // prev_row[j] 表示走到上一层第 j 个数的最大路径和
ll cur_row[MAXR];  // cur_row[j] 表示走到当前层第 j 个数的最大路径和

int main() {
    int R;
    if (!(cin >> R)) {
        return 0;
    }

    ll value;
    cin >> value;
    prev_row[1] = value; // 第一层只有一个数，它就是起点

    for (int i = 2; i <= R; i++) {
        for (int j = 1; j <= i; j++) {
            cin >> value;
            // 第 j 个数只能从上一层第 j-1、j 个数走下来；不存在的来源记为 -1
            ll from_left = (j >= 2) ? prev_row[j - 1] : -1;
            ll from_up = (j <= i - 1) ? prev_row[j] : -1;
            cur_row[j] = value + max(from_left, from_up);
        }
        for (int j = 1; j <= i; j++) {
            prev_row[j] = cur_row[j];
        }
    }

    // 终点可以停在底层任意位置，答案是末行的最大值
    ll answer = prev_row[1];
    for (int j = 2; j <= R; j++) {
        answer = max(answer, prev_row[j]);
    }
    cout << answer << "\n";
    return 0;
}
