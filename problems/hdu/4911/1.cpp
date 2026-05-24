#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const int maxn = 1e5 + 5;
int a[maxn];
int temp[maxn]; // 归并排序需要的辅助数组
ll total_inversions = 0; // 逆序对总数，注意要用 long long

// 归并排序的同时计算逆序对
void merge_sort(int l, int r) {
    if (l >= r) return;

    int mid = (l + r) >> 1;
    merge_sort(l, mid);
    merge_sort(mid + 1, r);

    // 开始合并
    int i = l, j = mid + 1, k = l;
    
    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) {
            temp[k++] = a[i++];
        } else {
            // a[i] > a[j]，构成了逆序对
            // 左边 a[i] 以及它后面的所有数 (直到 mid) 都比 a[j] 大
            temp[k++] = a[j++];
            total_inversions += (long long)(mid - i + 1);
        }
    }

    while (i <= mid) temp[k++] = a[i++];
    while (j <= r) temp[k++] = a[j++];

    // 拷贝回原数组
    for (int p = l; p <= r; ++p) {
        a[p] = temp[p];
    }
}

void solve() {
    int n;
    ll k;
    // 处理多组输入
    while (cin >> n >> k) {
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }

        total_inversions = 0; // 每次都要清零
        merge_sort(1, n);

        // 答案是 总逆序对 - k，但不能小于 0
        if (k >= total_inversions) {
            cout << 0 << "\n";
        } else {
            cout << (total_inversions - k) << "\n";
        }
    }
}

int main() {
    // 加速 I/O
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    solve();
    
    return 0;
}
