#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "math.h"

#define DIMBUFFER 10000
#define DIMHASH 200033

//DICHIARAZIONE STRUTTURE DATI --------------------------------------------------------------------------------------------------------------------------------------

//nodi albero entità
typedef struct nodoEntita{
	struct nodoEntita *Ep;                      //RB
	struct nodoEntita *Esx;
	struct nodoEntita *Edx;
	char Ecolore;
	
    char *nome;                                 //info entità stessa
}nodoEntita;

//nodi albero output
typedef struct nodoOutput{
    struct nodoOutput *Op;                      //RB
    struct nodoOutput *Osx;
    struct nodoOutput *Odx;
    char Ocolore;

    char *output_name;                          //info nome output 
}nodoOutput;

//nodi albero mittenti
typedef struct nodoMittente{
	struct nodoMittente *Mp;                        //RB
	struct nodoMittente *Msx;
	struct nodoMittente *Mdx;
	char Mcolore;
	
    char *mitt;                        //info mittente stesso
}nodoMittente;

//nodi albero destinatari
typedef struct nodoDestinatario{
	struct nodoDestinatario *Dp;                    //RB
	struct nodoDestinatario *Dsx;
	struct nodoDestinatario *Ddx;
	char Dcolore;
	
    char *dest;                                     //info destinatario stesso
	unsigned int followers;
    
    struct nodoMittente *radiceMittenti;            //info mittenti del destinatario (albero sottostante)
}nodoDestinatario;

//nodi albero relazioni
typedef struct nodoRelazione{
	struct nodoRelazione *Rp;                       //RB  
	struct nodoRelazione *Rsx;
	struct nodoRelazione *Rdx;
	char Rcolore;
    
    char *rel;                                      //info relazione stessa
	unsigned int max;
    
    struct nodoDestinatario *radiceDestinatari;     //info destinatari della relazione (albero sottostante)
    struct nodoOutput *radiceOutput;                //info output
}nodoRelazione;

//DICHIARAZIONE FUNZIONI --------------------------------------------------------------------------------------------------------------------------------------------

//funzione di hash
unsigned int hash_function(char *nome); 

//gestione RB-tree entità
nodoEntita *crea_nodoE(char *nomeEntita);
nodoEntita *searchE(nodoEntita **root, char *nomeEntita);
void insertE(nodoEntita **root, nodoEntita *nodo);
void insertfixupE(nodoEntita **root, nodoEntita *nodo);
void leftrotateE(nodoEntita **root, nodoEntita *nodo);
void rightrotateE(nodoEntita **root, nodoEntita *nodo);
nodoEntita *deleteE(nodoEntita **root, nodoEntita *nodo);
void deletefixupE(nodoEntita **root, nodoEntita *nodo);
nodoEntita *treesuccessorE(nodoEntita *nodo);
nodoEntita *treeminimumE(nodoEntita *nodo);

//gestione RB-tree relazioni--------------------------
nodoRelazione *crea_nodoR(char *nomeRelazione);
nodoRelazione *searchR(nodoRelazione **root, char *nomeRelazione);
void insertR(nodoRelazione **root, nodoRelazione *nodo);
void insertfixupR(nodoRelazione **root, nodoRelazione *nodo);
void leftrotateR(nodoRelazione **root, nodoRelazione *nodo);
void rightrotateR(nodoRelazione **root, nodoRelazione *nodo);

//gestione RB-tree destinatari--------------------------
nodoDestinatario *crea_nodoD(char *infoEntitaD);
nodoDestinatario *searchD(nodoDestinatario **root, char *infoEntitaD);
void insertD(nodoDestinatario **root, nodoDestinatario *nodo);
void insertfixupD(nodoDestinatario **root, nodoDestinatario *nodo);
void leftrotateD(nodoDestinatario **root, nodoDestinatario *nodo);
void rightrotateD(nodoDestinatario **root, nodoDestinatario *nodo);
nodoDestinatario *deleteD(nodoDestinatario **root, nodoDestinatario *nodo);
void deletefixupD(nodoDestinatario **root, nodoDestinatario *nodo);
nodoDestinatario *treesuccessorD(nodoDestinatario *nodo);
nodoDestinatario *treeminimumD(nodoDestinatario *nodo);

//gestione RB-tree mittenti-----------------------------
nodoMittente *crea_nodoM(char *infoEntitaM);
nodoMittente *searchM(nodoMittente **root, char *infoEntitaM);
void insertM(nodoMittente **root, nodoMittente *nodo);
void insertfixupM(nodoMittente **root, nodoMittente *nodo);
void leftrotateM(nodoMittente **root, nodoMittente *nodo);
void rightrotateM(nodoMittente **root, nodoMittente *nodo);
nodoMittente*deleteM(nodoMittente **root, nodoMittente *nodo);
void deletefixupM(nodoMittente **root, nodoMittente *nodo);
nodoMittente *treesuccessorM(nodoMittente *nodo);
nodoMittente *treeminimumM(nodoMittente *nodo);

//gestione RB-tree output-------------------------------
nodoOutput *crea_nodoO(char *nome_output);
nodoOutput *searchO(nodoOutput **root, char *nome_output);
void insertO(nodoOutput **root, nodoOutput *nodo);
void insertfixupO(nodoOutput **root, nodoOutput *nodo);
void leftrotateO(nodoOutput **root, nodoOutput *nodo);
void rightrotateO(nodoOutput **root, nodoOutput *nodo);
nodoOutput *deleteO(nodoOutput **root, nodoOutput *nodo);
void deletefixupO(nodoOutput **root, nodoOutput *nodo);
nodoOutput *treesuccessorO(nodoOutput *nodo);
nodoOutput *treeminimumO(nodoOutput *nodo);

//comandi------------------------------------------------
nodoEntita *addent(nodoEntita *radiceEntita, char *ID);

nodoRelazione *addrel(nodoRelazione *radiceRelazioni, char *IDrelazione, char *info_dest, char *info_mitt);

nodoRelazione *delrel(nodoRelazione *radiceRelazioni, char *IDrelazione, char *IDdest, char *IDmitt);

void delent_walkR(nodoRelazione *root, char *IDentita);
void delent_walkD(nodoDestinatario *root, char *IDentita, nodoDestinatario *punt_dest_elim, nodoRelazione *relazione);
void free_treeM(nodoMittente *root);

void report_walkR(nodoRelazione *root, int *none_rel);
void report_walkO(nodoOutput *root);

void reset_max(nodoDestinatario *root, unsigned int *new_max);
void reset_output_tree(nodoDestinatario *root_destinatario, unsigned int max, nodoOutput **root_output);
void free_treeO(nodoOutput *root);

//VARIABILI GLOBALI--------------------------------------------------------------------------------------------------------------------------------------------------

//creazione dei nodi nilX

struct nodoEntita TnilE;
nodoEntita *nilE=&TnilE;

struct nodoRelazione TnilR;
nodoRelazione *nilR=&TnilR;

struct nodoDestinatario TnilD;
nodoDestinatario *nilD=&TnilD;

struct nodoMittente TnilM;
nodoMittente *nilM=&TnilM;

struct nodoOutput TnilO;
nodoOutput *nilO=&TnilO;

// MAIN -------------------------------------------------------------------------------------------------------------------------------------------------------------

