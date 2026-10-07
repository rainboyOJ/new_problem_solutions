/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:18
 * update_at: 2026-10-06 01:18
 */
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXM = 1000000; // 值域上限

int n;
int a[100005];            // 每头奶牛的数字
int cnt[MAXM + 5];        // cnt[v] 表示数字 v 出现的次数
int div_sum[MAXM + 5];    // div_sum[v] 表示有多少个数字能整除 v（含自己）

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    int max_a = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        cnt[a[i]]++;
        if (a[i] > max_a) max_a = a[i];
    }

    // 对每个出现过的数字 d，把 cnt[d] 广播到 d 的所有倍数上
    for (int d = 1; d <= max_a; ++d) {
        if (cnt[d] == 0) continue;
        for (int multiple = d; multiple <= max_a; multiple += d) {
            div_sum[multiple] += cnt[d];
        }
    }

    // 自己整除自己多算了 1，输出时扣掉
    for (int i = 1; i <= n; ++i) {
        cout << div_sum[a[i]] - 1 << "\n";
    }
    return 0;
}
