#Script care primeste parametrii in linia de comanda si un cuvant
# & un director si va afisa numele fisierelor care contin cuvantul dat
# in ordine alfabetica


if [ $# -ne 2 ]
then
  echo "Must have two parameters"
  exit 1
fi

directory=$1
str=$2

if [ ! -d  $directory ]
then
  echo "First argument is not a directory"
  exit 2
fi

#Temporary file to concatenate all the results
fileName="saux.txt"

#Loop through all files from that folder
files=`ls $directory -p | grep -v -E "/"`
for file in $files
do
  #Check if the given string is present in that file
  res=`cat $directory"/"$file |  grep -c -E "\<$str\>"`
  
  if [ $res != "0" ]
  then
    `echo $file >> $fileName`
    a=3
  fi
done

#Print the result
`echo cat $fileName | sort`

#Remove that temporary file
`rm $fileName`
