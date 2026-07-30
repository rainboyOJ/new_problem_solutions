salary, annual_growth = map(int, input().split())
price = 200.0

for year in range(1, 21):
    if salary * year >= price:
        print(year)
        break
    price *= 1 + annual_growth / 100
else:
    print("Impossible")
