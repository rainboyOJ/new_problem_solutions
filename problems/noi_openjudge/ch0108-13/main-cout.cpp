#include <cstring>
#include <iostream>

int n,m;
int a[200][200];
int b[200][200];

void init(){
    std::cin >> n >> m;
    int i,j;
    for (i=1;i<=n;i++){
        for (j=1;j<=m;j++){
            std::cin >> a[i][j];
            b[i][j] = a[i][j];
        }
    }
}

int calc(int x,int y){
    int fx[4][2] = { 1,0, 0,1, -1,0, 0,-1 };
    int i;
    int sum = a[x][y];
    for (i=0;i<4;i++){
        int nx = x+fx[i][0];
        int ny = y+fx[i][1];
        sum += a[nx][ny];
    }
    return (int)(sum*1.0 / 5+0.5);
}
int main(){
    init();
    int i,j;
    for (i=2;i<n;i++){
        for (j=2;j<m;j++){
            b[i][j] = calc(i, j);
        }
    }
    for (i=1;i<=n;i++){
        for (j=1;j<=m;j++)
            std::cout << b[i][j] << " ";
        std::cout << "\n";
    }
    return 0;
}
