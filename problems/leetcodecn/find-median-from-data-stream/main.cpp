#include <bits/stdc++.h>
using namespace std;
class MedianFinder {
    priority_queue<int> lo; // max heap
    priority_queue<int, vector<int>, greater<>> hi; // min heap
public:
    void addNum(int num) {
        lo.push(num);
        hi.push(lo.top()); lo.pop();
        if (lo.size() < hi.size()) { lo.push(hi.top()); hi.pop(); }
    }
    double findMedian() {
        return lo.size() > hi.size() ? lo.top() : (lo.top() + hi.top()) / 2.0;
    }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int q; cin >> q; MedianFinder mf;
    while (q--) {
        string op; cin >> op;
        if (op == "add") { int v; cin >> v; mf.addNum(v); }
        else cout << fixed << setprecision(1) << mf.findMedian() << ' ';
    }
    return 0;
}
