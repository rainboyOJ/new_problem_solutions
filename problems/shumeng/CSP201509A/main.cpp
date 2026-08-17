/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:54
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    // 第一个数字一定形成第一段。
    int previous;
    cin >> previous;
    int answer = 1;
    // 相邻数字不同就说明新的一段从这里开始。
    for (int i = 2; i <= n; i++) {
        int current;
        cin >> current;
        if (current != previous) answer++;
        previous = current;
    }
    cout << answer << '\n';
    return 0;
}
