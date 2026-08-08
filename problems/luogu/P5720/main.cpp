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
    int length; // 第一天木棍长度
    cin >> length;
    int days = 1; // 第一天已经算一天
    // 每天长度折半（向下取整），直到长度为 1
    while (length > 1) {
        length /= 2;
        days++;
    }
    cout << days << endl;
    return 0;
}
