#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
ll ans;

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
    if (ans == -1 || ans > num) ans = num;
    return;
  }

  ll start = 0;
  if (pos == 1) start = 1;

  for (ll i = start; i < 10; i++) {
    if (rest < stick[i]) continue;
    rcd[pos] = i;
    dfs(pos + 1, rest - stick[i]);
  }
}

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

  for (ll i = 1; i <= 30; ++i) {
    n = i;
    ans = -1;
    dfs(1, n);
    std::cout << n << " " << ans << "\n";
  }

  return 0;
}
