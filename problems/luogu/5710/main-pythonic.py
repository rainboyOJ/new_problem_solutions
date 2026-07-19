x = int(input())
even, mid = x % 2 == 0, 4 < x <= 12
print(int(even and mid), int(even or mid), int(even ^ mid), int(not even and not mid))
