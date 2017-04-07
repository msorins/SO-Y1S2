#Sa se scrie un shell script care primeste ca si parametru
#un director, urmat de oricate cuvinte  (cel putin unul)
#Sa se determine cate fisiere  din directorul dat  ca prim parametru contin 
#un singur cuvant(oricare) dintre cele date ca parametrii

echo $#;

if [ $# -lt  2 ]
then
  echo Must give at least 2 arguments
  exit 1
fi

directory=$1
shift

if [ ! -d $directory ]
then
  echo First argument is not a folder
  exit 2
fi

files=`ls -p $directory | grep -E -v "/"`

resF=0
#Loop through every files
for file in $files
do
  #echo $file
  crt=0
  #Count number of words that appear in that files
  for((i=1; i <= $#; ++i ))
  do
   res=`cat $directory"/"$file | grep -E  -c "\<${!i}\>"`
    if [  "$res" !=  "0" ]
    then
      crt=`expr $crt + 1`
    fi
  done
 
  #If the number is exactly one, then
  if [ $crt -eq 1 ]
  then
    resF=`expr $resF + 1`
  fi 
done


echo "Result: " $resF
