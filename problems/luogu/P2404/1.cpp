#include <bits/stdc++.h>
using namespace std;
int n;

int a[100000];

void dfs(int pre,int left,int dep) {

    if( left == 0) {
        if( dep == 2) return;
        for(int i =1;i<=dep-2;i++)
        {
            cout << a[i] << "+";
        }
        cout << a[dep-1] << "\n";
        return ;
    }

    for(int i = pre ;i<=left;i++) {
        a[dep]  = i;
        dfs(i,left-i,dep+1);
    }

}

int main (int argc, char *argv[]) {
    std::cin >> n;
    dfs(1,n,1);
    
    return 0;
}
