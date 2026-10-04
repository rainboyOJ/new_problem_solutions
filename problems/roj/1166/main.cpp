/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:06
 * update_at: 2026-10-05 04:06
 */

// 求 f(x,n) = sqrt(n + sqrt(n-1 + ... + sqrt(2 + sqrt(1+x)))) 的值。
// 把嵌套根式看成递推 g_1 = sqrt(1+x)、g_k = sqrt(k + g_{k-1})，
// 从内层向外层一次循环折叠，O(n) 时间 O(1) 空间，保留两位小数输出。

#include <cstdio>
#include <cmath>

typedef long long ll;

double x;     // 嵌套根式中的实数
ll n_layer;   // 嵌套层数

int main() {
    scanf("%lf %lld", &x, &n_layer);

    double total = sqrt(1.0 + x); // 最内层 g_1 = sqrt(1+x)
    // 从第 2 层折到第 n_layer 层，每层把层号 k 加进根号再开方
    for (ll k = 2; k <= n_layer; k++) {
        total = sqrt(k + total); // ll 与 double 相加自动提升为 double
    }

    printf("%.2f\n", total);
    return 0;
}
