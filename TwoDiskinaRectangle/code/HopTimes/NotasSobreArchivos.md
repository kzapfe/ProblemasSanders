Tenemos los siguientes archivos de datos:

 * HopTimePromediosStrongerNumerics.dat:  
Este tiene numerica fuerte, pero antes de corregir el detallito del HopTime Exacto
 
 *HoptTimesTestLigera.dat:  
Este tiene YA la correccion de los hoptimes, pero no muchos datos y se pasa del rango

 *HopTimeNew.dat:  
 Este ya tiene  la correccion del hoptimes exacto (ver la rutina extra para 
 el tiempo de brinco, la que dice dinamicayhopp) Mas numerica y mejor rango... 
 se ve igual que el anterior

Al parecer el código CTParalel01.x calcula un tiempo de retorno, es decir,
repite varias veces la corrida usando el mismo sistema dinamico,
reseteando tiempos y todo. Fijate que eses archivos (es decir, 
HopTimePromediosStrongernumeris.dat y los que dicen `*Codigo01`) dan
el limete EXACTO para r->0, mientras que los otros tienen un comportamiento "rarito"
por encima de eso, es decir, que esta su limite una o dos unidades por encima.
 
Hasta ahora el mejor es HopTimeErgo05.dat, donde corregiste el error
idiota del doble producto punto.
