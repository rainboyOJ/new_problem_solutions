/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-27 21:38
 * update_at: 2026-09-27 21:38
 */
// subtask_05.cpp：测试点 1，所有询问都只有一轮接龙。
#include <bits/stdc++.h>
using namespace std;

const int MAXV = 200005;

bool reachable[MAXV];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, k, q;
        cin >> n >> k >> q;

        memset(reachable, 0, sizeof(reachable));

        for (int person = 1; person <= n; person++) {
            int len;
            cin >> len;
            vector<int> seq(len + 1);
            for (int i = 1; i <= len; i++) {
                cin >> seq[i];
            }

            // 第一轮必须从值 1 开始。
            for (int left = 1; left <= len; left++) {
                if (seq[left] != 1) continue;
                int right_end = min(len, left + k - 1);
                for (int right = left + 1; right <= right_end; right++) {
                    reachable[seq[right]] = true;
                }
            }
        }

        for (int i = 1; i <= q; i++) {
            int round, value;
            cin >> round >> value;
            // 本文件只面向保证 round = 1 的测试点。
            cout << (round == 1 && reachable[value] ? 1 : 0) << '\n';
        }
    }

    return 0;
}
