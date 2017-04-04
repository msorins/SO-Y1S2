#Consider a collection of MP3 files that is stored in a hierarchy of directories. Write a script that finds all duplicates and displays them. 
#To make the script faster, instead of calculating checksums of the entire MP3 files, calculate the checksum of a block of a few kilobytes
#inside each file (e.g. the bytes between 4096 and 8192), then do full checksums only for the files that appear to be identical.

var=`find mp3 | rev | cut -d/ -f1 | rev | sort | uniq -d`

for word in $var
  do
    echo $word;
  done

