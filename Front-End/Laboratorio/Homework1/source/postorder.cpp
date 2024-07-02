/*

2 PARTE PROGETTO

*/
#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <cstring>
using namespace std;

#define EPSILON '*'

int cont=0;   // contatore per gli stati
set<char> operators = {'*','|','.'}; // Il punto indica la concatenazione
char* simboloInput;    // IC
int* state1,*state2;     // STATE1,STATE2

class AST {
private:
  char symb;
  AST* left;
  AST* right;
  int start;
  int end;
public:
  AST(char symb, AST* left, AST* right): symb(symb), left(left), right(right) {};
  AST(char symb): symb(symb), left(nullptr), right(nullptr) {};
  string visit() {
    /*Algoritmo di visita dell'albero in post-ordine.
      Usando l'informazione ai nodi (un operatore o un carattere dell'alfabeto)
      la visita semplicemente risostruisce la rappresentazione esterna (come stringa)
      dell'albero che a sua volta rappresenta un'espressione regolare.
      Il metodo volutamente non è generico per evitare complicazioni con il C++.
      I tre casi (foglia, un solo figlio, due figli) vengono qui tenuti
      distinti "a scopo didattico" perché (in generale) le
      operazioni da fare possono essere completamente distinte.
     */
    string treerep = "";               // treerep conterrà la rappresentazione del
				       // sottoalbero radicato nel nodo corrente
    if (left != nullptr) {
      string ltree = left->visit();    // Visitiamo il sottoalbero di sx
      if (right != nullptr) {
	// Caso di nodo con due figli
	string rtree = right->visit(); // Visitiamo il sottoalbero di dx
  if(symb == '.')  {          // Calcoli dopo le due visite
     start = left->start;
     end = right->end;
     state1[left->end] = right->start;
     simboloInput[left->end] = EPSILON;
  }else{      // caso cui symb == '|'
     start=cont;
     simboloInput[cont] = EPSILON;
     state1[cont] = left->start;
     state2[cont] = right->start;
     end = ++cont;
     state1[left->end] = end;
     simboloInput[left->end] = EPSILON;
     state1[right->end] = end;
     simboloInput[right->end] = EPSILON;
     cont++;
  }
      } else {
	// Caso di nodo con un solo figlio (*)
	start = cont;
  state1[cont] = left->start;
  state2[cont] = cont+1;
  cont++;
  end = cont;
  state1[left->end] = end;
  state2[left->end] = left->start;
  simboloInput[left->end] = EPSILON;
  cont++;
  simboloInput[start] = EPSILON;
      }
    } else {
      start=cont;        // Calcolo nel caso di foglia
      state1[cont] = cont+1;
      cont++;
      end = cont++;
      simboloInput[start] = symb;
    }
    return treerep;
  }
};

int skipblank(string S, int j) {
  /* Restituisce il primo non blank a partire dalla
     posizione j (inclusa)
  */
  while (j<S.length() and S[j] == ' ') j++;
  return j;
}

string removeblank(string S) {
  /* Restituisce la stringa S "compattata", in cui cioè
     sono rimossi tutti i caratteri "blank"
  */
  int n = S.length();
  int j = skipblank(S,0);
  string compact = "";
  while (j<n) {
    compact.push_back(S.at(j));
    j = skipblank(S,++j);
  }
  return compact;
}

int getsubtree(string S, int j) {
  /* Restituisce la lunghezza della stringa che, a partire dalla
     posizione j, bilancia correttamente le parentesi
     Si aspetta S.at(j) == '('
  */
  int s = j;  // Ricorda la starting position
  j++;
  int numpar = 1;
  while (numpar>0) {
    if (S.at(j)=='(') numpar++;
    if (S.at(j)==')') numpar--;
    j++;
  }
  return j-s;
}

