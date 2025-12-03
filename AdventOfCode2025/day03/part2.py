banks = []

with open("input.txt", "r") as f:
    banks = [[int(jolt) for jolt in line.strip()] for line in f.readlines()]

total = 0

for bank in banks:
    joltage = 0
    left_index = 0

    for i in range(11, -1, -1):
        end = -i if i > 0 else None
        jolt = max(bank[left_index:end])
        left_index = bank[left_index:end].index(jolt) + left_index + 1
        joltage += jolt * (10 ** (i))

    total += joltage

print(f"Total: {total}")