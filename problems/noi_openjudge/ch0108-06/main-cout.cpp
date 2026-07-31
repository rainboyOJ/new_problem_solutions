#include <iomanip>
#include <iostream>

int m,n;
int map[200][200];

int main(){
    int i,j;
    std::cin >> m >> n;
    for (i=1;i<=m;i++){
        for (j=1;j<=n;j++){
            std::cin >> map[i][j];
        }
    }
    int t,cnt=0;
    for (i=1;i<=m;i++){
        for (j=1;j<=n;j++){
            std::cin >> t;
            if( map[i][j] == t)
                cnt++;
        }
    }

    double ans = cnt*100.0/(m*n);
    std::cout << std::fixed << std::setprecision(2) << ans << "\n";
    return 0;
}