int main(){

    //inizializzazione nodi nilE
    nilE->Ep=nilE;
    nilE->Esx=nilE;
    nilE->Edx=nilE;
    nilE->Ecolore='b';
    nilE->nome=NULL;

    //inizializzazione nodi nilR
    nilR->Rp=nilR;
    nilR->Rsx=nilR;
    nilR->Rdx=nilR;
    nilR->Rcolore='b';
    nilR->rel=NULL;
    nilR->max=0;
    nilR->radiceDestinatari=NULL;

    //inizializzazione nodi nilD
    nilD->Dp=nilD;
    nilD->Dsx=nilD;
    nilD->Ddx=nilD;
    nilD->Dcolore='b';
    nilD->dest=NULL;
    nilD->followers=0;
    nilD->radiceMittenti=NULL;

    //inizializzazione nodi nilM
    nilM->Mp=nilM;
    nilM->Msx=nilM;
    nilM->Mdx=nilM;
    nilM->Mcolore='b';
    nilM->mitt=NULL;

    //inizializzazione nodi nilO
    nilO->Op=nilO;
    nilO->Osx=nilO;
    nilO->Odx=nilO;
    nilO->Ocolore='b';
    nilO->output_name=NULL;               

    //stutture lettura input
    char buffer[DIMBUFFER];                     //buffer per lettura dell'input
    char comando[7];                            //in comando allocherò la stringa con l'istruzione
    unsigned int virgolette[6],i,pos;           //dati di supporto alla lettura
    
    char *ID=NULL;                              //nome entità (se ce n'è solo una)
    char *IDdest=NULL;                          //nome destinatario
    char *IDmitt=NULL;                          //nome mittente
    char *IDrelazione=NULL;                     //nome relazione
    
    //creazione hash table di alberi entità e inizializzazione a nilE
    nodoEntita *hash_table[DIMHASH];                                   
    unsigned int hash_value;
    unsigned int hash_mitt,hash_dest;

    for(i=0;i<DIMHASH;i++){
        hash_table[i]=nilE;                         
    }

    //creazione albero base (delle relazioni), con inizializzazione a NIL
    nodoRelazione *radiceRelazioni=nilR;

    //altre variabili da usare
    nodoEntita *addrel_mitt=NULL;               //trovare mittente da cui passare il nome 
    nodoEntita *addrel_dest=NULL;               //trovare destinatario da cui passare il nome
    
    nodoEntita *delent_elim=NULL;               //puntatore entità da eliminare
    nodoEntita *delent_remove=NULL;             //puntatore tornato dalla delete ed effettivamente da cancellare

    char none[]="none\n";                       //velocizzare usando fputs invece che printf nella report
    int none_flag=0;                            //finchè è 0 non ho aggiunto relazioni e stampo none direttamente
    int none_rel=0;                             //0 se devo scrivere none ma ho dovuto cercare nell'albero delle relazioni
  
    while(1){

        /*Leggo la stringa in input e la salvo in un vettore buffer. Calcolo la lunghezza delle varie  parti dell'input 
        basandomi sulle occorrenze di " e uso le posizioni delle " per stabilire le porzioni di informazioni rilevanti*/

        fgets(buffer,DIMBUFFER,stdin);                                                    

        if(strcmp(buffer,"report\n")==0){                                           //caso banale, comando è report
            strcpy(comando,"report");
        }else if(strcmp(buffer,"end\n")==0 || strcmp(buffer,"end")==0){             //caso banale, comando è end
            strcpy(comando,"end");                            
        }else{
            
            pos=0;                                                          //inizializzo a 0 il valore posizione
            for(i=0;i<6;i++){                                               //inizializzo il vettore delle virgolette
                virgolette[i]=0;
            }
            
            for(i=0;buffer[i]!='\0';i++){                                   //riempio vettore con le posizioni delle " leggendo tutto il buffer
                if(buffer[i]=='\"'){
                    virgolette[pos]=i;
                    pos++;
                }
            }

            strncpy(comando,buffer,6);                                     //se non sono in una caso banale le prime 6 lettere danno il comando da eseguire
            comando[6]='\0';
        }     
        
        /*Opero in base al comando letto da input */

        if(strcmp(comando,"addent")==0){
            
            ID=malloc((virgolette[1]-virgolette[0])*sizeof(char));
            strncpy(ID, buffer+(virgolette[0]+1), (virgolette[1]-virgolette[0]-1));
            ID[virgolette[1]-virgolette[0]-1]='\0';              

            //INSERIMENTO ID
            hash_value=hash_function(ID);                                           //calcolo l'hash del nome per individuare l'albero delle entità corretto            
            hash_table[hash_value]=addent(hash_table[hash_value],ID);               //e inserisco l'entità                           

            free(ID);
            ID=NULL;
        }

        else if(strcmp(comando,"delent")==0){
            
            ID=malloc((virgolette[1]-virgolette[0])*sizeof(char));
            strncpy(ID, buffer+(virgolette[0]+1), (virgolette[1]-virgolette[0]-1));
            ID[virgolette[1]-virgolette[0]-1]='\0';
            
            //RIMOZIONE ID

            hash_value=hash_function(ID);                                   //dato il nome dell'entita cerco se esiste nell'albero indicato
            delent_elim=searchE(&hash_table[hash_value],ID);                //dalla funzione di hash

            if(delent_elim!=nilE){                                              //se il nodo è nell'albero procedo a eliminarlo
                
                delent_walkR(radiceRelazioni,ID);                               //eliminazione dell'entità dall'albero delle relazioni,destinatari e mittenti                  
                
                delent_remove=deleteE(&hash_table[hash_value],delent_elim);     //chiamo delete che mi ritorna il puntatore al nodo da eliminare
                free(delent_remove);
                delent_remove=NULL;                                                                
            }

            delent_elim=NULL;

            free(ID);
            ID=NULL;
        }

        else if(strcmp(comando,"addrel")==0){

            IDmitt=malloc((virgolette[1]-virgolette[0])*sizeof(char));
            strncpy(IDmitt, buffer+virgolette[0]+1, virgolette[1]-virgolette[0]-1);
            IDmitt[virgolette[1]-virgolette[0]-1]='\0';          

            IDdest=malloc((virgolette[3]-virgolette[2])*sizeof(char));
            strncpy(IDdest, buffer+virgolette[2]+1, virgolette[3]-virgolette[2]-1);
            IDdest[virgolette[3]-virgolette[2]-1]='\0';

            IDrelazione=malloc((virgolette[5]-virgolette[4])*sizeof(char));
            strncpy(IDrelazione, buffer+virgolette[4]+1, virgolette[5]-virgolette[4]-1);
            IDrelazione[virgolette[5]-virgolette[4]-1]='\0';
        
            //INSERIMENTO RELAZIONE

            hash_mitt=hash_function(IDmitt);                                            //per mittente e destinatario calcolo la funzione di hash
            hash_dest=hash_function(IDdest);                                            //del nome per localizzare gli alberi delle entità  
                                                                                        
            addrel_mitt=searchE(&hash_table[hash_mitt],IDmitt);                         //una search per ognuno mi restituisce i puntatori ai      
            addrel_dest=searchE(&hash_table[hash_dest],IDdest);                         //rispettivi nodi entità

            if(addrel_mitt!=nilE && addrel_dest!=nilE){                                                     //procedo all'aggiunta solo se entrambe le entità
                radiceRelazioni=addrel(radiceRelazioni,IDrelazione,addrel_dest->nome,addrel_mitt->nome);    // esistono nell'albero delle entità e passo
            }                                                                                               //il riferimento ai nomi contenuti nei nodi entità

            none_flag=1;                            //ho almeno una relazione, sia che l'abbia aggiunta sia che ci sia già, non stampo none
            addrel_mitt=NULL;
            addrel_dest=NULL;

            free(IDmitt);
            IDmitt=NULL;
            free(IDdest);
            IDdest=NULL;
            free(IDrelazione);
            IDrelazione=NULL;
        }

        else if(strcmp(comando,"delrel")==0){
            
            IDmitt=malloc((virgolette[1]-virgolette[0])*sizeof(char));
            strncpy(IDmitt, buffer+virgolette[0]+1, virgolette[1]-virgolette[0]-1);
            IDmitt[virgolette[1]-virgolette[0]-1]='\0';
            
            IDdest=malloc((virgolette[3]-virgolette[2])*sizeof(char));
            strncpy(IDdest, buffer+virgolette[2]+1, virgolette[3]-virgolette[2]-1);
            IDdest[virgolette[3]-virgolette[2]-1]='\0';
            
            IDrelazione=malloc((virgolette[5]-virgolette[4])*sizeof(char));
            strncpy(IDrelazione, buffer+virgolette[4]+1, virgolette[5]-virgolette[4]-1);
            IDrelazione[virgolette[5]-virgolette[4]-1]='\0';

            //RIMOZIONE RELAZIONE
            
            radiceRelazioni=delrel(radiceRelazioni,IDrelazione,IDdest,IDmitt);

            free(IDmitt);
            IDmitt=NULL;
            free(IDdest);
            IDdest=NULL;
            free(IDrelazione);
            IDrelazione=NULL;
        }

        else if(strcmp(comando,"report")==0){
            
            if(none_flag==0){                               //è 0 finchè non ho aggiunto nessuna relazione o se dopo una serie di cancellazioni
               fputs(none,stdout);                          //la report dà none, in entrambi i casi finchè non aggiungo
            }else{                                          //almeno una relazione non ha senso richiamare ancora report_none, stampo none subito                
                report_walkR(radiceRelazioni,&none_rel);    
                if(none_rel==0){                            //none_rel==0 solo se tutte le relazioni hanno max=0 o è nil, quindi devo 
                    fputs(none,stdout);                     //stampare none, inoltre metto il none_flag a 0
                    none_flag=0;
                }else{
                    putchar('\n');
                }               
            }            
            none_rel=0;                 //lo preparo per il prossimo giro
        }

        else if(strcmp(comando,"end")==0){
 
            return 0;                                                          
        }

        else{
            //comando non valido, non faccio nulla
        }
        
    }
    
}

