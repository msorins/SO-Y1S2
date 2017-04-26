#Primul parametru un prefix, urmatoarele fisiere
#Cate cuvinte din lista sunr prefixate cu acel prefix

if [ $# -lt 2 ];
then
  echo "Invalid number of parameters"
  exit 1
fi

prefix=$1
shift

res=0

while [ $# -ne 0 ]
do
  file=$1

  if [ ! -f "test/"$file ]
  then
    echo "Invalid parameter"
    exit 2
  fi

  match=`cat "test/"$file | grep -E -c "\<$prefix[a-zA-Z]+\>"`

  if [ match != "0" ]
  then
    res=`expr $res + 1`
  fi

  #Go to the next parameter
  shift
done

echo "Result: " $res

