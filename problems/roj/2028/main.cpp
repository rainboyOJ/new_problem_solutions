/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:51
 * update_at: 2026-10-06 09:51
 */

#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;

const ll MAX_RUNAROUND = 9682415; // 循环数最大为 9682415，7 位以上不存在

// 判断 n 是否为循环数：各位非零互异，且从第 0 位起按当前位数字跳格走遍所有位并回到 0
bool is_runaround(ll n) {
    char s[32];
    snprintf(s, sizeof(s), "%lld", n);
    int len = strlen(s);

    bool seen[10] = {false};
    for (int i = 0; i < len; i++) {
        int d = s[i] - '0';
        if (d == 0) return false;       // 含 0 直接排除
        if (seen[d]) return false;      // 数字重复直接排除
        seen[d] = true;
    }

    int pos = 0;
    int visited = 0; // 用 bitmask 记录已访问的下标
    for (int i = 0; i < len; i++) {
        if (visited >> pos & 1) return false; // 重复踩点，未走遍全部位
        visited |= 1 << pos;
        pos = (pos + (s[pos] - '0')) % len;
    }
    return pos == 0;
}

int main() {
    ll m;
    scanf("%lld", &m);

    ll n = m + 1;
    // 线性搜索第一个大于 m 的循环数，超过上界则停止
    while (n <= MAX_RUNAROUND && !is_runaround(n)) n++;

    printf("%lld\n", n);
    return 0;
}
