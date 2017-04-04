if [ $# -ne 1 ];
  then
    echo "Please give 1 parameter"
    exit 1
fi

if [ ! -f $1 ];
  then
    echo "Input is not a file"
    exit 2
fi

#Save the original MD%
orgMD5=`md5sum $1 | cut -d' ' -f1`
echo $orgMD5

#Split that file into 10 smaller files that have the  prefix chunk
split -n 10 $1  chunk

#Move those chunks into an subfolder
rm -rf "dest"
mkdir "dest"
for file in `ls | grep 'chunk.*'`
  do 
    mv $file "./dest/"$file
  done


#Concatenate those chunks into one file
for file in `ls "./dest"`
  do
    cat "./dest/"$file >> "./dest/"$1
  done

newMD5=`md5sum "./dest/"$file | cut -d' ' -f1`
echo $newMD5;
if [ $orgMD5 = $newMD5 ];
  then
    echo "File copied succesfully";
  else
    echo "There was an error during the copy";
    exit 3;
fi
