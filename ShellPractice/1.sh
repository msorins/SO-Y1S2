#Get two parameters and concatenate them
if test $# -ne 2;
  then 
    echo "Please give 2 parameters";
    exit 1;
fi

a=$1;
b=$2;
c=$1$2;
echo $c;