//CODICE DELLE FUNZIONI -------------------------------------------------------------------------------------------------------

//DJB2 hash function
unsigned int hash_function(char *nome){                //VERSIONE PROVVISORIA

    unsigned long int hashvalue=5381;
    int c;

    while ((c=*nome++)){
        hashvalue=((hashvalue<<5)+hashvalue)+c;     /* hash * 33 + c */
    }
        
    return (hashvalue%DIMHASH);    
}

/*gli algoritmi di gestione dei RB-tree sono implementati a partire dallo pseudocodice visto a lezione (slide/libro Cormen)
Lo pseudocodice è trasformato così:  T=root, T.root=*root, T.nil=nilX */

//gestione dell'albero delle entità
nodoEntita *crea_nodoE(char *nomeEntita){
    
    nodoEntita *nodo=malloc(sizeof(nodoEntita));
    nodo->Ep=NULL;
    nodo->Esx=NULL;
    nodo->Edx=NULL;
    nodo->Ecolore='r';
    nodo->nome=malloc((strlen(nomeEntita)+1)*sizeof(char));
        strcpy(nodo->nome,nomeEntita);

    return nodo;
}

nodoEntita *searchE(nodoEntita **root, char *nomeEntita){

    nodoEntita *x=*root;
    
    while(x!=nilE && strcmp(x->nome,nomeEntita)!=0){
        if(strcmp(x->nome,nomeEntita)>0){
            x=x->Esx;
        }else{
            x=x->Edx;
        }
    }
    return x;
}

void insertE(nodoEntita **root, nodoEntita *nodo){

    nodoEntita *x=*root;        
    nodoEntita *y=nilE;         
    
    while(x!=nilE){
        y=x;
        if(strcmp(nodo->nome,x->nome)<0){
            x=x->Esx;
        }else{
            x=x->Edx;
        }
    }
    
    nodo->Ep=y;
    if(y==nilE){                                        
        *root=nodo;
    }else if(strcmp(nodo->nome,y->nome)<0){             
        y->Esx=nodo;    
    }else{
        y->Edx=nodo;                                    
    }

    nodo->Esx=nilE;
    nodo->Edx=nilE;
    nodo->Ecolore='r';
    insertfixupE(root,nodo);
}

void insertfixupE(nodoEntita **root, nodoEntita *nodo){

    nodoEntita *y;

    while(nodo->Ep->Ecolore=='r'){
        
        if(nodo->Ep==nodo->Ep->Ep->Esx){
            y=nodo->Ep->Ep->Edx;

            if(y->Ecolore=='r'){
                nodo->Ep->Ecolore='b';
                y->Ecolore='b';
                nodo->Ep->Ep->Ecolore='r';
                nodo=nodo->Ep->Ep;
            }else{
                if(nodo==nodo->Ep->Edx){
                    nodo=nodo->Ep;
                    leftrotateE(root,nodo);
                }
                nodo->Ep->Ecolore='b';
                nodo->Ep->Ep->Ecolore='r';
                rightrotateE(root,nodo->Ep->Ep);
            }

        }else{
            y=nodo->Ep->Ep->Esx;

            if(y->Ecolore=='r'){
                nodo->Ep->Ecolore='b';
                y->Ecolore='b';
                nodo->Ep->Ep->Ecolore='r';
                nodo=nodo->Ep->Ep;
            }else{
                if(nodo==nodo->Ep->Esx){
                    nodo=nodo->Ep;
                    rightrotateE(root,nodo);
                }
                nodo->Ep->Ecolore='b';
                nodo->Ep->Ep->Ecolore='r';
                leftrotateE(root,nodo->Ep->Ep);
            }
        }
    }
    (*root)->Ecolore='b';
}

void leftrotateE(nodoEntita **root, nodoEntita *nodo){

    nodoEntita *y;

    y=nodo->Edx;
    nodo->Edx=y->Esx;
    if(y->Esx!=nilE){
        y->Esx->Ep=nodo;
    }
    y->Ep=nodo->Ep;
    if(nodo->Ep==nilE){
        *root=y;
    }else if(nodo==nodo->Ep->Esx){
        nodo->Ep->Esx=y;
    }else{
        nodo->Ep->Edx=y;
    }
    y->Esx=nodo;
    nodo->Ep=y;
}

void rightrotateE(nodoEntita **root, nodoEntita *nodo){
    
    nodoEntita *y;

    y=nodo->Esx;
    nodo->Esx=y->Edx;
    if(y->Edx!=nilE){
        y->Edx->Ep=nodo;
    }
    y->Ep=nodo->Ep;
    if(nodo->Ep==nilE){
        *root=y;
    }else if(nodo==nodo->Ep->Edx){
        nodo->Ep->Edx=y;
    }else{
        nodo->Ep->Esx=y;
    }
    y->Edx=nodo;
    nodo->Ep=y;
}

nodoEntita *deleteE(nodoEntita **root, nodoEntita *nodo){

    nodoEntita *x;
    nodoEntita *y;

    if(nodo->Esx==nilE || nodo->Edx==nilE){
        y=nodo;
    }else{
        y=treesuccessorE(nodo);
    }

    if(y->Esx!=nilE){
        x=y->Esx;
    }else{
        x=y->Edx;
    }

    x->Ep=y->Ep;

    if(y->Ep==nilE){
        *root=x;
    }else if(y==y->Ep->Esx){
        y->Ep->Esx=x;
    }else{
        y->Ep->Edx=x;
    }

    if(y!=nodo){
        free(nodo->nome);           //prima di sostituire il nome con quello del successore devo liberare 
        nodo->nome=NULL;            //dalla memoria il nome originale che non serve più
        nodo->nome=y->nome;
    }

    if(y->Ecolore=='b'){
        deletefixupE(root,x);
    }

    return y;
}

void deletefixupE(nodoEntita **root, nodoEntita *nodo){

    nodoEntita *y;

    while(nodo!=*root && nodo->Ecolore=='b'){
        
        if(nodo==nodo->Ep->Esx){
            y=nodo->Ep->Edx;

            if(y->Ecolore=='r'){
                y->Ecolore='b';
                nodo->Ep->Ecolore='r';
                leftrotateE(root,nodo->Ep);
                y=nodo->Ep->Edx;
            }

            if(y->Esx->Ecolore=='b' && y->Edx->Ecolore=='b'){
                y->Ecolore='r';
                nodo=nodo->Ep;
            }else{
                if(y->Edx->Ecolore=='b'){
                    y->Esx->Ecolore='b';
                    y->Ecolore='r';
                    rightrotateE(root,y);
                    y=nodo->Ep->Edx;
                }
                y->Ecolore=nodo->Ep->Ecolore;
                nodo->Ep->Ecolore='b';
                y->Edx->Ecolore='b';
                leftrotateE(root,nodo->Ep);
                nodo=(*root);
            }           
        }else{
            y=nodo->Ep->Esx;

            if(y->Ecolore=='r'){
                y->Ecolore='b';
                nodo->Ep->Ecolore='r';
                rightrotateE(root,nodo->Ep);
                y=nodo->Ep->Esx;
            }

            if(y->Edx->Ecolore=='b' && y->Esx->Ecolore=='b'){
                y->Ecolore='r';
                nodo=nodo->Ep;
            }else{
                if(y->Esx->Ecolore=='b'){
                    y->Edx->Ecolore='b';
                    y->Ecolore='r';
                    leftrotateE(root,y);
                    y=nodo->Ep->Esx;
                }
                y->Ecolore=nodo->Ep->Ecolore;
                nodo->Ep->Ecolore='b';
                y->Esx->Ecolore='b';
                rightrotateE(root,nodo->Ep);
                nodo=(*root);
            }           
        }
    }
    nodo->Ecolore='b';
}

