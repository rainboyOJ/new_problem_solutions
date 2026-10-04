/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 06:19
 * update_at: 2026-10-05 06:19
 */

#include <cstdio>
#include <map>
using namespace std;

typedef long long ll;

const int MAXN = 200005;

ll a[MAXN];        // 读入的 n 个自然数

int main() {
    int n;
    scanf("%d", &n);
    // 用 map 自动按键升序排列，一边读一边统计每个值出现次数
    map<ll, int> cnt;
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
        cnt[a[i]]++;
    }
    // map 已经按 ll 升序排好，直接按顺序输出
    for (auto it = cnt.begin(); it != cnt.end(); ++it) {
        printf("%lld %d\n", it->first, it->second);
    }
    return 0;
}