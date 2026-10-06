/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:42
 * update_at: 2026-10-06 13:42
 */

#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 30005;

ll w;           // 每组价格之和的上界
int n;          // 纪念品件数
ll p[MAXN];     // 各纪念品价格

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> w;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> p[i];

    sort(p, p + n); // 升序排序

    int lo = 0, hi = n - 1;
    int groups = 0;
    while (lo <= hi) {
        if (lo < hi && p[lo] + p[hi] <= w) // 最便宜的能陪最贵的
            ++lo;                           // 配对成功，lo 前进
        --hi;                               // hi 每轮都处理掉
        ++groups;
    }

    cout << groups << '\n';
    return 0;
}
