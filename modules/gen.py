#! /usr/bin/env python

import sys
import re

def decypherCmd(rawcmd, data):
	func = False
	low = False
	upp = False
	
	if rawcmd[-2:] == '()':
		cmd = rawcmd.lower()
		func = True
	elif rawcmd.islower():
		cmd = rawcmd
		low = True
	elif rawcmd.isupper():
		cmd = rawcmd.lower()
		upp = True
	else:
		cmd = rawcmd.lower()
	
	replacement = ""
	if func:
		replacement = str(data[cmd]())
	else:
		replacement = str(data[cmd])
		
	if low:
		replacement.lower()
	elif upp:
		replacement.upper()

	return replacement

def fallDownCmd(rCmds, data):
	if len(rCmds) > 1:
		return fallDownCmd(rCmds[1:], data[str(rCmds[0])])
	else:
		return decypherCmd(rCmds[0], data)

def replaceFor(inputfile, data={}, flag='___'):
	if not data or data == None:
		sys.stderr.writeln("No data found; '{}' ignored\n".format(inputfile))
		return
	
	with open(inputfile, 'r') as f:
		file = f.read()
	
	#___[\[\]\w\.]+___
	results = re.findall(r'___[\(\)\w\.]+___', file)
	
	for result in set(results):
		rName = result[3:-3]
		rCmds = rName.split('.')
		replacement = fallDownCmd(rCmds, data)
		
		file = file.replace(result, replacement)
	print(file)

class Module:
	def __init__(self, title="", values=[], inputCount=0, outputCount=0, paralsCount=0):
		self.title = title
		self.values = values
		self.inputCount = inputCount
		self.outputCount = outputCount
		self.paralsCount = paralsCount
		
class BasicModule(Module):
	def __init__(self, title="", values=[], inputCount=0, outputCount=0, paralsCount=0, streamClass=""):
		super().__init__(title, values, inputCount, outputCount, paralsCount)
		self.streamClass = streamClass
		
# class SingleValueBasicModule(BasicModule):
# 	def __init__(self, title="", values=[], inputCount=0, outputCount=0, paralsCount=0, streamClass="", ):

if __name__ == '__main__':
	def creates():
		return "values[0] = new BoundedValue(0.3f, 0.0f, 0.05f, 5.0f);"
	
	def defaults():
		return "s->reverbTime(0.3f);"
		
	def deletes():
		return "delete values[0];"
	
	def names():
		return "\"reverb time\""
	
	def updates():
		return "// do something here"
	
	data = {
		'values': {
			'creates()': creates,
			'defaults()': defaults,
			'deletes()': deletes,
			'names()': names,
			'updates()': updates,
			'len': 1
		},
		'name': 'Reverb',
		'audiostream': 'AudioEffectReverb',
		'date': 'Some day',
		'paralscount': 1,
		'outputcount': 1,
		'inputcount': 1,
		'author': 'MisterCavespider',
		'title': 'REV'
	}
	
	replaceFor('___gen___.cpp', data)
