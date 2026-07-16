n = int(input())
countries = list(enumerate(map(int, input().split()), start=1))
half = 1 << (n - 1)
finalists = (
    max(countries[:half], key=lambda country: country[1]),
    max(countries[half:], key=lambda country: country[1]),
)

print(min(finalists, key=lambda country: country[1])[0])
