/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-28 18:13
 * update_at: 2026-07-28 18:15
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;

int n, target;
int nums[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> target;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    // 直接枚举所有 i < j 的下标对，只适合小数据。
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nums[i] + nums[j] == target) {
                cout << i << ' ' << j << '\n';
                return 0;
            }
        }
    }

    return 0;
}
