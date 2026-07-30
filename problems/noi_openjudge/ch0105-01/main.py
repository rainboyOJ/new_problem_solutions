count = int(input())
total_age = sum(int(input()) for _ in range(count))
print(f"{total_age / count:.2f}")