nodoEntita *treesuccessorE(nodoEntita *nodo){
    
    nodoEntita *x=nodo;
    nodoEntita *y;

    if(x->Edx!=nilE){
        return treeminimumE(x->Edx);
    }
    y=x->Ep;
    while(y!=nilE && x==y->Edx){
        x=y;
        y=y->Ep;
    }
    return y;
}

nodoEntita *treeminimumE(nodoEntita *nodo){

    nodoEntita *x=nodo;
    while(x->Esx!=nilE){
        x=x->Esx;
    }
    return x;
}

//gestione RB-tree relazioni

nodoRelazione *crea_nodoR(char *nomeRelazione){

    nodoRelazione *nodo=malloc(sizeof(nodoRelazione));
    nodo->Rp=NULL;
    nodo->Rsx=NULL;
    nodo->Rdx=NULL;
    nodo->Rcolore='r';
    nodo->rel=malloc((strlen(nomeRelazione)+1)*sizeof(char));
        strcpy(nodo->rel,nomeRelazione);
    nodo->max=0;
    nodo->radiceDestinatari=nilD;
    nodo->radiceOutput=nilO;

    return nodo;
}

nodoRelazione *searchR(nodoRelazione **root, char *nomeRelazione){

    nodoRelazione *x=*root;
    
    while(x!=nilR && strcmp(x->rel,nomeRelazione)!=0){
        if(strcmp(x->rel,nomeRelazione)>0){
            x=x->Rsx;
        }else{
            x=x->Rdx;
        }
    }
    return x;
}

void insertR(nodoRelazione **root, nodoRelazione *nodo){

    nodoRelazione *x=*root;        
    nodoRelazione *y=nilR;         
    
    while(x!=nilR){
        y=x;
        if(strcmp(nodo->rel,x->rel)<0){
            x=x->Rsx;
        }else{
            x=x->Rdx;
        }
    }
    
    nodo->Rp=y;
    if(y==nilR){                                        
        *root=nodo;
    }else if(strcmp(nodo->rel,y->rel)<0){             
        y->Rsx=nodo;    
    }else{
        y->Rdx=nodo;                                    
    }

    nodo->Rsx=nilR;
    nodo->Rdx=nilR;
    nodo->Rcolore='r';
    insertfixupR(root,nodo);
}

void insertfixupR(nodoRelazione **root, nodoRelazione *nodo){

    nodoRelazione *y;

    while(nodo->Rp->Rcolore=='r'){
        
        if(nodo->Rp==nodo->Rp->Rp->Rsx){
            y=nodo->Rp->Rp->Rdx;

            if(y->Rcolore=='r'){
                nodo->Rp->Rcolore='b';
                y->Rcolore='b';
                nodo->Rp->Rp->Rcolore='r';
                nodo=nodo->Rp->Rp;
            }else{
                if(nodo==nodo->Rp->Rdx){
                    nodo=nodo->Rp;
                    leftrotateR(root,nodo);
                }
                nodo->Rp->Rcolore='b';
                nodo->Rp->Rp->Rcolore='r';
                rightrotateR(root,nodo->Rp->Rp);
            }

        }else{
            y=nodo->Rp->Rp->Rsx;

            if(y->Rcolore=='r'){
                nodo->Rp->Rcolore='b';
                y->Rcolore='b';
                nodo->Rp->Rp->Rcolore='r';
                nodo=nodo->Rp->Rp;
            }else{
                if(nodo==nodo->Rp->Rsx){
                    nodo=nodo->Rp;
                    rightrotateR(root,nodo);
                }
                nodo->Rp->Rcolore='b';
                nodo->Rp->Rp->Rcolore='r';
                leftrotateR(root,nodo->Rp->Rp);
            }
        }
    }
    (*root)->Rcolore='b';
}

void leftrotateR(nodoRelazione **root, nodoRelazione *nodo){

    nodoRelazione *y;

    y=nodo->Rdx;
    nodo->Rdx=y->Rsx;
    if(y->Rsx!=nilR){
        y->Rsx->Rp=nodo;
    }
    y->Rp=nodo->Rp;
    if(nodo->Rp==nilR){
        *root=y;
    }else if(nodo==nodo->Rp->Rsx){
        nodo->Rp->Rsx=y;
    }else{
        nodo->Rp->Rdx=y;
    }
    y->Rsx=nodo;
    nodo->Rp=y;
}

void rightrotateR(nodoRelazione **root, nodoRelazione *nodo){

    nodoRelazione *y;

    y=nodo->Rsx;
    nodo->Rsx=y->Rdx;
    if(y->Rdx!=nilR){
        y->Rdx->Rp=nodo;
    }
    y->Rp=nodo->Rp;
    if(nodo->Rp==nilR){
        *root=y;
    }else if(nodo==nodo->Rp->Rdx){
        nodo->Rp->Rdx=y;
    }else{
        nodo->Rp->Rsx=y;
    }
    y->Rdx=nodo;
    nodo->Rp=y;
}


//gestione RB-tree destinatari

nodoDestinatario *crea_nodoD(char *infoEntitaD){

    nodoDestinatario *nodo=malloc(sizeof(nodoDestinatario));
    nodo->Dp=NULL;
    nodo->Dsx=NULL;
    nodo->Ddx=NULL;
    nodo->Dcolore='r';
    nodo->dest=infoEntitaD;
    nodo->followers=0;
    nodo->radiceMittenti=nilM;

    return nodo;
}

nodoDestinatario *searchD(nodoDestinatario **root, char *infoEntitaD){

    nodoDestinatario *x=*root;
    
    while(x!=nilD && strcmp(x->dest,infoEntitaD)!=0){
        if(strcmp(x->dest,infoEntitaD)>0){
            x=x->Dsx;
        }else{
            x=x->Ddx;
        }
    }
    return x;
}

void insertD(nodoDestinatario **root, nodoDestinatario *nodo){

    nodoDestinatario *x=*root;        
    nodoDestinatario *y=nilD;         
    
    while(x!=nilD){
        y=x;
        if(strcmp(nodo->dest,x->dest)<0){
            x=x->Dsx;
        }else{
            x=x->Ddx;
        }
    }
    
    nodo->Dp=y;
    if(y==nilD){                                        
        *root=nodo;
    }else if(strcmp(nodo->dest,y->dest)<0){             
        y->Dsx=nodo;    
    }else{
        y->Ddx=nodo;                                    
    }

    nodo->Dsx=nilD;
    nodo->Ddx=nilD;
    nodo->Dcolore='r';
    insertfixupD(root,nodo);
}

void insertfixupD(nodoDestinatario **root, nodoDestinatario *nodo){

    nodoDestinatario *y;

    while(nodo->Dp->Dcolore=='r'){
        
        if(nodo->Dp==nodo->Dp->Dp->Dsx){
            y=nodo->Dp->Dp->Ddx;

            if(y->Dcolore=='r'){
                nodo->Dp->Dcolore='b';
                y->Dcolore='b';
                nodo->Dp->Dp->Dcolore='r';
                nodo=nodo->Dp->Dp;
            }else{
                if(nodo==nodo->Dp->Ddx){
                    nodo=nodo->Dp;
                    leftrotateD(root,nodo);
                }
                nodo->Dp->Dcolore='b';
                nodo->Dp->Dp->Dcolore='r';
                rightrotateD(root,nodo->Dp->Dp);
            }

        }else{
            y=nodo->Dp->Dp->Dsx;

            if(y->Dcolore=='r'){
                nodo->Dp->Dcolore='b';
                y->Dcolore='b';
                nodo->Dp->Dp->Dcolore='r';
                nodo=nodo->Dp->Dp;
            }else{
                if(nodo==nodo->Dp->Dsx){
                    nodo=nodo->Dp;
                    rightrotateD(root,nodo);
                }
                nodo->Dp->Dcolore='b';
                nodo->Dp->Dp->Dcolore='r';
                leftrotateD(root,nodo->Dp->Dp);
            }
        }
    }
    (*root)->Dcolore='b';
}

