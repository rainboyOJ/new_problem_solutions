/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:42
 * update_at: 2026-10-06 14:42
 */
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

const int MAXK = 10005; // 色调数上限

int n, k;
ll p;
int total[MAXK]; // 每种色调已出现的客栈数
int valid[MAXK]; // 每种色调中位置不超过最近低价店的客栈数
int pending[MAXK]; // 暂存最近低价店之后出现的色调，补记时一次性处理
int pending_cnt;   // pending 当前长度

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k >> p;
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        int color;
        ll price;
        cin >> color >> price;
        if (price <= p) {
            // 本店是低价店：之前所有同色客栈都与它合法
            ans += total[color];
            // 把 pending 里的客栈全部补入 valid
            for (int j = 0; j < pending_cnt; ++j) {
                valid[pending[j]]++;
            }
            pending_cnt = 0;
            valid[color]++; // 本店自身对更右侧客栈可用
        } else {
            // 只能与最近低价店左侧（含）的同色客栈配对
            ans += valid[color];
            pending[pending_cnt++] = color;
        }
        total[color]++;
    }
    cout << ans << "\n";
    return 0;
}
