#primul argument director
#fisierul cu permisiuni de scriere cu numar minim de linii
#fisier cu permisiuni de executie cu numarul maxim de linii


min=999999
fisMin=""

max=-1
fisMax=""

if [ ! -d $1 ];
then
  echo "Primul argument trbuie sa fie un director"
  exit 1
fi


#Cerinta 2 -> fisiere cu permisiuni de executie (nr linii maxim)
files=`find $1 -perm -100 -type f`
for file in $files
do
  lines=`wc -l $file | cut -d" " -f1`
  if [ $lines -gt $max ]
  then
    max=$lines
    fisMax=$file
  fi
done

echo "File: " $fisMax ", lines: " $max


#Cerinta 1 -> fisiere cu permisiuni de scriere (nr linii minim)
files=`find $1 -perm -400 -type f`
for file in $files
do
  lines=`wc -l $file | cut -d" " -f1`
  if [ $lines -lt $min ]
  then
    min=$lines
    fisMin=$file
  fi
done
echo "Files: " $fisMin ", lines: " $min
