#!/bin/sh

###### COMANDA Y ########

#Inlocuim 1 cu a, 2 cu b, 3 cu c
#sed "y#123#abc#" lab3.txt

#Inlocuim a cu 1, b cu 1, c cu 1
#sed "y#abc#111#" lab3.txt

#Stergem toate liniile care contin cuvantul 'sterge
#sed "/sterge/d" lab3.txt

#Printeaza prima coloana
#awk '{ print $1 }' lab3.txt

#Printeaza ultima coloana
#awk '{ print $NF }' lab3.txt

#Numeroteaza liniile
#awk '{ print NR " " FNR " "$0 }' lab3.txt lab3.txt

#BLOCURI SPECIALE - BEGIN SI END . SE EXECUTA LA INCEPUT SI SFARSIT
#awk 'BEGIN{ print "INCEPUT NO" }{ print "Linie: "$0 }END{ print "Sfarsit"}' lab3.txt

#Numaram linii
#awk 'BEGIN{ n = 0 }{ n++ }END{ print "n: " n }' lab3.txt

#Numaram studentii care au numele Mircea
#grep -c "\<Sorin\>" /etc/passwd

#Studentii ale caror nume sa inceapa cu Pop
#awk -F: '{ if(index($5, "Pop ") == 1)  print $5}' /etc/passwd 

#Studentii care au unul dintre prenume Rares
#awk -F: 'BEGIN{ n = 0 }{ split($5, a, " "); for(i=2; i<=length(a); i++) if(index(a[i], "Rares") == 1) { n++; print $0 }}END{ printf "n: " n}' /etc/passwd

#Inversam primul cu ultimul cuvant
#awk -F: '{printf("%s ", $NF); for(i=2; i<NF; i++) printf("%s ", $i); printf("%s\n", $1);}' /etc/passwd 

#Sa numaram pentru fiecare prenume, cati studenti au prenumele respectiv
awk -F: '{
	split($5, a, " ");
	
        if(m[a[1]] == 0) {
		 m[a[1]] = 0;
		 nume[n] = a[1];
		 print nume[n] " "n;
		 n++ 
	}
	 m[a[1]]++
}END{
	 for(i=0; i<n; i++) 
		printf("%s apare: %d ori\n", nume[i], m[nume[i]]) }'  /etc/passwd | sort -k3n | tail
