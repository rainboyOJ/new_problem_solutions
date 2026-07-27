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
    double target; // 目标距离
    cin >> target;
    double distance = 0.0; // 已经游过的总距离
    double step = 2.0;     // 当前这一步能游的距离
    int answer = 0;        // 步数
    // 还没到目标就继续游
    while (distance < target) {
        distance += step;  // 游这一步
        step *= 0.98;      // 下一步距离是这一步的 98%
        answer++;          // 步数加 1
    }
    cout << answer << endl;
    return 0;
}