void leftrotateD(nodoDestinatario **root, nodoDestinatario *nodo){

    nodoDestinatario *y;

    y=nodo->Ddx;
    nodo->Ddx=y->Dsx;
    if(y->Dsx!=nilD){
        y->Dsx->Dp=nodo;
    }
    y->Dp=nodo->Dp;
    if(nodo->Dp==nilD){
        *root=y;
    }else if(nodo==nodo->Dp->Dsx){
        nodo->Dp->Dsx=y;
    }else{
        nodo->Dp->Ddx=y;
    }
    y->Dsx=nodo;
    nodo->Dp=y;
}

void rightrotateD(nodoDestinatario **root, nodoDestinatario *nodo){

    nodoDestinatario *y;

    y=nodo->Dsx;
    nodo->Dsx=y->Ddx;
    if(y->Ddx!=nilD){
        y->Ddx->Dp=nodo;
    }
    y->Dp=nodo->Dp;
    if(nodo->Dp==nilD){
        *root=y;
    }else if(nodo==nodo->Dp->Ddx){
        nodo->Dp->Ddx=y;
    }else{
        nodo->Dp->Dsx=y;
    }
    y->Ddx=nodo;
    nodo->Dp=y;
}

nodoDestinatario *deleteD(nodoDestinatario **root, nodoDestinatario *nodo){

    nodoDestinatario *x;
    nodoDestinatario *y;

    if(nodo->Dsx==nilD || nodo->Ddx==nilD){
        y=nodo;
    }else{
        y=treesuccessorD(nodo);
    }

    if(y->Dsx!=nilD){
        x=y->Dsx;
    }else{
        x=y->Ddx;
    }

    x->Dp=y->Dp;

    if(y->Dp==nilD){
        *root=x;
    }else if(y==y->Dp->Dsx){
        y->Dp->Dsx=x;
    }else{
        y->Dp->Ddx=x;
    }

    if(y!=nodo){
        nodo->dest=y->dest;
    }

    if(y->Dcolore=='b'){
        deletefixupD(root,x);
    }

    return y;
}

void deletefixupD(nodoDestinatario **root, nodoDestinatario *nodo){

    nodoDestinatario *y;

    while(nodo!=*root && nodo->Dcolore=='b'){
        
        if(nodo==nodo->Dp->Dsx){
            y=nodo->Dp->Ddx;

            if(y->Dcolore=='r'){
                y->Dcolore='b';
                nodo->Dp->Dcolore='r';
                leftrotateD(root,nodo->Dp);
                y=nodo->Dp->Ddx;
            }

            if(y->Dsx->Dcolore=='b' && y->Ddx->Dcolore=='b'){
                y->Dcolore='r';
                nodo=nodo->Dp;
            }else{
                if(y->Ddx->Dcolore=='b'){
                    y->Dsx->Dcolore='b';
                    y->Dcolore='r';
                    rightrotateD(root,y);
                    y=nodo->Dp->Ddx;
                }
                y->Dcolore=nodo->Dp->Dcolore;
                nodo->Dp->Dcolore='b';
                y->Ddx->Dcolore='b';
                leftrotateD(root,nodo->Dp);
                nodo=*root;
            }           
        }else{
            y=nodo->Dp->Dsx;

            if(y->Dcolore=='r'){
                y->Dcolore='b';
                nodo->Dp->Dcolore='r';
                rightrotateD(root,nodo->Dp);
                y=nodo->Dp->Dsx;
            }

            if(y->Ddx->Dcolore=='b' && y->Dsx->Dcolore=='b'){
                y->Dcolore='r';
                nodo=nodo->Dp;
            }else{
                if(y->Dsx->Dcolore=='b'){
                    y->Ddx->Dcolore='b';
                    y->Dcolore='r';
                    leftrotateD(root,y);
                    y=nodo->Dp->Dsx;
                }
                y->Dcolore=nodo->Dp->Dcolore;
                nodo->Dp->Dcolore='b';
                y->Dsx->Dcolore='b';
                rightrotateD(root,nodo->Dp);
                nodo=*root;
            }           
        }
    }
    nodo->Dcolore='b';
}

nodoDestinatario *treesuccessorD(nodoDestinatario *nodo){

    nodoDestinatario *x=nodo;
    nodoDestinatario *y;

    if(x->Ddx!=nilD){
        return treeminimumD(x->Ddx);
    }
    y=x->Dp;
    while(y!=nilD && x==y->Ddx){
        x=y;
        y=y->Dp;
    }
    return y;
}

nodoDestinatario *treeminimumD(nodoDestinatario *nodo){

    nodoDestinatario *x=nodo;
    while(x->Dsx!=nilD){
        x=x->Dsx;
    }
    return x;
}


//gestione RB-tree mittenti

nodoMittente *crea_nodoM(char *infoEntitaM){

    nodoMittente *nodo=malloc(sizeof(nodoMittente));
    nodo->Mp=NULL;
    nodo->Msx=NULL;
    nodo->Mdx=NULL;
    nodo->Mcolore='r';
    nodo->mitt=infoEntitaM;

    return nodo;
}

nodoMittente *searchM(nodoMittente **root, char *infoEntitaM){

    nodoMittente *x=*root;
    
    while(x!=nilM && strcmp(x->mitt,infoEntitaM)!=0){
        if(strcmp(x->mitt,infoEntitaM)>0){
            x=x->Msx;
        }else{
            x=x->Mdx;
        }
    }
    return x;
}

void insertM(nodoMittente **root, nodoMittente *nodo){

    nodoMittente *x=*root;        
    nodoMittente *y=nilM;         
    
    while(x!=nilM){
        y=x;
        if(strcmp(nodo->mitt,x->mitt)<0){
            x=x->Msx;
        }else{
            x=x->Mdx;
        }
    }
    
    nodo->Mp=y;
    if(y==nilM){                                        
        *root=nodo;
    }else if(strcmp(nodo->mitt,y->mitt)<0){             
        y->Msx=nodo;    
    }else{
        y->Mdx=nodo;                                    
    }

    nodo->Msx=nilM;
    nodo->Mdx=nilM;
    nodo->Mcolore='r';
    insertfixupM(root,nodo);
}

void insertfixupM(nodoMittente **root, nodoMittente *nodo){

    nodoMittente *y;

    while(nodo->Mp->Mcolore=='r'){
        
        if(nodo->Mp==nodo->Mp->Mp->Msx){
            y=nodo->Mp->Mp->Mdx;

            if(y->Mcolore=='r'){
                nodo->Mp->Mcolore='b';
                y->Mcolore='b';
                nodo->Mp->Mp->Mcolore='r';
                nodo=nodo->Mp->Mp;
            }else{
                if(nodo==nodo->Mp->Mdx){
                    nodo=nodo->Mp;
                    leftrotateM(root,nodo);
                }
                nodo->Mp->Mcolore='b';
                nodo->Mp->Mp->Mcolore='r';
                rightrotateM(root,nodo->Mp->Mp);
            }

        }else{
            y=nodo->Mp->Mp->Msx;

            if(y->Mcolore=='r'){
                nodo->Mp->Mcolore='b';
                y->Mcolore='b';
                nodo->Mp->Mp->Mcolore='r';
                nodo=nodo->Mp->Mp;
            }else{
                if(nodo==nodo->Mp->Msx){
                    nodo=nodo->Mp;
                    rightrotateM(root,nodo);
                }
                nodo->Mp->Mcolore='b';
                nodo->Mp->Mp->Mcolore='r';
                leftrotateM(root,nodo->Mp->Mp);
            }
        }
    }
    (*root)->Mcolore='b';
}

void leftrotateM(nodoMittente **root, nodoMittente *nodo){

    nodoMittente *y;

    y=nodo->Mdx;
    nodo->Mdx=y->Msx;
    if(y->Msx!=nilM){
        y->Msx->Mp=nodo;
    }
    y->Mp=nodo->Mp;
    if(nodo->Mp==nilM){
        *root=y;
    }else if(nodo==nodo->Mp->Msx){
        nodo->Mp->Msx=y;
    }else{
        nodo->Mp->Mdx=y;
    }
    y->Msx=nodo;
    nodo->Mp=y;
}

