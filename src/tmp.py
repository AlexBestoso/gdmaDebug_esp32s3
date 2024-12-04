import re
t = "./tmp"


def writeOutput(output, target):
	with open(target, "w") as f:
		for line in output:
			f.write(line)

def structsOnly(target):
	ret = []
	ctx = 0
	with open(target, 'r') as f:
		for line in f:
			if re.match('^//.*$', line):
				print('[+] removed comment...')
			elif ctx == 0 and re.match('^struct .*{$', line):
				ret.append(line)
				ctx = 1
			elif ctx == 1 and not re.match('^};$', line):
				ret.append(line)
			elif ctx == 1 and re.match('^};$', line):
				ret.append(line)
				ctx = 0
		writeOutput(ret, target)

def nameSwap(target1, target2):
	ret = []
	f2 = open(target2, "r")
	for name in f2:
		with open(target1, "r") as f1:
			for line in f1:
				if re.match('^void GdmaDebug::', line):
					ret.append(re.sub('init_gdma.*{', "init_"+re.sub('[\n\r]+$', '', name)+"(void){", line))
				else:
					ret.append(line)
		writeOutput(ret, target1)
		ret = []
	f2.close()

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

gdmaStructNames = [
	"in_conf0",
	"in_conf1",
	"in_pop",
	"in_link",
	"out_conf0",
	"out_conf1",
	"out_push",
	"out_link",
	"pd_conf",
	"misc_conf",
	"in_int_raw",
	"in_int_st",
	"in_int_ena",
	"in_int_clr",
	"out_int_raw",
	"out_int_st",
	"out_int_ena",
	"out_int_clr",
	"extmem_reject_int",
	"extmem_reject_int_st",
	"extmem_reject_int_ena",
	"extmem_reject_int_clr",
	"infifo_status",
	"in_state",
	"in_suc_eof_des_addr",
	"in_err_eof_des_addr",
	"in_dscr",
	"in_dscr_bf0",
	"in_dscr_bf1",
	"outfifo_status",
	"out_state",
	"out_eof_des_addr",
	"out_eof_bfr_des_addr",
	"out_dscr",
	"out_dscr_bf0",
	"out_dscr_bf1",
	"in_pri",
	"out_pri",
	"in_peri_sel",
	"out_peri_sel",
	"extmem_reject_addr",
	"extmem_reject_st",
	"date"
]

def getFuncName(func):
	for line in func.split('\n'):
		if re.match('^void GdmaDebug',line):
			ret = re.sub('void .*::init_', '', line)
			ret = re.sub('\(void.*', '', ret)
			return ret
	return False

def getFuncVars(func):
	ctx = 0
	ret = []
	retG = ""
	for line in func.split('\n'):
		if ctx == 0 and re.match('^.*regRead.*$', line):
			ctx = 1
		elif ctx == 1 and re.match('^.*bool.*$', line):
			retG = line + "\n"
			ctx = 2
		elif ctx == 1 and re.match('^.*uint32_t.*$', line):
			retG = line + "\n"
			ctx = 3
		elif ctx == 2 and re.match('^.*int.*$', line):
			ret.append(retG + line + "\n")
			ctx = 1
		elif (ctx == 3 or ctx == 6) and re.match('^.*int.*$', line):
			retG = retG + line + "\n"
			if ctx == 3:
				ctx = 6
			else:
				ctx = 1
				ret.append(retG)
	return ret

def processVars(coreName, var):
	ret = []
	ctx = 0
	name = ""
	pos = ""
	x = ""
	y = ""
	for v in var.split('\n'):
		if ctx == 1 and re.match('^.*int ', v):
			x = re.sub('^.*int ', '', v)
			x = re.sub(' = .*$', '', x)
			ctx = 3
		elif ctx == 3 and re.match('^.*int ', v):
			y = re.sub('^.*int ', '', v)
			y = re.sub(' = .*$', '', y)
			ctx = 0
			ret.append('\tthis->'+coreName+"."+name+' = this->regGet(\n\t\tthis->'+coreName+'.val,\n\t\tthis->'+coreName+'.'+x+',\n\t\tthis->'+coreName+'.'+y+'\n\t);')
		elif ctx == 2 and re.match('^.*int ', v):
			pos = re.sub('^.*int ', '', v)
			pos = re.sub(' = .*$', '', pos)
			ret.append('\tthis->'+coreName+"."+name+' = this->regGet(\n\t\tthis->'+coreName+'.val,\n\t\tthis->'+coreName+'.'+pos+'\n\t);')
			ctx = 0
		elif re.match('^.*uint32_t ', v):
			name = re.sub('^.*uint32_t ', '', v)
			name = re.sub(' = .*$', '', name)
			ctx = 1
		elif re.match('^.*bool ', v):
			name = re.sub('^.*bool ', '', v)
			name = re.sub(' = .*$', '', name)
			ctx = 2
	return ret
	
	
### Script start
output = []
newVarList = []
funcList = getFuncList(t)
print('[R]eady to serve Master');

for i in range(0, len(funcList)):
	funcName = getFuncName(funcList[i])
	funcVars = getFuncVars(funcList[i])
	ctx = 0
	outG = ""	
	newVarList = []
	for var in funcVars:
		newVarList.append(processVars(funcName, var))

	ctx = 0
	for f in funcList[i].split('\n'):
		if ctx == 0 and not re.match('^.*regRead.*$', f):
			output.append(f+'\n')
		elif ctx == 0 and re.match('^.*regRead.*$', f):
			output.append(f+'\n')
			ctx = 1
		elif ctx == 1:
			for nvl in newVarList:
				for n in nvl:
					output.append(n+'\n')
			output.append('}\n')
			ctx = 0
			break
	
			
		
writeOutput(output, t)
