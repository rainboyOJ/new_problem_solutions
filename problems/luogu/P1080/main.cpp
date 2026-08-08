#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

struct Person {
    int left_num;
    int right_num;
};

int n;
Person people[MAXN];

bool cmp_person(const Person &a, const Person &b) {
    return 1LL * a.left_num * a.right_num < 1LL * b.left_num * b.right_num;
}

vector<int> multiply_small(vector<int> num, int x) {
    int carry = 0;
    for (int i = 0; i < (int)num.size(); i++) {
        int cur = num[i] * x + carry;
        num[i] = cur % 10;
        carry = cur / 10;
    }
    while (carry > 0) {
        num.push_back(carry % 10);
        carry /= 10;
    }
    return num;
}

vector<int> divide_small(const vector<int> &num, int x) {
    vector<int> res;
    int rem = 0;
    for (int i = (int)num.size() - 1; i >= 0; i--) {
        int cur = rem * 10 + num[i];
        res.push_back(cur / x);
        rem = cur % x;
    }
    reverse(res.begin(), res.end());
    while (res.size() > 1 && res.back() == 0) {
        res.pop_back();
    }
    return res;
}

bool less_big(const vector<int> &a, const vector<int> &b) {
    if (a.size() != b.size()) {
        return a.size() < b.size();
    }
    for (int i = (int)a.size() - 1; i >= 0; i--) {
        if (a[i] != b[i]) {
            return a[i] < b[i];
        }
    }
    return false;
}

void print_big(const vector<int> &num) {
    for (int i = (int)num.size() - 1; i >= 0; i--) {
        cout << num[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cin >> people[0].left_num >> people[0].right_num;
    for (int i = 1; i <= n; i++) {
        cin >> people[i].left_num >> people[i].right_num;
    }

    sort(people + 1, people + n + 1, cmp_person);

    vector<int> product;
    product.push_back(people[0].left_num);
    vector<int> ans;
    ans.push_back(0);

    for (int i = 1; i <= n; i++) {
        vector<int> reward = divide_small(product, people[i].right_num);
        if (less_big(ans, reward)) {
            ans = reward;
        }
        product = multiply_small(product, people[i].left_num);
    }

    print_big(ans);
    return 0;
}