void rightrotateM(nodoMittente **root, nodoMittente *nodo){

    nodoMittente *y;

    y=nodo->Msx;
    nodo->Msx=y->Mdx;
    if(y->Mdx!=nilM){
        y->Mdx->Mp=nodo;
    }
    y->Mp=nodo->Mp;
    if(nodo->Mp==nilM){
        *root=y;
    }else if(nodo==nodo->Mp->Mdx){
        nodo->Mp->Mdx=y;
    }else{
        nodo->Mp->Msx=y;
    }
    y->Mdx=nodo;
    nodo->Mp=y;
}

nodoMittente*deleteM(nodoMittente **root, nodoMittente *nodo){

    nodoMittente *x;
    nodoMittente *y;

    if(nodo->Msx==nilM || nodo->Mdx==nilM){
        y=nodo;
    }else{
        y=treesuccessorM(nodo);
    }

    if(y->Msx!=nilM){
        x=y->Msx;
    }else{
        x=y->Mdx;
    }

    x->Mp=y->Mp;

    if(y->Mp==nilM){
        *root=x;
    }else if(y==y->Mp->Msx){
        y->Mp->Msx=x;
    }else{
        y->Mp->Mdx=x;
    }

    if(y!=nodo){
        nodo->mitt=y->mitt;
    }

    if(y->Mcolore=='b'){
        deletefixupM(root,x);
    }

    return y;
}

void deletefixupM(nodoMittente **root, nodoMittente *nodo){

    nodoMittente *y;

    while(nodo!=*root && nodo->Mcolore=='b'){
        
        if(nodo==nodo->Mp->Msx){
            y=nodo->Mp->Mdx;

            if(y->Mcolore=='r'){
                y->Mcolore='b';
                nodo->Mp->Mcolore='r';
                leftrotateM(root,nodo->Mp);
                y=nodo->Mp->Mdx;
            }

            if(y->Msx->Mcolore=='b' && y->Mdx->Mcolore=='b'){
                y->Mcolore='r';
                nodo=nodo->Mp;
            }else{
                if(y->Mdx->Mcolore=='b'){
                    y->Msx->Mcolore='b';
                    y->Mcolore='r';
                    rightrotateM(root,y);
                    y=nodo->Mp->Mdx;
                }
                y->Mcolore=nodo->Mp->Mcolore;
                nodo->Mp->Mcolore='b';
                y->Mdx->Mcolore='b';
                leftrotateM(root,nodo->Mp);
                nodo=*root;
            }           
        }else{
            y=nodo->Mp->Msx;

            if(y->Mcolore=='r'){
                y->Mcolore='b';
                nodo->Mp->Mcolore='r';
                rightrotateM(root,nodo->Mp);
                y=nodo->Mp->Msx;
            }

            if(y->Mdx->Mcolore=='b' && y->Msx->Mcolore=='b'){
                y->Mcolore='r';
                nodo=nodo->Mp;
            }else{
                if(y->Msx->Mcolore=='b'){
                    y->Mdx->Mcolore='b';
                    y->Mcolore='r';
                    leftrotateM(root,y);
                    y=nodo->Mp->Msx;
                }
                y->Mcolore=nodo->Mp->Mcolore;
                nodo->Mp->Mcolore='b';
                y->Msx->Mcolore='b';
                rightrotateM(root,nodo->Mp);
                nodo=*root;
            }           
        }
    }
    nodo->Mcolore='b';
}

nodoMittente *treesuccessorM(nodoMittente *nodo){

    nodoMittente *x=nodo;
    nodoMittente *y;

    if(x->Mdx!=nilM){
        return treeminimumM(x->Mdx);
    }
    y=x->Mp;
    while(y!=nilM && x==y->Mdx){
        x=y;
        y=y->Mp;
    }
    return y;
}

nodoMittente *treeminimumM(nodoMittente *nodo){

    nodoMittente *x=nodo;
    while(x->Msx!=nilM){
        x=x->Msx;
    }
    return x;
}

//gestione RB-tree output

nodoOutput *crea_nodoO(char *nome_output){
    
    nodoOutput *nodo=malloc(sizeof(nodoOutput));
    nodo->Op=NULL;
    nodo->Osx=NULL;
    nodo->Odx=NULL;
    nodo->Ocolore='r';
    nodo->output_name=nome_output;

    return nodo;
}

nodoOutput *searchO(nodoOutput **root, char *nome_output){

    nodoOutput *x=*root;
    
    while(x!=nilO && strcmp(x->output_name,nome_output)!=0){
        if(strcmp(x->output_name,nome_output)>0){
            x=x->Osx;
        }else{
            x=x->Odx;
        }
    }
    return x;
}

void insertO(nodoOutput **root, nodoOutput *nodo){

    nodoOutput *x=*root;        
    nodoOutput *y=nilO;         
    
    while(x!=nilO){
        y=x;
        if(strcmp(nodo->output_name,x->output_name)<0){
            x=x->Osx;
        }else{
            x=x->Odx;
        }
    }
    
    nodo->Op=y;
    if(y==nilO){                                        
        *root=nodo;
    }else if(strcmp(nodo->output_name,y->output_name)<0){             
        y->Osx=nodo;    
    }else{
        y->Odx=nodo;                                    
    }

    nodo->Osx=nilO;
    nodo->Odx=nilO;
    nodo->Ocolore='r';
    insertfixupO(root,nodo);
}

void insertfixupO(nodoOutput **root, nodoOutput *nodo){

    nodoOutput *y;

    while(nodo->Op->Ocolore=='r'){
        
        if(nodo->Op==nodo->Op->Op->Osx){
            y=nodo->Op->Op->Odx;

            if(y->Ocolore=='r'){
                nodo->Op->Ocolore='b';
                y->Ocolore='b';
                nodo->Op->Op->Ocolore='r';
                nodo=nodo->Op->Op;
            }else{
                if(nodo==nodo->Op->Odx){
                    nodo=nodo->Op;
                    leftrotateO(root,nodo);
                }
                nodo->Op->Ocolore='b';
                nodo->Op->Op->Ocolore='r';
                rightrotateO(root,nodo->Op->Op);
            }

        }else{
            y=nodo->Op->Op->Osx;

            if(y->Ocolore=='r'){
                nodo->Op->Ocolore='b';
                y->Ocolore='b';
                nodo->Op->Op->Ocolore='r';
                nodo=nodo->Op->Op;
            }else{
                if(nodo==nodo->Op->Osx){
                    nodo=nodo->Op;
                    rightrotateO(root,nodo);
                }
                nodo->Op->Ocolore='b';
                nodo->Op->Op->Ocolore='r';
                leftrotateO(root,nodo->Op->Op);
            }
        }
    }
    (*root)->Ocolore='b';
}

void leftrotateO(nodoOutput **root, nodoOutput *nodo){

    nodoOutput *y;

    y=nodo->Odx;
    nodo->Odx=y->Osx;
    if(y->Osx!=nilO){
        y->Osx->Op=nodo;
    }
    y->Op=nodo->Op;
    if(nodo->Op==nilO){
        *root=y;
    }else if(nodo==nodo->Op->Osx){
        nodo->Op->Osx=y;
    }else{
        nodo->Op->Odx=y;
    }
    y->Osx=nodo;
    nodo->Op=y;
}

void rightrotateO(nodoOutput **root, nodoOutput *nodo){

    nodoOutput *y;

    y=nodo->Osx;
    nodo->Osx=y->Odx;
    if(y->Odx!=nilO){
        y->Odx->Op=nodo;
    }
    y->Op=nodo->Op;
    if(nodo->Op==nilO){
        *root=y;
    }else if(nodo==nodo->Op->Odx){
        nodo->Op->Odx=y;
    }else{
        nodo->Op->Osx=y;
    }
    y->Odx=nodo;
    nodo->Op=y;
}

