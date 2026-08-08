/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

int cost[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int calc(int x) {
    if (x == 0) return cost[0];
    int sum = 0;
    while (x) { sum += cost[x % 10]; x /= 10; }
    return sum;
}

int n, ans;
int cost_pre[2005]; // 预处理 0..2000 的火柴消耗

int main() {
    cin >> n;
    int target = n - 4;
    for (int i = 0; i <= 2000; i++) cost_pre[i] = calc(i);
    for (int a = 0; a <= 1000; a++) {
        int ca = cost_pre[a];
        for (int b = 0; b <= 1000; b++) {
            int c = a + b;
            if (c > 2000) continue; // 不超过范围
            if (ca + cost_pre[b] + cost_pre[c] == target) ans++;
        }
    }
    cout << ans << endl;
    return 0;
}
