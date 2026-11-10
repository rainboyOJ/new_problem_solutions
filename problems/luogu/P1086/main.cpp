/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 22:57
 * update_at: 2026-11-10 22:57
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// 花生植株结构体，记录坐标和花生数量
struct Peanut {
    int x;
    int y;
    int val;

    bool operator<(const Peanut& other) const {
        return val > other.val; // 按花生数从大到小排序
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n, k;
    if (!(cin >> m >> n >> k)) return 0;

    vector<Peanut> peanuts;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int val;
            cin >> val;
            if (val > 0) {
                peanuts.push_back({i, j, val});
            }
        }
    }

    sort(peanuts.begin(), peanuts.end());

    int total_peanuts = 0;
    int time_used = 0;
    int cur_x = 0;
    int cur_y = 0;

    for (size_t i = 0; i < peanuts.size(); ++i) {
        int target_x = peanuts[i].x;
        int target_y = peanuts[i].y;

        int move_time = 0;
        if (i == 0) {
            // 从路边进入，直接跳到 (1, target_y) 并走到 (target_x, target_y)
            // 总共耗时 target_x 步
            move_time = target_x;
        } else {
            // 从上一个植株走到当前植株，耗费曼哈顿距离
            move_time = abs(target_x - cur_x) + abs(target_y - cur_y);
        }

        int pick_time = 1;
        int return_time = target_x; // 返回路边耗时 target_x 步

        // 判断采摘完后能否顺利返回路边
        if (time_used + move_time + pick_time + return_time <= k) {
            time_used += move_time + pick_time;
            total_peanuts += peanuts[i].val;
            cur_x = target_x;
            cur_y = target_y;
        } else {
            // 无法安全返回，必须放弃后续所有采摘
            break;
        }
    }

    cout << total_peanuts << "\n";

    return 0;
}
