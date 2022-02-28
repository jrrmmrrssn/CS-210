"""
	Author:	Jeremy Morrison
	Course:	CS210 Programming Languages 22EW3
	Date:	02/22/2022
"""


import re

import string

import os.path

from os import path

# Function CountAll to read all occurrances of an item

def CountAll():

		#Open the file to read

		text = open("CS210_Project_Three_Input_File.txt", "r")

		#Create an empty dictionary to store items

		dictionary = dict()

		#read each line of file

		for line in text:

			#remove white space from file

			line = line.strip()

			#change to lowercase letters

			word = line.lower()

  

			#check for multiple occurrances

			if word in dictionary:

				#Increment occurrances

				dictionary[word] = dictionary[word] + 1

			else:

				#If item not in dictionary add it with value 1

				dictionary[word] = 1

		#Print the dictionary

		for key in list (dictionary.keys()):

			print(key.capitalize(), ":", dictionary[key])

		#Close file.

		text.close()

#Function CountInstances to display number of times search item appears

def CountInstances(searchTerm):

	#Change search item to lowercase

	searchTerm = searchTerm.lower()

	#Open file to read

	text = open("CS210_Project_Three_Input_File.txt", "r")

	#variable to hold number of item occurrances

	wordCount = 0

	#read each line in file

	for line in text:

		#remove whitespace

		line = line.strip()

		#change to lowercase

		word = line.lower()

  

		#check to make sure item in file matches search item

		if word == searchTerm:

			#increment occurrances

			wordCount += 1

	#Return search item count

	return wordCount

	#Close file

	text.close()

#Function CollectData to read from file and write occorances to new file

def CollectData():

	#Open file to read

	text = open("CS210_Project_Three_Input_File.txt", "r")

	#Create the file to write to

	frequency = open("frequency.dat", "w")

	#Create dictionary to hold items

	dictionary = dict()

	#read each line from file

	for line in text:

		#remove whitespace

		line = line.strip()

		#change to lowercase

		word = line.lower()

		#check for multiple occorances in dictionary

		if word in dictionary:

			#increment occorances

			dictionary[word] = dictionary[word] + 1

		else:

			#if item not in dictionary add and increment

			dictionary[word] = 1

	#write each dictionary item and value to new file

	for key in list (dictionary.keys()):

		#write to file as string with new line

		frequency.write(str(key.capitalize()) + " " + str(dictionary[key]) + "\n")

	#Close files

	text.close()

	frequency.close()