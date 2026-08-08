usage = int(input())

if usage <= 150:
    fee = usage * 0.4463
elif usage <= 400:
    fee = 150 * 0.4463 + (usage - 150) * 0.4663
else:
    fee = 150 * 0.4463 + 250 * 0.4663 + (usage - 400) * 0.5663

print(f"{fee:.1f}", end="")
