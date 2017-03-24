#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string.h>
#include <stdio.h>

#define LARGURA_TELA 1024
#define ALTURA_TELA 768

typedef struct Bloco
{
 char nome[10], desc[10], origem[10], destino[10];
 struct Bloco *prox;
} Nodo;

void inicializa_lista(Nodo **N)
{
 *N = NULL;
}


Nodo * Cria_Nodo()
{
 Nodo *p;
 p = (Nodo *) malloc(sizeof(Nodo));
 if(!p)
 	{
 	printf("Problema de alocação");
	exit(0);
 	p->prox = NULL;
 	}
 return p;
}

void insere_fim_lista(Nodo **N, int *tam, char nome[10], char desc[10], char origem[10], char destino[10])
{
 Nodo *novo, *aux;
 novo = Cria_Nodo ();
 strcpy(novo->nome, nome);
 strcpy(novo->desc, desc);
 strcpy(novo->origem, origem);
 strcpy(novo->destino, destino);
 novo->prox = NULL;
 *tam = *tam + 1;
 if(*N == NULL)
     *N = novo;
  else
 {
    aux = *N;
    while(aux->prox != NULL)
    	aux = aux->prox;
    aux->prox = novo;
 }
 if((*N)==NULL)
    printf("dsa");
}

int remove_inicio_lista(Nodo **N, int *tam, char nome[10])
{
 Nodo *aux;

    strcpy(nome, (*N)->nome);
    aux =(*N)->prox;
    free(*N);
    *N = aux;
    *tam = *tam - 1;

 return 0;
}

