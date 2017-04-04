if [ $# -ne 1 ];
  then 
    echo "Must give 1 parameter"
    exit 1
fi

folder=$1/*
files=`find $folder`
#echo $files;
#echo $folder
i=1
j=1

for fileI in $files
  do
    j=1
    for fileJ in $files
      do
        if [ $i -ne $j ];
          then
            #COMPARE TO FILES THAT ARE ON DIFFERENT POSITIONS
            if [ !  -f $fileI -o !  -f $fileI ];
               then
                 continue;
            fi

            #Select a part of them
            `dd skip=2 count=10 if="$fileI" of="byte1.aux" > /dev/null 2>&1`
            `dd skip=2 count=10 if="$fileJ" of="byte2.aux" > /dev/null 2>&1`
            
            if [ "`cat "byte1.aux"`" = "`cat "byte2.aux"`" ];
              then
                #possible match, must check all
                md5File1=`md5sum  $fileI  | cut -d' ' -f1 > /dev/null 2>&1`
                md5File2=`md5sum  $fileJ  | cut -d' ' -f1 > /dev/null 2>&1`
                if [ "$md5File1" = "$md5File2" ];
                  then
                    echo "Full match found" 
                    echo $fileI "---"  $fileJ
                fi
            fi
          fi 
     
        j=`expr $j + 1`
      done
    i=`expr $i + 1`
  done

#dd skip=2 count=1 if="" of="bigFile.txt.bysasates"
