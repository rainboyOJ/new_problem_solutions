/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:49
 * update_at: 2026-11-10 19:52
 */
// main.cpp：众数频次统计法。
// 核心思路：相同战力的怪兽无法相互击杀，若战力 x 出现次数为 cnt[x]，
// 则任何时刻至少保留 cnt[x] 只怪兽存活；贪心构造可证明最终未退出游戏的怪兽数恰为 max(cnt[x])。
#include <iostream>
#include <algorithm>

using namespace std;

// 战力值域上限为 10^5
const int MAX_R = 100005;

// cnt[x] 表示战力为 x 的怪兽数量
int cnt[MAX_R];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int max_freq = 0; // 出现频次的最大值（众数频次即最终最少剩余怪兽数）
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
        max_freq = max(max_freq, cnt[x]);
    }

    cout << max_freq << '\n';

    return 0;
}
