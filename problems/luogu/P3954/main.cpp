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
    int a, b, c; // 作业、小测、期末成绩
    cin >> a >> b >> c;
    // 将百分比权重转为整数：20%→2，30%→3，50%→5，总和除以 10
    int score = (a * 2 + b * 3 + c * 5) / 10;
    cout << score << endl;
    return 0;
}
