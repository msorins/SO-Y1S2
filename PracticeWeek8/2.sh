#Primete prin parametrii doua numere
#Afiseaza toate numerele pare din acel interva

if [ $# -ne 2 ]
then
  echo "Nr invalid de parametrii"
  exit 1
fi

a=$1
b=$2

#Swap a with b if a is greater than b
if [ $a -gt $b ]
then
  aux=$a
  a=$b
  b=$aux
fi

if [ `expr $a % 2` -eq 1 ]
then
  a=`expr $a + 1`
fi

while [ $a -le $b ]
do
  echo -n $a" "
  a=`expr $a + 2`
done
