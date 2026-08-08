/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

int n, m;
int a[10005];

void next_perm() {
    int i = n - 2;
    while (i >= 0 && a[i] > a[i + 1]) i--;
    int j = n - 1;
    while (a[j] < a[i]) j--;
    swap(a[i], a[j]);
    reverse(a + i + 1, a + n);
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int t = 0; t < m; t++) next_perm();
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;
    return 0;
}
