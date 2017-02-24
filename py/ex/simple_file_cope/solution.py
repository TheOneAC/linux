#!/usr/bin/python

import sys


def file_to_ls(filename):
	try:
		file = open(filename,"r")
	except IOError:
		print "open failed"
		sys.exit()
	else:
		ls = []
		for line in file:
			line = line.split(',')
			l = [];
			for word in line:
				#print word.strip(' ')
				l.append(word.strip(' '))
			ls.append(l)

	file.close()
	return ls
def show_ls(ls):
	for re in ls:
		for index in re:
			print index

def less_sixty(ls):
	for re in ls:
		if int(re[2]) < 60:
			print re[0]

def first_l(ls):
	for re in ls:
		if re[0][0] == 'L':
			print re[0]

def ad(ls):
	s = 0
	for re in ls:
		s += int(re[2])
	return s
def is_right(filename):
	ls = file_to_ls(filename)
	flag = True
	for re in ls:
		if re[0][0].islower():
			flag = False
	return flag

if __name__ == "__main__":
	filename = "record.txt"
	ls = file_to_ls(filename)
	print ('*' * 10)
	show_ls(ls)
	print ('*' * 10)
	less_sixty(ls)
	print "***** first l:"
	first_l(ls)
	print ad(ls)

	if is_right(filename):
		print "Yes"
	else:
		print "No"
