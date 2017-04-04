#Print the names of those who contributed between $75 and $200 in the first month.
#awk -F: '{ split($2, A, " "); X = substr(A[1], 2, length(A) + 1); X = X + 0; if(X >= 75 && X <= 500) print $1 }' script2.txt

#Print the names and phone numbers of those with an average monthly contribution greater than $200.
#awk -F: '{ A = $3 + 0; B = $3 +0; C = $3 + 0; if((A+B+C)/3 >= 200) print $1, $2 }' script2.txt

#Add $10 to Chet’s second contribution and print the changed record.
#awk -F: '{ A = $4 + 10;  print $1, $2, $3, A, $5}' script2.txt

#Change Nancy McNeil’s name to Louise McInnes and print the changed record.
#awk -F: 'BEGIN{ print "## BEGIN ##"}{ if( index($1, "Nancy McNeil") == 1 ) $1 = "Louise McInnes"; print $0}END{ print "## END ##" }' script2.txt

#Display the Name - Minimum contribution
#awk -F: '{ MIN = $3; if($4 < MIN) MIN = $4; if($5 < MIN) MIN = $5; print $1, " - " MIN;}' script2.txt


#Name,Team,First Test, Second Test, Third Test
#Tom,Red,5,17,22
#Joe,Green,3,14,22
#Maria,Blue,6,18,21
#Fred,Blue,2,15,23
#Carlos,Red,-1,15,24
#Phuong,Green,7,19,21
#Enrique,Green,3,16,20
#Nancy,Red,9,12,24

#awk -F, 'BEGIN{
# AVGT1 = 0;
# AVGT2 = 0;
# AVGT2 = 0;
# AVGRED = 0;
# AVGGREEN = 0;
# AVGBLUE = 0;
# printf("\n\n");
# printf("NAME           |        AVERAGE  \n");
# printf("----------------------------------\n");
#}{
# AVGT1 = AVGT1 + $3;
# AVGT2 = AVGT2 + $4;
# AVGT3 = AVGT3 + $5;
#
# AVG = ($3 + $4 + $5) / 3;
# printf("%s %s         %-10llf \n", $1,  $2,  AVG);
# }
#END{
# printf("----------------------------------\n");
# printf("Average test 1 %llf\n", AVGT1);
# printf("Average test 2 %llf\n", AVGT2);
# printf("Average test 2 %llf\n", AVGT3);
#}' script2v2.txt
#


#awk -F: 'BEGIN{print "##   NAME     |     COUNT   ##\n";
#N = 0;
#}{
#  ok = 0;
#  for(i=1; i<=N; i++) {
#    if(index($2, A[i]) == 1) {
#       C[i] = C[i] + $3;
#       ok = 1;
#       break;
#    }
#  }
#
#  if(ok == 0) {
#      N = N + 1;
#      A[i] = $2;
#      C[i] = $3 + 0;
#  }
#}END{
#  for(i=1; i<=N; i++) 
#    for(j=i+1; j<=N; j++)
#       if(C[i] < C[j]) {
#       aux = C[i];
#       C[i] = C[j];
#       C[j] = aux;
#       
#       aux2 = A[i];
#       A[i] = A[j];
#       A[j] = aux2;
#      }
#  for(i=1; i<=N; i++) {
#      print A[i], " - ", C[i], "\n"
#  }
# print "N = ", N;
#}' script2v3.txt 
  
