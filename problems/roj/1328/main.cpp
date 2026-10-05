/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 09:49
 * update_at: 2026-10-05 09:49
 */
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 10005;

ll a[MAXN];   // a[1..n] 原数列
ll tmp[MAXN]; // 归并排序的临时存放数组
ll ans;       // 逆序对总数，也就是最少相邻交换次数

// 归并排序 [left, right]，同时统计跨段逆序对
void merge_sort(int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = (left + right) / 2;
    merge_sort(left, mid);
    merge_sort(mid + 1, right);

    int i = left;
    int j = mid + 1;
    int k = left;
    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) {
            // 相等时先取左半，不把相等元素算成逆序对
            tmp[k] = a[i];
            i++;
            k++;
        } else {
            tmp[k] = a[j];
            j++;
            k++;
            ans += mid - i + 1; // 左半剩余元素都比 a[j] 大，各配成一个逆序对
        }
    }
    while (i <= mid) {
        tmp[k] = a[i];
        i++;
        k++;
    }
    while (j <= right) {
        tmp[k] = a[j];
        j++;
        k++;
    }
    for (int p = left; p <= right; p++) {
        a[p] = tmp[p];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    ans = 0;
    merge_sort(1, n);
    cout << ans << "\n";

    return 0;
}
