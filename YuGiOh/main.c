#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#define HEIGHT 960
#define WIDTH 540
#define MAX_LETTER 4
#define ERRO 0
#define SUCCESSFUL 1

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
	
	tLetter letter[MAX_LETTER];
}tDeck;


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
	 
	 return home_screen;
}
 
int home(ALLEGRO_DISPLAY* home_screen){
	  
  	
  	ALLEGRO_BITMAP *image_home_screen 	= NULL;
  	ALLEGRO_BITMAP *image_play_home 	= NULL;
    ALLEGRO_EVENT_QUEUE *queue 			= NULL;
	int play = 0;
    
  	if(!al_init_image_addon())
  	{
  		fprintf(stderr,"Problema no addon !!\n");
  		return -1;	
  	}
  	
  	
  	
  	al_set_window_title(home_screen,"Yu-Gi-Oh!");
  	
	if(!al_install_mouse())
	{
		fprintf(stderr,"Problema ao adicionar mouse !!\n");
  		al_destroy_display(home_screen);
		return -1;	
	}
  	
	  //SO PODE SETAR CURSOR SE TIVER INICIALIZADO A JANELA
  	if (!al_set_system_mouse_cursor(home_screen, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
  	{
   		fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
    	al_destroy_display(home_screen);
		return -1;
  	} 
  	  
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
					if(event.mouse.x >=104  && event.mouse.x <=(104 + al_get_bitmap_height(image_play_home)/2) && event.mouse.y >=386  && event.mouse.y <= (386+(al_get_bitmap_height(image_play_home)/2)))
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
	ALLEGRO_BITMAP* deck1 		= NULL;
	
	int play=0;
	
	if(!al_install_mouse())
	{
		fprintf(stderr,"Problema ao adicionar mouse !!\n");
  		al_destroy_display(home_screen);
		return -1;	
	}
  	
	  //SO PODE SETAR CURSOR SE TIVER INICIALIZADO A JANELA
  	if (!al_set_system_mouse_cursor(home_screen, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
  	{
   		fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
    	al_destroy_display(home_screen);
		return -1;
  	}
	
	deck1  = al_load_bitmap("kaiba.jpg");
	if(!deck1)
	 {
		fprintf(stderr,"Falha ao abrir deck !!\n");
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
  	
	 al_draw_bitmap(deck1,0,0,0);
	 al_flip_display();
	 
	 
	 while(!play)
	{
			while(!al_is_event_queue_empty(queue))
			{
				ALLEGRO_EVENT event;
				al_wait_for_event(queue, &event);
				
				if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
				{
					if(event.mouse.x >=0  && event.mouse.x <=186 && event.mouse.y >=0  && event.mouse.y <= 186)
					{
						
						play = 1;
						set_deck("test.csv",deck);
					}
					
				}
			}
			 	al_flip_display();
	}
	al_destroy_bitmap(deck1);
	al_destroy_event_queue(queue);
	return SUCCESSFUL;
}


// ======================================FUNCAO MAIN===================================
int main(void)
{
	ALLEGRO_DISPLAY *home_screen = NULL; // janela DEFAULT para tudo, o que mudamos é apenas o conteudo que será apresentado
	home_screen = window(home_screen);
	
	tDeck deck1,deck2;	
	start(&deck1);
	
	int play = home(home_screen);
	int deck10 = deck(home_screen,&deck1);
	
	int i;
	for(i=0;i<MAX_LETTER;++i)
	{
		fprintf(stderr,"id:%d  attack:%d  defense:%d\n",deck1.letter[i].id,deck1.letter[i].attack,deck1.letter[i].defense);
	}
	
	

}
