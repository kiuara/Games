#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdbool.h>
 
 
int main(void)
{
	
	bool pressed_keys[ALLEGRO_KEY_MAX];
  ALLEGRO_DISPLAY *janela = NULL;
  ALLEGRO_BITMAP *imagem = NULL;
  ALLEGRO_BITMAP *imagem2 = NULL;
  
  al_init();
  al_init_image_addon();
 
  janela = al_create_display(960, 540);
  imagem = al_load_bitmap("bg.jpg");
  imagem2 = al_load_bitmap("play.png");
 
  al_draw_bitmap(imagem, 0, 0, 0);
  al_draw_bitmap(imagem2, 50, 20, 30);
  // Atualiza a tela
  al_flip_display();
 
  // Segura a execução por 10 segundos
  while(!pressed_keys[ALLEGRO_KEY_SPACE]){
  	
  }
 
  // Finaliza a janela
  al_destroy_display(janela);
 
  return 0;
}
