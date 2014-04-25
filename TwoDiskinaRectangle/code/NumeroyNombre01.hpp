/* Rutina auxiliar para hacer nombres de archivos que empiecen con un numero */

using namespace std;


string Num_nombre(int num, string nombregeneral){

  std::ostringstream escupe;
  escupe<<num<<"_"<<nombregeneral<<std::ends;    
     
  std::string escupestring;
  escupestring=escupefirst.str();
  
  return escupestring;

};

