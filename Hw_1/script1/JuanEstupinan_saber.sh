#consigue los archivos
wget http://www.finiterank.com/saber/2011.csv 
wget https://raw.github.com/forero/ComputationalPhysicsUniandes/master/hands_on/unix/columnas_2011.csv.txt

#copia columnas 5 y 8 a colegios.txt
awk -F "\"*,\"*" '{print $5$8}' 2011.csv > colegios.txt

echo busca colegios privados
grep NO colegios.txt | wc -w
echo busca colegios publicos
grep SI colegios.txt | wc -w
echo busca privados A
grep NOA colegios.txt | wc -w
echo busca privados B
grep NOB colegios.txt | wc -w
echo busca públicos B
grep SIB colegios.txt | wc -w

echo limpiando datos
rm colegios.txt
rm 2011.csv
rm columnas_2011_csv.txt
