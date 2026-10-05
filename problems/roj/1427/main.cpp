/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:26
 * update_at: 2026-10-05 23:26
 */
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef long long ll;

const int MAXN = 100005;

int n;
ll a[MAXN]; // 黑板上最初的 n 个正整数

void read_input() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
}

// 按题目规则每次合并两个数 a、b 为 a*b+1，直到只剩一个数，返回最终值。
// 求 max 时每次合并当前最小的两个数（小根堆）；
// 求 min 时每次合并当前最大的两个数：把数取负放进同一个小根堆，弹出后再还原。
ll merge_all(bool pick_smallest) {
    priority_queue<ll, vector<ll>, greater<ll> > heap;
    for (int i = 0; i < n; i++) {
        if (pick_smallest) {
            heap.push(a[i]);
        } else {
            heap.push(-a[i]);
        }
    }
    while (heap.size() > 1) {
        ll x = heap.top();
        heap.pop();
        ll y = heap.top();
        heap.pop();
        ll merged = x * y + 1;
        if (!pick_smallest) {
            merged = -merged; // 放回堆前再取负，保持"堆顶是原数最大者"
        }
        heap.push(merged);
    }
    ll res = heap.top();
    return pick_smallest ? res : -res;
}

void solve() {
    ll max_value = merge_all(true);
    ll min_value = merge_all(false);
    cout << max_value - min_value << endl;
}

int main() {
    read_input();
    solve();
    return 0;
}
