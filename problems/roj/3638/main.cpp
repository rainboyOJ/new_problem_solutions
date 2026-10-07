/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 15:50
 * update_at: 2026-10-06 15:50
 */

#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 100000 + 10;

int n, m;
int f[MAXN];              // 第 i 个小人的朝向，0 朝圈内，1 朝圈外
char name[MAXN][15];      // 每个小人的职业名

// 把方向折算成下标增减：a 与 f 相异则 +1，相同则 -1
inline int step_dir(int a, int fc) {
    return (a != fc) ? 1 : -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> f[i] >> name[i];
    }

    int pos = 0;  // 从第 1 个读入的小人（下标 0）出发
    for (int i = 0; i < m; ++i) {
        int a, s;
        cin >> a >> s;
        int step = step_dir(a, f[pos]);
        // 环上走 s 步，负数取模后归到 [0, n)
        pos = (pos + step * (s % n) + n) % n;
    }

    cout << name[pos] << '\n';
    return 0;
}
