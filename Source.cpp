#include <allegro5/allegro.h>
#include<allegro5\allegro_primitives.h>
#include <iostream>
using namespace std;
//constants: variables that shouldn't change once the game starts
const float FPS = 60;
const int SCREEN_W = 500;
const int SCREEN_H = 500;
const int BOUNCER_SIZE = 32;
//enumeration to help you remember what numbers represent which directions
enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};
bool cWall(int Px, int Py, int Pw, int Ph, int Wx, int Wy, int Ww, int Wh);
int main()
{
	//double xWall = ;
	//set up allegro
	al_init();
	al_install_keyboard();
	al_init_primitives_addon();
	int level = 1;
	//set up game screen, event queue, and timer
	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_W, SCREEN_H);
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
	al_start_timer(timer);
	//position of player
	double xPos = 30;
	double yPos = 30;
	//game variables
	bool key[4] = { false, false, false, false }; //holds key clicks
	bool redraw = true; //variable needed for render section
	bool doexit = false; //handles game loop

	//tell event queue what to look for
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	while (!doexit)//game loop!
	{

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//timer (physics) section////////////////////////////////////////
		if (ev.type == ALLEGRO_EVENT_TIMER) {

			//check for collect!
			if (cWall(xPos, yPos, 20, 20, 30, 450, 50, 470) == true) {
				cout << "Secret Collect!" << endl;
				doexit = true;//kill the game

			}

			if (cWall(xPos, yPos, 20, 20, 400, 60, 40, 20) == true || cWall(xPos, yPos, 20, 20, 60, 120, 40, 20) == true ||
				cWall(xPos, yPos, 20, 20, 400, 180, 40, 20) == true || cWall(xPos, yPos, 20, 20, 60, 240, 40, 20) == true ||
				cWall(xPos, yPos, 20, 20, 400, 300, 40, 20) == true || cWall(xPos, yPos, 20, 20, 60, 360, 40, 20) == true ||
				cWall(xPos, yPos, 20, 20, 400, 420, 40, 20) == true) {
				cout << "Death!" << endl;
				xPos = 30;//resets position
				yPos = 30;//resets position

			}

			//move player 4 pixels in a direction when key is pressed
			if (key[KEY_UP] && yPos > 20 && cWall(xPos, yPos - 5, 20, 20, 0, 60, 400, 20) == false && cWall(xPos, yPos - 5, 20, 20, 100, 120, 400, 20) == false &&
				cWall(xPos, yPos - 5, 20, 20, 0, 180, 400, 20) == false && cWall(xPos, yPos - 5, 20, 20, 100, 240, 400, 20) == false && cWall(xPos, yPos - 5, 20, 20, 0, 300, 400, 20) == false &&
				cWall(xPos, yPos - 5, 20, 20, 100, 360, 400, 20) == false && cWall(xPos, yPos - 5, 20, 20, 0, 420, 400, 20) == false) {
				yPos -= 5.0;
			}
			if (key[KEY_DOWN] && yPos + 20 < 480 && cWall(xPos, yPos + 5, 20, 20, 0, 60, 400, 20) == false && cWall(xPos, yPos + 5, 20, 20, 100, 120, 400, 20) == false &&
				cWall(xPos, yPos + 5, 20, 20, 0, 180, 400, 20) == false && cWall(xPos, yPos + 5, 20, 20, 100, 240, 400, 20) == false && cWall(xPos, yPos + 5, 20, 20, 0, 300, 400, 20) == false &&
				cWall(xPos, yPos + 5, 20, 20, 100, 360, 400, 20) == false && cWall(xPos, yPos + 5, 20, 20, 0, 420, 400, 20) == false) {
				yPos += 5.0;
			}
			if (key[KEY_LEFT] && xPos > 20 && cWall(xPos - 5, yPos, 20, 20, 0, 60, 400, 20) == false && cWall(xPos - 5, yPos, 20, 20, 100, 120, 400, 20) == false &&
				cWall(xPos - 5, yPos, 20, 20, 0, 180, 400, 20) == false && cWall(xPos - 5, yPos, 20, 20, 100, 240, 400, 20) == false && cWall(xPos - 5, yPos, 20, 20, 0, 300, 400, 20) == false &&
				cWall(xPos - 5, yPos, 20, 20, 100, 360, 400, 20) == false && cWall(xPos - 5, yPos, 20, 20, 0, 420, 400, 20) == false) {
				xPos -= 5.0;
			}
			if (key[KEY_RIGHT] && xPos + 20 < 480 && cWall(xPos + 5, yPos, 20, 20, 0, 60, 400, 20) == false && cWall(xPos + 5, yPos, 20, 20, 100, 120, 400, 20) == false &&
				cWall(xPos + 5, yPos, 20, 20, 0, 180, 400, 20) == false && cWall(xPos + 5, yPos, 20, 20, 100, 240, 400, 20) == false && cWall(xPos + 5, yPos, 20, 20, 0, 300, 400, 20) == false &&
				cWall(xPos + 5, yPos, 20, 20, 100, 360, 400, 20) == false && cWall(xPos + 5, yPos, 20, 20, 0, 420, 400, 20) == false) {
				xPos += 5.0;
			}
			redraw = true;
		}
		//keyboard and screen sections//////////////////////////////////////////
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;

			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;
			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}
		//render section//////////////////////////////////////////////////
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0)); //wipe screen black between drawing(without this things smear)
			al_draw_rectangle(10, 10, 490, 490, al_map_rgb(0, 100, 0), 20);

			if (level == 1) {
				//walls
				al_draw_filled_rectangle(0, 60, 400, 80, al_map_rgb(0, 100, 0));
				al_draw_filled_rectangle(100, 120, 500, 140, al_map_rgb(0, 100, 0));
				al_draw_filled_rectangle(0, 180, 400, 200, al_map_rgb(0, 100, 0));
				al_draw_filled_rectangle(100, 240, 500, 260, al_map_rgb(0, 100, 0));
				al_draw_filled_rectangle(0, 300, 400, 320, al_map_rgb(0, 100, 0));
				al_draw_filled_rectangle(100, 360, 500, 380, al_map_rgb(0, 100, 0));
				al_draw_filled_rectangle(0, 420, 400, 440, al_map_rgb(0, 100, 0));

				//death corners
				al_draw_filled_rectangle(400, 60, 440, 80, al_map_rgb(255, 255, 255));
				al_draw_filled_rectangle(60, 120, 100, 140, al_map_rgb(255, 255, 255));
				al_draw_filled_rectangle(400, 180, 440, 200, al_map_rgb(255, 255, 255));
				al_draw_filled_rectangle(60, 240, 100, 260, al_map_rgb(255, 255, 255));
				al_draw_filled_rectangle(400, 300, 440, 320, al_map_rgb(255, 255, 255));
				al_draw_filled_rectangle(60, 360, 100, 380, al_map_rgb(255, 255, 255));
				al_draw_filled_rectangle(400, 420, 440, 440, al_map_rgb(255, 255, 255));

				//secret collect
				al_draw_filled_rectangle(30, 450, 50, 470, al_map_rgb(255, 255, 0));
			}

			al_draw_filled_rectangle(xPos, yPos, xPos + 20, yPos + 20, al_map_rgb(255, 0, 0)); //draw the player
			al_flip_display(); //flip everything from memory to gamescreen
		}//end render

	}//end game loop
	//clean up memory
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	return 0;
}
bool cWall(int Px, int Py, int Pw, int Ph, int Wx, int Wy, int Ww, int Wh) {

	if ((Px + Pw > Wx) &&//collision from the left
		(Px < Wx + Ww) &&//collision from right
		(Py + Ph > Wy) && //collision from top
		(Py < Wy + Wh) //collision from bottom
		) {
		cout << "Collision!" << endl;
		return true;
	}
	else
		return false;
}