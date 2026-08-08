/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

int n, ans = 2e9;
int s[15], b[15];

void dfs(int dep, int sour, int bitter, bool used) {
    if (dep == n) {
        if (used && abs(sour - bitter) < ans)
            ans = abs(sour - bitter);
        return;
    }
    dfs(dep + 1, sour, bitter, used);           // 不放当前食材
    dfs(dep + 1, sour * s[dep], bitter + b[dep], true); // 放
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> s[i] >> b[i];
    dfs(0, 1, 0, false);
    cout << ans << endl;
    return 0;
}
