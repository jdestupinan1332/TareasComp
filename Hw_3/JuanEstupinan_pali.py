import sys, string, codecs
n_argv = len(sys.argv)
if (n_argv != 2):
    print "EL programa debe inicializarse con un argumento"
    sys.exit(1)

filein = codecs.open(sys.argv[1],"r","utf8")
Lineas = filein.readlines()
filein.close()

to_remove = [';',':',' ', ',', '_','-', '.','(', ')', '#','"','[',']','\n', '\r', u'\x0c',u'\u011d', u'\u2014', u'\u016d', u'\u0109', u'\u2123']
PPali = []

for Linea in Lineas:
    l = -1
    linea = Linea.lower()
    ListLinea = list(linea)
    for letra in linea:
        l = l+1
        for quitar in to_remove:
            if letra == quitar:
                ListLinea.pop(l)
                l = l-1
    PPali.append(ListLinea)
  
finalCheck = []
for item in PPali:
    it = True;
    longitud = len(item)
    check = []
    i = -1
    while i <= 0.5*len(item)-1:
        i = i + 1
        forw = item[i]
        reve = item[len(item)-1-i]
        if reve != forw:
            check.append(0)
        elif reve == forw:
            check.append(1)
    for numero in  check:
        if numero == 0:
            it = False
    finalCheck.append(it)

a = 0
#print finalCheck
while a<=len(Lineas)-1:
    Lin = Lineas[a]
    Val = finalCheck[a]
    print Val
    a = a+1
                        
           

        
                
