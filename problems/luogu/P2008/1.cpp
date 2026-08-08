// dp[i] = min(dp[j]) + 1
// sum[i] = 
// pre[i]
#include <bits/stdc++.h>
using namespace std;

typedef  long long ll ;
const int maxn = 1e4+5;
ll dp[maxn];
ll sum[maxn];
int pre[maxn];

ll a[maxn];

int n;

void init(){
    std::cin >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> a[i];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init();

    // dp dp[1] = a[1]
    dp[1] = 1;
    sum[1] = a[1];
    // pre[1] = 0;

    // calc dp
    for(int i = 2;i <= n ;++i ) // i: 2->n
    {
        dp[i] = 1;

        int pre_j = 0;
        for(int j = 1;j <= i-1 ;++j ) // j: 1->i
        {

            if( a[j] <= a[i]) {

                if( pre_j == 0) {
                    pre_j = j;
                    continue;
                }

                // 找到一个更好的前驱,也就是更大的
                if( dp[pre_j] < dp[j] ) {
                    pre_j = j;
                    continue;
                }

                // if( dp[pre_j] == dp[j] && sum[pre_j]  < sum[j] )
                // {
                //     pre_j = j;
                //     continue;
                // }

            }
        }

        pre[i] = pre_j;
        sum[i] = a[i];
        if( pre_j != 0 ) {
            dp[i] = dp[pre_j] +1;
            sum[i] = sum[pre_j] + a[i];
        }

    }

    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        cout << sum[i] << " ";
    }
    std::cout << "\n";

    return 0;
}
