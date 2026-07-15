def next_permutation(a):
    n = len(a)
    i = n - 2
    while i >= 0 and a[i] > a[i + 1]:
        i -= 1

    j = n - 1
    while a[j] < a[i]:
        j -= 1

    a[i], a[j] = a[j], a[i]
    a[i + 1:] = reversed(a[i + 1:])


n = int(input())
m = int(input())
numbers = list(map(int, input().split()))

for _ in range(m):
    next_permutation(numbers)

print(*numbers)
