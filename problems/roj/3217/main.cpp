/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int width;               // 节点数 = 2^(k-1)
vector<char> used;       // 边 v*2+b 是否已走
vector<int> route;       // 逆后序节点序列

// de Bruijn 图上的 Hierholzer，优先走 0 边
void euler_route() {
    vector<int> stack;
    stack.push_back(0);
    while (!stack.empty()) {
        int v = stack.back();
        int base = v << 1;
        int nxt = -1;
        for (int b = 0; b < 2; b++) {
            if (!used[base + b]) { nxt = base + b; break; }
        }
        if (nxt == -1) {
            route.push_back(stack.back());
            stack.pop_back();
        } else {
            used[nxt] = 1;
            stack.push_back(nxt & (width - 1));
        }
    }
    reverse(route.begin(), route.end());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int k;
    cin >> k;
    width = 1 << (k - 1);
    int total = 1 << k;
    used.assign(width << 2, 0);
    euler_route();

    string bits;
    for (int i = 0; i < k - 1; i++) bits.push_back('0');
    for (size_t i = 1; i < route.size(); i++)
        bits.push_back('0' + (route[i] & 1));
    cout << total << " " << bits.substr(0, total) << "\n";
    return 0;
}
