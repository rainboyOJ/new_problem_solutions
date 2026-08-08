#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 500005;

int n;
int a[MAXN];
int tmp[MAXN];
ll answer;

void merge_sort_count(int l, int r) {
    if (l >= r) {
        return;
    }

    int mid = (l + r) >> 1;
    merge_sort_count(l, mid);
    merge_sort_count(mid + 1, r);

    int i = l;
    int j = mid + 1;
    int k = l;

    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) {
            tmp[k++] = a[i++];
        }
        else {
            // a[i] > a[j] 时，左半边从 i 到 mid 的所有数都和 a[j] 构成逆序对。
            tmp[k++] = a[j++];
            answer += (ll)(mid - i + 1);
        }
    }

    while (i <= mid) {
        tmp[k++] = a[i++];
    }
    while (j <= r) {
        tmp[k++] = a[j++];
    }

    for (int p = l; p <= r; p++) {
        a[p] = tmp[p];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    answer = 0;
    merge_sort_count(1, n);

    cout << answer << '\n';
    return 0;
}
