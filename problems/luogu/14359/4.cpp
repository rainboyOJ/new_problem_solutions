#include <bits/stdc++.h>
using namespace std;

const int MAXV = 1 << 20; // 2^20 = 1048576
int vis[MAXV]; // 时间戳数组
int cur = 1;   // 当前时间戳

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    
    int pre = 0; // 前缀异或和
    int ans = 0; // 答案
    vis[0] = cur; // 初始前缀异或和0出现过
    
    for (int i = 1; i <= n; ++i) {
        pre ^= a[i];
        int target = pre ^ k;
        if (vis[target] == cur) { // 之前出现过 target
            ans++;
            cur++; // 时间戳增加，相当于清空vis
            pre = 0;
            vis[0] = cur; // 重新开始
        } else {
            vis[pre] = cur;
        }
    }
    
    cout << ans << "\n";
    return 0;
}
