#!/usr/bin/env python3
import pandas as pd
import os
import sys

##please give two args: process.py and the filename.
if len(sys.argv)!=2:
	sys.exit("Incorrect number of arguments.")

file = sys.argv[1] #'./dataset_large.tsv'

df = pd.read_csv(file, sep='\t', header =None, names =["word","frequency"])
# print("I have ingested file "+file)

choice = ""
word = ""

while choice != ":q":
	choice = input()
	# print("Input was "+choice)

	if choice.startswith(':g'):
		print(word)
		word = choice.split(" ")[1]
		print("word is "+word)
		# print(word)
		# print("word is lll"+word+"lll")
		freq = df.loc[df['word']==word]
		# print(freq)

		if not freq.empty:
			print(word + " "+ str(freq.iloc[0]['frequency']))
		else:
			print("Not found")

	if choice.startswith(':r'):
		word = choice.split(" ")[1]
		found = df.loc[df['word']==word]

		if found.empty:
			print("Not found")
		else:
			df = df[df.word != word]
			print("Removed")

	##"put" expects word and frequency separated by a space.
	if choice.startswith(':p'):
		myInput   = choice.split(" ")
		word 	  = myInput[1]
		frequency = myInput[2]
		
		newDf = pd.DataFrame(columns=('word','frequency'))

		newDf.loc[0] = [word,frequency]

		#check to see if already exists:
		found = df.loc[df['word']==word]

		if not freq.empty:
			df = df[df.word != word]#unfortunately loop entire thing.

		df = df.append(newDf)
		print("Added")

