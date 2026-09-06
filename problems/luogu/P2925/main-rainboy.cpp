/* author: Rainboy  email: rainboylvx@qq.com  time: 2020年 07月 31日 星期五 10:13:51 CST */
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+5;
int C,n;
int f[50005];

int main(){
    cin >> C >> n;
    int i,j,t;
    for(i=1;i<=n;i++){
        cin >> t;
        for(j=C;j>=t;j--)
            f[j] = max(f[j],f[j-t]+t);
    }
    cout << f[C] << endl;
    return 0;
}