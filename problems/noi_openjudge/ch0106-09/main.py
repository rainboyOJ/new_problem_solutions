dimension = int(input())
first = map(int, input().split())
second = map(int, input().split())
print(sum(left * right for left, right in zip(first, second)))
