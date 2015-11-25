#include<allegro5\allegro.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5\allegro_font.h>
#include<allegro5\allegro_ttf.h>
#include<allegro5\allegro_native_dialog.h>
#include<allegro5\allegro_image.h>

int main(void)
{
	int width = 640;
	int height = 480;

	bool done = false;
	int pos_x = width / 2;
	int pos_y = height / 2;
	int FPS = 60;

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	if (!al_init()){
		al_show_native_message_box(NULL, NULL, NULL, "failed to initialize allegro!", NULL, NULL);
		return -1;
	}

	display = al_create_display(width, height);

	if (!display){
		al_show_native_message_box(NULL, NULL, NULL, "failed to initialize allegro!", NULL, NULL);
		return -1;
	}

	al_init_primitives_addon();
	al_install_keyboard(); 
	al_install_mouse();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon(); 

	ALLEGRO_BITMAP *bitmapa = al_load_bitmap("lab.jpeg");
	ALLEGRO_FONT *font = al_load_font("FORTE.TTF", 80, 0);
	ALLEGRO_FONT *font1 = al_load_font("FORTE.TTF", 30, 0);
	ALLEGRO_BITMAP *plansza01 = al_load_bitmap("lab00.jpg");

	timer = al_create_timer(1.0 / FPS);
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source()); 
	al_register_event_source(event_queue, al_get_mouse_event_source());
	
	al_start_timer(timer);

	while (!done){
		al_draw_bitmap(bitmapa, 0, 0, 0); 
		al_draw_textf(font, al_map_rgb(26, 255, 241), 130, 100, 0, "LABIRYNT");
		al_draw_textf(font1, al_map_rgb(26, 255, 241), 130, 200, 0, "Start gry");
		al_draw_textf(font1, al_map_rgb(26, 255, 241), 130, 230, 0, "Wybor planszy");
		al_draw_textf(font1, al_map_rgb(26, 255, 241), 130, 260, 0, "Pomoc");
		al_draw_textf(font1, al_map_rgb(26, 255, 241), 130, 290, 0, "Wyjscie z gry");
		
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_UP && ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
			done = true;
		}
		//start gry
		else if (ev.mouse.x >= 130 && ev.mouse.x <= 300 && ev.mouse.y >= 200 && ev.mouse.y <= 230 && ev.mouse.button == 1){
			al_destroy_bitmap(bitmapa);
			al_draw_bitmap(plansza01,0,0,0);
			al_wait_for_event(event_queue, &ev);
			al_destroy_bitmap(plansza01);
		}
		//wybor planszy
		else if (ev.mouse.x >= 130 && ev.mouse.x <= 300 && ev.mouse.y >= 230 && ev.mouse.y <= 260 && ev.mouse.button == 1){
			
		}
		//pomoc
		else if (ev.mouse.x >= 130 && ev.mouse.x <= 200 && ev.mouse.y >= 260 && ev.mouse.y <= 290 && ev.mouse.button == 1){
			
		}
		//wyjscie z gry
		else if (ev.mouse.x >= 130 && ev.mouse.x <= 300 && ev.mouse.y >= 290 && ev.mouse.y <= 320 && ev.mouse.button == 1)
			done = true;

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}

	if (!bitmapa) {
		al_show_native_message_box(display, "Blad", NULL,
			"Nie moge wczytac bitmapy !", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	} 
	if (!plansza01) {
		al_show_native_message_box(display, "Blad", NULL,
			"Nie moge wczytac bitmapy !", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}

	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	al_destroy_bitmap(bitmapa); 

	return 0;
}