grid =[]

with open("input.txt", "r") as f:
    grid = [[y for y in x.strip()] for x in f.readlines()]


def get_adjacent(grid: list[list[str]], x: int, y: int) -> list[str]:
    if y >= len(grid) or x >= len(grid[0]):
        return []

    directions = [
        (1, 1),
        (1, 0),
        (1, -1),
        (0, 1),
        (0, -1),
        (-1, 1),
        (-1, 0),
        (-1, -1),
    ]

    adjacent = []
    for dx, dy in directions:
        nx, ny = x + dx, y + dy
        if 0 <= nx < len(grid[0]) and 0 <= ny < len(grid):
            adjacent.append(grid[ny][nx])
    return adjacent

rolls = 0


for y in range(len(grid)):
    for x in range(len(grid[0])):
        if grid[y][x] != "@":
            continue

        adj = get_adjacent(grid, x, y)

        if (adj.count("@") + adj.count("x")) < 4:
            rolls += 1

            grid[y][x] = "x"

print(f"Number of rolls the forklift can access: {rolls}")