AST* create(string linearrep, set<char> alphabet, bool verbose) {
  /* Costruisce la rappresentazione interna dell'AST
     corrispondente alla rappresentazione lineare linearrep.
     Posto n=lunghezza di linearrep, i casi n=1 e n=3
     indicano che linearrep rappresenta un nodo foglia.
     La differenza è che, se n=1, l'intero albero di cui
     dobbiamo costruire la rappresentazione è formato da un
     solo nodo (radice e foglia simultaneamente).
     Il caso n=3 implica invece che siamo in un passaggio ricorsivo.
     Se n>3 allora linerrep descrive un (sotto) albero composto da
     una radice, con l'operatore, e da almeno un figlio. L'algoritmo
     ricerca nella stringa la rappresentazione del figlio/dei figli,
     ricorsivamente ne costruisce la/le rappresentazione/i, e la/le usa
     per costruire l'albero da restituire al chiamante.
   */
  int n = linearrep.length();
  if (n==1 or n==3) { // linearrep = 'c' oppure "(c)"
    char c = linearrep.at(max(0,n-2));  // Unifica i due casi recuperando la lettera
    if (alphabet.count(c) == 0) throw invalid_argument("Il simbolo "+string(1,c)+" non fa parte dell'alfabeto");
    return new AST(c);
  }
  char op = linearrep.at(1);
  if (operators.count(op) == 0) throw invalid_argument("Il simbolo "+string(1,op)+" non è un operatore legale");
  int start = 2;
  int stop = getsubtree(linearrep, start);
  string left = linearrep.substr(start,stop);
  start += stop;
  if (op=='*') {  // L'albero andrà costruito con un solo figlio
    if (verbose) cout << "op:" << op << "\tleft:" << left << endl;
    AST* lt = create(left,alphabet,verbose);
    return new AST(op,lt,nullptr);
  } else {       // Operatore binario -> due figli
    stop = getsubtree(linearrep, start);
    string right = linearrep.substr(start,stop);
    if (verbose) {
      cout << "op:" << op  << "\tleft:" << left;
      cout << "\tright:" << right << endl;
    }
    AST* lt = create(left,alphabet,verbose);
    AST* rt = create(right,alphabet,verbose);
    return new AST(op,lt,rt);
  }
}


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

/* Stampa l'automa nel formato valido per il subset_construction*/
void printAutoma(int dim , set<char> symbols){

  //stampa simboli
  for (const char& s : symbols) {
      cout<<s<<" ";
  }
  cout<<endl;

  //stampa n. stati finali
  cout<<dim<<endl; 

  //Stampa transizioni

  set<char>::iterator it;
  symbols.insert(EPSILON);
  int S = symbols.size();
  int indice;
  for(int i=0 ; i<(S*dim) ; i++){
      if(i%S == 0){
        it = symbols.begin();
      }
      indice = i/S;
      if(simboloInput[indice] == *it){
        if(state2[indice] != -1){
          cout<<state1[indice]<<" "<<state2[indice]<<endl;
        }else{
          cout<<state1[indice]<<endl;
        }
      }else{
        cout<<endl;
      }
      it++;    // Mi sposto al prossimo simbolo
    }

}

int main(int argc, char** argv) {
  int nStati = 0;
  bool verbose = false;
  string fn;
  if (argc==1) {
    cout << "Missing file name\n";
    return 1;
  } else if (strcmp(argv[1],"-v")==0) {
    verbose = true;
    fn = argv[2];
  } else {
    fn = argv[1];
  }
  set<char> symbols;           // Conterrà i simboli dell'alfabeto
  ifstream f(fn);              // Apriamo il file con alfabeto e con la rapp. esterna dell'albero
  string line;                 // La prima riga deve contenere l'alfabeto
  getline(f, line);
  
  stringstream alphabet(line); // Ci prepariamo per scan e tokenizzazionea
  char symb;
  while(alphabet>>symb) {      // Se il primo parametro è un oggetto di tipo
                               // stringstream, getline è di fatto uno scanner
        symbols.insert(symb);
  }

  getline(f, line);           // La seconda riga contiene la rappresentazione
                              // esterna dell'AST che, a sua volta, rappresenta
                              // l'espressione regolare.
                              // Per semplicità, non contempliamo l'uso di
                              // espressioni regolari che includono epsilom


  line = removeblank(line);
  
  //Calcolo numero di stati, in modo da allocare la struttura dati principale ( 3 array )
  for(int i=0 ; i<line.size() ; i++){
    symb = (char)line[i];
    if( symb != '(' && symb != ')' && symb != '.'){
      nStati++;
    }
  }
  nStati = nStati*2;
  //cout<<"[DEBUG : Num stati = "<<nStati<<" ]"<<endl;

  AST *root = create(line, symbols, verbose);

//Allocazione struttura dati automa
    int dimensioneAutoma = nStati;
    simboloInput = new char[dimensioneAutoma];   
    state1 = new int[dimensioneAutoma];  
    state2 = new int[dimensioneAutoma];  
    for(int i=0 ; i<dimensioneAutoma ; i++) {
        simboloInput[i] = '%';
        state1[i] = -1;
        state2[i] = -1;
    }

  root->visit();    // Esegue l'algoritmo di post_order nell'albero
  
  
  printAutoma(nStati , symbols);
  //printAutoma_debug(nStati);

                              
}
