amount = int(input())

for denomination in (100, 50, 20, 10, 5, 1):
    count, amount = divmod(amount, denomination)
    print(count)
