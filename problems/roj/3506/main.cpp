/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 12:15
 * update_at: 2026-10-06 12:15
 */
#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

string inorder, postorder;

// 由中序区间 [l1, r1] 与后序区间 [l2, r2] 递归输出先序
void preorder(ll l1, ll r1, ll l2, ll r2) {
    if (l1 > r1 || l2 > r2) return; // 空子树
    char root = postorder[r2];      // 后序末位是根
    cout << root;
    ll i = l1;
    while (i <= r1 && inorder[i] != root) ++i; // 根在中序中的位置
    ll left_size = i - l1;          // 左子树结点个数
    // 左子树：中序 [l1, i-1]，后序 [l2, l2+left_size-1]
    preorder(l1, i - 1, l2, l2 + left_size - 1);
    // 右子树：中序 [i+1, r1]，后序 [l2+left_size, r2-1]
    preorder(i + 1, r1, l2 + left_size, r2 - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> inorder >> postorder;
    ll n = inorder.size();
    preorder(0, n - 1, 0, n - 1);
    cout << '\n';
    return 0;
}
