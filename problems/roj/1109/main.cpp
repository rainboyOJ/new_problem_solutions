/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 01:40
 * update_at: 2026-10-05 01:40
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 5005;

int n, m;
// off[j] = 1 表示灯 j 被翻过奇数次（初始全亮，翻奇数次即最终关闭）。
int off[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m)) return 0;

    // 1 号"全部关闭"、2 号"打开 2 的倍数"、k>=3 号"取反 k 的倍数"，
    // 三类操作在"初始全亮"下都等价于：把该人编号的倍数翻转一次。
    // 循环直接落在倍数上，省掉 j % k == 0 的逐灯判断。
    for (int d = 1; d <= m; d++) {
        for (int j = d; j <= n; j += d) {
            off[j] ^= 1;
        }
    }

    bool first = true;
    for (int j = 1; j <= n; j++) {
        if (off[j]) {
            if (!first) cout << ',';
            cout << j;
            first = false;
        }
    }
    cout << '\n';
    return 0;
}
