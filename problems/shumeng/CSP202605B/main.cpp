/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-07-31 16:22
 */
#include <bits/stdc++.h>
using namespace std;

long long apples_initial;
long long spoil_percent;
long long days;

bool can_feed(long long robots) {
    long long apples = apples_initial;
    for (long long day = 0; day < days; day++) {
        long long spoiled = (apples * spoil_percent + 99) / 100;
        apples -= spoiled;
        if (apples < robots) return false;
        apples -= robots;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> apples_initial >> spoil_percent >> days;

    long long left = 0, right = apples_initial;
    while (left < right) {
        long long middle = left + (right - left + 1) / 2;
        if (can_feed(middle)) left = middle;
        else right = middle - 1;
    }
    cout << left << '\n';
    return 0;
}
