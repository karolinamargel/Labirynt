#include<allegro5\allegro.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5\allegro_font.h>
#include<allegro5\allegro_ttf.h>
#include<allegro5\allegro_native_dialog.h>
#include<allegro5\allegro_image.h>
#include<fstream>

#define RozmiarBloku 16

int licznikX = 0, licznikY = 0, rozmiarX, rozmiarY;
int mapa[100][100];
int mapa1[100][100];  //????
int mapa2[100][100];  //????

void WczytajMape(const char *nazwa, int mapa[][100]){
	std::ifstream openfile(nazwa);
	if (openfile.is_open()){
		openfile >> rozmiarX >> rozmiarY;
		while (!openfile.eof()){
			openfile >> mapa[licznikX][licznikY];
			licznikX++;

			if (licznikX >= rozmiarX){
				licznikX = 0;
				licznikY++;
			}
		}
	}
	else{

	}
}

void RysujMape(int mapa[][100]);

int main(void)
{
	int width = 640;
	int height = 480;
	int pos_x = 65;
	int pos_y = 265;

	bool done = false;
	bool redraw = true;
	bool eventy = true;

	int FPS = 60;
	int wroc = 0;
	int licz = 0;

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

	ALLEGRO_BITMAP *menu = al_load_bitmap("grafika/lab.jpeg");
	ALLEGRO_FONT *font = al_load_font("czcionki/FORTE.TTF", 80, 0);
	ALLEGRO_FONT *font1 = al_load_font("czcionki/FORTE.TTF", 30, 0);
	ALLEGRO_FONT *font2 = al_load_font("czcionki/FORTE.TTF", 25, 0);
	ALLEGRO_BITMAP *plansza01 = al_load_bitmap("grafika/lab00.jpg");
	ALLEGRO_BITMAP *wybor_planszy = al_load_bitmap("grafika/tlo1.jpg");
	ALLEGRO_BITMAP *wybor_planszy1 = al_load_bitmap("grafika/plansza1.jpg");
	ALLEGRO_BITMAP *pomoc = al_load_bitmap("grafika/pomoc.jpg");
	WczytajMape("plansze/plansza1.txt", mapa);
	//WczytajMape("plansze/plansza2.txt", mapa1); 

	timer = al_create_timer(1.0 / FPS);
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source()); 
	al_register_event_source(event_queue, al_get_mouse_event_source());
	
	al_start_timer(timer);

	while (!done){
		if (redraw){
			al_draw_bitmap(menu, 0, 0, 0);
			al_draw_textf(font, al_map_rgb(26, 255, 241), 130, 100, 0, "LABIRYNT");
			al_draw_textf(font1, al_map_rgb(26, 255, 241), 130, 200, 0, "Start gry");
			al_draw_textf(font1, al_map_rgb(26, 255, 241), 130, 230, 0, "Wybor planszy");
			al_draw_textf(font1, al_map_rgb(26, 255, 241), 130, 260, 0, "Pomoc");
			al_draw_textf(font1, al_map_rgb(26, 255, 241), 130, 290, 0, "Wyjscie z gry");
			al_flip_display();
			redraw = false;
		}

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE){
			if (wroc == 1){
				redraw = true;
				eventy = true;
				wroc = 0;
			}
		}
		if (ev.type == ALLEGRO_EVENT_KEY_UP && ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			done = true;

		if (eventy){
			//start gry
			if (ev.mouse.x >= 130 && ev.mouse.x <= 300 && ev.mouse.y >= 200 && ev.mouse.y <= 230 && ev.mouse.button == 1){
				al_draw_bitmap(plansza01, 0, 0, 0);
				RysujMape(mapa);
				al_draw_textf(font2, al_map_rgb(26, 255, 241), 5, 250, 0, "Start");
				al_draw_textf(font2, al_map_rgb(26, 255, 241), 450, 10, 0, "Meta");
				al_draw_textf(font2, al_map_rgb(26, 255, 241), 10, 10, 0, "Czas: %i", licz);
				al_draw_filled_rectangle(pos_x, pos_y, pos_x + 10, pos_y + 10, al_map_rgb(255, 0, 0));
				wroc = 1;
				eventy = false;
				licz++;
				al_flip_display();
			}
			//wybor planszy
			else if (ev.mouse.x >= 130 && ev.mouse.x <= 300 && ev.mouse.y >= 230 && ev.mouse.y <= 260 && ev.mouse.button == 1){
				ALLEGRO_EVENT ev;
				al_wait_for_event(event_queue, &ev);

				al_draw_bitmap(wybor_planszy, 0, 0, 0);
				al_draw_textf(font1, al_map_rgb(26, 255, 241), 220, 10, 0, "Wybierz plansze");
				al_draw_bitmap(wybor_planszy1, 30, 50, 0);
				al_draw_bitmap(wybor_planszy1, 180, 50, 0);
				al_draw_bitmap(wybor_planszy1, 330, 50, 0);
				al_draw_bitmap(wybor_planszy1, 480, 50, 0);
				al_draw_bitmap(wybor_planszy1, 30, 190, 0);
				al_draw_bitmap(wybor_planszy1, 180, 190, 0);
				al_draw_bitmap(wybor_planszy1, 330, 190, 0);
				al_draw_bitmap(wybor_planszy1, 480, 190, 0);
				al_draw_bitmap(wybor_planszy1, 30, 330, 0);
				al_draw_bitmap(wybor_planszy1, 180, 330, 0);
				al_draw_bitmap(wybor_planszy1, 330, 330, 0);
				al_draw_bitmap(wybor_planszy1, 480, 330, 0);
				eventy = false;
				wroc = 1;
				al_flip_display();

			}
			//pomoc
			else if (ev.mouse.x >= 130 && ev.mouse.x <= 200 && ev.mouse.y >= 260 && ev.mouse.y <= 290 && ev.mouse.button == 1){
				al_draw_bitmap(pomoc, 0, 0, 0);
				al_draw_textf(font1, al_map_rgb(40, 200, 200), 275, 10, 0, "Pomoc");
				al_draw_textf(font1, al_map_rgb(40, 200, 200), 20, 275, 0, "Wyjscie");
				al_draw_textf(font1, al_map_rgb(40, 200, 200), 500, 272, 0, "Powrot");
				al_draw_textf(font1, al_map_rgb(40, 200, 200), 230, 260, 0, "Poruszanie sie");
				wroc = 1;
				eventy = false;
				al_flip_display();
			}
			//wyjscie z gry
			else if (ev.mouse.x >= 130 && ev.mouse.x <= 300 && ev.mouse.y >= 290 && ev.mouse.y <= 320 && ev.mouse.button == 1){
				done = true;
				eventy = false;
			}
		}

		al_flip_display();
	}

	if (!menu) {
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
	al_destroy_bitmap(menu); 

	return 0;
}

void RysujMape(int mapa[][100]){
	for (int i = 0; i < rozmiarX; i++){
		for (int j = 0; j < rozmiarY; j++){
			if (mapa[i][j] == 0)
				al_draw_filled_rectangle(i*RozmiarBloku, j*RozmiarBloku, i*RozmiarBloku + RozmiarBloku, j*RozmiarBloku + RozmiarBloku, al_map_rgba_f(0, 0, 255, 0.3));
			else
				al_draw_filled_rectangle(i*RozmiarBloku, j*RozmiarBloku, i*RozmiarBloku + RozmiarBloku, j*RozmiarBloku + RozmiarBloku, al_map_rgb(0, 255, 0));
		}
	}
}