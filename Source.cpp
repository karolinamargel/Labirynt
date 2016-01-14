#include<allegro5\allegro.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5\allegro_font.h>
#include<allegro5\allegro_ttf.h>
#include<allegro5\allegro_native_dialog.h>
#include<allegro5\allegro_image.h>
#include<fstream>
#include<iostream>
#include<allegro5\allegro_color.h>
#include<cmath>

bool Kolizje(float x, float y, float dx, float dy, int szerokosc, int wysokosc){
	if (x + szerokosc < dx || x > dx + szerokosc || y + wysokosc < dy || y > dy + wysokosc){
		//brak kolizji
		return false;
	}
	return true;
}

/* W FUNKCJI MAIN
if(Kolizje(x,y,200,200,32,32)){
if (kierunek == 0) //dol
y -= szybkosc;
else if (kierunek == 1) //prawo
x += szybkosc;
else if (kierunek == 2) //lewo
x -= szybkosc;
else if (kierunek == 3) //gora
y += szybkosc;
}
*/


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
#define niebieski1 al_map_rgba_f(0, 0, 255,0.005)
#define czerwony1 al_map_rgba_f(255,0,0,0.005)
#define bordowy1 al_map_rgba_f(128,0,0,0.005)
#define pomaranczowy1 al_map_rgba_f(255,165,0,0.005)
#define zolty1 al_map_rgba_f(255,255,0,0.0005)
#define zielony1 al_map_rgba_f(0,255,0,0.001)
#define fioletowy1 al_map_rgba_f(128,0,128,0.005)
#define rozowy1 al_map_rgba_f(255,20,147,0.005)
#define roz1 al_map_rgba_f(255,0,255,0.005)
#define blekitny1 al_map_rgba_f(0,255,255,0.005)
#define granatowy1 al_map_rgba_f(0,0,128,0.005)
#define bialy1 al_map_rgba_f(255,255,255,0.005)
#define czarny1 al_map_rgba_f(0,0,0,0.005)

int licznikX = 0, licznikY = 0, rozmiarX, rozmiarY;
int mapa1[40][30];
int mapa2[40][30];
int mapa3[40][30];
int mapa4[40][30];
int mapa5[40][30];
int mapa6[40][30];
int mapa7[40][30];
int mapa8[40][30];
int mapa9[40][30];
int mapa10[40][30];
int mapa11[40][30];
int mapa12[40][30];

void poruszanie(ALLEGRO_EVENT ev,int *pos_x,int *pos_y,int *licz,int szybkosc){
	if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
		switch (ev.keyboard.keycode){
		case ALLEGRO_KEY_DOWN:
			*pos_y += szybkosc;
			*licz++;
			break;
		case ALLEGRO_KEY_UP:
			*pos_y -= szybkosc;
			*licz++;
			break;
		case ALLEGRO_KEY_RIGHT:
			*pos_x += szybkosc;
			*licz++;
			break;
		case ALLEGRO_KEY_LEFT:
			*pos_x -= szybkosc;
			*licz++;
			break;
		}
	}
}

