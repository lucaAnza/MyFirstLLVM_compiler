#include<iostream>
#include<fstream>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <utility>

#define EPSILON '*'
#define NOT_MARK '%'

using namespace std;

char* simboloInput;   // IC
int* state1,*state2;   // STATE1,STATE2
set<char> simboli;       // Alfabeto


/* Stampa l'automa in modo tale da vedere in modo chiaro il suo contenuto */
void printAutoma_debug(int dim){
    cout<<"Automa : "<<endl;

    // STATI
    cout<<" | ";
    for(int i=0 ; i<dim ; i++){
        if( (state1[i-1] > 10 || state2[i-1] >10 ) && i<10) 
          cout<<" ";
        cout<<i<<"  ";
    }
    cout<<"\n";

    //Separatore
    for(int i=0 ; i<dim ; i++){cout<<"----";}
    // Simboli Input
    cout<<endl<<"IC ";
    for (int i=0 ; i<dim ; i++){
      if(state1[i-1] >= 10 || state2[i-1] >= 10)
          cout<<" ";
      cout<<simboloInput[i]<<"  ";
    }
    cout<<endl;
    for(int i=0 ; i<dim ; i++){cout<<"----";}
    // Stato1
    cout<<endl<<"S1 ";
    for (int i=0 ; i<dim ; i++){
        if(state2[i-1] >= 10)
          cout<<" ";
        if(state1[i] != -1)
          cout<<state1[i]<<"  ";
        else
          cout<<"X"<<"  ";
    }
    cout<<endl;
    for(int i=0 ; i<dim ; i++){cout<<"----";}
     // Stato2
    cout<<endl<<"S2 ";
    for (int i=0 ; i<dim ; i++){
        if(state1[i-1] >= 10)
          cout<<" ";
        if(state2[i] != -1)
          cout<<state2[i]<<"  ";
        else
          cout<<"X"<<"  ";
    }
    cout<<endl;
}

//Stampa di un set di interi
void printSet(set<int> inputSet){
    cout<<"Set : "<<endl;
    for ( const int& i : inputSet){
        cout<<i<<" ";
    }
}


/* Funzione che legge da file l'automa indeterminato e riempie la struttura dati principale*/
bool inputFile(string nomeFile, int &k){

    string line;
    int S;
    int temp;

    ifstream f(nomeFile);

    if(!f){
        cout<<"Errore nell'apertura del file!"<<endl;
        return false;
    }

    //Lettura alfabeto
    simboli.insert(EPSILON);   //Inserimento Epsilon
    getline(f,line);
    for(int i=0 ; i<line.length() ; i++){
        if(line[i] != ' '){
            simboli.insert(line[i]);
        }
    }
    S = simboli.size();

    //lettura n. di stati
    f>>k;
    getline(f,line);

    //Allocazione struttura dati automa
    int dimensioneAutoma = k;
    simboloInput = new char[dimensioneAutoma];   
    state1 = new int[dimensioneAutoma];  
    state2 = new int[dimensioneAutoma];  
    for(int i=0 ; i<dimensioneAutoma ; i++) {
        simboloInput[i] = '%';
        state1[i] = -1;
        state2[i] = -1;
    }

    set<char>::iterator it;
    for(int i=0 ; i<(simboli.size())*k ; i++){
        if(i%S == 0){
            it = simboli.begin();
        }
        getline(f,line);
        istringstream input_stream(line);   //così posso leggere la stringa come se fosse una flusso di input
        int j=0,indice;
        while ( input_stream >> temp){            
            indice = (int)i/S;
            simboloInput[indice] = *it;
            if(j++==0){
                state1[indice] = temp;
            }else{                       
                state2[indice] = temp;
            }
            
        }
        it++;    // Mi sposto al prossimo simbolo
    }

    //Chiusura file
    f.close();

    return true;

}

