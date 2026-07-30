left, right = map(int, input().split())
first_multiple = (left + 16) // 17 * 17
print(sum(range(first_multiple, right + 1, 17)))
