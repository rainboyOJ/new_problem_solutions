/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:05
 * update_at: 2026-10-06 14:05
 */
#include <cstdio>

typedef long long ll;

const int MAXN = 500005; // n < 5e5，数组开到 5e5+5 即可
ll a[MAXN];              // 当前用例的序列
ll buf[MAXN];            // 归并排序使用的缓冲区

// 合并有序的 a[lo..mid-1] 与 a[mid..hi-1]，返回跨中线的逆序对数，并就地排好序。
ll merge_count(int lo, int mid, int hi) {
    for (int i = lo; i < hi; i++) {
        buf[i] = a[i];
    }
    int i = lo;
    int j = mid;
    ll cross = 0;
    for (int k = lo; k < hi; k++) {
        if (j >= hi || (i < mid && buf[i] <= buf[j])) {
            a[k] = buf[i];
            i++;
        } else {
            a[k] = buf[j];
            j++;
            cross += mid - i; // buf[j] 比左半还没被取走的所有元素都小
        }
    }
    return cross;
}

// 统计 a[lo..hi-1] 的逆序对数：左半内部 + 右半内部 + 跨中线。
ll inversions(int lo, int hi) {
    if (hi - lo <= 1) {
        return 0;
    }
    int mid = (lo + hi) / 2;
    ll left = inversions(lo, mid);
    ll right = inversions(mid, hi);
    ll cross = merge_count(lo, mid, hi);
    return left + right + cross;
}

int main() {
    int n;
    while (scanf("%d", &n) == 1 && n != 0) {
        for (int i = 0; i < n; i++) {
            scanf("%lld", &a[i]);
        }
        printf("%lld\n", inversions(0, n));
    }
    return 0;
}
