import sys, string
narchiv = len(sys.argv)
if (narchiv != 2):
    print "El programa debe iniciarse con un argumento"
    sys.exit(1)

filein = sys.argv[1]
N_a = 0
N_e = 0
N_i = 0
N_o = 0
N_u = 0



infile = open(filein,'r')
text = infile.readlines()
for palabra in text:
    for letra in palabra:
        if (letra == 'a' or letra == 'A'):
            N_a = N_a + 1
        if (letra == 'e' or letra == 'E'):
            N_e = N_e + 1
        if (letra == 'i' or letra == 'I'):
            N_i = N_i + 1
        if (letra == 'o' or letra == 'O'):
            N_o = N_o + 1
        if (letra == 'u' or letra == 'U'):
            N_u = N_u + 1
infile.close()
print "a = ", N_a
print "e = ", N_e
print "i = ", N_i
print "o = ", N_o
print "u = ", N_u


                    



