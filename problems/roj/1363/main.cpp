/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:07
 * update_at: 2026-10-05 12:07
 */

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll D, I; // D 为满二叉树深度，I 表示第 I 个下落的小球

int main() {
    scanf("%lld %lld", &D, &I);

    ll node = 1; // 当前所在节点编号，从根开始
    for (ll i = 1; i <= D - 1; ++i) {
        // 第 j 个到达该节点的球：j 奇数走左，偶数走右
        // 第 I 个球在本节点是第 I 个，即 I 的奇偶决定方向
        ll go_left = I & 1;
        node = 2 * node + (1 - go_left);
        // 走左的球占前一半序号（1..⌈I/2⌉），走右的占后一半，序号折半
        I = (I + go_left) >> 1;
    }

    printf("%lld\n", node);
    return 0;
}
