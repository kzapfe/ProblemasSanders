#!/bin/bash
#Script para estandarizar los plots del paper a un solo estilo
#Quien sabe que sea mas divertido: aceptar argumentos o pegar a lo guey...
#Puede ser que mejor modificar a lo guey

NameData=$1
Name=`basename $NameData .dat`
NameTex=$Name"-ForPaper.tex"

gnuplot<<EOF
a(x)=0.5-x
b(x)=0.5-x
factor = 3.33216220361877
VolCubo(x)=16.*(a(x)*b(x))**2
VolFree(x)=16.*(a(x)*b(x))**2-4.*pi*(a(x)*b(x)*(2.*x)**2)+8./3.*(a(x)+b(x))*(2.*x)**3-8.*x**4
AreaHop(x)=2.*sqrt(2)*a(x)*(2.*b(x)-2.*x)**2
Acol(x)=16.*sqrt(2)*pi*a(x)*b(x)*x-32.*sqrt(2)*(a(x)+b(x))*x*x+16.*sqrt(2)*x*x*x
AreaPared(x)=32*a(x)*b(x)*(a(x)+b(x))-16.*pi*x*x*(a(x)+b(x))+128/3.*(x*x*x)
set key above
set xl "Radius"
set yl "Time"
set pointsize 0.75
set term cairolatex size 22cm,14cm lw 3 standalone pdf
set out "$NameTex"
set multiplot
plot "$NameData" ls 7 lc rgb "red" t "Numerics", VolFree(x)/AreaHop(x)*sqrt(2) ls 1 lw 2 lc rgb "blue" t "Analytical"
set size 0.45
unset xl
unset yl 
set origin 0.05, 0.45
set log y
unset key
replot
#plot "$NameData" ls 7 lc rgb "red" t "Numerics", VolFree(x)/Acol(x)*factor ls 1 lw 2 lc rgb "blue" t "Analytical"
unset multiplot
set out
EOF

pdflatex $NameTex


