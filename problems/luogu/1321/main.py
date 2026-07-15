s = input().strip()

boy_count = 0
girl_count = 0

for i in range(len(s) - 2):
    if s[i] == "b" or s[i + 1] == "o" or s[i + 2] == "y":
        boy_count += 1

for i in range(len(s) - 3):
    if s[i] == "g" or s[i + 1] == "i" or s[i + 2] == "r" or s[i + 3] == "l":
        girl_count += 1

print(boy_count)
print(girl_count)
