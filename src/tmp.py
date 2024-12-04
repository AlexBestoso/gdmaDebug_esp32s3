import re
t = "./tmp"


def writeOutput(output, target):
	with open(target, "w") as f:
		for line in output:
			f.write(line)


def getFuncList(target):
	ret = []
	retG = ""
	ctx = 0
	with open(target, "r") as f:
		for line in f:
			if ctx == 0 and re.match('^void ./*', line):
				retG = line
				ctx = 1
			elif ctx == 1 and not re.match('}', line):
				retG = retG + line
			elif ctx == 1 and re.match('}', line):
				ret.append(retG + line)
				retG = ""
				ctx = 0
	return ret

def getFuncName(func):
	for line in func.split('\n'):
		if re.match('^void GdmaDebug',line):
			ret = re.sub('void .*::print_', '', line)
			ret = re.sub('\(bool.*', '', ret)
			return ret
	return False

def getPrintableVars(func, funcName):
	ret = []
	ctx = 0
	for line in func.split('\n'):
		if re.match('^void.*$', line):
			continue
		if re.match('^.*regGet.*$', line):
			retG = re.sub('^\s', '', line)
			retG = re.sub(' = .*$', '', retG)
			outName = re.sub('this->'+funcName+'.', '', retG)
			out = '\tSerial.printf("\\t'+outName+' : 0x%x\\n", '+retG+');'
			ret.append(out)
	return ret
	
### Script start
output = []
newVarList = []
funcList = getFuncList(t)
print('[R]eady to serve Master');

for i in range(0, len(funcList)):
	funcName = getFuncName(funcList[i])
	printableVars = getPrintableVars(funcList[i], funcName)
	ctx = 0
	for line in funcList[i].split('\n'):
		if re.match('^void .*$', line):
			output.append(line+'\n')
			output.append('\tSerial.printf("=== '+funcName+' values ===\\n");\n')
			output.append('\tSerial.printf("\\tRegister Value : 0x%x", this->'+funcName+'.val);\n')
			output.append('\tif(!onlyCoreValues){\n')
			output.append('\t\tSerial.printf("\\tReset Value : 0x%x", this->'+funcName+'.reset);\n')
			output.append('\t\tSerial.printf("\\tOffset Value : 0x%x", this->'+funcName+'.offset);\n')
			for pv in printableVars:
				output.append('\t'+pv+'\n')
			output.append('\t}\n')
			output.append('}\n')
		

for i in output:
	print(i)
writeOutput(output, t)
