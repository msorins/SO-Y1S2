#Check if all the params are executabile files

while [ $# -ne 0 ]
  do
    echo $1
    if [ -x $1 ];
      then echo $1 "are permisiuni de executaree";
    else
      echo $1 "nu are permisiuni de executareee";
    fi
    shift
  done
