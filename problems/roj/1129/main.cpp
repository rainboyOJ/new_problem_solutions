/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2025-01-20 21:30
 * update_at: 2026-10-05 02:53
 */
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;

char s[260]; // 读入缓冲区，fgets 最多保留 255 个可见字符

int main() {
    // 用 fgets 模拟官方参考实现：缓冲区 256 字节（含 '\0'），最多读入 255 个字符
    if (fgets(s, 256, stdin) == NULL) {
        printf("0\n");
        return 0;
    }

    ll ans = 0;
    ll len = strlen(s);
    for (ll i = 0; i < len; i++) {
        if (s[i] >= '0' && s[i] <= '9') ans++;
    }
    printf("%lld\n", ans);
    return 0;
}
