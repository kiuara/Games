#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#define HEIGHT 960
#define WIDTH 540
#define MAX_LETTER 4
#define SIZE_NAME_DECK 50
#define ERRO 0
#define SUCCESSFUL 1
#define IMAGE_SIZE_X 240
#define IMAGE_SIZE_Y 393

// ======================================Funcoes DE FILAS===================================
typedef struct
{
	int id;
	int attack;
	int defense;
		
}tLetter;

typedef struct
{
	int start;
	int end;
	char  name[SIZE_NAME_DECK];
	tLetter letter[MAX_LETTER];
}tDeck;

typedef struct
{
	int  life; 
	char  name[SIZE_NAME_DECK];
	tDeck deck;
}tPlayer;

void start(tDeck* deck)
{
	deck->start = -1;
	deck->end = -1;
}

int next_deck()
{
	
}

tLetter get_letter(int id,int attack,int defense)
{
		tLetter letter;
		letter.id = id;
		letter.attack = attack;
		letter.defense = defense;
		
		return letter;
}

int insert_letter(tDeck* Decks, tLetter letter)
{
	int position = (Decks->end+1) % MAX_LETTER;
	
	if(position == Decks->start)
	{
		fprintf(stderr,"Fila cheia\n");
		return ERRO;
	}
	
	if(Decks->start == -1)
	{
		Decks->start += 1;
	}
	
	Decks->end = position;
	Decks->letter[Decks->end] = letter;
	return SUCCESSFUL;
}

void set_deck(char* nome,tDeck* deck)
{

	FILE* file = fopen(nome,"r");
	
	int line_position = 0;
    char line[100];
    
    int id;
    int attack;
    int defense;
    
	fgets(line,100,file);
	do{
		
		sscanf(strtok(line,";"),"%d",&id);

		sscanf(strtok(NULL,";"),"%d",&attack);
	
		sscanf(strtok(NULL,";"),"%d",&defense);
	
		++line_position;
		fgets(line,100,file);	
		
		insert_letter(deck,get_letter(id,attack,defense));	
		
	}while(line_position < MAX_LETTER );		
}

