distance = int(input())

# 把步行和骑车时间同乘 6 后，比较 5*distance 与 2*distance+300。
walk_scaled = 5 * distance
bike_scaled = 2 * distance + 300

if bike_scaled < walk_scaled:
    print("Bike")
elif bike_scaled > walk_scaled:
    print("Walk")
else:
    print("All")
