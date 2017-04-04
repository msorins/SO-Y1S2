#Primeste ca si argumente un cuvant, un numar n urmat de oricate fisiere
#Sa se determine care din fisiere contin cuvantul dat pe primele n linii
#scrie rezultatul in fisierul sol.txt

if [ $# -lt 3 ]
then
   echo "Must give at least 3 arguments"
   exit 1
fi

#Get the first two arguments and then shift them
str=$1
n=$2
shift 2

while [ $# -ne 0 ];
do
   if [ ! -f  $1 ];
   then
      echo "Not a file"
      exit 1
   fi
   
   echo "FILE " $1
   cat $1 | awk -v n="$n" -v str="$str" 'BEGIN{ ok = 0; }{ if( NR < n  && match($0, str) != 0) ok = 1; echo $NR}END{ print ok; }'
   shift
done