bool inputStream(int &k){
    string line;
    int S;
    int temp;;


    //Lettura alfabeto
    simboli.insert(EPSILON);   //Inserimento Epsilon
    getline(cin,line);
    for(int i=0 ; i<line.length() ; i++){
        if(line[i] != ' '){
            simboli.insert(line[i]);
        }
    }
    S = simboli.size();

    //lettura n. di stati
    cin>>k;
    getline(cin,line);

    //Allocazione struttura dati automa
    int dimensioneAutoma = k;
    simboloInput = new char[dimensioneAutoma];   
    state1 = new int[dimensioneAutoma];  
    state2 = new int[dimensioneAutoma];  
    for(int i=0 ; i<dimensioneAutoma ; i++) {
        simboloInput[i] = '%';
        state1[i] = -1;
        state2[i] = -1;
    }

    set<char>::iterator it;
    for(int i=0 ; i<(simboli.size())*k ; i++){
        if(i%S == 0){
            it = simboli.begin();
        }
        getline(cin,line);
        istringstream input_stream(line);   //così posso leggere la stringa come se fosse una flusso di input
        int j=0,indice;
        while ( input_stream >> temp){            
            indice = (int)i/S;
            simboloInput[indice] = *it;
            if(j++==0){
                state1[indice] = temp;
            }else{                       
                state2[indice] = temp;
            }
            
        }
        it++;    // Mi sposto al prossimo simbolo
    }

    return true;

}


void closure(set<int> &output_set , int start , int dim){

    if(start == dim || simboloInput[start] != EPSILON){   //caso base
        output_set.insert(start);
    }else if(simboloInput[start] == EPSILON){    // Caso Epsilon       // Potresti mettere && temp.count(start) != 0
        //set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), std::inserter(result, result.begin()));
        output_set.insert(start);
        if(state2[start] != -1){
            closure(output_set,state1[start] , dim);
            closure(output_set,state2[start] , dim);
        }else{
            closure(output_set,state1[start] , dim);
        } 
    }


}


/* Funzione che restituisce il carattere corrispondente al set ( A,B,C,...) altrimenti se non lo trova la costante NOT_MARK*/
char findSet( map<char, set<int> > mappa , set<int> set){
    
    for (const auto& coppia : mappa) {
        if(coppia.second == set){
            return coppia.first;
        }
    }

    return NOT_MARK;
}

