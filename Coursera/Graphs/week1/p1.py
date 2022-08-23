

def explore(start, end, ar):
    global visited

    if start == end:
        return True

    for val in ar[start]:
        if visited[val]:
            continue
        visited[val] = True
        if explore(val, end, ar) == True:
            return True
    
    return False


n, m = map(int, input().split())
ar = []
visited = [False] * (n + 1)

for i in range(n + 1):
    ar.append([])

for i in range(m):
    x, y = map(int, input().split())
    ar[x].append(y)
    ar[y].append(x)

start, end = map(int, input().split())

res = explore(start, end, ar)
print("1" if res else "0")

