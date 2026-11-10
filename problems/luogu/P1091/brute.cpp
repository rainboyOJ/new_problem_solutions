/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 22:57
 * update_at: 2026-11-10 22:57
 */
// brute.cpp：纯枚举峰顶位置 + 递归求 LIS/LDS，作为基准
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n;
int t[105];

// 递归求以 idx 结尾的 LIS
int get_lis(int idx) {
    int res = 1;
    for (int j = 1; j < idx; ++j) {
        if (t[j] < t[idx]) {
            res = max(res, get_lis(j) + 1);
        }
    }
    return res;
}

// 递归求以 idx 开头的 LDS
int get_lds(int idx) {
    int res = 1;
    for (int j = idx + 1; j <= n; ++j) {
        if (t[j] < t[idx]) {
            res = max(res, get_lds(j) + 1);
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n)) return 0;
    for (int i = 1; i <= n; ++i) {
        cin >> t[i];
    }

    int max_keep = 0;
    for (int i = 1; i <= n; ++i) {
        int cur = get_lis(i) + get_lds(i) - 1;
        max_keep = max(max_keep, cur);
    }

    cout << n - max_keep << "\n";

    return 0;
}
