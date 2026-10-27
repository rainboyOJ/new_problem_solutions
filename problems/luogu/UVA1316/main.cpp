/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-27 21:05
 * update_at: 2026-10-27 21:05
 */
// main.cpp：反悔贪心 + 优先队列。按截止日期从小到大处理，维护一个"当前决定卖的商品"的小顶堆。
// 堆里攒够 d 件时，用利润更高的新商品替换掉堆里利润最低的那件。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 10000 + 5;

// 一个商品：利润 p，截止日期 d
struct Item {
    int p;
    int d;
};

int n;
Item item[MAXN];

// 按截止日期从小到大排序
bool compare_by_deadline(const Item &a, const Item &b) {
    return a.d < b.d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 本题是多组输入，读到 EOF 为止
    while (cin >> n) {
        for (int i = 0; i < n; i++) cin >> item[i].p >> item[i].d;

        sort(item, item + n, compare_by_deadline);

        // cart 里存已选中商品的利润。用小顶堆放利润最低的那件，方便"反悔"时换掉它
        priority_queue<int, vector<int>, greater<int> > cart;
        for (int i = 0; i < n; i++) {
            if ((int)cart.size() < item[i].d) {
                cart.push(item[i].p); // 还有空位，直接卖
            } else if (!cart.empty() && item[i].p > cart.top()) {
                // 位置已经排满，但当前商品更值钱：扔掉最差的，换上它
                cart.pop();
                cart.push(item[i].p);
            }
        }

        ll answer = 0;
        while (!cart.empty()) {
            answer += cart.top();
            cart.pop();
        }
        cout << answer << '\n';
    }

    return 0;
}
