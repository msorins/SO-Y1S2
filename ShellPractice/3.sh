#Check if all the files in a given directory are having names shorter than 10 characters
if [ $# -ne 1 ];
  then echo "Must give 1 parameter";
  exit 1;
fi

ok=1
for file in `ls $1`
  do
    if [ ${#file} -gt 10 ];
      then ok=0;
    fi
  done

if [ $ok -eq 1 ];
  then echo "All files are OK";
  else echo "Some of the files are not OK";
fi
