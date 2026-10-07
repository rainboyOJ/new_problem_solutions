/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:10
 * update_at: 2026-10-05 23:10
 */

// 笨小猴：统计每个字母出现次数，判断 maxn-minn 是否为质数。

#include <cstdio>
#include <cstring>
typedef long long ll;

const int MAXL = 105;

char s[MAXL];      // 输入的单词，只含小写字母
int cnt[26];       // cnt[i] = 字母 'a'+i 在单词中出现的次数
bool appear[26];   // 该字母是否在单词中出现过（未出现的 0 次不参与 minn 统计）

// 试除法判定 n 是否为质数；n 最大不超过单词长度，直接枚举因子即可
bool is_prime(ll n) {
    if (n < 2) return false; // 0 和 1 不是质数
    for (ll i = 2; i * i <= n; ++i)
        if (n % i == 0) return false;
    return true;
}

int main() {
    scanf("%s", s);
    ll len = strlen(s);
    for (ll i = 0; i < len; ++i) {
        int c = s[i] - 'a';
        cnt[c]++;
        appear[c] = true;
    }

    // 只在出现过的字母中取最大、最小次数
    ll maxn = -1, minn = -1;
    for (int i = 0; i < 26; ++i) {
        if (!appear[i]) continue;
        if (maxn == -1 || cnt[i] > maxn) maxn = cnt[i];
        if (minn == -1 || cnt[i] < minn) minn = cnt[i];
    }

    ll d = maxn - minn;
    if (is_prime(d)) {
        printf("Lucky Word\n");
        printf("%lld\n", d);
    } else {
        printf("No Answer\n");
        printf("0\n");
    }
    return 0;
}