nodoOutput *deleteO(nodoOutput **root, nodoOutput *nodo){

    nodoOutput *x;
    nodoOutput *y;

    if(nodo->Osx==nilO || nodo->Odx==nilO){
        y=nodo;
    }else{
        y=treesuccessorO(nodo);
    }

    if(y->Osx!=nilO){
        x=y->Osx;
    }else{
        x=y->Odx;
    }

    x->Op=y->Op;

    if(y->Op==nilO){
        *root=x;
    }else if(y==y->Op->Osx){
        y->Op->Osx=x;
    }else{
        y->Op->Odx=x;
    }

    if(y!=nodo){
        nodo->output_name=y->output_name;
    }

    if(y->Ocolore=='b'){
        deletefixupO(root,x);
    }

    return y;
}

void deletefixupO(nodoOutput **root, nodoOutput *nodo){

    nodoOutput *y;

    while(nodo!=*root && nodo->Ocolore=='b'){
        
        if(nodo==nodo->Op->Osx){
            y=nodo->Op->Odx;

            if(y->Ocolore=='r'){
                y->Ocolore='b';
                nodo->Op->Ocolore='r';
                leftrotateO(root,nodo->Op);
                y=nodo->Op->Odx;
            }

            if(y->Osx->Ocolore=='b' && y->Odx->Ocolore=='b'){
                y->Ocolore='r';
                nodo=nodo->Op;
            }else{
                if(y->Odx->Ocolore=='b'){
                    y->Osx->Ocolore='b';
                    y->Ocolore='r';
                    rightrotateO(root,y);
                    y=nodo->Op->Odx;
                }
                y->Ocolore=nodo->Op->Ocolore;
                nodo->Op->Ocolore='b';
                y->Odx->Ocolore='b';
                leftrotateO(root,nodo->Op);
                nodo=*root;
            }           
        }else{
            y=nodo->Op->Osx;

            if(y->Ocolore=='r'){
                y->Ocolore='b';
                nodo->Op->Ocolore='r';
                rightrotateO(root,nodo->Op);
                y=nodo->Op->Osx;
            }

            if(y->Odx->Ocolore=='b' && y->Osx->Ocolore=='b'){
                y->Ocolore='r';
                nodo=nodo->Op;
            }else{
                if(y->Osx->Ocolore=='b'){
                    y->Odx->Ocolore='b';
                    y->Ocolore='r';
                    leftrotateO(root,y);
                    y=nodo->Op->Osx;
                }
                y->Ocolore=nodo->Op->Ocolore;
                nodo->Op->Ocolore='b';
                y->Osx->Ocolore='b';
                rightrotateO(root,nodo->Op);
                nodo=*root;
            }           
        }
    }
    nodo->Ocolore='b';
}

nodoOutput *treesuccessorO(nodoOutput *nodo){

    nodoOutput *x=nodo;
    nodoOutput *y;

    if(x->Odx!=nilO){
        return treeminimumO(x->Odx);
    }
    y=x->Op;
    while(y!=nilO && x==y->Odx){
        x=y;
        y=y->Op;
    }
    return y;
}

nodoOutput *treeminimumO(nodoOutput *nodo){
    
    nodoOutput *x=nodo;
    while(x->Osx!=nilO){
        x=x->Osx;
    }
    return x;
}

//addent
nodoEntita *addent(nodoEntita *radiceEntita, char *ID){

    if(searchE(&radiceEntita,ID)==nilE){                                                                                                                                                                           
        insertE(&radiceEntita,crea_nodoE(ID));        
    }
    return radiceEntita;
}

//addrel
nodoRelazione *addrel(nodoRelazione *radiceRelazioni, char *IDrelazione, char *info_dest, char *info_mitt){

    nodoRelazione *punt_rel=NULL;
    nodoDestinatario *punt_dest=NULL;
    nodoMittente *punt_mitt=NULL;
    nodoOutput *punt_out=NULL;
    nodoOutput *erase=NULL;

    punt_rel=searchR(&radiceRelazioni,IDrelazione);                     //cerco il nodo relazione corrispondente, se non c'è lo
    if(punt_rel==nilR){                                                 //creo e lo metto nell'albero delle relazioni, ottenendone 
        punt_rel=crea_nodoR(IDrelazione);                               //il puntatore, altrimenti ottengo subito il puntatore di 
        insertR(&radiceRelazioni,punt_rel);                             //quella relazione
    }
                               
    punt_dest=searchD(&(punt_rel->radiceDestinatari),info_dest);        //cerco il nodo destinatario nell'albero destinatari della
    if(punt_dest==nilD){                                                //relazione, se lo trovo ottengo il puntatore, altrimenti
        punt_dest=crea_nodoD(info_dest);                                //creo il nodo ottenendone il puntatore e lo inserisco 
        insertD(&(punt_rel->radiceDestinatari),punt_dest);
    }
                
    punt_mitt=searchM(&(punt_dest->radiceMittenti),info_mitt);          //cerco il nodo mittente nell'albero del destinatario, se lo 
    if(punt_mitt==nilM){                                                //trovo ne ottengo il puntatore ma non devo fare più niente 
        punt_mitt=crea_nodoM(info_mitt);                                //perchè la relazione esisteva già, altrimenti creo il nodo
        insertM(&(punt_dest->radiceMittenti),punt_mitt);                //e lo aggiungo all'albero, in questo caso incremento il 
        punt_dest->followers++;                                         //numero di followers del destinatario

        if(punt_dest->followers>punt_rel->max){                         //se il numero di seguaci è aumentato oltre il massimo della relazione
            punt_rel->max=punt_dest->followers;                         //ho ottenuto un nuovo massimo, quinid resetto il max al numero di seguaci 

            erase=punt_rel->radiceOutput;                               //inoltre devo eliminare l'albero di output del massimo precedente e 
            punt_rel->radiceOutput=nilO;                                //creare un nuovo nodo con riferimento all'entità destinataria che sarà
            free_treeO(erase);                                          //l'unico nodo del nuovo albero di output
            punt_out=crea_nodoO(info_dest);
            insertO(&(punt_rel->radiceOutput),punt_out);

        }else if(punt_dest->followers==punt_rel->max){                  

            punt_out=crea_nodoO(info_dest);                             //se ho pareggiato il massimo allora il destinatario prima non era nell'albero
            insertO(&(punt_rel->radiceOutput),punt_out);                //dei massimi per la relazione, quindi gli creo un nodo e lo aggiungo       
        }
    }

    return radiceRelazioni;
}

//delrel
nodoRelazione *delrel(nodoRelazione *radiceRelazioni, char *IDrelazione, char *IDdest, char *IDmitt){

    nodoRelazione *punt_relazione=NULL;                 //puntatore alla relazione
    nodoDestinatario *punt_destinatario=NULL;           //puntatore al destinatario
    nodoMittente *punt_mittente=NULL;                   //puntatore al mittente
    nodoMittente *mitt_eliminare=NULL;                  //puntatore al nodo mittente da eliminare
    nodoOutput *punt_output=NULL;                       //puntatore al nodo di output 
    nodoOutput *out_eliminare=NULL;                     //puntatore al nodo di output da eliminare
    unsigned int new_max=0;

    punt_relazione=searchR(&radiceRelazioni,IDrelazione);
    if(punt_relazione!=nilR){                                                               //la relazione esiste (e quindi posso cancellarla) solo se 
        punt_destinatario=searchD(&(punt_relazione->radiceDestinatari),IDdest);             //esiste la relazione, e per quella relazione il  
        if(punt_destinatario!=nilD){                                                        //destinatario ha il mittente nel proprio albero di seguaci
            punt_mittente=searchM(&(punt_destinatario->radiceMittenti),IDmitt);
            if(punt_mittente!=nilM){
                        
                mitt_eliminare=deleteM(&(punt_destinatario->radiceMittenti),punt_mittente);          //cancello il nodo mittente dall'albero dei mittenti
                free(mitt_eliminare);
                mitt_eliminare=NULL;
                punt_destinatario->followers--;                                                 //e diminuisco il numero di follower dell'entità destinatario

                if(punt_destinatario->followers+1==punt_relazione->max){                        //se il destinatario era uno dei massimi della relazione (prima                                                                                                      
                                                                                                //della sottrazione) allora lo tolgo dall'albero di output (in        
                    punt_output=searchO(&(punt_relazione->radiceOutput),IDdest);                //cui era in quanto massimo).                       
                    out_eliminare=deleteO(&(punt_relazione->radiceOutput),punt_output);         //se c'erano più massimi allora la cancellazione
                    free(out_eliminare);                                                        //semplicemente rimuove quel nodo tra i tanti, se era
                    out_eliminare=NULL;                                                         //l'unico allora l'albero di output dopo punterà ora a nilO

                    if(punt_relazione->radiceOutput==nilO){                                     //se l'albero ora è vuoto devo ricalcolare il nuovo massimo e      
                        reset_max(punt_relazione->radiceDestinatari, &new_max);                 //ricostruire l'albero di output con i destinatari appropriati
                        punt_relazione->max=new_max;                                                                                
                        reset_output_tree(punt_relazione->radiceDestinatari,punt_relazione->max,&(punt_relazione->radiceOutput));
                    }                                                                                                      

                }                                   
                                                    
            }                                       
        }
    }

    return radiceRelazioni;
}

