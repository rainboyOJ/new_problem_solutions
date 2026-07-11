/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 13:03
 * update_at: 2026-07-11 13:08
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
long long T;
long long day_arr[MAXN];
long long bale_arr[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> T;
    for (int i = 1; i <= n; i++) {
        cin >> day_arr[i] >> bale_arr[i];
    }

    // 哨兵交货日，用来统一处理最后一次交货到第 T 天的吃草过程。
    day_arr[n + 1] = T + 1;
    bale_arr[n + 1] = 0;

    long long remain = 0;      // 当前仓库里还剩多少草包。
    long long answer = 0;      // 前 T 天实际吃掉的草包数。
    long long last_day = 1;    // 上一次开始统计吃草的日期。

    for (int i = 1; i <= n + 1; i++) {
        long long days = day_arr[i] - last_day;
        long long eat = min(remain, days);

        answer += eat;
        remain -= eat;

        remain += bale_arr[i];
        last_day = day_arr[i];
    }

    cout << answer << '\n';

    return 0;
}
