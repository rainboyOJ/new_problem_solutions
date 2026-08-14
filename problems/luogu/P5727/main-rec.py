def hailstone(n):
    if n == 1:
        print(1, end=" ")
        return
    if n % 2 == 1:
        hailstone(n * 3 + 1)
    else:
        hailstone(n // 2)
    print(n, end=" ")


n = int(input())
hailstone(n)