//report
void report_walkR(nodoRelazione *root, int *none_rel){
    
    if(root!=nilR){                                                     //la funzione è una inorderwalk delle relazioni che stampa in nome solo
        report_walkR(root->Rsx,none_rel);                               //delle relazioni con massimo >0, e dopo ogni scrittura da inizio a quella
        if(root->max>0){                                                //dei nomi dei destinatari con il massimo numero di follower            
                                                                        //inserisce infine il valore del massimo
            (*none_rel)=1;                                              
            putchar('\"');                                              
            fputs(root->rel,stdout);                                    
            putchar('\"');
            putchar(' ');                                
            
            report_walkO(root->radiceOutput);
            
            printf("%u",root->max);                                     
            putchar(';');
            putchar(' ');

        }
        report_walkR(root->Rdx,none_rel);
    }
}

void report_walkO(nodoOutput *root){

    if(root!=nilO){                                                     
        
        report_walkO(root->Osx);                              
                                              
        putchar('\"');                                              
        fputs(root->output_name,stdout);                                    
        putchar('\"');
        putchar(' ');

        report_walkO(root->Odx);
    }                                
}

//delent
void delent_walkR(nodoRelazione *root, char *IDentita){

    if(root!=nilR){
        
        nodoDestinatario *punt_dest_elim=nilD;                                          
        nodoDestinatario *remove=NULL;
        
        //root->radiceDestinatari= radice albero destinatari della relazione
        //IDentità nome usato per cercare mittenti/destinatari
        //punt_dest_elim puntatore ad eventuale nodo da eliminare
        //root=puntatore al nodo relazione che sto considerando

        delent_walkD(root->radiceDestinatari,IDentita,punt_dest_elim,root);           //vado a controllare i nomi dei destinatari e dei loro mittenti                            
                                                                                    
        if(punt_dest_elim!=nilD){                                               //se tra i destinatari della relazione uno aveva il nome cercato allora punt_dest_elim      
            remove=deleteD(&(root->radiceDestinatari),punt_dest_elim);          //sarà diverso da nilD e lo elimino dai destinatari
            free(remove);
            remove=NULL;               
        }                                                                       
        
        if(root->radiceOutput==nilO){                                                                                                                                           
            unsigned int new_max=0;                                         //se l'albero dei massimi si è svuotato la delent ha comportato la cancellazione di tutti
                                                                            //quelli che precedentemente erano massimi, quindi devo ricalcolare l'albero di output             
            reset_max(root->radiceDestinatari, &new_max);                   //con i nuovi massimi per la relazione
            root->max=new_max;                        
            reset_output_tree(root->radiceDestinatari,root->max,&(root->radiceOutput));
        }
                                
        delent_walkR(root->Rsx,IDentita);
        delent_walkR(root->Rdx,IDentita);
    }
}

void delent_walkD(nodoDestinatario *root, char *IDentita, nodoDestinatario *punt_dest_elim, nodoRelazione *relazione){

    if(root!=nilD){

        nodoOutput *out_elim=NULL;                              //uso questi puntatori per rimuovere i massimi dall'albero di output quando la delent causa che
        nodoOutput *punt_elim=NULL;                             //il destinatario non sia più un massimo per la relazione. può avvenire in due modi:

        if(strcmp(root->dest,IDentita)==0){                                 //se il destinatario è l'entità da eliminare verifico prima di tutto se esso sia uno dei                                                                                                    
                                                                            //massimi della relazione, in caso affermativo rimuovo dall'albero di output il nodo
            nodoMittente *erase=NULL;                                       //ad esso corrispondente

            if(root->followers==relazione->max){                            //inoltre non mi serve più mantenere l'albero dei mittenti per tale nodo nè il nodo stesso,
                                                                            //quindi ne pongo il numro di seguaci a 0 ed elimino l'albero dei mittenti. poichè non
                out_elim=searchO(&(relazione->radiceOutput),root->dest);    //eliminare il nodo stesso in questa funzione senza causare problemi alla ricorsione ci
                punt_elim=deleteO(&(relazione->radiceOutput),out_elim);     //attacco un puntatore che userò per eliminarlo una volta terminata la ricerca dell'entità
                free(punt_elim);                                            //nella relazione, quindi in delent_walkR
                punt_elim=NULL;                                          
            }                                                           
                                                                         
            root->followers=0;                                          
            erase=root->radiceMittenti;                                 
            root->radiceMittenti=nilM;
            free_treeM(erase);
            erase=NULL;
            punt_dest_elim=root;

        }else{                                                                  //se invece il destiatario considerato non corrispode all'entità da eliminare
                                                                                //procedo a cercare l'entità tra i mittenti. se non la trovo non faccio nulla,
            nodoMittente *punt_mitt=NULL;                                       //se invece la trovo e il destinatario era uno dei massimi,rimuovo il nodo
            nodoMittente *remove=NULL;                                          //corrispondente dall'albero di output, poi diminuisco di 1 il numero di seguaci
                                                                                //e tolgo il mittente dall'albero dei mittenti
            punt_mitt=searchM(&(root->radiceMittenti),IDentita);
            if(punt_mitt!=nilM){                                            
                
                if(root->followers==relazione->max){
                    
                    out_elim=searchO(&(relazione->radiceOutput),root->dest);
                    punt_elim=deleteO(&(relazione->radiceOutput),out_elim);
                    free(punt_elim);
                    punt_elim=NULL;
                }
               
                root->followers--;
                remove=deleteM(&(root->radiceMittenti),punt_mitt);
                free(remove);
                remove=NULL;
            }
        }

        delent_walkD(root->Dsx,IDentita,punt_dest_elim,relazione);
        delent_walkD(root->Ddx,IDentita,punt_dest_elim,relazione);

    }
}

//altre
void reset_max(nodoDestinatario *root, unsigned int *new_max){

    if(root!=nilD){

        if(root->followers>*new_max){                               //per ogni destinatario vedo quanti sono i follower, se sono più del massimo
            *new_max=root->followers;                               //aggiorno il massimo
        } 
        reset_max(root->Dsx,new_max);
        reset_max(root->Ddx,new_max);

    }
}

void reset_output_tree(nodoDestinatario *root_destinatario, unsigned int max, nodoOutput **root_output){

    if(root_destinatario!=nilD){
        
        reset_output_tree(root_destinatario->Dsx,max,root_output);              //faccio una walk dell'albero dei destinatario, e aggiungo nodi di output
        if(root_destinatario->followers==max){                                  //per i destinatari che hanno il nuovo massimo di relazioni entranti per
            insertO(root_output,crea_nodoO(root_destinatario->dest));           //la relazione
        }
        reset_output_tree(root_destinatario->Ddx,max,root_output);
    }
}

void free_treeO(nodoOutput *root){
    
    if(root!=nilO){
        free_treeO(root->Osx);
        free_treeO(root->Odx);         
        free(root);
    }
}

void free_treeM(nodoMittente *root){

    if(root!=nilM){
        free_treeM(root->Msx);           //cancellazione e liberazione della memoria per tutti i nodi dell'albero, non è necessario sistemare
        free_treeM(root->Mdx);           //e ribilanciare l'RB-tree se tanto devo cancellare tutti i nodi, lo tratto come un qualsiasi BST
        free(root);
    }
}