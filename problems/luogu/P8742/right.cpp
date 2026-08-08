#include <bits/stdc++.h>
using namespace std;
const int maxn = 105, maxv = 1e5 + 5;
int n, a[maxn], f[maxn][maxv], sum, ans;
int main()
{
	cin >> n;
	for( int i = 1; i <= n; i ++ )
	{
		cin >> a[i];
		sum += a[i];
	}
	f[0][0] = 1;
	for( int i = 1; i <= n; i ++ )
	{
		for( int j = sum; j >= 0; j -- )
		{
			f[i][j] |= f[i - 1][j];
			f[i][j] |= f[i - 1][abs( j - a[i] )];
			if( j + a[i] <= sum )
				f[i][j] |= f[i - 1][j + a[i]];
		}
	}
	for( int i = 1; i <= sum; i ++ )
		ans += f[n][i];
	cout << ans;
}

