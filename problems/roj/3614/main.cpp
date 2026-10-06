/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 15:14
 * update_at: 2026-10-06 15:14
 */

#include <cstdio>
#include <set>
using namespace std;

typedef long long ll;

const int MAXN = 105;

ll n;               // 集合中数的个数
ll a[MAXN];         // a[i] 表示集合里的第 i 个数（保证互不相同）
set<ll> sum_set;    // 收集所有“两个不同的数”的和，set 自动去重

int main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);

    // 枚举无序组合：每个数只与它后面的数配对，天然保证两个加数不同
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            sum_set.insert(a[i] + a[j]);

    // 统计有多少个数落在和集合里；同一个数哪怕能凑出多次也只算一个
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        if (sum_set.count(a[i]) > 0)
            ans++;

    printf("%lld\n", ans);
    return 0;
}
