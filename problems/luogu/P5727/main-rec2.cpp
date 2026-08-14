/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 11:26
 * update_at: 2026-08-14 11:26
 */
#include <bits/stdc++.h>
using namespace std;

int a[10000];
int cnt;
// 递归生成冰雹序列：dfs(x) 表示处理当前数字 x。
// 先递归计算下一步，回溯时再输出 x，
// 这样输出的顺序正好是题目要求的倒序（从 1 开始）。
void dfs(int x) {
    a[++cnt] = x;
    if (x == 1) {          // 到达序列末尾 1，开始回溯输出
        return;
    }
    if (x % 2 == 1)        // 奇数：下一步是 3x+1
        dfs(x * 3 + 1);
    else                   // 偶数：下一步是 x/2
        dfs(x / 2);
}

int main() {
    int n;
    cin >> n;
    dfs(n);                // 从初始值开始递归
    for(int i = cnt; i >= 1 ;--i )
        cout << a[i] << " ";
    return 0;
}
