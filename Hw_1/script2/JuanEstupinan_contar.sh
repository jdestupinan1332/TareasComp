echo bajando archivo
wget https://raw.github.com/forero/ComputationalPhysicsUniandes/master/hands_on/unix/random_3D.dat

echo contando 0 = 
grep -o 0 random_3D.dat | wc -l
echo contando 1 = 
grep -o 1 random_3D.dat | wc -l
echo contando 2 = 
grep -o 2 random_3D.dat | wc -l
echo contando 3 = 
grep -o 3 random_3D.dat | wc -l
echo contando 4 = 
grep -o 4 random_3D.dat | wc -l
echo contando 5 = 
grep -o 5 random_3D.dat | wc -l
echo contando 6 = 
grep -o 6 random_3D.dat | wc -l
echo contando 7 = 
grep -o 7 random_3D.dat | wc -l
echo contando 8 = 
grep -o 8 random_3D.dat | wc -l
echo contando 9 = 
grep -o 9 random_3D.dat | wc -l

echo borrando datos
rm random_3D.dat
