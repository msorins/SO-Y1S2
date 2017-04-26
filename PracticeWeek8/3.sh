#Prim argument un director
#Al doilea argument o extensia
#Se gasesc fisierele din directorul respectiv, cu extensia respectiva care
#Nu contin niciun numar par, si au numere impare de cuvinte
#Saa se afiseze numele si drepturile de acces

if [ $# -ne 2 ]
then
  echo "Numar invalid de parametri"
  exit 1
fi

if [ ! -d $1 ]
then
  echo "Primul parametru trebuie sa fie un director"
  exit 2
fi

dir=$1
ext=$2

#find and loop through all the files
files=`find $dir/*.$ext -type f`
for file in $files
do
  wc=`wc -w $file | cut -d" " -f1`

  #Check to see if odd number of words
  if [ `expr $wc % 2 ` -eq 0 ]
  then
    continue
  fi

  #Check to see if there are no even numbers
  evenNr=`cat $file | grep -E -c "\<[0-9]*[02468]\>"`
  if [ $evenNr != "0" ]
  then
    continue
  fi

  echo $file ": "`ls -l $file | cut -d" " -f1`
done
