/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:36
 * update_at: 2026-10-06 10:36
 */
#include <cstdio>
#include <string>
#include <iostream>

typedef long long ll;

using std::string;

string inorder_str;  // 中序遍历序列
string preorder_str; // 前序遍历序列

// 递归输出后序遍历：左子树 -> 右子树 -> 根
// l1, r1 是当前中序序列的区间，l2, r2 是当前前序序列的区间（闭区间）
void dfs(ll l1, ll r1, ll l2, ll r2) {
    if (l1 > r1) return; // 空子树

    // 前序的第一个字符就是当前子树的根
    char root = preorder_str[l2];

    // 节点字母唯一，在中序中找根的位置，左边是左子树，右边是右子树
    ll mid = l1;
    while (inorder_str[mid] != root) mid++;

    ll left_len = mid - l1; // 左子树节点个数

    dfs(l1, mid - 1, l2 + 1, l2 + left_len);              // 先递归左子树
    dfs(mid + 1, r1, l2 + left_len + 1, r2);              // 再递归右子树
    std::cout << root;                                    // 最后输出根
}

int main() {
    std::cin >> inorder_str >> preorder_str;
    ll n = inorder_str.size();

    dfs(0, n - 1, 0, n - 1);
    std::cout << "\n";
    return 0;
}
