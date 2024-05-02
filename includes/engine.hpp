// define gaurd
#ifndef ENGINE_H_
#define ENGINE_H_
// end define gaurd

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <LUA/lua.hpp>

#define TARGET_FPS 60 // How many frames per second are *desired*.
#define TARGET_TPS 30 // How many update ticks per second are *desired*.

#define MAX_TEXTURES 1024
#define MAX_FONTS 32


class texture {
public:
	const char *id = NULL;
	SDL_Texture *data = NULL;
	
	int width = 0;
	int height = 0;
	
	~texture();
	texture();
	texture(const char *id, const char *file);
	
	int render_at(int x, int y, double scale_x, double scale_y, bool centered, double rotation);
};

class font {
public:
	const char *id = NULL;
	TTF_Font *data = NULL;
	
	~font();
	font();
	font(const char *id, const char *file, int size);
	
	int render_at(const char *text, int x, int y, int r, int g, int b, bool centered, double rotation);
};

class engine {
private:
public:
	Uint32 last_render = 0; // in ms
	Uint32 last_update = 0; // in ms
	
	texture *Textures[MAX_TEXTURES];
	font *Fonts[MAX_FONTS];
	SDL_Window *window = NULL;
	lua_State *lua_instance = NULL;
	SDL_Renderer *renderer = NULL;
	Uint32 current_tick = 0; // the time since the engine began in ms

	int screen_width = 1000;
	int screen_height = 700;

	bool initialized = true;
	bool running = false;

	int loop_function(); // main loop function. calls render and update;

	int render_function(); // called every *fps* times per second;
	int update_function(); // called every update tick;

	int initialize(); // set everything up;
	int cleanup(); // clean everything up;

	int begin(); // starts and handles the main loop;
	void stop(); // called to stop the main loop;

	engine(); // kinda just exists;
	
	int load_texture(const char *id,const char *file_name);
	int render_texture(const char *id, int x, int y, double scale_x, double scale_y, bool centered, double rotation);
	
	int load_font(const char *id, const char *file_name, int size);
	int render_text(const char *id, const char *text, int x, int y, int r, int g, int b, bool centered, double rotation);
	void render_line(int x1, int y1, int x2, int y2, int r, int g, int b, int a);
	void render_rectangle(int x, int y, int w, int h, int r, int g, int b, int a, bool centered);
	void render_rectangle_border(int x, int y, int w, int h, int r, int g, int b, int a, bool centered);
};

engine* gEngine = NULL;
#endif