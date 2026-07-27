/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005; // 候选人编号最大值

int n, m;
int cnt[MAXN]; // 计数数组，cnt[x] 表示编号 x 获得的票数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    // 统计每张票
    for (int i = 0; i < m; i++) {
        int vote;
        cin >> vote;
        cnt[vote]++;
    }

    // 按编号从小到大展开输出
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < cnt[i]; j++) {
            cout << i << " ";
        }
    }
    cout << "\n";

    return 0;
}
