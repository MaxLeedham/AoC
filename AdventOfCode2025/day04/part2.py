grid =[]

with open("test-input.txt", "r") as f:
    grid = [[y for y in x.strip()] for x in f.readlines()]

def get_adjacent(grid: list[list[str]], x: int, y: int) -> list[str]:
    if y > len(grid) or x > len(grid[0]):
        return []

    directions = [(1, 1), (1, 0), (1, -1), (0, 1), (0, -1), (-1, 1), (-1, 0), (-1, -1)]

    adjacent = []
    for x_dir, y_dir in directions:
        new_x = x + x_dir
        new_y = y + y_dir

        if new_x < 0 or new_y < 0 or new_x > len(grid[0])-1 or new_y > len(grid)-1:
            continue

        adjacent.append(grid[new_y][new_x])

    return adjacent

total_removed = 0

while True:
    to_remove = []

    for y in range(len(grid)):
        for x in range(len(grid[0])):
            if grid[y][x] != "@":
                continue

            adj = get_adjacent(grid, x, y)
            if (adj.count("@") + adj.count("x")) < 4:
                to_remove.append((x, y))

    if to_remove == []:
        break

    for x, y in to_remove:
        grid[y][x] = "."

    total_removed += len(to_remove)

print(f"Number of rolls removed: {total_removed}")