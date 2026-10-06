/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:03
 * update_at: 2026-10-06 13:03
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

typedef long long ll;

ll len;          // 环形字符串的长度 L
char s[MAXN];    // 存放原字符串（0-indexed，读入时复制两遍成倍长串）
char t[2 * MAXN]; // 破环成链后的字符串 t = s + s

// 最小表示法：返回字典序最小的循环同构串的起始下标（0-indexed）。
// 两个候选起点 i、j 一起向后比，失配时利用已匹配的 k 个公共前缀
// 把劣势区间 [x, x+k] 整段跳过，保证总复杂度 O(L)。
ll min_representation() {
    ll i = 0, j = 1, k = 0;
    while (i < len && j < len && k < len) {
        if (t[i + k] == t[j + k]) {
            k++; // 当前公共前缀还在继续，继续往后比
        } else if (t[i + k] > t[j + k]) {
            // i 劣于 j：[i, i+k] 里的每个起点都必然劣于 j 平移同样的距离
            i = i + k + 1;
            if (i == j) i++; // 两个候选起点不能重合
            k = 0;
        } else {
            // j 劣于 i：同理整段淘汰 [j, j+k]
            j = j + k + 1;
            if (j == i) j++;
            k = 0;
        }
    }
    // 活下来的那个指针就是最优起点，取较小者
    return min(i, j);
}

int main() {
    scanf("%lld", &len);
    scanf("%s", s);

    // 破环成链：t = s + s，长度 2L，比较时用 t 上的子串代替环形读取
    for (ll i = 0; i < len; i++) {
        t[i] = s[i];
        t[i + len] = s[i];
    }

    printf("%lld\n", min_representation());
    return 0;
}
