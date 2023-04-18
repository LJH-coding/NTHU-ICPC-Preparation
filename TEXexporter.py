import os
import sys

def getDirectories(path):
	return [f for f in os.listdir(path) if not os.path.isfile(os.path.join(path, f))]

def getFiles(path):
	return [f for f in os.listdir(path) if os.path.isfile(os.path.join(path, f))]

def isFile(path):
	return os.path.exists(path) and os.path.isfile(path)

def isDirectory(path):
	return os.path.exists(path) and not isFile(path)

args = []

def add(str, newLine = True):
	if newLine == True:
		str += '\n'
	args.append(str)
	# if newLine == True:
	# 	args.append('')

if __name__ == '__main__':
	assert len(sys.argv) > 1
	folder = sys.argv[1]

	with open('settings.txt') as f:
		add(''.join(f.readlines()), False)

	add('\\begin{document}')
	# add('\\fontsize{8.3pt}')
	add('\\maketitle')
	add('\\tableofcontents')

	with open('includes.txt') as f:
		current_dir = ''
		for file in f.readlines():
			file = file.strip()
			if isDirectory(os.path.join(folder, file)):
				current_dir = os.path.join(folder, file)
				add('\\section{{{name}}}'.format(name = file.capitalize()))
				print('[Directory]', file, 'included')
			else:
				pos = file.find('.')
				fmt = file[pos + 1:]
				if fmt == 'tex':
					add(f'\\subsection{{{file[: pos]}}}')
				else:
					add(f'\\subsection{{{file}}}')
				if fmt == 'h':
					add('\\begin{code}')
				with open(os.path.join(current_dir, file)) as r:
					for s in r.readlines():
						if len(s.strip()) > 0:
							add(s.replace('\t', '    '), False)
					# add(''.join([word.replace('\t', '    ') for word in r.readlines()]), False)
				if fmt == 'h':
					add('\\end{code}')
				print('[File]', file, 'included')

	add('\\end{document}')

	# result = []
	# for s in args:
	# 	if len(s.strip()) > 0:
	# 		result.append(s)
	# 		print(s, len(s.strip()))

	with open('main.tex', 'w') as f:
		f.write(''.join(args))