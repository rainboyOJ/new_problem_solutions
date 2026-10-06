/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 15:25
 * update_at: 2026-10-06 15:25
 */

#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

// 按段发放金币：第 wage 段是连续 wage 天、每天 wage 枚
// O(√K)：前 N 段共 N(N+1)/2 天，1e4 天只需约 141 段
int main() {
    ll k;                 // 要统计的天数
    ll left;              // 还没计入答案的剩余天数
    ll wage = 1;          // 当前段号，也是本段每天的金币数
    ll total = 0;         // 累计金币数

    scanf("%lld", &k);
    left = k;

    while (left > 0) {
        // 本段实际计入的天数：够一整段取整段，不够就取完剩余天数
        ll days = min(wage, left);
        total += days * wage; // 段内每天都是 wage 枚，N 次加法合并成一次乘法
        left -= days;
        wage++;
    }

    printf("%lld\n", total);
    return 0;
}