void WczytajMape(const char *nazwa, int mapa[40][30]){
	licznikX = 0;
	licznikY = 0;
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

void RysujMape(int mapa[40][30], ALLEGRO_COLOR kolor_tlo, ALLEGRO_COLOR kolor_lab);

int main(void)
{
	int width = 640;
	int height = 480;
	int szybkosc = 10;
	int stan = NULL;

	bool done = false;
	bool redraw = true;
	bool ruch = true;

	int FPS = 1; // 60
	int wroc = 0;
	int licz1 = 0, licz2 = 0, licz3 = 0, licz4 = 0, licz5 = 0, licz6 = 0, licz7 = 0, licz8 = 0, licz9 = 0, licz10 = 0, licz11 = 0, licz12 = 0;
	int pozycja = 1; //1-menu, 2-gra, 3-wybor planszy, 4-pomoc
	int kierunek = 0; //0-dol, 1-gora, 2-prawo, 3-lewo

	int pos_x1 = 0, pos_y1 = 0, pos_x2 = 0, pos_y2 = 0, pos_x3 = 0, pos_y3 = 0;
	int pos_x4 = 0, pos_y4 = 0, pos_x5 = 0, pos_y5 = 0, pos_x6 = 0, pos_y6 = 0;
	int pos_x7 = 0, pos_y7 = 0, pos_x8 = 0, pos_y8 = 0, pos_x9 = 0, pos_y9 = 0;
	int pos_x10 = 0, pos_y10 = 0, pos_x11 = 0, pos_y11 = 0, pos_x12 = 0, pos_y12 = 0;
	//int x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7, x8, y8, x9, y9, x10, y10, x11, y11, x12, y12;

	//x1 = floor(pos_x1 / 16);
	//y1 = floor(pos_y1 / 16);

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
	ALLEGRO_BITMAP *plansza4 = al_load_bitmap("grafika/plansza4.jpg");
	ALLEGRO_BITMAP *plansza5 = al_load_bitmap("grafika/plansza5.jpg");
	ALLEGRO_BITMAP *plansza6 = al_load_bitmap("grafika/plansza6.jpg");
	ALLEGRO_BITMAP *plansza7 = al_load_bitmap("grafika/plansza7.jpg");
	ALLEGRO_BITMAP *plansza8 = al_load_bitmap("grafika/plansza8.jpg");
	ALLEGRO_BITMAP *plansza9 = al_load_bitmap("grafika/plansza9.jpg");
	ALLEGRO_BITMAP *plansza10 = al_load_bitmap("grafika/plansza10.jpg");
	ALLEGRO_BITMAP *plansza11 = al_load_bitmap("grafika/plansza11.jpg");
	ALLEGRO_BITMAP *plansza12 = al_load_bitmap("grafika/plansza12.jpg");
	ALLEGRO_BITMAP *pomoc = al_load_bitmap("grafika/pomoc.jpg");
	ALLEGRO_BITMAP *plansza2_tlo = al_load_bitmap("grafika/tlo2.jpg");
	ALLEGRO_BITMAP *plansza3_tlo = al_load_bitmap("grafika/tlo3.jpg");
	ALLEGRO_BITMAP *plansza4_tlo = al_load_bitmap("grafika/tlo4.jpg");
	ALLEGRO_BITMAP *plansza5_tlo = al_load_bitmap("grafika/tlo5.jpg");
	ALLEGRO_BITMAP *plansza6_tlo = al_load_bitmap("grafika/tlo6.jpg");
	ALLEGRO_BITMAP *plansza7_tlo = al_load_bitmap("grafika/tlo7.jpg");
	ALLEGRO_BITMAP *plansza8_tlo = al_load_bitmap("grafika/tlo8.jpg");
	ALLEGRO_BITMAP *plansza9_tlo = al_load_bitmap("grafika/tlo9.jpg");
	ALLEGRO_BITMAP *plansza10_tlo = al_load_bitmap("grafika/tlo10.jpg");
	ALLEGRO_BITMAP *plansza11_tlo = al_load_bitmap("grafika/tlo11.jpg");
	ALLEGRO_BITMAP *plansza12_tlo = al_load_bitmap("grafika/tlo12.jpg");
	WczytajMape("plansze/plansza1.txt", mapa1);
	WczytajMape("plansze/plansza2.txt", mapa2); 
	WczytajMape("plansze/plansza3.txt", mapa3);
	WczytajMape("plansze/plansza4.txt", mapa4);
	WczytajMape("plansze/plansza5.txt", mapa5);
	WczytajMape("plansze/plansza6.txt", mapa6);
	WczytajMape("plansze/plansza7.txt", mapa7);
	WczytajMape("plansze/plansza8.txt", mapa8);
	WczytajMape("plansze/plansza9.txt", mapa9);
	WczytajMape("plansze/plansza10.txt", mapa10);
	WczytajMape("plansze/plansza11.txt", mapa11);
	WczytajMape("plansze/plansza12.txt", mapa12);

	timer = al_create_timer(1.0 / FPS);
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source()); 
	al_register_event_source(event_queue, al_get_mouse_event_source());
	
	al_start_timer(timer);

	while (!done){

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
		
		if (redraw){
			pozycja = 1;
			redraw = false;
		}

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
			pozycja = 7;
			wroc = 1;
		}
		//plansza #5
		else if (ev.mouse.x >= 30 && ev.mouse.x <= 158 && ev.mouse.y >= 190 && ev.mouse.y <= 311 && ev.mouse.button == 1 && pozycja == 3){
			pozycja = 8;
			wroc = 1;
		}
		//plansza #6
		else if (ev.mouse.x >= 180 && ev.mouse.x <= 308 && ev.mouse.y >= 190 && ev.mouse.y <= 311 && ev.mouse.button == 1 && pozycja == 3){
			pozycja = 9;
			wroc = 1;
		}
		//plansza #7
		else if (ev.mouse.x >= 330 && ev.mouse.x <= 458 && ev.mouse.y >= 190 && ev.mouse.y <= 311 && ev.mouse.button == 1 && pozycja == 3){
			pozycja = 10;
			wroc = 1;
		}
		//plansza #8
		else if (ev.mouse.x >= 480 && ev.mouse.x <= 608 && ev.mouse.y >= 190 && ev.mouse.y <= 311 && ev.mouse.button == 1 && pozycja == 3){
			pozycja = 11;
			wroc = 1;
		}
		//plansza #9
		else if (ev.mouse.x >= 30 && ev.mouse.x <= 158 && ev.mouse.y >= 330 && ev.mouse.y <= 451 && ev.mouse.button == 1 && pozycja == 3){
			pozycja = 12;
			wroc = 1;
		}
		//plansza #10
		else if (ev.mouse.x >= 180 && ev.mouse.x <= 308 && ev.mouse.y >= 330 && ev.mouse.y <= 451 && ev.mouse.button == 1 && pozycja == 3){
			pozycja = 13;
			wroc = 1;
		}
		//plansza #11
		else if (ev.mouse.x >= 330 && ev.mouse.x <= 458 && ev.mouse.y >= 330 && ev.mouse.y <= 451 && ev.mouse.button == 1 && pozycja == 3){
			pozycja = 14;
			wroc = 1;
		}
		//plansza #12
		else if (ev.mouse.x >= 480 && ev.mouse.x <= 608 && ev.mouse.y >= 330 && ev.mouse.y <= 451 && ev.mouse.button == 1 && pozycja == 3){
			pozycja = 15;
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
			poruszanie(ev, &pos_x1, &pos_y1, &licz1, szybkosc);
			al_draw_bitmap(plansza01, 0, 0, 0);
			RysujMape(mapa1, niebieski1, zielony);
			al_draw_textf(font2, zielony, 5, 250, 0, "Start");
			al_draw_textf(font2, zielony, 450, 10, 0, "Meta");
			al_draw_textf(font2, zielony, 10, 10, 0, "Ilos ruchow: %i", licz1);
			al_draw_filled_rectangle(pos_x1 + 65, pos_y1 + 265, pos_x1 + 75, pos_y1 + 275, czerwony);
		}
		//wybor planszy
		else if (pozycja == 3){
			al_draw_bitmap(wybor_planszy, 0, 0, 0);
			al_draw_textf(font1, al_map_rgb(26, 255, 241), 220, 10, 0, "Wybierz plansze");
			al_draw_bitmap(plansza1, 30, 50, 0);
			al_draw_bitmap(plansza2, 180, 50, 0);
			al_draw_bitmap(plansza3, 330, 50, 0);
			al_draw_bitmap(plansza4, 480, 50, 0);
			al_draw_bitmap(plansza5, 30, 190, 0);
			al_draw_bitmap(plansza6, 180, 190, 0);
			al_draw_bitmap(plansza7, 330, 190, 0);
			al_draw_bitmap(plansza8, 480, 190, 0);
			al_draw_bitmap(plansza9, 30, 330, 0);
			al_draw_bitmap(plansza10, 180, 330, 0);
			al_draw_bitmap(plansza11, 330, 330, 0);
			al_draw_bitmap(plansza12, 480, 330, 0);
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
			poruszanie(ev, &pos_x2, &pos_y2, &licz2, szybkosc);
			al_draw_bitmap(plansza2_tlo, 0, 0, 0);
			RysujMape(mapa2, czerwony1, zolty);
			al_draw_textf(font2, zolty, 5, 255, 0, "Start");
			al_draw_textf(font2, zolty, 565, 115, 0, "Meta");
			al_draw_textf(font2, zolty, 10, 10, 0, "Ilosc ruchow: %i", licz2);
			al_draw_filled_rectangle(pos_x2 + 65, pos_y2 + 266, pos_x2 + 75, pos_y2 + 276, niebieski);
		}
		//trzecia plansza
		else if (pozycja == 6){
			poruszanie(ev, &pos_x3, &pos_y3, &licz3, szybkosc);
			al_draw_bitmap(plansza3_tlo, 0, 0, 0);
			RysujMape(mapa3, zielony1, roz);
			al_draw_textf(font2, roz, 5, 255, 0, "Start");
			al_draw_textf(font2, roz, 560, 115, 0, "Meta");
			al_draw_textf(font2, roz, 10, 10, 0, "Ilosc ruchow: %i", licz3);
			al_draw_filled_rectangle(pos_x3 + 65, pos_y3 + 266, pos_x3 + 75, pos_y3 + 276, granatowy);
		}
		//czwarta plansza
		else if (pozycja == 7){
			poruszanie(ev, &pos_x4, &pos_y4, &licz4, szybkosc);
			al_draw_bitmap(plansza4_tlo, 0, 0, 0);
			RysujMape(mapa4, fioletowy1, blekitny);
			al_draw_textf(font2, blekitny, 5, 255, 0, "Start");
			al_draw_textf(font2, blekitny, 300, 10, 0, "Meta");
			al_draw_textf(font2, blekitny, 10, 10, 0, "Ilosc ruchow: %i", licz4);
			al_draw_filled_rectangle(pos_x4 + 65, pos_y4 + 266, pos_x4 + 75, pos_y4 + 276, zolty);
		}
		//piata plansza
		else if (pozycja == 8){
			poruszanie(ev, &pos_x5, &pos_y5, &licz5, szybkosc);
			al_draw_bitmap(plansza5_tlo, 0, 0, 0);
			RysujMape(mapa5, pomaranczowy1, granatowy);
			al_draw_textf(font2, granatowy, 100, 10, 0, "Start");
			al_draw_textf(font2, granatowy, 572, 360, 0, "Meta");
			al_draw_textf(font2, granatowy, 430, 10, 0, "Ilosc ruchow: %i", licz5);
			al_draw_filled_rectangle(pos_x5 + 123, pos_y5 + 50, pos_x5 + 133, pos_y5 + 60, czarny);
		}
		//szosta plansza
		else if (pozycja == 9){
			poruszanie(ev, &pos_x6, &pos_y6, &licz6, szybkosc);
			al_draw_bitmap(plansza6_tlo, 0, 0, 0);
			RysujMape(mapa6, blekitny1, czerwony);
			al_draw_textf(font2, czerwony, 10, 340, 0, "Start");
			al_draw_textf(font2, czerwony, 420, 450, 0, "Meta");
			al_draw_textf(font2, czerwony, 10, 10, 0, "Ilosc ruchow: %i", licz6);
			al_draw_filled_rectangle(pos_x6 + 65, pos_y6 + 350, pos_x6 + 75, pos_y6 + 360, niebieski);
		}
		
		//siodma plansza
		else if (pozycja == 10){
			poruszanie(ev, &pos_x7, &pos_y7, &licz7, szybkosc);
			al_draw_bitmap(plansza7_tlo, 0, 0, 0);
			RysujMape(mapa7, roz1, niebieski);
			al_draw_textf(font2, niebieski, 5, 33, 0, "Start");
			al_draw_textf(font2, niebieski, 5, 323, 0, "Meta");
			al_draw_textf(font2, bordowy, 430, 0, 0, "Ilosc ruchow: %i", licz7);
			al_draw_filled_rectangle(pos_x7 + 65, pos_y7 + 40, pos_x7 + 75, pos_y7 + 50, bordowy);
		}
		
		//osma plansza
		else if (pozycja == 11){
			poruszanie(ev, &pos_x8, &pos_y8, &licz8, szybkosc);
			al_draw_bitmap(plansza8_tlo, 0, 0, 0);
			RysujMape(mapa8, bordowy1, bialy);
			al_draw_textf(font2, bialy, 5, 32, 0, "Start");
			al_draw_textf(font2, bialy, 578, 420, 0, "Meta");
			al_draw_textf(font2, granatowy, 430, 0, 0, "Ilosc ruchow: %i", licz8);
			al_draw_filled_rectangle(pos_x8 + 65, pos_y8 + 40, pos_x8 + 75, pos_y8 + 50, granatowy);
		}
		//dziewiata plansza
		else if (pozycja == 12){
			poruszanie(ev, &pos_x9, &pos_y9, &licz9, szybkosc);
			al_draw_bitmap(plansza9_tlo, 0, 0, 0);
			RysujMape(mapa9, zolty1, czarny);
			al_draw_textf(font2, czarny, 5, 180, 0, "Start");
			al_draw_textf(font2, czarny, 578, 272, 0, "Meta");
			al_draw_textf(font2, rozowy, 430, 0, 0, "Ilosc ruchow: %i", licz9);
			al_draw_filled_rectangle(pos_x9 + 65, pos_y9 + 190, pos_x9 + 75, pos_y9 + 200, rozowy);
		}
		//dziesiata plansza
		else if (pozycja == 13){
			poruszanie(ev, &pos_x10, &pos_y10, &licz10, szybkosc);
			al_draw_bitmap(plansza10_tlo, 0, 0, 0);
			RysujMape(mapa10, granatowy1, rozowy);
			al_draw_textf(font2, rozowy, 5, 130, 0, "Start");
			al_draw_textf(font2, rozowy, 578, 370, 0, "Meta");
			al_draw_textf(font2, bialy, 430, 0, 0, "Ilosc ruchow: %i", licz10);
			al_draw_filled_rectangle(pos_x10 + 65, pos_y10 + 140, pos_x10 + 75, pos_y10 + 150, bialy);
		}
		//jedenasta plansza
		else if (pozycja == 14){
			poruszanie(ev, &pos_x11, &pos_y11, &licz11, szybkosc);
			al_draw_bitmap(plansza11_tlo, 0, 0, 0);
			RysujMape(mapa11, zielony1, bordowy);
			al_draw_textf(font2, bordowy, 5, 420, 0, "Start");
			al_draw_textf(font2, bordowy, 578, 32, 0, "Meta");
			al_draw_textf(font2, fioletowy, 430, 0, 0, "Ilosc ruchow: %i", licz11);
			al_draw_filled_rectangle(pos_x11 + 65, pos_y11 + 430, pos_x11 + 75, pos_y11 + 440, fioletowy);
		}
		//dwusnata plansza
		else if (pozycja == 15){
			poruszanie(ev, &pos_x12, &pos_y12, &licz12, szybkosc);
			al_draw_bitmap(plansza12_tlo, 0, 0, 0);
			RysujMape(mapa12, czarny1, pomaranczowy);
			al_draw_textf(font2, pomaranczowy, 5, 80, 0, "Start");
			al_draw_textf(font2, pomaranczowy, 578, 80, 0, "Meta");
			al_draw_textf(font2, zielony, 430, 0, 0, "Ilosc ruchow: %i", licz12);
			al_draw_filled_rectangle(pos_x12 + 65, pos_y12 + 90, pos_x12 + 75, pos_y12 + 100, zielony);
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

void RysujMape(int mapa[40][30], ALLEGRO_COLOR kolor_tlo, ALLEGRO_COLOR kolor_lab){
	for (int i = 0; i < rozmiarX; i++){
		for (int j = 0; j < rozmiarY; j++){
			if (mapa[i][j] == 0)
				al_draw_filled_rectangle(i*RozmiarBloku, j*RozmiarBloku, i*RozmiarBloku + RozmiarBloku, j*RozmiarBloku + RozmiarBloku, kolor_tlo);
			else 
				al_draw_filled_rectangle(i*RozmiarBloku, j*RozmiarBloku, i*RozmiarBloku + RozmiarBloku, j*RozmiarBloku + RozmiarBloku, kolor_lab);
		}
	}
}