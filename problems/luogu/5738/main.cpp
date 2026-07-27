/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int n, m;

int main() {
    cin >> n >> m;
    double best = 0; // 最高平均分
    for (int i = 1; i <= n; i++) {
        int sum = 0, maxs = 0, mins = 105;
        for (int j = 1; j <= m; j++) {
            int x;
            cin >> x;
            sum += x;
            if (x > maxs) maxs = x;
            if (x < mins) mins = x;
        }
        // 去掉最高分和最低分后的平均分
        double avg = 1.0 * (sum - maxs - mins) / (m - 2);
        if (avg > best) best = avg;
    }
    printf("%.2f", best);
    return 0;
}
