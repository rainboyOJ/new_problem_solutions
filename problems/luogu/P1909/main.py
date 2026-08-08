n = int(input())

answer = 10**18
for _ in range(3):
    count, price = map(int, input().split())
    packs = (n + count - 1) // count
    answer = min(answer, packs * price)

print(answer, end="")
