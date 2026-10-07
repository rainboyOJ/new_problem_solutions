/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-06-18 10:40
 * update_at: 2026-10-06 14:05
 */
// 奇数码问题：n 为奇数时，两个局面可达 <=> 忽略空格 0 后的
// 两个一维序列逆序对个数奇偶性相同。用归并排序统计逆序对。

#include <cstdio>

typedef long long ll;

const int MAXN = 505;      // n < 500
const int MAXM = MAXN * MAXN;

ll a[MAXM];   // 第一个局面忽略 0 后的一维序列
ll b[MAXM];   // 第二个局面忽略 0 后的一维序列
ll tmp1[MAXM]; // 归并辅助数组（局面一）
ll tmp2[MAXM]; // 归并辅助数组（局面二）

// 归并排序统计 a[l..r] 的逆序对个数，过程中会排好序
ll merge_sort_count(ll *arr, ll *tmp, ll l, ll r) {
    if (l >= r)
        return 0;
    ll mid = (l + r) >> 1;
    // 逆序对 = 左半内部的 + 右半内部的 + 合并时跨越两半的
    ll inv = merge_sort_count(arr, tmp, l, mid) + merge_sort_count(arr, tmp, mid + 1, r);
    ll i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r) {
        if (arr[i] <= arr[j]) {
            tmp[k] = arr[i];
            i++;
        } else {
            // arr[j] 比左边剩下的 mid - i + 1 个数都小，各构成一个逆序对
            tmp[k] = arr[j];
            inv += mid - i + 1;
            j++;
        }
        k++;
    }
    while (i <= mid) {
        tmp[k] = arr[i];
        i++;
        k++;
    }
    while (j <= r) {
        tmp[k] = arr[j];
        j++;
        k++;
    }
    for (ll p = l; p <= r; p++)
        arr[p] = tmp[p];
    return inv;
}

// 读入一个 n*n 局面（n 已在 main 中读出），把非 0 数字依次存入 arr，返回长度
ll read_board(ll *arr, int n) {
    ll len = 0;
    for (int i = 0; i < n * n; i++) {
        ll v;
        scanf("%lld", &v);
        if (v != 0) { // 忽略空格 0
            len++;
            arr[len] = v;
        }
    }
    return len;
}

int main() {
    int n;
    // 多组数据，读到文件末尾为止
    while (scanf("%d", &n) == 1) {
        ll len1 = read_board(a, n); // 第一个局面，忽略 0 后的长度
        ll len2 = read_board(b, n); // 第二个局面
        ll inv1 = merge_sort_count(a, tmp1, 1, len1);
        ll inv2 = merge_sort_count(b, tmp2, 1, len2);
        if ((inv1 & 1) == (inv2 & 1))
            printf("TAK\n");
        else
            printf("NIE\n");
    }
    return 0;
}
