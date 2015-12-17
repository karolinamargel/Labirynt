#include<allegro5\allegro.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5\allegro_font.h>
#include<allegro5\allegro_ttf.h>
#include<allegro5\allegro_native_dialog.h>
#include<allegro5\allegro_image.h>
#include<fstream>

#define RozmiarBloku 16
//definiowanie kolorow
#define czerwony al_map_rgb(255,0,0)
#define bordowy al_map_rgb(128,0,0)
#define pomaranczowy al_map_rgb(255,165,0)
#define zolty al_map_rgb(255,255,0)
#define zielony al_map_rgb(0,255,0)
#define niebieski al_map_rgb(0,0,255)
#define fioletowy al_map_rgb(128,0,128)
#define rozowy al_map_rgb(255,20,147)
#define roz al_map_rgb(255,0,255)
#define blekitny al_map_rgb(0,255,255)
#define granatowy al_map_rgb(0,0,128)
#define bialy al_map_rgb(255,255,255)
#define czarny al_map_rgb(0,0,0)
//kolory przezroczyste
#define niebieski1 al_map_rgba_f(0, 0, 255,0.3)
#define czerwony1 al_map_rgba_f(255,0,0,0.05)
#define bordowy1 al_map_rgba_f(128,0,0,0.3)
#define pomaranczowy1 al_map_rgba_f(255,165,0,0.3)
#define zolty1 al_map_rgba_f(255,255,0,0.3)
#define zielony1 al_map_rgba_f(0,255,0,0.01)
#define fioletowy1 al_map_rgba_f(128,0,128,0.3)
#define rozowy1 al_map_rgba_f(255,20,147,0.3)
#define roz1 al_map_rgba_f(255,0,255,0.3)
#define blekitny1 al_map_rgba_f(0,255,255,0.3)
#define granatowy1 al_map_rgba_f(0,0,128,0.3)
#define bialy1 al_map_rgba_f(255,255,255,0.3)
#define czarny1 al_map_rgba_f(0,0,0,0.3)

int licznikX = 0, licznikY = 0, rozmiarX, rozmiarY;
int mapa1[40][30];
int mapa2[40][30];  
int mapa3[40][30];  

