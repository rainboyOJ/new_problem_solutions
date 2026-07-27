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
    int n;
    cin >> n;
    int peaches = 1; // 第 n 天早上剩 1 个
    // 倒推 n-1 次，回到第 1 天
    for (int i = 1; i < n; i++) {
        peaches = (peaches + 1) * 2;
    }
    cout << peaches;
    return 0;
}
