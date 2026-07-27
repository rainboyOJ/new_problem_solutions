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
    int n; // 评委人数
    cin >> n;
    int scores[1005]; // 存储所有评分
    int sum = 0;
    int max_val = 0;    // 最高分
    int min_val = 101;  // 最低分（分数范围 0~100）
    for (int i = 0; i < n; i++) {
        cin >> scores[i];
        sum += scores[i];
        if (scores[i] > max_val) max_val = scores[i];
        if (scores[i] < min_val) min_val = scores[i];
    }
    // 去掉一个最高分和一个最低分后取平均
    double avg = (double)(sum - max_val - min_val) / (n - 2);
    printf("%.2f\n", avg);
    return 0;
}
