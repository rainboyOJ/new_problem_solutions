#include <iostream>

int m,n;
int map[200][200];
int main(){
    int i,j,sum=0;
    std::cin >> m >> n;
    for (i=1;i<=m;i++){
        for (j=1;j<=n;j++){
            std::cin >> map[i][j];
            if( i == 1 || j == 1 || i == m || j==n){
                sum += map[i][j];
            }
        }
    }
    std::cout << sum << "\n";
    return 0;
}
