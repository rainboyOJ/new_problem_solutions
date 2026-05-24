
#include <bits/stdc++.h>
using namespace std;
const long long maxn = 1e6+5;
long long a[maxn];
long long b[maxn];
long long cnt[maxn];
long long n,c;
int main(long long argc, char const *argv[])
{
  cin >> n >> c;
  for (long long i = 0; i < n; i++)
  {
    cin >> a[i+1];
  }
  sort(a+1,a+1+n);
  b[1] = a[1];
  cnt[1]++;
  long long idx = 1;
  for(long long i = 2;i<=n;i++) {
    if( a[i] == a[i-1]) {
      cnt[idx]++;
    }
    else {
      idx++;
      cnt[idx] = 1;
      b[idx] = a[i];
    }
  }
  // for(long long i =1;i<=idx;i++)
  // {
  //   cout << b[i] << ' ' << cnt[i] << endl;
  // }

  long long h=1,t=2;

  long long ans = 0;
  while(1) {

    if( t > idx || h > idx ) break;

    if( b[t] - b[h] == c) {
      ans += cnt[t] * cnt[h];
      // b[t]不可能再和前面产生贡献了
      t++;
    }
    else if (b[t] - b[h] > c) {
      h++;
    }
    else if ( b[t] - b[h] < c) {
      t++;
    }
  }
  cout << ans << endl;

  return 0;
}