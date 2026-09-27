#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
ll ans;
ll ans_len;

// 0 1 2 3 4 5 6 7 8 9
ll stick[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
ll rcd[100009];

void dfs(ll pos, ll rest) {

  if (rest == 1) {
    return;
  }
  if (rest == 0) {
    ll num = 0;
    for (ll i = 1; i < pos; i++) num = num * 10 + rcd[i];
    if (ans == -1 || ans > num) {
      ans_len = pos - 1;
      ans = num;
    }
    return;
  }

  // 剪枝
  if (pos > ans_len && ans_len != -1) return;

  ll start = 0;
  if (pos == 1) start = 1;

  for (ll i = 9; i >= start; i--) {
    if (rest < stick[i]) continue;
    rcd[pos] = i;
    dfs(pos + 1, rest - stick[i]);
  }
}

// 1 -1
// 2 1
// 3 7
// 4 4
// 5 2
// 6 6
// 7 8
// 8 10
// 9 18
// 10 22
// 11 20
// 12 28
// 13 68
// 14 88
// 15 108
// 16 188
// 17 200
// 18 208
// 19 288
// 20 688
// 21 888
// 22 1088
// 23 1888
// 24 2008
// 25 2088
// 26 2888
// 27 6888
// 28 8888
// 29 10888
// 30 18888
// 31 20088
// 32 20888
// 33 28888
// 34 68888
// 35 88888
// 36 108888
// 37 188888
// 38 200888
// 39 208888
// 40 288888
// 41 688888
// 42 888888
// 43 1088888
// 44 1888888
// 45 2008888
// 46 2088888
// 47 2888888
// 48 6888888
// 49 8888888
// 50 10888888
// 打表

int main() {

  ll t;
  std::cin >> t;
  // while (t--) {
  //   ll n;
  //   std::cin >> n;
  //
  //   ans = -1;
  //   dfs(1, n);
  //   std::cout << ans << "\n";
  // }

  for (ll i = 1; i <= 50; ++i) {
    n = i;
    ans = -1;
    ans_len = -1;
    dfs(1, n);
    std::cout << n << " " << ans << "\n";
  }

  return 0;
}
