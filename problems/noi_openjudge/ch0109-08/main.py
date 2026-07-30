sample_count = int(input())
samples = [float(input()) for _ in range(sample_count)]
samples.remove(max(samples))
samples.remove(min(samples))
average = sum(samples) / len(samples)
error = max(abs(sample - average) for sample in samples)
print(f"{average:.2f} {error:.2f}")
