/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 00:58
 * update_at: 2026-10-06 01:24
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 15;    // 堆数上限 10，留少量余量
const int MAXA = 1005;  // 每堆石子数上限 1000，SG 表按最大石子树开
const int MAXG = 32;    // SG 值不超过取法种数 M<=10，时间戳数组按 SG 值域开

int n, m;
int heap[MAXN];   // heap[i] 表示第 i 堆的石子数
int take[15];     // take[j] 表示第 j 种可以取走的石子数，题面保证递增
int sg[MAXA];     // sg[x] 表示一堆 x 个石子的 SG 值
int stamp[MAXG];  // stamp[v] == x 表示 SG 值 v 在第 x 轮的 mex 集合里出现过，用 x 当时间戳省去每轮清零

// 单堆 SG 递推：sg[x] = mex{ sg[x - take[j]] | take[j] <= x }
void build_sg() {
    int max_stones = 0;
    for (int i = 1; i <= n; i++) {
        if (heap[i] > max_stones) max_stones = heap[i];
    }
    for (int x = 1; x <= max_stones; x++) {
        for (int j = 1; j <= m; j++) {
            if (take[j] > x) break;              // 取法递增，后面的都取不动了
            stamp[sg[x - take[j]]] = x;
        }
        while (stamp[sg[x]] == x) sg[x]++;       // 最小未出现的 SG 值就是 mex
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> heap[i];
    cin >> m;
    for (int j = 1; j <= m; j++) cin >> take[j];

    build_sg();

    int nim = 0; // 整个局面的 SG 值等于各堆 SG 的异或和
    for (int i = 1; i <= n; i++) nim ^= sg[heap[i]];

    if (nim == 0) {
        cout << "NO\n";                          // 异或和为 0，先手必败
        return 0;
    }
    cout << "YES\n";

    // 取第 i 堆 t 个后异或和变为 0，等价于 sg[heap[i]-t] == nim ^ sg[heap[i]]；
    // 按 i 从小到大、t 从小到大扫描，第一个可行解即题面要求的字典序最小解。
    for (int i = 1; i <= n; i++) {
        int target = nim ^ sg[heap[i]];
        for (int j = 1; j <= m; j++) {
            if (take[j] > heap[i]) break;
            if (sg[heap[i] - take[j]] == target) {
                cout << i << " " << take[j] << "\n";
                return 0;
            }
        }
    }
    return 0;
}
