#/bin/bash
#Write a shell script that takes pairs of parameters (a filename and a number 
#n) and outputs for each pair the name of the file, the number n and the nth 
#word from each file.


#VALIDATION FOR THE PARAMETERS
if [ $# -eq 0 ]
then
   echo "Must provide parameters"
   exit 1
fi

if [  `expr $# % 2` -eq 1 ]
then
   echo "Number of parameters must be divisible with 2 (pairs)"
   exit 2
fi


#TAKE PAIR OF PARAMETERS AND DO THE REQUIRED COMPUTATION
while [ $# -ne 0 ]
do
  #Save the current pair and get ready to move to the next one
  a=$1
  b=$2
  shift 2

  #Check if a is a file
  if [ ! -f $a ]
  then
    echo "First parameter from the current pair is not a file"
    exit 3
  fi

  #Get all the words
  words=`cat $a | awk 'BEGIN{ str=""; }{
      gsub("[^a-zA-Z ]", "", $0);
      printf("%s ", $0);
  }'`
  
  countWords=0
  foundWord="Not enough words in file"
  #Loop through them
  for word in $words
  do
    countWords=`expr $countWords + 1`
    if [ $countWords -eq $b ]
    then
      foundWord=$word
      break
    fi
  done
  
  #Print the result for this pair, move to the next one
  echo $a " - " $b ": " $foundWord


done

