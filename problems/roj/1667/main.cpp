/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:25
 * update_at: 2026-10-06 01:25
 */

#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 15;

ll a[MAXN]; // a[j] 表示第 j 根巧克力棒的长度

// 判断盒中是否存在非空子集，其异或和为 0（即棒长向量组线性相关）。
// 逐根插入线性基：x 与基中元素异或时最高位严格变小，过程必然终止；
// 若 x 最终异或到 0，说明它被现有基表出 → 出现异或和为 0 的子集。
bool has_zero_subset(int n) {
    ll basis[35]; // 线性基：basis[k] 的最高位是第 k 位
    int top = 0;  // 当前基中元素个数
    for (int i = 1; i <= n; i++) {
        ll x = a[i];
        for (int k = 0; k < top; k++)
            x = min(x, x ^ basis[k]); // 与基中元素异或，直到最高位无法再降
        if (x == 0)
            return true; // 该棒能被已有基表出 → 存在异或和为 0 的子集
        // 把 x 插入基中：保持基元素按最高位从大到小的顺序
        int pos = 0;
        while (pos < top && basis[pos] > x) pos++;
        for (int k = top; k > pos; k--)
            basis[k] = basis[k - 1];
        basis[pos] = x;
        top++;
    }
    return false;
}

int main() {
    for (int round = 1; round <= 10; round++) {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%lld", &a[i]);
        // 先手能把任意非空子集一次性移出盒子：
        // 移出的部分若能凑出异或和为 0，先手就掌握一个后手永远拿不回的 Nim 必胜态
        bool win = has_zero_subset(n);
        if (win)
            printf("NO\n"); // 胜则输出 NO，负则输出 YES
        else
            printf("YES\n");
    }
    return 0;
}
