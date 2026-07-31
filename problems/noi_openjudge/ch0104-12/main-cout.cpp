#include <iostream>
int main(){
    int a,b;
    std::cin >> a;
    double walk_time = a / 1.2;
    double bike_time = a / 3.0;
    bike_time += 23;
    bike_time += 27;
    if( bike_time == walk_time)
        std::cout << "All";
    else if ( bike_time > walk_time)
        std::cout << "Walk";
    else {
        std::cout << "Bike";
    }
    return 0;
}
