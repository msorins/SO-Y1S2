#Script care primeste ca si parametru un director, urmat de oricate cuvinte (min 1)
#cate fisiere din directorul dat contin toate cuvintele date


if [ $# -lt 2 ]
then
   echo "Must have at least 2 parameters"
   exit 1
fi

directory=$1
shift

if [ ! -d $directory ]
then
   echo "First parameter must be a directory"
fi

resF=0

#Loop through all files from given folder
files=` ls $directory -p | grep -v -E "/"`

for file in $files
do
  #Loop through each string parameter
  foundNR=0
  
  for((i=1; i <= $#; ++i ))
  do
    found=`cat $directory"/"$file | grep -c -E "\<${!i}\>"`
    
    if [ $found != "0" ]
    then
      foundNR=`expr $foundNR + 1`
    fi
  done

  if [ $foundNR == $# ]
  then
    resF=`expr $resF + 1`
  fi
done

echo "Result" $resF


