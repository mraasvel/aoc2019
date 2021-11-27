FILE = 'input.txt'
A,B = open(FILE).read().split('\n')
A,B = [x.split(',') for x in [A,B]]

DX = {'U' : 0, 'D': 0, 'R': 1, 'L': -1}
DY = {'U' : 1, 'D': -1, 'R': 0, 'L': 0}

def createPoints(S):
	result = dict()
	x = 0
	y = 0
	steps = 1
	for cmd in S:
		d = cmd[0]
		n = int(cmd[1:])
		assert d in ['U', 'D', 'R', 'L']
		for i in range(n):
			x += DX[d]
			y += DY[d]
			result[(x, y)] = steps
			# result.add((x, y))
			steps += 1
	return result

P1 = createPoints(A)
P2 = createPoints(B)

I = set(P1.keys()) & set(P2.keys())

ans = min([abs(x) + abs(y) for (x, y) in I])
ans2 = min([P1[(x, y)] + P2[(x, y)] for (x, y) in I])

print(ans)
print(ans2)
