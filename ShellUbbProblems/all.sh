#1.Archive a hierarchy of directories into archives of the following types: zip, tar, tar.gz, tar.bz2.
#The last two types are actually regular TAR archives compressed using gzip or bzip2.


if [ $# -ne 1 ];
  then
    echo "Please give 1 parameter";
    exit 1;
fi

file=$1
ext=".tar.gz"
tar -zcvf $file$ext $file

#================================================================================================

#2Explode a given archive, using the appropriate commands based on the file's extension. This means, recursively extracting
#the original archive and any other archives that it contains.

if [ $# -ne 1 ];
  then
    echo "Please give 1 parameter"
    exit 1
fi


ext=`echo $1 | cut -d\. -f2`
ext2=`echo $1 | cut -d\. -f3`
name=`echo $1 | cut -d\. -f1`

if [ "$ext" = "tar" -a "$ext2" = "gz" ];
  then
    tar -xvf  $1 > unpack
    exit 1
fi

#================================================================================================

#3 Write a script that takes a large file, cuts it into smaller pieces, and uploads all the pieces to a server (in our case it is easier to just copy all the pieces
#to a different location). Write a second script that checks whether all the pieces were copied correctly and none of them were corrupted during the transfer, and
#then concatenates the pieces to obtain the original large file. Hint: create an extra text file containing the checksums of each piece and transfer it along with
#the pieces; then use it to check for corruption
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

#================================================================================================

#4. Consider a collection of MP3 files that is stored in a hierarchy of directories. Write a script that finds all duplicates and displays them.
#To make the script faster, instead of calculating checksums of the entire MP3 files, calculate the checksum of a block of a few kilobytes
#inside each file (e.g. the bytes between 4096 and 8192), then do full checksums only for the files that appear to be identical.

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


#================================================================================================

#5.Find recursively all the file types in a given directory, and display a report showing how many files of each type are there, what is the
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

#================================================================================================

#6 List a file in a directory with different type of permission
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

#================================================================================================

#7. Display the content of a directory as a tree similar to how it is shown below. After each file or directory name, display its total size

printDirectory() {
  depth=$1

  newDepth=`expr $depth + 1`
  path=$2
  echo "Directory: "$path

  files=`find $2/* -maxdepth 1 -type f`
  directories=`find $2/* -maxdepth 1 -type d`



  for file in $files
   do
    i=1
     while [ $i -le $depth ]
       do
         printf "  "
         i=`expr $i + 1`
       done

     printf $file"\n"
   done

  for directory in $directories
    do
       printDirectory $newDepth $directory
    done
  return 0;
}


printDirectory  1 $1

#================================================================================================

#8.Sa se scrie un script shell care afiseaza directoarele primite ca si argum
#in  linia de  comanda crescatoare a spatiuliul  disk care il ocupa, doar
#pentru acele directoare care au dimensiunea lor in biti un numar ce contine
#cel putin o cifra para

computeDirectory() {
   a=1
}

while [ $# -ne 0 ];
do
   if [ ! -d $1 ];
   then
      shift
      continue
   fi

   echo "###  Directory " $1 " ###"

   computeDirectory $1 "beach"

   #This command does the job recursive for each subfolder
   #lst=`du $1 | sort | awk '{ A=int($1); para=0; while(A){ if(A%2==0) para=1; A = A / 10; } if(para == 1) {  print $0; } }'`

   lst=`du -c $1 | tail -n 1 |  awk '{ para = 0; A = int($1); while(A != 0){ if(A%2==0){para = 1; }  A = int( A / 10 ); } if(para==1)  print $1; }' `

   `echo "$lst" > "auxX.tst"`
    cat auxX.tst
    rm auxX.tst

  shift
done


#================================================================================================

#9.Primeste ca si argumente un cuvant, un numar n urmat de oricate fisiere
#Sa se determine care din fisiere contin cuvantul dat pe primele n linii
#scrie rezultatul in fisierul sol.txt

if [ $# -lt 3 ]
then
   echo "Must give at least 3 arguments"
   exit 1
fi

#Get the first two arguments and then shift them
str=$1
n=$2
shift 2

while [ $# -ne 0 ];
do
   if [ ! -f  $1 ];
   then
      echo "Not a file"
      exit 1
   fi

   echo "FILE " $1
   cat $1 | awk -v n="$n" -v str="$str" 'BEGIN{ ok = 0; }{ if( NR < n  && match($0, str) != 0) ok = 1; echo $NR}END{ print ok; }'
   shift
done


#10. ================================================================================================

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


#11. ================================================================================================
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

#12. ================================================================================================
#Script care primeste parametrii in linia de comanda si un cuvant
# & un director si va afisa numele fisierelor care contin cuvantul dat
# in ordine alfabetica


if [ $# -ne 2 ]
then
  echo "Must have two parameters"
  exit 1
fi

directory=$1
str=$2

if [ ! -d  $directory ]
then
  echo "First argument is not a directory"
  exit 2
fi

#Temporary file to concatenate all the results
fileName="saux.txt"

#Loop through all files from that folder
files=`ls $directory -p | grep -v -E "/"`
for file in $files
do
  #Check if the given string is present in that file
  res=`cat $directory"/"$file |  grep -c -E "\<$str\>"`

  if [ $res != "0" ]
  then
    `echo $file >> $fileName`
    a=3
  fi
done

#Print the result
`echo cat $fileName | sort`

#Remove that temporary file
`rm $fileName`
