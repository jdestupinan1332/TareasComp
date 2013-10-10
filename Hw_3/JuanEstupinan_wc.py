import sys, string, os
for files in os.listdir("."):
    try:
        infile = open(files, 'r')
        text = infile.readlines()
        print files, len(text)
    except:
        pass
