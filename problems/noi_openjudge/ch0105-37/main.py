maximum_stamina, combat_power, energy = map(int, input().split())

while True:
    # 每个元素至多恢复当前战斗力，需要向上取整计算元素数。
    energy_needed = (maximum_stamina + combat_power - 1) // combat_power
    if energy < energy_needed:
        break

    energy -= energy_needed
    combat_power += maximum_stamina // combat_power

print(combat_power)
