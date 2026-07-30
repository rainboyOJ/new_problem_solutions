count = int(input())
samples = map(float, input().split())
print(f"{sum(samples) / count:.4f}")
