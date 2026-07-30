count = int(input())
total = sum(int(input()) for _ in range(count))
print(f"{total} {total / count:.5f}")
