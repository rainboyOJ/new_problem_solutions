/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-08-17 22:40
 */
#include <bits/stdc++.h>
using namespace std;

long long apples_initial; // 初始苹果数量 n
long long spoil_percent;  // 每日变质比例 k%
long long days;           // 需要支撑的天数 m

// 判断 robots 个机器人能否支撑 days 天：
// 每天先丢弃 ceil(t*k/100) 个变质苹果，再让每个机器人吃一个。
bool can_feed(long long robots) {
    long long apples = apples_initial;
    for (long long day = 0; day < days; day++) {
        long long spoiled = (apples * spoil_percent + 99) / 100; // 向上取整
        apples -= spoiled;
        if (apples < robots) return false; // 不够吃就失败
        apples -= robots;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> apples_initial >> spoil_percent >> days;

    // 机器人越多越难支撑，可行性单调，二分最大的可行值。
    long long left = 0, right = apples_initial;
    while (left < right) {
        long long middle = left + (right - left + 1) / 2;
        if (can_feed(middle)) {
            left = middle;
        } else {
            right = middle - 1;
        }
    }
    cout << left << '\n';
    return 0;
}