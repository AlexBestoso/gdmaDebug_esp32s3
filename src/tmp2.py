import re
target = "./tmp"
output = []
ctx = 0
with open(target, "r") as f:
	for line in f:
		if ctx == 0 and re.match('^register .*$', line):
			print(line)
			output.append(line)
			ctx = 1
		elif ctx == 1 and not re.match('^reset$', line):
			output.append(line)
		elif ctx == 1 and re.match('^reset$', line):
			output.append(line)
			ctx = 0


with open(target, "w") as f:
	for line in output:
		f.write(line)
