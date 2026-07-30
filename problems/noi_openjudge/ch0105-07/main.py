days = int(input())
gold = silver = bronze = 0

for _ in range(days):
    today_gold, today_silver, today_bronze = map(int, input().split())
    gold += today_gold
    silver += today_silver
    bronze += today_bronze

print(gold, silver, bronze, gold + silver + bronze)
