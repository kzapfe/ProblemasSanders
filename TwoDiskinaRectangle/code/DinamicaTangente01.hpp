//Todas las rutinas de la dinamica Tangente
//requiere armadillo

//Bueno, al parecer todos tus objetos chistosos los pasas
// por sepa el diablo referencia?

void MapeoDifLibre(vec &TanQ, vec &TanP, 
		   Disco &Disk,  double tiempolibre){
  //El vuelo libre induce una separacion algebraica en el espacio tangente
  TanQ+=TanP/Disk.masa*tiempolibre;
  return;
  
}; 


void MapeoDifParedVertical(vec &TanQ, vec &TanP){
  vec norm(2);
  norm[0]=1;
  norm[1]=0;
  
  //sin kurvatura, los dos son iguales.
  TanQ=TanQ-2*(dot(TanQ, norm))*norm;
  TanP=TanP-2*(dot(TanP, norm))*norm;
  return;

};



void MapeoDifParedHorizontal(vec &TanQ, vec &TanP){
  vec norm(2);
  norm[0]=0;
  norm[1]=1;
  
  //sin kurvatura, los dos son iguales.
  TanQ=TanQ-2*(dot(TanQ, norm))*norm;
  TanP=TanP-2*(dot(TanP, norm))*norm;
  return;
  

};



void MapeoDifChoque(vec &TanQ1, vec &TanP1, 
			    vec &TanQ2, vec &TanP2, 
		    Disco &Disk1, Disco &Disk2, vec &MomAux){
  
  vec deltaTanQ(2), deltaTanP(2);
  vec deltaQ(2), deltaP(2);
  vec ortopantes(2), ortopdespues(2);
  double sigma, normaP;
  vec AuxQ(2), AuxP(2);

  
  deltaQ[0]=Disk2.qx-Disk1.qx;
  deltaQ[1]=Disk2.qy-Disk1.qy;

  deltaP[0]=Disk2.px-Disk1.px;
  deltaP[1]=Disk2.py-Disk1.py;
  
  deltaTanQ=TanQ2-TanQ1;
  deltaTanP=TanP2-TanP1;

  sigma=Disk2.radio+Disk1.radio;

  AuxQ=deltaQ*dot(deltaTanQ, deltaQ)/(sigma*sigma); 
  
  ortopantes[0]=MomAux[1];
  ortopantes[1]=-MomAux[0];
  
 
  ortopantes/=norm(ortopantes,2);
    
  ortopdespues[0]=deltaP[1];
  ortopdespues[1]=-deltaP[0];
  
  ortopdespues/=norm(ortopdespues,2);
  
  normaP=norm(deltaP,2);

  cout<<"Vaya vaya  P "<< deltaP<<endl;
  cout<<"Vaya vaya norma p "<< normaP<<endl;

  AuxP=deltaQ*dot(deltaTanP, deltaQ)/(sigma*sigma)
    +ortopdespues*normaP*normaP*dot(deltaTanQ, ortopantes);
    //  /dot(deltaQ, deltaP);
  


  TanQ1+=AuxQ;
  TanQ2-=AuxQ;

  TanP1+=AuxP;
  TanP2-=AuxP;
  

};


