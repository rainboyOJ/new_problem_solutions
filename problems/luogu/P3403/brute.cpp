/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-17 01:40
 * update_at: 2026-10-21 09:10
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 直接按楼层标记：从 1 楼出发，每次尝试加 x/y/z，标出所有不超过 h 的可达楼层，最后数个数。
// 与 main.cpp 的同余最短路完全不共享实现，因此适合用来独立验证 main.cpp。
// 复杂度 O(h)，只在 h 很小时可用。
#include <bits/stdc++.h>
using namespace std;

const int MAXH = 1000005;  // 只枚举极小数据：h <= 1e6

int h;
int step[3];
bool reachable[MAXH];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> h;
    for (int i = 0; i < 3; i++) cin >> step[i];

    // 从 1 楼开始做一次 BFS/DFS：楼层只会增加，所以不需要队列，栈即可
    vector<int> stack;
    reachable[1] = true;
    stack.push_back(1);

    while (!stack.empty()) {
        int floor_now = stack.back();
        stack.pop_back();

        for (int i = 0; i < 3; i++) {
            int next_floor = floor_now + step[i];
            if (next_floor <= h && !reachable[next_floor]) {
                reachable[next_floor] = true;
                stack.push_back(next_floor);
            }
        }
    }

    long long answer = 0;
    for (int f = 1; f <= h; f++) {
        if (reachable[f]) answer++;
    }
    cout << answer << '\n';
    return 0;
}
