source, first, second = input().split(",")
first_start = source.find(first)
second_start = source.rfind(second)

if first_start == -1 or second_start == -1 or first_start + len(first) > second_start:
    print(-1)
else:
    print(second_start - (first_start + len(first)))