int main (int argc, char *args[]){
    int sair=0, opcaoMenu, opcaoAdicionar, escrevendo=0, i, um=0;//io= enter pra escrever enter pra parar
    int qntDec, qntAte;
	qntDec = 0;
	qntAte = 0;
	int *pa, *pb;
	pa = &qntDec;
	pb = &qntAte;
    char nome[10]={' '}, desc[10]={' '}, origem[10]={' '}, destino[10]={' '}, total[1];
    Nodo *dec, *ate, *aux;
    SDL_Window *janela;
	SDL_Surface *superficie, *intro, *menu, *seta1, *seta2, *adicionar, *visualizar, *autorizar;
	SDL_Rect objeto;
	Mix_Chunk *somIntro, *somAviao;
	SDL_Event evento;
    TTF_Font *fonte;
    SDL_Color corTexto={0, 0, 0};
    SDL_Surface *superficieTexto;

    inicializa_lista(&dec);
	inicializa_lista(&ate);
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);//Inicia funçoes de video do SDL
	janela=SDL_CreateWindow("Awiao", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LARGURA_TELA, ALTURA_TELA, 0);//Cria a janela
    superficie=SDL_GetWindowSurface(janela);//superficie-janela
    IMG_Init(IMG_INIT_PNG);//Inicia função para importar png
    TTF_Init();
    fonte=TTF_OpenFont("media/Monoton-Regular.ttf", 28);
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 );//inicializa mixer
    intro=IMG_Load("media/intro.png");//importa o png pra superficie
    menu=IMG_Load("media/menu.png");
    seta1=IMG_Load("media/seta1.png");
    seta2=IMG_Load("media/seta2.png");
    adicionar=IMG_Load("media/adicionar.png");
    visualizar=IMG_Load("media/visualizar.png");
    autorizar=IMG_Load("media/autorizar.png");
    somIntro=Mix_LoadWAV("media/intro.wav");
    somAviao=Mix_LoadWAV("media/aviao.wav");

    SDL_Delay(1000);
    SDL_BlitScaled(intro, NULL, superficie, NULL);
    SDL_UpdateWindowSurface(janela);
    Mix_PlayChannel( -1, somIntro, 0 );
    SDL_Delay(2000);
    opcaoMenu=7;//avioes esperando para decolar
	do{//MENU
        SDL_BlitScaled(menu, NULL, superficie, NULL);

        objeto.w=80;//tamanho da seta
        objeto.h=30;
        if(opcaoMenu==7){
            objeto.x=50;
            objeto.y=100;
            SDL_BlitScaled(seta1, NULL, superficie, &objeto);
            objeto.x=900;
            SDL_BlitScaled(seta2, NULL, superficie, &objeto);
        }else if(opcaoMenu==6){
            objeto.x=55;
            objeto.y=190;
            SDL_BlitScaled(seta1, NULL, superficie, &objeto);
            objeto.x=890;
            SDL_BlitScaled(seta2, NULL, superficie, &objeto);
        }else if(opcaoMenu==5){
            objeto.x=170;
            objeto.y=280;
            SDL_BlitScaled(seta1, NULL, superficie, &objeto);
            objeto.x=780;
            SDL_BlitScaled(seta2, NULL, superficie, &objeto);
        }else if(opcaoMenu==4){
            objeto.x=230;
            objeto.y=360;
            SDL_BlitScaled(seta1, NULL, superficie, &objeto);
            objeto.x=720;
            SDL_BlitScaled(seta2, NULL, superficie, &objeto);
        }else if(opcaoMenu==3){
            objeto.x=170;
            objeto.y=450;
            SDL_BlitScaled(seta1, NULL, superficie, &objeto);
            objeto.x=780;
            SDL_BlitScaled(seta2, NULL, superficie, &objeto);
        }else if(opcaoMenu==2){
            objeto.x=230;
            objeto.y=540;
            SDL_BlitScaled(seta1, NULL, superficie, &objeto);
            objeto.x=710;
            SDL_BlitScaled(seta2, NULL, superficie, &objeto);
        }else{
            objeto.x=380;
            objeto.y=620;
            SDL_BlitScaled(seta1, NULL, superficie, &objeto);
            objeto.x=560;
            SDL_BlitScaled(seta2, NULL, superficie, &objeto);
        }
        while( SDL_PollEvent( &evento ) != 0 ){
            if( evento.type == SDL_QUIT )
                sair=1;
            else if( evento.type == SDL_KEYDOWN ){
                Mix_PlayChannel( -1, somAviao, 0 );
                switch( evento.key.keysym.sym ){
                case SDLK_UP:
                    if(opcaoMenu+1<8)
                        opcaoMenu++;
                    break;
                case SDLK_DOWN:
                    if(opcaoMenu-1>0)
                        opcaoMenu--;
                    break;
                case SDLK_KP_ENTER:
                    if(opcaoMenu==1)
                        sair=1;
                    else if(opcaoMenu==2)
                        opcaoMenu=13;//adc
                    else if(opcaoMenu==3)
                        opcaoMenu=12;
                    else if(opcaoMenu==4)
                        opcaoMenu=11;
                    else if(opcaoMenu==5)//autoriza dec
                        opcaoMenu=10;
                    else if(opcaoMenu==6)
                        opcaoMenu=9;
                    else if(opcaoMenu==7)
                        opcaoMenu=8;
                    break;
                case SDLK_RETURN:
                    if(opcaoMenu==1)
                        sair=1;
                    else if(opcaoMenu==2)
                        opcaoMenu=13;//adc
                    else if(opcaoMenu==3)
                        opcaoMenu=12;
                    else if(opcaoMenu==4)
                        opcaoMenu=11;
                    else if(opcaoMenu==5)//autoriza dec
                        opcaoMenu=10;
                    else if(opcaoMenu==6)
                        opcaoMenu=9;
                    else if(opcaoMenu==7)
                        opcaoMenu=8;
                    break;
                }
            }
        }

        if((opcaoMenu==11)||(opcaoMenu==10)){
            if(um==0)
                um=1;
            if((opcaoMenu==11)&&(ate==NULL))
                sair=2;
            else if((opcaoMenu==10)&&(dec==NULL))
                sair=2;

            while((sair!=1)&&(sair!=2)){
                SDL_BlitScaled(autorizar, NULL, superficie, NULL);

				if(opcaoMenu==10){
                    superficieTexto=TTF_RenderText_Solid(fonte, (*dec).nome, corTexto);
                    objeto.x=90;
                    objeto.y=120;
                    objeto.w=superficieTexto->w;
                    objeto.h=superficieTexto->h;
                    SDL_BlitScaled(superficieTexto, NULL, superficie, &objeto);
                    superficieTexto=TTF_RenderText_Solid(fonte, (*dec).desc, corTexto);
                    objeto.x=270;
                    objeto.w=superficieTexto->w;
                    objeto.h=superficieTexto->h;
                    SDL_BlitScaled(superficieTexto, NULL, superficie, &objeto);
                    superficieTexto=TTF_RenderText_Solid(fonte, (*dec).origem, corTexto);
                    objeto.x=460;
                    objeto.w=superficieTexto->w;
                    objeto.h=superficieTexto->h;
                    SDL_BlitScaled(superficieTexto, NULL, superficie, &objeto);
                    superficieTexto=TTF_RenderText_Solid(fonte, (*dec).destino, corTexto);
                    objeto.x=710;
                    objeto.w=superficieTexto->w;
                    objeto.h=superficieTexto->h;
                    SDL_BlitScaled(superficieTexto, NULL, superficie, &objeto);
				}else{
                    superficieTexto=TTF_RenderText_Solid(fonte, (*ate).nome, corTexto);
                    objeto.x=90;
                    objeto.y=120;
                    objeto.w=superficieTexto->w;
                    objeto.h=superficieTexto->h;
                    SDL_BlitScaled(superficieTexto, NULL, superficie, &objeto);
                    superficieTexto=TTF_RenderText_Solid(fonte, (*ate).desc, corTexto);
                    objeto.x=270;
                    objeto.w=superficieTexto->w;
                    objeto.h=superficieTexto->h;
                    SDL_BlitScaled(superficieTexto, NULL, superficie, &objeto);
                    superficieTexto=TTF_RenderText_Solid(fonte, (*ate).origem, corTexto);
                    objeto.x=460;
                    objeto.w=superficieTexto->w;
                    objeto.h=superficieTexto->h;
                    SDL_BlitScaled(superficieTexto, NULL, superficie, &objeto);
                    superficieTexto=TTF_RenderText_Solid(fonte, (*ate).destino, corTexto);
                    objeto.x=710;
                    objeto.w=superficieTexto->w;
                    objeto.h=superficieTexto->h;
                    SDL_BlitScaled(superficieTexto, NULL, superficie, &objeto);
				}

                SDL_UpdateWindowSurface(janela);

                while(SDL_PollEvent(&evento)!=0){
					if(evento.type==SDL_QUIT){
						sair=1;
					}
					else if(evento.type==SDL_KEYDOWN){
                        Mix_PlayChannel( -1, somAviao, 0 );
                        switch( evento.key.keysym.sym ){
                        case SDLK_y:
                            if(opcaoMenu==11)
                                remove_inicio_lista(&ate, pb, nome);
                            else
                                remove_inicio_lista(&dec, pa, nome);
                            sair=2;
                            break;
                        case SDLK_n:
                            sair=2;
                            break;
                        }
					}
				}
            }
            if(sair!=1)
                sair=0;
            if(opcaoMenu==11)
                opcaoMenu=4;
            else
                opcaoMenu=5;
        }

        if((opcaoMenu==8)||(opcaoMenu==9)){//visualizar decolagem/pouso
            if(um==0)
                um=1;
            if((opcaoMenu==9)&&(ate==NULL))
                sair=2;
            else if((opcaoMenu==8)&&(dec==NULL))
                sair=2;
            while((sair!=1)&&(sair!=2)){
                SDL_BlitScaled(visualizar, NULL, superficie, NULL);

                while(SDL_PollEvent(&evento)!=0){
					if(evento.type==SDL_QUIT){
						sair=1;
					}
					else if(evento.type==SDL_KEYDOWN){
                        Mix_PlayChannel( -1, somAviao, 0 );
                        switch( evento.key.keysym.sym ){
                        case SDLK_KP_ENTER:
                            sair=2;
                            break;
                        case SDLK_RETURN:
                            sair=2;
                            break;
                        }
					}
				}

				if(opcaoMenu==8){//decolagem
                    objeto.y=70;
                    for(aux=dec; aux!=NULL; aux=aux->prox){
                        superficieTexto=TTF_RenderText_Solid(fonte, aux->nome, corTexto);
                        objeto.x=80;
                        objeto.y+=60;
                        objeto.w=superficieTexto->w;
                        objeto.h=superficieTexto->h;
                        SDL_BlitScaled(superficieTexto, NULL, superficie, &objeto);
                        superficieTexto=TTF_RenderText_Solid(fonte, aux->desc, corTexto);
                        objeto.x=270;
                        objeto.w=superficieTexto->w;
                        objeto.h=superficieTexto->h;
                        SDL_BlitScaled(superficieTexto, NULL, superficie, &objeto);
                        superficieTexto=TTF_RenderText_Solid(fonte, aux->origem, corTexto);
                        objeto.x=460;
                        objeto.w=superficieTexto->w;
                        objeto.h=superficieTexto->h;
                        SDL_BlitScaled(superficieTexto, NULL, superficie, &objeto);
                        superficieTexto=TTF_RenderText_Solid(fonte, aux->destino, corTexto);
                        objeto.x=720;
                        objeto.w=superficieTexto->w;
                        objeto.h=superficieTexto->h;
                        SDL_BlitScaled(superficieTexto, NULL, superficie, &objeto);
                    }
				}else{
                    objeto.y=70;
                    for(aux=ate; aux!=NULL; aux=aux->prox){
                        superficieTexto=TTF_RenderText_Solid(fonte, aux->nome, corTexto);
                        objeto.x=80;
                        objeto.y+=60;
                        objeto.w=superficieTexto->w;
                        objeto.h=superficieTexto->h;
                        SDL_BlitScaled(superficieTexto, NULL, superficie, &objeto);
                        superficieTexto=TTF_RenderText_Solid(fonte, aux->desc, corTexto);
                        objeto.x=270;
                        objeto.w=superficieTexto->w;
                        objeto.h=superficieTexto->h;
                        SDL_BlitScaled(superficieTexto, NULL, superficie, &objeto);
                        superficieTexto=TTF_RenderText_Solid(fonte, aux->origem, corTexto);
                        objeto.x=460;
                        objeto.w=superficieTexto->w;
                        objeto.h=superficieTexto->h;
                        SDL_BlitScaled(superficieTexto, NULL, superficie, &objeto);
                        superficieTexto=TTF_RenderText_Solid(fonte, aux->destino, corTexto);
                        objeto.x=720;
                        objeto.w=superficieTexto->w;
                        objeto.h=superficieTexto->h;
                        SDL_BlitScaled(superficieTexto, NULL, superficie, &objeto);
                    }
				}
				superficieTexto=TTF_RenderText_Solid(fonte, "Total", corTexto);
				objeto.x=80;
				objeto.y=650;
				objeto.w=superficieTexto->w;
                objeto.h=superficieTexto->h;
                SDL_BlitScaled(superficieTexto, NULL, superficie, &objeto);
                if(opcaoMenu==8)
                    total[0]=qntDec+'0';
                else
                    total[0]=qntAte+'0';
                superficieTexto=TTF_RenderText_Solid(fonte, total, corTexto);
				objeto.x=200;
				objeto.w=superficieTexto->w;
                objeto.h=superficieTexto->h;
                SDL_BlitScaled(superficieTexto, NULL, superficie, &objeto);

				SDL_UpdateWindowSurface(janela);
            }//volta aonde tava
            if(sair!=1)
                sair=0;
            if(opcaoMenu==8)
                opcaoMenu=7;
            else
                opcaoMenu=6;
        }

        if((opcaoMenu==12)||(opcaoMenu==13)){//adc decolagem ou pouso
            if(um==0)
                um=1;
            opcaoAdicionar=6;
            do{
                SDL_BlitScaled(adicionar, NULL, superficie, NULL);

                objeto.w=80;//tamanho da seta
                objeto.h=30;
                objeto.x=55;
                if(opcaoAdicionar==6){//nome
                    objeto.y=110;
                    SDL_BlitScaled(seta1, NULL, superficie, &objeto);
                }else if(opcaoAdicionar==5){//desc
                    objeto.y=190;
                    SDL_BlitScaled(seta1, NULL, superficie, &objeto);
                }else if(opcaoAdicionar==4){
                    objeto.y=280;
                    SDL_BlitScaled(seta1, NULL, superficie, &objeto);
                }else if(opcaoAdicionar==3){
                    objeto.y=360;
                    SDL_BlitScaled(seta1, NULL, superficie, &objeto);
                }else if(opcaoAdicionar==2){
                    objeto.y=530;
                    SDL_BlitScaled(seta1, NULL, superficie, &objeto);
                }else{
                    objeto.y=610;
                    SDL_BlitScaled(seta1, NULL, superficie, &objeto);
                }
                while(SDL_PollEvent(&evento)!=0){
					if(evento.type==SDL_QUIT){
						sair=1;
					}else if(escrevendo==0){
                        if(evento.type==SDL_KEYDOWN){
                            Mix_PlayChannel( -1, somAviao, 0 );
                            switch( evento.key.keysym.sym ){
                            case SDLK_UP:
                                if(opcaoAdicionar+1<7)
                                    opcaoAdicionar++;
                                break;
                            case SDLK_DOWN:
                                if(opcaoAdicionar-1>0)
                                    opcaoAdicionar--;
                                break;
                            case SDLK_KP_ENTER:
                                if((opcaoAdicionar==6)||(opcaoAdicionar==5)||(opcaoAdicionar==4)||(opcaoAdicionar==3)){
                                    SDL_StartTextInput();
                                    escrevendo=1;
                                }else if((opcaoAdicionar==2)&&(opcaoMenu==12)){
                                    insere_fim_lista(&dec, pa, nome, desc, origem, destino);
                                    opcaoAdicionar=0;
                                }else if(opcaoAdicionar==2){
                                    insere_fim_lista(&ate, pb, nome, desc, origem, destino);
                                    opcaoAdicionar=0;
                                }else if(opcaoAdicionar==1)
                                    opcaoAdicionar=0;
                                break;
                            case SDLK_RETURN:
                                if((opcaoAdicionar==6)||(opcaoAdicionar==5)||(opcaoAdicionar==4)||(opcaoAdicionar==3)){
                                    SDL_StartTextInput();
                                    escrevendo=1;
                                }else if((opcaoAdicionar==2)&&(opcaoMenu==12)){
                                    insere_fim_lista(&dec, pa, nome, desc, origem, destino);
                                    opcaoAdicionar=0;
                                }else if(opcaoAdicionar==2){
                                    insere_fim_lista(&ate, pb, nome, desc, origem, destino);
                                    opcaoAdicionar=0;
                                }else if(opcaoAdicionar==1)
                                    opcaoAdicionar=0;
                                break;
                            }
                        }
					}else if(escrevendo==1){
                        if( evento.type == SDL_KEYDOWN ){
                            Mix_PlayChannel( -1, somAviao, 0 );
                            if( evento.key.keysym.sym == SDLK_BACKSPACE && strlen(nome) > 0 ){
                                i=0;
                                if(opcaoAdicionar==6)
                                    while(i<strlen(nome))
                                        i++;
                                else if(opcaoAdicionar==5)
                                    while(i<strlen(desc))
                                        i++;
                                else if(opcaoAdicionar==4)
                                    while(i<strlen(origem))
                                        i++;
                                else
                                    while(i<strlen(destino))
                                        i++;
                                i--;
                                if(i==0){
                                    if(opcaoAdicionar==6)
                                        nome[i]=' ';
                                    else if(opcaoAdicionar==5)
                                        desc[i]=' ';
                                    else if(opcaoAdicionar==4)
                                        origem[i]=' ';
                                    else
                                        destino[i]=' ';
                                }else{
                                    if(opcaoAdicionar==6)
                                        nome[i]=NULL;
                                    else if(opcaoAdicionar==5)
                                        desc[i]=NULL;
                                    else if(opcaoAdicionar==4)
                                        origem[i]=NULL;
                                    else
                                        destino[i]=NULL;
                                }
                            }else if(evento.key.keysym.sym==SDLK_KP_ENTER){
                                Mix_PlayChannel( -1, somAviao, 0 );
                                SDL_StopTextInput();
                                escrevendo=0;
                            }else if(evento.key.keysym.sym==SDLK_RETURN){
                                Mix_PlayChannel( -1, somAviao, 0 );
                                SDL_StopTextInput();
                                escrevendo=0;
                            }
                        }else if( evento.type == SDL_TEXTINPUT ){
                            Mix_PlayChannel( -1, somAviao, 0 );
                            if(opcaoAdicionar==6){
                                if(strlen(nome)<9){
                                    if(nome[0]==' ')
                                        strcpy(nome, evento.text.text);
                                    else
                                        strcat(nome, evento.text.text);
                                }
                            }else if(opcaoAdicionar==5){
                                if(strlen(desc)<9){
                                    if(desc[0]==' ')
                                        strcpy(desc, evento.text.text);
                                    else
                                        strcat(desc, evento.text.text);
                                }
                            }else if(opcaoAdicionar==4){
                                if(strlen(origem)<9){
                                    if(origem[0]==' ')
                                        strcpy(origem, evento.text.text);
                                    else
                                        strcat(origem, evento.text.text);
                                }
                            }else{
                                if(strlen(destino)<9){
                                    if(destino[0]==' ')
                                        strcpy(destino, evento.text.text);
                                    else
                                        strcat(destino, evento.text.text);
                                }
                            }
                        }
					}
				}

                superficieTexto=TTF_RenderText_Solid(fonte, nome, corTexto);
                objeto.x=360;
                objeto.y=120;
                objeto.w=superficieTexto->w;
                objeto.h=superficieTexto->h;
                SDL_BlitScaled(superficieTexto, NULL, superficie, &objeto);
                superficieTexto=TTF_RenderText_Solid(fonte, desc, corTexto);
                objeto.x=370;
                objeto.y=200;
                objeto.w=superficieTexto->w;
                objeto.h=superficieTexto->h;
                SDL_BlitScaled(superficieTexto, NULL, superficie, &objeto);
                superficieTexto=TTF_RenderText_Solid(fonte, origem, corTexto);
                objeto.x=420;
                objeto.y=280;
                objeto.w=superficieTexto->w;
                objeto.h=superficieTexto->h;
                SDL_BlitScaled(superficieTexto, NULL, superficie, &objeto);
                superficieTexto=TTF_RenderText_Solid(fonte, destino, corTexto);
                objeto.x=420;
                objeto.y=360;
                objeto.w=superficieTexto->w;
                objeto.h=superficieTexto->h;
                SDL_BlitScaled(superficieTexto, NULL, superficie, &objeto);

				SDL_UpdateWindowSurface(janela);
            }while((opcaoAdicionar!=0)&&(sair!=1));//volta aonde tava
            if(opcaoMenu==12)
                opcaoMenu=3;
            else
                opcaoMenu=2;
            for(i=1; i<10; i++){
                nome[i]=NULL;
                desc[i]=NULL;
                origem[i]=NULL;
                destino[i]=NULL;
            }
            nome[0]=' ';
            desc[0]=' ';
            origem[0]=' ';
            destino[0]=' ';
        }

        SDL_UpdateWindowSurface(janela);
	}while(sair!=1);

	SDL_FreeSurface(intro);//free nas surfaces
	SDL_FreeSurface(menu);
	SDL_FreeSurface(seta1);
	SDL_FreeSurface(seta2);
	SDL_FreeSurface(adicionar);
	SDL_FreeSurface(visualizar);
	SDL_FreeSurface(autorizar);
	if(um==1)
        SDL_FreeSurface(superficieTexto);
	Mix_FreeChunk(somIntro);
	Mix_FreeChunk(somAviao);
	TTF_CloseFont(fonte);
	SDL_DestroyWindow(janela);//free na janela e na surface dela
	TTF_Quit();
	IMG_Quit();
    Mix_Quit();
    SDL_Quit();
    return 0;
}
