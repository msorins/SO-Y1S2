
if [ $# -ne 1 ];
  then
    echo "Please give one parameter"
    exit 1
fi

dir=$1
files=`find $dir/* -type f  -perm 777`

echo "###   FILES that have 777 PERMISION   ###"
for file in $files
  do
    echo $file
  done

echo -e "\n\n"


echo "### FILES that have WRITE PERMISION ###"
filesx=`find mp3 -perm -222`
for file in $filesx
  do
    #Print it
    echo $file
   
    #Remove its permision
    chmod a-w "$file"
   done

