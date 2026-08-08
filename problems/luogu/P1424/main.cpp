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
    int x, n; // 起始星期几，经过天数
    cin >> x >> n;
    // 完整周数，每周 5 个工作日
    int full_weeks = n / 7;
    int rest_days = n % 7;
    int work_days = full_weeks * 5;
    // 剩余不足一周的天数，逐天判断是否为工作日
    for (int i = 0; i < rest_days; i++) {
        // 星期编号保持在 1~7
        int weekday = (x + i - 1) % 7 + 1;
        if (weekday <= 5) {
            work_days++;
        }
    }
    // 每天游 250 公里
    cout << work_days * 250 << endl;
    return 0;
}
