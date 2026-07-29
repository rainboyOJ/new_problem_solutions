#include <bits/stdc++.h>
using namespace std;

class MedianFinder {
    // lo 保存较小的一半，且元素个数始终等于 hi 或比 hi 多 1。
    priority_queue<int> lo;
    priority_queue<int, vector<int>, greater<>> hi;

public:
    void addNum(int num) {
        lo.push(num);
        hi.push(lo.top());
        lo.pop();
        if (lo.size() < hi.size()) {
            lo.push(hi.top());
            hi.pop();
        }
    }

    double findMedian() {
        return lo.size() > hi.size() ? lo.top() : (lo.top() + hi.top()) / 2.0;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> q;
    MedianFinder mf;
    while (q--) {
        string op;
        cin >> op;
        if (op == "add") {
            int v;
            cin >> v;
            mf.addNum(v);
        } else
            cout << fixed << setprecision(1) << mf.findMedian() << ' ';
    }
    return 0;
}
