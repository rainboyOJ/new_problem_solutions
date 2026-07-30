left, right = map(int, input().split())
first_odd = left if left % 2 else left + 1
print(sum(range(first_odd, right + 1, 2)))
