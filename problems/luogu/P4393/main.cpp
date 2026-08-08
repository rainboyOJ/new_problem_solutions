#include <bits/stdc++.h>
using namespace std;

const int INF = 2000000000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> st(n + 5);
    int top = 0;
    st[++top] = INF;

    long long answer = 0;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;

        // 当栈顶不大于当前值时，说明这个较小值已经找到了
        // 左右两边第一个不小于它的候选值，可以现在结算它的最优贡献。
        while (top > 1 && st[top] <= x) {
            int mid = st[top--];
            answer += min(st[top], x);
        }

        st[++top] = x;
    }

    // 扫描结束后，栈里剩下的是一个严格递减序列。
    // 这些数只能依次向左合并，贡献就是它左边那个更大的值。
    while (top > 2) {
        top--;
        answer += st[top];
    }

    cout << answer << '\n';

    return 0;
}
