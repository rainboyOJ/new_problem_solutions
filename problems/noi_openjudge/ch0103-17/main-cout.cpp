#include <iomanip>
#include <iostream>
/* 
三角形的三个顶点坐标求其面积的公式为:
S=(1/2)*(x1y2+x2y3+x3y1-x1y3-x2y1-x3y2)
 * */

int main(){
    double x1,y1,x2,y2,x3,y3;
    std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    double ans = (x1*y2+x2*y3+x3*y1-x1*y3-x2*y1-x3*y2)/2;
    std::cout << std::setw(0) << std::fixed << std::setprecision(2) << ans << "\n";
    return 0;
}
