def count_vk(text):
    total = 0
    for i in range(len(text) - 1):
        if text[i:i + 2] == "VK":
            total += 1
    return total


n = int(input())
s = input().strip()

answer = count_vk(s)

for i in range(n):
    changed = list(s)
    changed[i] = "K" if changed[i] == "V" else "V"
    answer = max(answer, count_vk("".join(changed)))

print(answer)