void WczytajMape(const char *nazwa, int mapa[][30]){
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

void RysujMape(int mapa[][30], ALLEGRO_COLOR kolor_tlo, ALLEGRO_COLOR kolor_lab);

int main(void)
{
	int width = 640;
	int height = 480;
	int pos_x = 65;
	int pos_y = 265;

	bool done = false;
	bool redraw = true;

	int FPS = 60;
	int wroc = 0;
	int licz = 0;
	int pozycja = 1; //1-menu, 2-gra, 3-wybor planszy, 4-pomoc

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
	ALLEGRO_BITMAP *plansza1 = al_load_bitmap("grafika/plansza1.jpg");
	ALLEGRO_BITMAP *plansza2 = al_load_bitmap("grafika/plansza2.jpg");
	ALLEGRO_BITMAP *plansza3 = al_load_bitmap("grafika/plansza3.jpg");
	ALLEGRO_BITMAP *pomoc = al_load_bitmap("grafika/pomoc.jpg");
	ALLEGRO_BITMAP *plansza2_tlo = al_load_bitmap("grafika/tlo2.jpg");
	ALLEGRO_BITMAP *plansza3_tlo = al_load_bitmap("grafika/tlo3.jpg");
	WczytajMape("plansze/plansza1.txt", mapa1);
	WczytajMape("plansze/plansza2.txt", mapa2); 
	WczytajMape("plansze/plansza3.txt", mapa3);

	timer = al_create_timer(1.0 / FPS);
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source()); 
	al_register_event_source(event_queue, al_get_mouse_event_source());
	
	al_start_timer(timer);

	while (!done){
		if (redraw){
			pozycja = 1;
			redraw = false;
		}

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE){
			if (wroc == 1){
				redraw = true;
				wroc = 0;
			}
		}
		if (ev.type == ALLEGRO_EVENT_KEY_UP && ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			done = true;

		//EVENTY - MENU
		//start gry
		if (ev.mouse.x >= 130 && ev.mouse.x <= 300 && ev.mouse.y >= 200 && ev.mouse.y <= 230 && ev.mouse.button == 1 && pozycja == 1){
			pozycja = 2;
			wroc = 1;
		}
		//wybor planszy
		else if (ev.mouse.x >= 130 && ev.mouse.x <= 300 && ev.mouse.y >= 230 && ev.mouse.y <= 260 && ev.mouse.button == 1 && pozycja == 1){
			pozycja = 3;
			wroc = 1;
		}
		//pomoc
		else if (ev.mouse.x >= 130 && ev.mouse.x <= 200 && ev.mouse.y >= 260 && ev.mouse.y <= 290 && ev.mouse.button == 1 && pozycja == 1){
			pozycja = 4;
			wroc = 1;
		}
		//wyjscie z gry
		else if (ev.mouse.x >= 130 && ev.mouse.x <= 300 && ev.mouse.y >= 290 && ev.mouse.y <= 320 && ev.mouse.button == 1 && pozycja == 1){
			done = true;
		}

		//EVENTY - WYBOR PLANSZY
		//plansza #1
		else if (ev.mouse.x >= 30 && ev.mouse.x <= 158 && ev.mouse.y >= 50 && ev.mouse.y <= 171 && ev.mouse.button == 1 && pozycja == 3){
			pozycja = 2;
			wroc = 1;
		}
		//plansza #2
		else if (ev.mouse.x >= 180 && ev.mouse.x <= 308 && ev.mouse.y >= 50 && ev.mouse.y <= 171 && ev.mouse.button == 1 && pozycja == 3){
			pozycja = 5;
			wroc = 1;
		}
		//plansza #3
		else if (ev.mouse.x >= 330 && ev.mouse.x <= 458 && ev.mouse.y >= 50 && ev.mouse.y <= 171 && ev.mouse.button == 1 && pozycja == 3){
			pozycja = 6;
			wroc = 1;
		}
		//plansza #4
		else if (ev.mouse.x >= 480 && ev.mouse.x <= 608 && ev.mouse.y >= 50 && ev.mouse.y <= 171 && ev.mouse.button == 1 && pozycja == 3){
			pozycja = 2;
			wroc = 1;
		}
		//plansza #5
		else if (ev.mouse.x >= 30 && ev.mouse.x <= 158 && ev.mouse.y >= 190 && ev.mouse.y <= 311 && ev.mouse.button == 1 && pozycja == 3){
			pozycja = 2;
			wroc = 1;
		}
		//plansza #6
		else if (ev.mouse.x >= 180 && ev.mouse.x <= 308 && ev.mouse.y >= 190 && ev.mouse.y <= 311 && ev.mouse.button == 1 && pozycja == 3){
			pozycja = 2;
			wroc = 1;
		}
		//plansza #7
		else if (ev.mouse.x >= 330 && ev.mouse.x <= 458 && ev.mouse.y >= 190 && ev.mouse.y <= 311 && ev.mouse.button == 1 && pozycja == 3){
			pozycja = 2;
			wroc = 1;
		}
		//plansza #8
		else if (ev.mouse.x >= 480 && ev.mouse.x <= 608 && ev.mouse.y >= 190 && ev.mouse.y <= 311 && ev.mouse.button == 1 && pozycja == 3){
			pozycja = 2;
			wroc = 1;
		}
		//plansza #9
		else if (ev.mouse.x >= 30 && ev.mouse.x <= 158 && ev.mouse.y >= 330 && ev.mouse.y <= 451 && ev.mouse.button == 1 && pozycja == 3){
			pozycja = 2;
			wroc = 1;
		}
		//plansza #10
		else if (ev.mouse.x >= 180 && ev.mouse.x <= 308 && ev.mouse.y >= 330 && ev.mouse.y <= 451 && ev.mouse.button == 1 && pozycja == 3){
			pozycja = 2;
			wroc = 1;
		}
		//plansza #11
		else if (ev.mouse.x >= 330 && ev.mouse.x <= 458 && ev.mouse.y >= 330 && ev.mouse.y <= 451 && ev.mouse.button == 1 && pozycja == 3){
			pozycja = 2;
			wroc = 1;
		}
		//plansza #12
		else if (ev.mouse.x >= 480 && ev.mouse.x <= 608 && ev.mouse.y >= 330 && ev.mouse.y <= 45 && ev.mouse.button == 1 && pozycja == 3){
			pozycja = 2;
			wroc = 1;
		}
		//RYSOWANIE
		//menu
		if (pozycja == 1){
			al_draw_bitmap(menu, 0, 0, 0);
			al_draw_textf(font, al_map_rgb(26, 255, 241), 130, 100, 0, "LABIRYNT");
			al_draw_textf(font1, al_map_rgb(26, 255, 241), 130, 200, 0, "Start gry");
			al_draw_textf(font1, al_map_rgb(26, 255, 241), 130, 230, 0, "Wybor planszy");
			al_draw_textf(font1, al_map_rgb(26, 255, 241), 130, 260, 0, "Pomoc");
			al_draw_textf(font1, al_map_rgb(26, 255, 241), 130, 290, 0, "Wyjscie z gry");
		}
		//gra-pierwsza plansza
		else if (pozycja == 2){
			al_draw_bitmap(plansza01, 0, 0, 0);
			RysujMape(mapa1,niebieski1,zielony);
			al_draw_textf(font2, al_map_rgb(26, 255, 241), 5, 250, 0, "Start");
			al_draw_textf(font2, al_map_rgb(26, 255, 241), 450, 10, 0, "Meta");
			al_draw_textf(font2, al_map_rgb(26, 255, 241), 10, 10, 0, "Czas: %i", 10);
			al_draw_filled_rectangle(pos_x, pos_y, pos_x + 10, pos_y + 10, al_map_rgb(255, 0, 0));
		}
		//wybor planszy
		else if (pozycja == 3){
			al_draw_bitmap(wybor_planszy, 0, 0, 0);
			al_draw_textf(font1, al_map_rgb(26, 255, 241), 220, 10, 0, "Wybierz plansze");
			al_draw_bitmap(plansza1, 30, 50, 0);
			al_draw_bitmap(plansza2, 180, 50, 0);
			al_draw_bitmap(plansza3, 330, 50, 0);
			al_draw_bitmap(plansza1, 480, 50, 0);
			al_draw_bitmap(plansza1, 30, 190, 0);
			al_draw_bitmap(plansza1, 180, 190, 0);
			al_draw_bitmap(plansza1, 330, 190, 0);
			al_draw_bitmap(plansza1, 480, 190, 0);
			al_draw_bitmap(plansza1, 30, 330, 0);
			al_draw_bitmap(plansza1, 180, 330, 0);
			al_draw_bitmap(plansza1, 330, 330, 0);
			al_draw_bitmap(plansza1, 480, 330, 0);
		}
		//pomoc
		else if (pozycja == 4){
			al_draw_bitmap(pomoc, 0, 0, 0);
			al_draw_textf(font1, al_map_rgb(40, 200, 200), 275, 10, 0, "Pomoc");
			al_draw_textf(font1, al_map_rgb(40, 200, 200), 20, 275, 0, "Wyjscie");
			al_draw_textf(font1, al_map_rgb(40, 200, 200), 500, 272, 0, "Powrot");
			al_draw_textf(font1, al_map_rgb(40, 200, 200), 230, 260, 0, "Poruszanie sie");
		}
		//druga plansza
		else if (pozycja == 5){
			al_draw_bitmap(plansza2_tlo, 0, 0, 0);
			RysujMape(mapa2,czerwony1,zolty);
			al_draw_textf(font2, al_map_rgb(26, 255, 241), 5, 255, 0, "Start");
			al_draw_textf(font2, al_map_rgb(26, 255, 241), 578, 115, 0, "Meta");
			al_draw_textf(font2, al_map_rgb(26, 255, 241), 10, 10, 0, "Czas: %i", 10);
			al_draw_filled_rectangle(pos_x+20, pos_y, pos_x + 30, pos_y + 10, niebieski);
		}
		//trzecia plansza
		else if (pozycja == 6){
			al_draw_bitmap(plansza3_tlo, 0, 0, 0);
			RysujMape(mapa3, zielony1, roz);
			al_draw_textf(font2, al_map_rgb(26, 255, 241), 5, 255, 0, "Start");
			al_draw_textf(font2, al_map_rgb(26, 255, 241), 578, 115, 0, "Meta");
			al_draw_textf(font2, al_map_rgb(26, 255, 241), 10, 10, 0, "Czas: %i", 10);
			al_draw_filled_rectangle(pos_x + 20, pos_y, pos_x + 30, pos_y + 10, niebieski);
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

void RysujMape(int mapa[][30], ALLEGRO_COLOR kolor_tlo, ALLEGRO_COLOR kolor_lab){
	for (int i = 0; i < rozmiarX; i++){
		for (int j = 0; j < rozmiarY; j++){
			if (mapa[i][j] == 0)
				al_draw_filled_rectangle(i*RozmiarBloku, j*RozmiarBloku, i*RozmiarBloku + RozmiarBloku, j*RozmiarBloku + RozmiarBloku, kolor_tlo);
			else 
				al_draw_filled_rectangle(i*RozmiarBloku, j*RozmiarBloku, i*RozmiarBloku + RozmiarBloku, j*RozmiarBloku + RozmiarBloku, kolor_lab);
		}
	}
}