/* Funzione che costruisce l'automa determinato*/
void subsetConstructionSolver (const int k , bool debug) {
    
    map<char, set<int> > mappa;    // Esempio  A = { 0,1,8 }
    map< pair<char, char> , char > transizioni;  // Esempio  ẟ(0,a) = 1
    set<int> T,T_Primo,Q;
    char it_char = 'A';
    char starting_it_char ='A';
    int statiFinali;


    closure(Q , 0 , k);
    mappa[it_char++] = Q;        // A = { 0 , 1 , 8}
    while ( starting_it_char <= it_char ){
        
        for (const char& s : simboli) {   // Per ogni simbolo ( a,b,....) 
            //cout<<"\n[DEBUG : Analising with letter : "<<s<<" ]"<<endl;
            
            T.clear();
            if(s != EPSILON){   // EPSILON NO!
                for (const int& stato : Q) {        // Aggiungi a T ogni stato raggiungibile da Q con s
                    if(simboloInput[stato] == s){    // Per vedere che stiamo vedendo il carattere prossimo giusto
                        //cout<<"    [DEBUG : Link found from "<<stato<<" with letter : "<<s<<" ]"<<endl;
                        if(stato != k){
                            if(state2[stato] != -1){
                                T.insert(state2[stato]);
                            }
                            T.insert(state1[stato]);
                        }
                    }
                }
                if(T.size() != 0) {        // Per controllare che dagli stati di N esce almeno un transizione etichettata 's'
                    //cout<<"     [DEBUG : Join in final steps with T.size() = "<<T.size()<<" ]"<<endl;
                    // T' = T(Closure)
                    T_Primo.clear();  //svuota SET
                    for (const int& stato : T) {      // Per ogni T fai la closure
                        //cout<<"Closure("<<stato<<")"<<endl;
                        closure(T_Primo,stato,k);       
                    }
                    char res = (char) findSet(mappa,T_Primo);   // La funzione restituisce la lettere se uno stato è marcato altrimenti %
                    if( res == NOT_MARK){   // Se è uno stato non marcato
                        //printSet(T_Primo);
                        // ẟ(0,a) = 1
                        transizioni[make_pair(starting_it_char,s )] = it_char;  
                        // A = { 1, ...}
                        mappa[it_char] = T_Primo;
                        it_char++;
                    }else{
                        transizioni[make_pair(starting_it_char,s )] = res;
                    }
                }
            }
        }
        starting_it_char++;
        //cout<<"starting("<<starting_it_char<<") vs char("<<it_char<<")"<<endl;
        if(starting_it_char < it_char)
            Q = mappa[starting_it_char];   
    }

    
    if(debug){
        //Stampa automa
        printAutoma_debug(k);
        cout<<"\n\n\n";
        //Stampa debugging mode
        cout<<"Stampa nuovi stati : "<<endl;
        for (const auto& coppia : mappa) {
            cout<<coppia.first<<" : ";
            for ( const int& i : coppia.second){
                cout<<i<<" ";
            }
            cout<<endl;
        }
        cout<<"\nStampa delle transizioni : "<<endl;
        for (const auto& coppia : transizioni) {
            cout<<"ẟ("<<coppia.first.first<<","<<coppia.first.second<<") = "<<coppia.second<<endl;
        }
    }else{
        //Contenuto stati finali ( Example : A = { 0,1,3}  B = { 3 ,5 ,6} ... )
        for (const auto& coppia : mappa) {
            for ( const int& i : coppia.second){
                cout<<i<<" ";
            }
            cout<<endl;
        }
        statiFinali = mappa.size();
        //Indicizazione stati finali  ( Example : 0 1 2 3  [Stati finali = 4] )
        for(int i=0 ; i<statiFinali ; i++){
            cout<<i<<" ";
        }
        cout<<endl;
        //Stampa delle transizioni
        set<char>::iterator it;
        pair<char,char> tempPair;
        int indice;
        int S = simboli.size();   // Cardinalità alfabeto
        std::map< pair<char, char> , char >::iterator it_map = transizioni.begin();
        //L'idea di questo algoritmo è di generare le coppie (A,a),(A,b)...(A,z) fintantochè non si trova un match con la mappa finale. 
        //In tal caso stampare la transizione e andare all'elemento successivo della mappa.
        for(int i=0 ; i<(S*statiFinali) ; i++){
            it_char = 'A';
            if(i%S == 0){
                it = simboli.begin();
            }
            indice = i/S;
            it_char = it_char + indice;
            tempPair.first = it_char;
            tempPair.second = *it;
            //cout<<"confronto tra ("<<tempPair.first<<","<<tempPair.second<<") e ("<<it_map->first.first<<","<<it_map->first.second<<")"<<endl;
            if( it_map->first == tempPair){
                int n = (int) it_map->second % 65;
                cout<<n<<endl;
                it_map++;
            }else{
                cout<<endl;
            }
            it++;
        }
    }
        
        
    

    
    

}



int main(int argc, char** argv) {
    
    //variabili principali
    int k;
    string fn;
    
    if (argc==1) {
        inputStream(k);
    } else {
        fn = argv[1];
    }

    //lettura da file
    if ( argc !=1 && !inputFile(fn, k) ){
        cout<<"Errore nella lettura del file.\nPossibile causa : aggiunta di spazi involontari\n";
        return -1;
    }
    
    subsetConstructionSolver(k,false);   // k -> numero di stati  false -> disattivata la modalità stampa debug
    return 0;
}

