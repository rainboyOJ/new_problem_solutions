#include <iostream>
using namespace std;
const int maxn = 1e5+5;
int n;
int s[maxn];
int ans;

int main(int argc, char const *argv[])
{
    cin >> n;
    for(int i =1;i<=n;i++) {
        cin >> s[i];
        s[i] += s[i-1];// si  = si-1 + a[i]
    }

    for(int i =1;i<=n;i++) {
        for(int j = i;j<=n;j++)
        {
            // cout << i<< " " << j << endl;
            int t= s[j] - s[i-1];
            if( t % 7 == 0) {
                int len = j-i+1;
                if( ans < len)
                    ans = len;
            }
        }
    }
    cout << ans;
    return 0;
}

