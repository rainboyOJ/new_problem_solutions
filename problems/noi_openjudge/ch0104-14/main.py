weight_text, express = input().split()
weight = int(weight_text)

fee = 8
if weight > 1000:
    fee += (weight - 1000 + 499) // 500 * 4
if express == "y":
    fee += 5

print(fee)
