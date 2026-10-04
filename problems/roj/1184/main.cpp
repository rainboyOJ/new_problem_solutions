/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:41
 * update_at: 2026-10-05 04:41
 */

// 明明的随机数：值域只有 [1,1000]，用桶数组去重 + 按下标扫描输出即有序。
#include <iostream>
typedef long long ll;
using namespace std;

const int MAXV = 1000;
int bucket[MAXV + 1]; // bucket[v] = 1 表示数字 v 出现过，重复写同一格即去重

int main() {
    ll n;
    cin >> n; // n 只决定读入多少个数，不参与计算
    for (ll i = 1; i <= n; i++) {
        ll v;
        cin >> v;
        bucket[v] = 1;
    }
    ll m = 0;
    for (int v = 1; v <= MAXV; v++) // 按下标从小到大扫，天然有序
        if (bucket[v])
            m++;
    cout << m << "\n";
    bool first = true; // 控制数字之间的空格
    for (int v = 1; v <= MAXV; v++)
        if (bucket[v]) {
            if (!first)
                cout << " ";
            cout << v;
            first = false;
        }
    cout << "\n";
    return 0;
}
