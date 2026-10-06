/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 15:07
 * update_at: 2026-10-06 15:07
 */
#include <cstdio>

using namespace std;

typedef long long ll;

const ll MOD = 10000;

char expr[1200005]; // 输入的表达式

int main() {
    scanf("%s", expr);
    ll ans = 0;      // 已结算的加法项之和
    ll prod = 1;     // 当前乘法项的累积积
    ll cur = 0;      // 当前正在读的数字
    for (ll i = 0; expr[i]; ++i) {
        char ch = expr[i];
        if (ch == '+') {
            // 当前乘法项结束，把它累进答案，并开始新的加法项
            ans = (ans + prod * cur) % MOD;
            prod = 1;
            cur = 0;
        } else if (ch == '*') {
            // 当前因子结束，把它乘进乘法项
            prod = prod * cur % MOD;
            cur = 0;
        } else {
            cur = cur * 10 + ch - '0';
        }
    }
    ans = (ans + prod * cur) % MOD;
    printf("%lld\n", ans);
    return 0;
}
