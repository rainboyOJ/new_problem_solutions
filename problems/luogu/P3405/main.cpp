/**
 * P3405 [USACO16DEC] Cities and States S
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

// 2 个大写字母 → 0~675 的编码
int enc(const char *s) {
    return (s[0] - 'A') * 26 + (s[1] - 'A');
}

// cnt[城市前缀][州编码] = 出现次数
int cnt[676][676];
int n;
long long ans;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        char city[15], state[5];
        scanf("%s%s", city, state);
        int prefix = enc(city);
        int st = enc(state);
        if (prefix != st) {
            // 当前城市可以和之前所有 (state == prefix 且 city_prefix == st) 的城市配对
            ans += cnt[st][prefix];
            ++cnt[prefix][st];
        }
    }
    printf("%lld\n", ans);
    return 0;
}
