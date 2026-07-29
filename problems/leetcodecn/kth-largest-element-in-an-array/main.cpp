#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findKthLargest(vector<int> &nums, int k) {
        priority_queue<int, vector<int>, greater<>> pq;
        for (int x : nums) {
            pq.push(x);
            if ((int)pq.size() > k)
                pq.pop();
        }
        return pq.top();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int &x : a)
        cin >> x;
    cout << Solution().findKthLargest(a, k) << '\n';
    return 0;
}
