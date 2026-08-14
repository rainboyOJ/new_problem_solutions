/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 15:01
 * update_at: 2026-08-14 15:20
 */
// P10840 【MX-J2-T1】Turtle and Sequences
// 每次操作删除一个元素，上界 n-1 次。
// 若序列不是全相同，总能通过把 a_i 改成全新值继续操作，答案为 n-1；
// 若全相同则无法开始，答案为 0。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
long long a[MAXN]; // 输入序列

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // 判断是否所有元素相等
    bool all_same = true;
    for (int i = 2; i <= n; i++) {
        if (a[i] != a[1]) {
            all_same = false;
            break;
        }
    }

    cout << (all_same ? 0 : n - 1) << '\n';
    return 0;
}
