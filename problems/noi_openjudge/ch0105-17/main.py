position = int(input())
first = second = 1

for _ in range(position - 2):
    first, second = second, first + second

print(first if position == 1 else second)
