/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-04 14:50
 * update_at: 2026-11-04 19:08
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 5;

int n;
ll a[MAXN];                   // 原序列，下标从 1 开始
int f[MAXN];                  // f[i]：以 i 结尾的最长连续递增子序列长度，最大为 n，int 够用
int pre[MAXN];                // pre[i]：拼出 f[i] 时 i 前面接的下标，-1 表示没有前驱
unordered_map<ll, int> last;  // last[v]：值 v 最后一次出现的下标；键来自输入，不必防构造攻击

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    last.reserve(n * 2);  // 键最多 n 个，先预留桶，避免反复 rehash
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    // 前驱的值只能是 a[i] - 1，所以查一次表就够，不用回扫
    for (int i = 1; i <= n; ++i) {
        f[i] = 1;
        pre[i] = -1;
        auto it = last.find(a[i] - 1);
        if (it != last.end()) {
            f[i] = f[it->second] + 1;
            pre[i] = it->second;
        }
        last[a[i]] = i;  // 每次出现都覆盖，桶里留的是最后一次出现
    }

    int ans_pos = 1;  // 取第一个最大长度的结尾，题面允许任意一组合法答案
    for (int i = 2; i <= n; ++i) {
        if (f[i] > f[ans_pos]) {
            ans_pos = i;
        }
    }
    cout << f[ans_pos] << "\n";

    // 沿 pre 回退得到倒序的下标序列，反转后输出
    vector<int> path;
    for (int pos = ans_pos; pos != -1; pos = pre[pos]) {
        path.push_back(pos);
    }
    reverse(path.begin(), path.end());
    for (int pos : path) {
        cout << pos << " ";
    }
    cout << "\n";

    return 0;
}
