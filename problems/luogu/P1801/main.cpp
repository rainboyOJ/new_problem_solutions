#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    vector<int> a(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }
    vector<int> u(n);
    for (int i = 0; i < n; i++) {
        cin >> u[i];
    }

    priority_queue<int> L; // 最大堆，存储前 i-1 个最小元素
    priority_queue<int, vector<int>, greater<int>> R; // 最小堆，存储剩余元素，堆顶为第 i 小

    int inserted = 0;
    for (int q : u) {
        // 插入 a[inserted .. q-1]
        for (int i = inserted; i < q; i++) {
            int x = a[i];
            if (!L.empty() && x < L.top()) {
                L.push(x);
                R.push(L.top());
                L.pop();
            } else {
                R.push(x);
            }
        }
        inserted = q;
        // GET 操作
        cout << R.top() << "\n";
        L.push(R.top());
        R.pop();
    }

    return 0;
}
