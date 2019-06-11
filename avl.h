#ifndef _avl_h
#define _avl_h
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "generic_tree.h"

typedef struct NO{
    int info;
    TAG *elemento;
    struct NO*  esq;
    struct NO*  dir;
    int alt;
}NO;

NO *inicializa_avl(){
    return NULL;
}

void libera_avl(NO* t){
    if( t != NULL ){
        libera_avl( t->esq );
        libera_avl( t->dir );
        free(t);
    }
}

NO* busca_avl(int e, NO* t ){
    if( t == NULL ) return NULL;
    if( e < t->info ) return busca_avl( e, t->esq );
    if( e > t->info ) return busca_avl( e, t->dir );
    return t;
}

static int calc_alt( NO* n ){
    if( n == NULL ) return -1;
    return n->alt;
}


static int max( int l, int r){
    return l > r ? l: r;
}


static NO* rot_dir( NO* k2 ){
    NO* k1 = NULL;
    k1 = k2->esq;
    k2->esq = k1->dir;
    k1->dir = k2;
    k2->alt = max( calc_alt( k2->esq ), calc_alt( k2->dir ) ) + 1;
    k1->alt = max( calc_alt( k1->esq ), k2->alt ) + 1;
    return k1; /* nova raiz */
}


static NO* rot_esq( NO* k1 ){
    NO* k2;
    k2 = k1->dir;
    k1->dir = k2->esq;
    k2->esq = k1;
    k1->alt = max( calc_alt( k1->esq ), calc_alt( k1->dir ) ) + 1;
    k2->alt = max( calc_alt( k2->dir ), k1->alt ) + 1;
    return k2;  /* nova raiz */
}


static NO* rot_esq_dir( NO* k3 ){
    k3->esq = rot_esq( k3->esq );
    return rot_dir( k3 );
}


static NO* rot_dir_esq( NO* k1 ){
    k1->dir = rot_dir( k1->dir );
    return rot_esq( k1 );
}


NO* insere_avl(int e, NO *t, TAG *elemento){
    if( t == NULL ){
        t = (NO*)malloc(sizeof(NO));
        if( t == NULL ){
            fprintf (stderr, "Out of memory!!! (insere)\n");
            exit(1);
        }
        else{
            t->info = e;
            t->elemento = elemento;
            t->alt = 0;
            t->esq = t->dir = NULL;

        }
    }
    else if(e < t->info){
        t->esq = insere_avl( e, t->esq, elemento );
        if(calc_alt(t->esq)-calc_alt(t->dir) == 2){
            if( e < t->esq->info ){
                t = rot_dir( t );
            }else{
                t = rot_esq_dir( t );
            }
        }
    }else if( e > t->info ){
        t->dir = insere_avl( e, t->dir, elemento);
        if( calc_alt( t->dir ) - calc_alt( t->esq ) == 2 ){
            if( e > t->dir->info ){
                t = rot_esq( t );
            }else{
                t = rot_dir_esq( t );
            }
        }
    }
    t->alt = max( calc_alt( t->esq ), calc_alt( t->dir ) ) + 1;
    //printf("cod: %d\n", t->info);
    return t;
}

int calc_alt_retira(NO *T){
    int lh,rh;
    if(T==NULL) return(0);
    if(T->esq==NULL) lh=0;
    else lh=1+T->esq->alt;
    if(T->dir==NULL) rh=0;
    else rh=1+T->dir->alt;
    if(lh>rh) return(lh);
    return(rh);
}

int FB(NO *T){
    int lh,rh;
    if(T==NULL) return(0);
    if(T->esq==NULL) lh=0;
    else lh=1+T->esq->alt;
    if(T->dir==NULL) rh=0;
    else rh=1+T->dir->alt;
    return(lh-rh);
}

void imprime_aux_avl(NO *a, int andar){
  if(a){
      int j;
      imprime_aux_avl(a->esq,andar+1);
      for(j=0; j<=andar; j++) printf("   ");
      printf("%d\n", a->info);
      imprime_aux_avl(a->dir,andar+1);
  }
}

void imprime_avl(NO *a){
  imprime_aux_avl(a, 1);
}

NO * retira_avl(int x, NO *T){
    NO *p;
    if(T==NULL)
        return NULL;
    else
        if(x > T->info){
            T->dir=retira_avl(x,T->dir);
            if(FB(T)==2){
                if(FB(T->esq)>=0){
                    T=rot_dir(T);
                }else{
                    T=rot_esq_dir(T);
                }
            }
        }
        else
            if(x<T->info){
                    T->esq=retira_avl(x,T->esq);
                    if(FB(T)==-2){//Rebalance during windup
                        if(FB(T->dir)<=0){
                            T=rot_esq(T);
                        }else{
                            T=rot_dir_esq(T);
                        }
                    }
            }
            else{
                //info to be deleted is found
                  if(T->esq != NULL){
                      p=T->esq;
                      while(p->dir != NULL) p=p->dir;
                      T->info=p->info;
                      T->esq=retira_avl(p->info, T->esq);
                      if(FB(T)== -2){//Rebalance during windup
                        if(FB(T->dir)<=0){
                            T=rot_esq(T);
                        }else{
                            T=rot_dir_esq(T);
                        }
                    }
                  }
                  else{
                      NO *x = T;
                      T = T->dir;
                      free(x);
                      return(T);
                  }
            }
    T->alt=calc_alt_retira(T);
    return(T);
}

static int min( int l, int r){
    return l < r ? l: r;
}

NO* generic_to_avl(TAG *generic, NO *avl){
	if(generic){
    	avl = insere_avl(generic->cod, avl, generic);
    	avl = generic_to_avl(generic->irmao, avl);
    	avl = generic_to_avl(generic->filho, avl);
    }

	return avl;
}

void imprime_poly_avl(NO *avl){
    if(avl){
      imprime_poly_avl(avl->esq);
      imprime_no(avl->elemento, avl->info);
      imprime_poly_avl(avl->dir);
    }
 }



#endif
