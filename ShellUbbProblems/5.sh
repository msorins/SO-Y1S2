#Find recursively all the file types in a given directory, and display a report showing how many files of each type are there, what is the
#total space occupied by each type, what is the largest file size of each type. Use the command "file" to determine the type of a file.

if [ $# -ne 1 ];
  then
    echo "Please enter one command"
    exit 1
fi

dir=$1"/*"
files=`find $1`
filesTypes=""
for file in $files
  do
    type=`file $file | sort`
    typeCut=`echo $type | cut -d' ' -f2`
    filesTypes="$filesTypes""$file""-""$typeCut""\n"
    #echo $typeCut
  done

`echo -e $filesTypes > aux.txt`

echo "###   NUMBER of files by type   ###"
cat "aux.txt" | cut -d'-' -f2 | sort -n | uniq -c  


echo -e "\n"
echo "### LARGEST files by type ###"
#filesBySize=`find mp3/* | du | sort -n -r| awk '{gsub("(\t)", "-", $0); print $0}'`
#for file in $filesBySize
#  do
#    fileName=`echo $file | cut -d'-' -f2`
#    #fileName=`echo $fileName | cut -d'/' -f2`
#    echo $fileName
#    if test  -f $fileName ;
#     then
#      echo $file
#    fi
#  done


filesBySize=`find $dir -type f  -exec ls -lh {} \; | awk '{ print $5 "-" $9 }' | sort -r`
crt=0
last=""
past[0]=""
for file in $filesBySize
  do
    crt=`expr $crt + 1`
    extension=`echo $file | rev | cut -d'.' -f1 | rev`
    past[$crt]=$extension
 
    if [ $crt -eq 1 -o ! "$last" == "$extension" ];
      then
        i=1
        ok=1
        while [ $i -lt $crt ]
          do
            if [ "${past[$i]}" == "$extension" ];
              then
                ok=0
            fi
            i=`expr $i + 1`
          done

        if [ $ok -eq 1 ];
          then
            echo $file
        fi

        last=$extension
    fi
  done

