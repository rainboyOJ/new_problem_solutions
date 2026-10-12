/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:07
 * update_at: 2026-10-12 14:55
 */
// main.cpp：满二叉树小球下落：奇偶折半递推直接定位叶子，O(D) 时间、O(1) 空间。
//
// 不建树、不模拟每个结点的布尔标记：所有球都经过根，第 I 个球就是第 I 个到达根的球；
// 第 j 个到达某结点的球，j 为奇数走左、偶数走右，走左的球占前一半序号、走右的占后一半。
// 所以只需跟踪"第几个球在当前子树里的序号"，逐层定方向并折半，走 D-1 层即落在叶子上
// （满二叉树按层序编号：结点 k 的左孩子 2k、右孩子 2k+1）。

#include <cstdio>

typedef long long ll;

ll depth; // 满二叉树的深度 D（2 ≤ D ≤ 20），从根到叶子要走 depth-1 层
ll ball;  // 小球序号 I（1 ≤ I ≤ 524288，不超过叶子数 2^(D-1)）

// 求第 ball 个小球停下时的叶子编号：每层用序号的奇偶定方向，再把序号折半
ll find_leaf(ll depth, ll ball) {
    ll node = 1; // 当前所在结点编号，根是 1
    for (ll i = 1; i <= depth - 1; i++) {
        ll go_left = ball & 1; // 该结点第奇数次被访问的球走左，偶数次走右
        node = 2 * node + (1 - go_left);
        ball = (ball + go_left) >> 1; // 走左的球挤进前一半序号，走右的落到后一半
    }
    return node;
}

// 读入 D、I，输出第 I 个小球停止时的叶子序号
void solve() {
    scanf("%lld %lld", &depth, &ball);
    printf("%lld\n", find_leaf(depth, ball));
}

int main() {
    solve();
    return 0;
}
