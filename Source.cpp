#include<allegro5\allegro.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5\allegro_font.h>
#include<allegro5\allegro_ttf.h>
#include<allegro5\allegro_native_dialog.h>
#include <allegro5/allegro_image.h>

int main(void)
{
	int width = 640;
	int height = 480;

	bool done = false;

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;


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
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon(); // inicjowanie bitmap, mo¿liwoœci odczytu jak i zapisu bitmap.

	ALLEGRO_BITMAP *bitmapa = al_load_bitmap("lab.jpeg");
	ALLEGRO_FONT *font = al_load_font("FORTE.TTF", 80, 0);
	ALLEGRO_FONT *font1 = al_load_font("FORTE.TTF", 30, 0);

	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	while (!done){
		al_draw_bitmap(bitmapa, 0, 0, 0);
		al_draw_textf(font, al_map_rgb(26, 255, 241), 130, 100, 0, "LABIRYNT");
		al_draw_textf(font1, al_map_rgb(26, 255, 241), 130, 200, 0, "Start gry");
		al_draw_textf(font1, al_map_rgb(26, 255, 241), 130, 230, 0, "Wybor planszy");
		al_draw_textf(font1, al_map_rgb(26, 255, 241), 130, 260, 0, "Pomoc");
		al_draw_textf(font1, al_map_rgb(26, 255, 241), 130, 290, 0, "Wyjscie z gry");
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_UP&&ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			done = true;
	}

	if (!bitmapa) {
		al_show_native_message_box(display, "B³¹d", "Coœ nie tak",
			"Nie mogê wczytaæ bitmapy !", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	} // sprawdzenie czy bitmapa zosta³a poprawnie wczytana.


	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	al_destroy_bitmap(bitmapa);

	return 0;
}