// ======================================Funcoes DE JANELAS===================================
ALLEGRO_DISPLAY* window(ALLEGRO_DISPLAY *home_screen)
{
	if (!al_init())
  	{
    	fprintf(stderr, "Falha ao inicializar a Allegro.\n");
 	}
 
	home_screen = al_create_display(HEIGHT, WIDTH);
	if(!home_screen)
	 {
		fprintf(stderr,"Falha ao abrir janela 'home_screen' !!\n");
	 }
	
	if(!al_init_image_addon())
  	{
  		fprintf(stderr,"Problema no addon !!\n");
  	}
  	
  	if(!al_install_mouse())
	{
		fprintf(stderr,"Problema ao adicionar mouse !!\n");
  		al_destroy_display(home_screen);
	}
  	
	  //SO PODE SETAR CURSOR SE TIVER INICIALIZADO A JANELA
  	if (!al_set_system_mouse_cursor(home_screen, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
  	{
   		fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
    	al_destroy_display(home_screen);
  	} 
	 return home_screen;
}
 
int home(ALLEGRO_DISPLAY* home_screen){
	  
  	
  	ALLEGRO_BITMAP *image_home_screen 	= NULL;
  	ALLEGRO_BITMAP *image_play_home 	= NULL;
    ALLEGRO_EVENT_QUEUE *queue 			= NULL;
	int play = 0;
    
  	
  	al_set_window_title(home_screen,"Yu-Gi-Oh!");
  	
	 
  	image_home_screen  = al_load_bitmap("bg.jpg");
	if(!image_home_screen)
	 {
		fprintf(stderr,"Falha ao abrir Image 'image_home_screen' !!\n");
		al_destroy_display(home_screen);
  		return -1;	 	
	 }
	 
  	image_play_home = al_load_bitmap("play.png");
 	if(!image_play_home)
	 {
		fprintf(stderr,"Falha ao abrir Image 'image_play_home' !!\n");
		al_destroy_bitmap(image_home_screen);
		al_destroy_display(home_screen);
  		return -1;	 	
	 }
  	
	queue = al_create_event_queue();
	if(!queue)
	{
		fprintf(stderr,"Falha ao tentar criar uma Fila de eventos 'queue'");
		al_destroy_bitmap(image_play_home);
		al_destroy_bitmap(image_home_screen);
		al_destroy_display(home_screen);
  		return -1;	 	
	}
	
	//coloca na fila as acoes do mouse
	al_register_event_source(queue,al_get_mouse_event_source());

 	al_draw_bitmap(image_home_screen ,0, 0, 0);
  	al_draw_bitmap(image_play_home ,104, 386, 0);
 
	
	while(!play)
	{
			while(!al_is_event_queue_empty(queue))
			{
				ALLEGRO_EVENT event;
				al_wait_for_event(queue, &event);
				
				if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
				{
					if(event.mouse.x >=104  && event.mouse.x <=(104 + al_get_bitmap_width(image_play_home)/2) && event.mouse.y >=386  && event.mouse.y <= (386+(al_get_bitmap_height(image_play_home)/2)))
					{
						
						play = 1;
					}
					
				}
			}
			 	al_flip_display();
	}
 	al_destroy_bitmap(image_play_home);
	al_destroy_bitmap(image_home_screen);
	al_destroy_event_queue(queue);
	al_clear_to_color(al_map_rgb(0, 0, 0));
  	return 1;
}

int deck(ALLEGRO_DISPLAY* home_screen,tDeck* deck)
{
	ALLEGRO_EVENT_QUEUE *queue 	= NULL;
	ALLEGRO_BITMAP* logo 		= NULL;
	ALLEGRO_BITMAP* deck1 		= NULL;
	ALLEGRO_BITMAP* deck2 		= NULL;
	ALLEGRO_BITMAP* deck3 		= NULL;
	ALLEGRO_BITMAP* deck4 		= NULL;
	
	int play=0;
  	
	  //SO PODE SETAR CURSOR SE TIVER INICIALIZADO A JANELA
  	
	logo  = al_load_bitmap("logo.jpg");
	
	if(!logo)
	 {
		fprintf(stderr,"Falha ao abrir logo !!\n");
		al_destroy_display(home_screen);
  		return -1;	 	
	 }
	
	deck1  = al_load_bitmap("kaiba.png");
	if(!deck1)
	 {
		fprintf(stderr,"Falha ao abrir deck !!\n");
		al_destroy_display(home_screen);
  		return -1;	 	
	 }
	 
	deck2  = al_load_bitmap("yugi.png");
	if(!deck2)
	 {
		fprintf(stderr,"Falha ao abrir deck !!\n");
		printf("erro 1: %d\n", deck2);
		al_destroy_display(home_screen);
  		return -1;	 	
	 }
	
	deck3  = al_load_bitmap("joey.png");
	if(!deck3)
	 {
		fprintf(stderr,"Falha ao abrir deck !!\n");
		printf("erro 2: %d\n", deck3);
		al_destroy_display(home_screen);
  		return -1;	 	
	 }
	deck4  = al_load_bitmap("marik.png");
	if(!deck4)
	 {
		fprintf(stderr,"Falha ao abrir deck !!\n");
		printf("erro 3: %d\n", deck4);
		al_destroy_display(home_screen);
  		return -1;	 	
	 }
	 
	al_set_window_title(home_screen,"Yu-Gi-Oh! -> SELECIONE O DECK REFERENTE AO PERSSONAGEM");
  	
	queue = al_create_event_queue();
	if(!queue)
	{
		fprintf(stderr,"Falha ao tentar criar uma Fila de eventos 'queue'");
		al_destroy_display(home_screen);
  		return -1;	 	
	}
	
	//coloca na fila as acoes do mouse
	al_register_event_source(queue,al_get_mouse_event_source());
  	
  	al_draw_bitmap(logo,0,394,0);
	al_draw_bitmap(deck1,0,0,0);
	al_draw_bitmap(deck2,IMAGE_SIZE_X,0,0);
	al_draw_bitmap(deck3,2*IMAGE_SIZE_X,0,0);
	al_draw_bitmap(deck4,3*IMAGE_SIZE_X,0,0);
	al_flip_display();
	  
	 while(!play)
	{
			while(!al_is_event_queue_empty(queue))
			{
				ALLEGRO_EVENT event;
				al_wait_for_event(queue, &event);
				
				if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
				{
					if(event.mouse.x >=0  && event.mouse.x <=IMAGE_SIZE_X && event.mouse.y >=0  && event.mouse.y <= IMAGE_SIZE_Y)
					{
						play = 1;
						strcpy(deck->name,"kaiba");
						set_deck("test.csv",deck);
					}else if(event.mouse.x >IMAGE_SIZE_X && event.mouse.x <= 2*IMAGE_SIZE_X && event.mouse.y >=0  && event.mouse.y <= IMAGE_SIZE_Y)
					{
						play = 1;
						strcpy(deck->name,"yugi");
						set_deck("yugi.csv",deck);
					}else if(event.mouse.x >2*IMAGE_SIZE_X && event.mouse.x <= 3*IMAGE_SIZE_X && event.mouse.y >=0  && event.mouse.y <= IMAGE_SIZE_Y)
					{
						play = 1;
						strcpy(deck->name,"joey");
						set_deck("joey.csv",deck);
					}else if(event.mouse.x >3*IMAGE_SIZE_X && event.mouse.x <= 4*IMAGE_SIZE_X && event.mouse.y >=0  && event.mouse.y <= IMAGE_SIZE_Y)
					{
						play = 1;
						strcpy(deck->name,"marik");
						set_deck("marik.csv",deck);
					}
					
				}
			}
			 	al_flip_display();
	}
	al_destroy_bitmap(deck1);
	al_destroy_bitmap(deck2);
	al_destroy_bitmap(deck3);
	al_destroy_bitmap(deck4);
	al_destroy_bitmap(logo);
	al_destroy_event_queue(queue);
	return SUCCESSFUL;
}
//======================================FUNCAO GAME===================================
void init_game(tPlayer* player,tDeck deck)
{
	player->life = 4000;
	player->deck = deck;
}

// ======================================FUNCAO MAIN===================================

int main(void)
{
	ALLEGRO_DISPLAY *home_screen = NULL; // janela DEFAULT para tudo, o que mudamos � apenas o conteudo que ser� apresentado
	home_screen = window(home_screen);
	
	tDeck deck1,deck2;
	start(&deck1);
	
	int play = home(home_screen);
	int p1 = deck(home_screen,&deck1);
	int p2 = deck(home_screen,&deck2);
	
	tPlayer	player1,player2;
	init_game(&player1,deck1);
	init_game(&player2,deck2);

	
	
	al_set_window_title(home_screen,"Yu-Gi-Oh! -> Game");
	ALLEGRO_BITMAP* game	= NULL;
}
