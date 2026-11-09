/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-09 20:44
 * update_at: 2026-11-09 20:44
 */
// brute2.cpp：双指针（滑动窗口）的原始版本，即“枚举所有区间”的暴力解，用来辅助理解与对拍。
// 思路：最优解一定等价于「选一个窗口，把窗口内的 0 全部改成 1」（交换论证），
//      所以直接枚举区间 [i, j]，用前缀和求区间内 0 的个数，只要 <= k 就可用区间长度更新答案。
// 复杂度 O(n^2)。双指针正是根据它的单调性做的优化：
//      固定左端点时右端点越远 0 越多；左端点右移时，最远的合法右端点只会右移、不会左移，
//      于是两个指针都能只进不退，把 O(n^2) 的枚举压成 O(n)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxn = 300005;

int n;              // 元素个数
int k;              // 最多可以改的 0 的个数
int a[maxn];        // 原数组，元素只有 0/1，用 int 足够
int b[maxn];        // 答案数组（原数组修改后的结果）
int zero_pref[maxn]; // zero_pref[i]：前 i 个元素里 0 的个数，用来 O(1) 求区间内 0 的个数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i] = a[i];
        zero_pref[i] = zero_pref[i - 1] + (a[i] == 0 ? 1 : 0);
    }

    int best_len = 0;  // 目前找到的最大合法区间长度
    int best_left = 1; // 最大合法区间的左端点

    // 枚举区间的起点 i 和终点 j
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            int zero_cnt = zero_pref[j] - zero_pref[i - 1]; // 区间 [i, j] 内 0 的个数
            if (zero_cnt <= k) {
                if (j - i + 1 > best_len) {
                    best_len = j - i + 1;
                    best_left = i;
                }
            }
        }
    }

    // 把最优区间内的 0 全部改成 1
    for (int i = best_left; i <= best_left + best_len - 1; i++) {
        b[i] = 1;
    }

    cout << best_len << "\n";
    for (int i = 1; i <= n; i++) {
        cout << b[i] << " \n"[i == n];
    }

    return 0;
}
