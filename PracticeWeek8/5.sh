#Citeste nume de fisiere pana cand acele fisiere au in total 10 randuri

ok=1
total=0

while [ $ok -eq 1 ]
do
  read file

  if [ ! -f $file ]
  then
    echo "Input must be a valid file"
    continue
  fi

  crt=`wc -l $file | cut -d" " -f1`
  total=`expr $total + $crt`
  
  echo "Current lines: " $total

  if [ $total -ge 10 ];
  then
    break
  fi
done

echo "Result: " $total
