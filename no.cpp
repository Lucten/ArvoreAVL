#include<iostream>
using namespace std;

template <typename T>
class AVL{
    public:
        class no{
            public:
                T chave;
                int alt;
                no * esq;
                no * dir;
                no(T val){
                    alt = 1;
                    chave = val;
                    esq = NULL;
                    dir = NULL;
                }
        };
        no * raiz = NULL;
        int n;
        void inserir(T valor){
            raiz=inserirNaArvore(raiz, valor);
        }
        void remove(T valor){
            raiz=removerNaArvore(raiz, valor);
        }
        no * buscar(T valor){
            return buscarNaArvore(raiz,valor);
        }
        void mostrarEmOrdem(){
            emOrdem(raiz);
            cout<<endl;
        }
    private:
        int alt(no * noP){
            if(noP==NULL){ 
                return 0;
            }
            return noP->alt;
        }
        no * rodarDir(no * noP){
            no * novoNo = noP->esq;
            noP->esq = novoNo->dir;
            novoNo->dir = noP;
            noP->alt = 1+max(alt(noP->esq), alt(noP->dir));
            novoNo->alt = 1+max(alt(novoNo->esq), alt(novoNo->dir));
            return novoNo;
        }

        no * rodarEsq(no * noP){
            no * novoNo = noP->dir;
            noP->dir = novoNo->esq;
            novoNo->esq = noP;
            noP->alt = 1+max(alt(noP->esq), alt(noP->dir));
            novoNo->alt = 1+max(alt(novoNo->esq), alt(novoNo->dir));
            return novoNo;
        }

        void emOrdem(no * noP){
            if(noP==NULL){
                return;
            }
            emOrdem(noP->esq);
            cout<<noP->chave<<" ";
            emOrdem(noP->dir);
        }

        no * inserirNaArvore(no * noP, T valor){
            if(noP==NULL){
                n+=1;
                no * temp = new no(valor);
                return temp;
            }
            if(valor < noP->chave) noP->esq = inserirNaArvore(noP->esq, valor);
            else if(valor > noP->chave) noP->dir = inserirNaArvore(noP->dir, valor);
            noP->alt = 1 + max(alt(noP->esq), alt(noP->dir));
            int bal = alt(noP->esq) - alt(noP->dir);
            if(bal>1){
                if(valor < noP->esq->chave){
                    return rodarDir(noP); //Rotacionar uma vez ao se inserir no mesmo lado seguidamente e no sentido oposto ao inserido.
                }else{
                    noP->esq = rodarEsq(noP->esq);  //Rotacionar duas vezes ao se inserir
                    return rodarDir(noP);           //em lados opostos seguidamente.
                }
            }else if(bal<-1){
                if(valor > noP->dir->chave){
                    return rodarEsq(noP);
                }else{
                    noP->dir = rodarDir(noP->dir);
                    return rodarEsq(noP);
                }
            }
            return noP;
        }
        no * removerNaArvore(no * noP, T valor){
            if(noP==NULL) return NULL;
            if(valor < noP->chave){
                noP->esq = removerNaArvore(noP->esq, valor);
            }else if(valor > noP->chave){
                noP->dir = removerNaArvore(noP->dir, valor);
            }else{
                no * d = noP->dir;
                if(noP->dir==NULL){
                    no * e = noP->esq;
                    delete(noP);
                    noP = e;
                }else if(noP->esq==NULL){
                    delete(noP);
                    noP = d;
                }else{
                    while(d->esq!=NULL) d = d->esq;
                    noP->chave = d->chave;
                    noP->dir = removerNaArvore(noP->dir, d->chave);
                }
            }
            if(noP==NULL) return noP;
            noP->alt = 1 + max(alt(noP->esq), alt(noP->dir));
            int bal = alt(noP->esq) - alt(noP->dir);
            if(bal>1){
                if(valor > noP->esq->chave){
                    return rodarDir(noP);
                }else{
                    noP->esq = rodarEsq(noP->esq);
                    return rodarDir(noP);
                }
            }else if(bal < -1){
                if(valor < noP->dir->chave){
                    return rodarEsq(noP);
                }else{
                    noP->dir = rodarDir(noP->dir);
                    return rodarEsq(noP);
                }
            }
            return noP;
        }
        no * buscarNaArvore(no * noP, T valor){
            if(noP == NULL) return NULL;
            T val = noP->chave;
            if(val == valor) return noP;
            if(val > valor) return buscarNaArvore(noP->esq, valor);
            if(val < valor) return buscarNaArvore(noP->dir, valor);
        }
};
int main(){
    AVL<int> t;
    t.inserir(1);
    t.inserir(2);
    t.inserir(3);
    t.inserir(4);
    t.inserir(5);
    t.inserir(6);
    t.inserir(7);
    t.mostrarEmOrdem();
    t.remove(5);
    t.remove(6);
    t.remove(7);
    t.mostrarEmOrdem();
}