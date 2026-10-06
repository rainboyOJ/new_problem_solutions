/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 12:31
 * update_at: 2026-10-06 12:31
 */
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;

ll n, k;
ll memo[205][7]; // memo[i][j] 表示把 i 分成 j 份的方案数

// 把 total 分成 parts 份非空、不计顺序的正整数方案数
ll ways(ll total, ll parts) {
    if (total < parts) return 0; // 每份至少 1，总和小于份数则无解
    if (parts == 1) return 1;    // 只剩一份，唯一分法就是 total 本身
    if (memo[total][parts] != -1) return memo[total][parts];
    // 按是否有一份等于 1 分类：有则去掉一个 1；没有则每份先减 1
    memo[total][parts] = ways(total - 1, parts - 1) + ways(total - parts, parts);
    return memo[total][parts];
}

int main() {
    memset(memo, -1, sizeof(memo));
    scanf("%lld %lld", &n, &k);
    printf("%lld\n", ways(n, k));
    return 0;
}
