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
    int usage; // 月用电量
    cin >> usage;
    double fee;
    // 三段阶梯电价，每段只算自己管辖的超出的部分
    if (usage <= 150) {
        fee = usage * 0.4463;
    } else if (usage <= 400) {
        fee = 150 * 0.4463 + (usage - 150) * 0.4663;
    } else {
        fee = 150 * 0.4463 + 250 * 0.4663 + (usage - 400) * 0.5663;
    }
    // 保留 1 位小数
    printf("%.1f\n", fee);
    return 0;
}
