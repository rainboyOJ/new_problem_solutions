/**
 * P4715 【深基16.例1】淘汰赛
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 260;

// 完全二叉树：tree[i] 存两个值
// [节点能力值, 该国原始编号]
pair<int,int> tree[MAXN * 2];
int n;

int main() {
    scanf("%d", &n);
    int total = 1 << n; // 选手总数 = 2^n
    // 读入叶子（第 1 轮选手）
    for (int i = total; i < 2 * total; ++i) {
        scanf("%d", &tree[i].first);
        tree[i].second = i - total + 1; // 原始编号
    }
    // 自底向上模拟淘汰赛
    for (int i = total - 1; i >= 1; --i) {
        int l = i * 2, r = i * 2 + 1;
        if (tree[l].first > tree[r].first) tree[i] = tree[l];
        else tree[i] = tree[r];
    }
    // 亚军 = 总决赛中输给冠军的一方
    if (tree[2].first > tree[3].first) printf("%d\n", tree[3].second);
    else printf("%d\n", tree[2].second);
    return 0;
}
