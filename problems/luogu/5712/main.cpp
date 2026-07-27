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
    int x; // 吃掉的苹果数量
    cin >> x;
    cout << "Today, I ate " << x << " ";
    // 数量为 1 用单数 apple，否则用复数 apples
    if (x == 1) {
        cout << "apple";
    } else {
        cout << "apples";
    }
    cout << "." << endl;
    return 0;
}
