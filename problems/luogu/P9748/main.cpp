#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    cin >> n;

    long long rest = n;
    long long total_days = 0;
    while (rest > 0) {
        ++total_days;
        // 每天拿走当前位置为 1,4,7,... 的苹果，剩下 floor(2*rest/3) 个。
        rest = rest * 2 / 3;
    }

    long long pos = n;
    long long removed_day = 0;
    while (pos > 0) {
        ++removed_day;
        if (pos % 3 == 1) {
            break;
        }
        // 原来的第 pos 个苹果没被拿走，删除它左边若干苹果后位置变小。
        pos = pos * 2 / 3;
    }

    cout << total_days << ' ' << removed_day << '\n';
    return 0;
}
