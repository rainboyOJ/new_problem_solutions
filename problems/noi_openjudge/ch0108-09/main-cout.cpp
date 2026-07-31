#include <iostream>

int n,m,k;
int a[200][200];
int b[200][200];
int c[200][200];
int main(){
    int i,j;
    std::cin >> n >> m >> k;
    for (i=1;i<=n;i++){
        for (j=1;j<=m;j++){
            std::cin >> a[i][j];
        }
    }
    for (i=1;i<=m;i++){
        for (j=1;j<=k;j++){
            std::cin >> b[i][j];
        }
    }
    int x,y;
    for (i=1;i<=n;i++){
        for (j=1;j<=k;j++){
            for(x=1;x<=m;x++){
                c[i][j] += a[i][x]*b[x][j];
            }
            std::cout << c[i][j] << " ";
        }
        std::cout << "\n";
    }
    return 0;
}
