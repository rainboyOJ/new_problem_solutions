/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:58
 * update_at: 2026-10-05 03:58
 */

// 阿克曼(Ackmann)函数：把三分支定义逐条翻译成递归函数。
// 数据规模 m<=3、n<=10，答案最大 A(3,10)=8189，递归深度最多约 8190 层，
// C++ 的调用栈完全够用，直接照抄定义即可，不需要记忆化或改成递推。

#include <cstdio>

typedef long long ll;

ll m, n; // 输入的一对非负整数

// ackermann(m, n)：按定义返回 A(m, n)
ll ackermann(ll m, ll n) {
    if (m == 0) {
        return n + 1; // 分支一：A(0, n) = n + 1
    }
    if (n == 0) {
        return ackermann(m - 1, 1); // 分支二：A(m, 0) = A(m-1, 1)
    }
    // 分支三：A(m, n) = A(m-1, A(m, n-1))，内层先算出 A(m, n-1) 再作为下标传下去
    return ackermann(m - 1, ackermann(m, n - 1));
}

int main() {
    scanf("%lld %lld", &m, &n);
    printf("%lld\n", ackermann(m, n));
    return 0;
}
