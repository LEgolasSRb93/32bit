# -*- coding: utf-8 -*-
"""
Created on Thu Feb  8 09:57:22 2018

@author: lazarc
"""

"""
IS NOT WORKING
"""


import sys

# open output file
outputFile = open('filter.txt', 'w')

# input file name
inputFileName = 'filter.txt'

with open(inputFileName) as openfileobject:
    for line in openfileobject:
         #line = line.replace(" ", "\n\r", 122)
         print(line)
         #outputFile.writelines(line)
        
#outputFile.close