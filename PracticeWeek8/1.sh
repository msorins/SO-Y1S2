#Primeste ca argumente 1 director.
#Se parcurge recursiv dir, se identifica fisiere .txt cu nr par de linii, fisierele .c cu
#nr impar de cuvinte
#Se afiseasals

if [ $# -ne 1 ];
then
  echo "Numar invalid de parametrii"
  exit 1
fi

if [ ! -d $1 ];
then
  echo "Primul argument nu este un director"
  exit 2
fi

dir=$1


#Fisierele .txt 
echo "Fisiere .tt cu numar par de linii"

txtFiles=`find $dir/*.txt`
for file in $txtFiles
do
  lines=`wc -l $file | cut -d" " -f1`
  res=`expr $lines % 2`

  if [ $res -eq 0 ];
  then
    echo $file;
  fi
  #echo $file
done


#Fisiere .c
echo "Fisere .c cu numar impar de cuvinte"
cFiles=`find $dir/*.c`
for file in $cFiles
do
  lines=`wc -w $file | cut -d" " -f1`
  res=`expr $lines % 2`
  
  if [ $res -eq 1 ] 
  then
    echo $file
  fi
done
