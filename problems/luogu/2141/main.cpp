/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int a[105];        // 原数组
bool exist[20005]; // exist[sum] = true 表示 sum 可以由两个不同数相加得到
int n, ans;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    // 枚举所有 i < j 的数对
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            exist[a[i] + a[j]] = true;
        }
    }
    // 统计哪些数在 exist 中
    for (int i = 1; i <= n; i++) {
        if (exist[a[i]]) ans++;
    }
    cout << ans;
    return 0;
}
