#include <bits/stdc++.h>
using namespace std;

int n;
long long ans;

// 小数据直接搜索：
// red 表示已经放了多少个红筹，black 表示已经放了多少个黑筹。
// 任意前缀都要满足 red >= black。
void dfs(int red, int black) {
    if (red == n && black == n) {
        ans++;
        return;
    }

    if (red < n) {
        dfs(red + 1, black);
    }

    if (black < n && red > black) {
        dfs(red, black + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    dfs(0, 0);
    cout << ans << '\n';

    return 0;
}
