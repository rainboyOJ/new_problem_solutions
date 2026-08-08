/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

int a, b, c;

int main() {
    cin >> a >> b >> c;
    if (a == 0) { cout << "No!!!" << endl; return 0; }
    bool found = false;
    int left = (100 + a - 1) / a;   // 上取整, 保证 x 至少三位数
    int right = 999 / c;            // 保证 z 最多三位数
    for (int t = left; t <= right; t++) {
        int x = a * t, y = b * t, z = c * t;
        int cnt[10] = {0};
        cnt[x/100]++; cnt[x/10%10]++; cnt[x%10]++;
        cnt[y/100]++; cnt[y/10%10]++; cnt[y%10]++;
        cnt[z/100]++; cnt[z/10%10]++; cnt[z%10]++;
        bool ok = true;
        for (int d = 1; d <= 9; d++)
            if (cnt[d] != 1) { ok = false; break; }
        if (!ok || cnt[0] > 0) continue;
        found = true;
        cout << x << " " << y << " " << z << endl;
    }
    if (!found) cout << "No!!!" << endl;
    return 0;
}
