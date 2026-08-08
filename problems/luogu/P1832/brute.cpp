#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。

const int MAXN = 1005;

int n;
bool is_prime[MAXN];
vector<int> primes;
vector<int> choose_count; // choose_count[i] 表示第 i 个素数用了多少次
long long answer;

void build_primes() {
    for (int i = 2; i <= n; i++) {
        if (!is_prime[i]) {
            primes.push_back(i);
            for (int j = i + i; j <= n; j += i) {
                is_prime[j] = true;
            }
        }
    }
}

int calc_sum() {
    int sum = 0;
    for (int i = 0; i < (int)primes.size(); i++) {
        sum += choose_count[i] * primes[i];
    }
    return sum;
}

// 依次枚举每个素数用了多少次，最后统一检查总和。
void dfs_choose(int dep) {
    if (dep == (int)primes.size()) {
        if (calc_sum() == n) {
            answer++;
        }
        return;
    }

    int p = primes[dep];
    int limit = n / p;
    for (int cnt = 0; cnt <= limit; cnt++) {
        choose_count[dep] = cnt;
        dfs_choose(dep + 1);
    }
}

void read_input() {
    cin >> n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    build_primes();
    choose_count.assign(primes.size(), 0);
    dfs_choose(0);
    cout << answer << '\n';

    return 0;
}
