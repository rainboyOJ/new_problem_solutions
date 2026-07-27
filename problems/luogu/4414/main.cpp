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
    int a[3]; // 三个数
    cin >> a[0] >> a[1] >> a[2];
    // 排序为 a[0]<=a[1]<=a[2]，对应 A(最小) B(中间) C(最大)
    if (a[0] > a[1]) swap(a[0], a[1]);
    if (a[1] > a[2]) swap(a[1], a[2]);
    if (a[0] > a[1]) swap(a[0], a[1]);

    char order[4]; // 输出顺序字符串，如 "ABC"
    cin >> order;
    for (int i = 0; order[i] != '\0'; i++) {
        if (i > 0) cout << " "; // 空格分隔
        if (order[i] == 'A') {
            cout << a[0];
        } else if (order[i] == 'B') {
            cout << a[1];
        } else {
            cout << a[2];
        }
    }
    cout << endl;
    return 0;
}
