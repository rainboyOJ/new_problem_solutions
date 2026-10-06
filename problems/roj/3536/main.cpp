/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:27
 * update_at: 2026-10-06 13:27
 */
#include <iostream>
using namespace std;

typedef long long ll;

const int STOOL = 30; // 板凳高度 30 厘米

ll a[15]; // 10 个苹果高度

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 读入 10 个苹果高度
    for (int i = 1; i <= 10; ++i) {
        cin >> a[i];
    }

    ll hand;
    cin >> hand; // 伸手高度

    ll reach = hand + STOOL; // 踩板凳后能碰到的最大高度
    ll cnt = 0; // 能摘到的苹果个数

    for (int i = 1; i <= 10; ++i) {
        if (a[i] <= reach) {
            ++cnt;
        }
    }

    cout << cnt << "\n";
    return 0;
}
