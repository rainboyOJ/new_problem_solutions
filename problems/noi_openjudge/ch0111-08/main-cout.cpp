#include <bits/stdc++.h>
using namespace std;

int n;
int a[1000005];

int main(){
    std::cin >> n;
    int i;
    for (i=1;i<=n;i++){
        std::cin >> a[i];
    }
    sort(a+1,a+n+1);
    int pos = unique(a+1, a+n+1)-(a+1);
    for(i=1;i<=pos;i++)
        std::cout << a[i] << " ";
    return 0;
}
