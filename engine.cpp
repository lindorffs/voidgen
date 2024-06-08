#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#define PLATFORM_WEB
#endif

#include <engine.hpp>
#include <stdio.h>
#include <string.h>

#include <sys/stat.h>
int file_exists(const char *name)
{
  struct stat   buffer;
  return (stat (name, &buffer) == 0);
}

/// BEGIN LUA PASSTHROUGHS

int lua_load_texture(lua_State *lua_instance) {
	const char *id = lua_tolstring(lua_instance, 1, NULL);
	const char *file = lua_tolstring(lua_instance, 2, NULL);
	
	gEngine->load_texture(id, file);
	
	return 0;
}

int lua_load_font(lua_State *lua_instance) {
	const char *id = lua_tolstring(lua_instance, 1, NULL);
	const char *file = lua_tolstring(lua_instance, 2, NULL);
	int size = lua_tonumber(lua_instance, 3);
	
	gEngine->load_font(id, file, size);
	
	return 0;
}

int lua_render_texture(lua_State *lua_instance) {
	const char *id = lua_tolstring(lua_instance, 1, NULL);
	int x = lua_tonumber(lua_instance, 2);
	int y = lua_tonumber(lua_instance, 3);
	double sx = lua_tonumber(lua_instance, 4);
	double sy = lua_tonumber(lua_instance, 5);
	bool centered = lua_toboolean(lua_instance, 6);
	double r = lua_tonumber(lua_instance, 7);
	
	gEngine->render_texture(id, x, y, sx, sy, centered, r);
	
	return 0;
}
int lua_render_subtexture(lua_State *lua_instance) {
	const char *id = lua_tolstring(lua_instance, 1, NULL);
	int x = lua_tonumber(lua_instance, 2);
	int y = lua_tonumber(lua_instance, 3);
	double sx = lua_tonumber(lua_instance, 4);
	double sy = lua_tonumber(lua_instance, 5);
	bool centered = lua_toboolean(lua_instance, 6);
	double r = lua_tonumber(lua_instance, 7);
	
	gEngine->render_subtexture(id, x, y, sx, sy, centered, r);
	
	return 0;
}

int lua_create_sub_texture(lua_State *lua_instance) {
	const char *id = lua_tolstring(lua_instance, 1, NULL);
	const char *src = lua_tolstring(lua_instance, 2, NULL);
	int x = lua_tonumber(lua_instance, 3);
	int y = lua_tonumber(lua_instance, 4);
	int w = lua_tonumber(lua_instance, 5);
	int h = lua_tonumber(lua_instance, 6);
	
	gEngine->create_subtexture(id, src, x, y, w, h);
	
	return 0;
}
int lua_render_rectangle(lua_State *lua_instance) {
	int x = lua_tonumber(lua_instance, 1);
	int y = lua_tonumber(lua_instance, 2);
	int w = lua_tonumber(lua_instance, 3);
	int h = lua_tonumber(lua_instance, 4);
	int r = lua_tonumber(lua_instance, 5);
	int g = lua_tonumber(lua_instance, 6);
	int b = lua_tonumber(lua_instance, 7);
	int a = lua_tonumber(lua_instance, 8);
	bool centered = lua_toboolean(lua_instance, 9);
	
	gEngine->render_rectangle(x, y, w, h, r, g, b, a, centered);
	
	return 0;
}

int lua_render_border(lua_State *lua_instance) {
	int x = lua_tonumber(lua_instance, 1);
	int y = lua_tonumber(lua_instance, 2);
	int w = lua_tonumber(lua_instance, 3);
	int h = lua_tonumber(lua_instance, 4);
	int r = lua_tonumber(lua_instance, 5);
	int g = lua_tonumber(lua_instance, 6);
	int b = lua_tonumber(lua_instance, 7);
	int a = lua_tonumber(lua_instance, 8);
	bool centered = lua_toboolean(lua_instance, 9);
	
	gEngine->render_rectangle_border(x, y, w, h, r, g, b, a, centered);
	
	return 0;
}

int lua_render_line(lua_State *lua_instance) {
	int x1 = lua_tonumber(lua_instance, 1);
	int y1 = lua_tonumber(lua_instance, 2);
	int x2 = lua_tonumber(lua_instance, 3);
	int y2 = lua_tonumber(lua_instance, 4);
	int r = lua_tonumber(lua_instance, 5);
	int g = lua_tonumber(lua_instance, 6);
	int b = lua_tonumber(lua_instance, 7);
	int a = lua_tonumber(lua_instance, 8);
	
	gEngine->render_line(x1, y1, x2, y2, r, g, b, a);
	
	return 0;
}

int lua_render_text(lua_State *lua_instance) {
	int args = lua_gettop(lua_instance);
	
	const char *font = lua_tolstring(lua_instance, 1, NULL);
	const char *text = lua_tolstring(lua_instance, 2, NULL);
	
	int x = lua_tonumber(lua_instance, 3);
	int y = lua_tonumber(lua_instance, 4);
	int r = lua_tonumber(lua_instance, 5);
	int g = lua_tonumber(lua_instance, 6);
	int b = lua_tonumber(lua_instance, 7);
	bool centered = lua_toboolean(lua_instance, 8);
	
	gEngine->render_text(font, text, x, y, r, g, b, centered, 0);
	
	//this->render_text(text, x, y, r, g, b);
	return 0;
}

int lua_get_screen_dimensions(lua_State *lua_instance) {
	lua_pushnumber(lua_instance, gEngine->screen_width);
	lua_pushnumber(lua_instance, gEngine->screen_height);
	
	return 2;
}

int lua_set_screen_dimensions(lua_State *lua_instance) {
	int w = lua_tonumber(lua_instance, 1);
	int h = lua_tonumber(lua_instance, 2);
	int current_x = 0;
	int current_y = 0;
	
	SDL_GetWindowPosition(gEngine->window, &current_x, &current_y);
	SDL_SetWindowSize(gEngine->window, w, h);
	SDL_SetWindowPosition(gEngine->window, current_x+gEngine->screen_width/2-w/2, current_y+gEngine->screen_height/2-h/2);
	gEngine->screen_height = h;
	gEngine->screen_width = w;
	return 0;
}

int lua_get_mouse_position(lua_State *lua_instance) {
	float x = 0;
	float y = 0;
	
	SDL_GetMouseState(&x, &y);
	
	lua_pushnumber(lua_instance,x);
	lua_pushnumber(lua_instance,y);
	
	return 2;
}

int lua_get_key_down(lua_State *lua_instance) {
	SDL_Keycode check;
	const char *key = lua_tolstring(lua_instance, 1, NULL);
	check = SDL_GetKeyFromName(key);
	
	lua_pushboolean(lua_instance, gEngine->key_states.down[SDL_GetScancodeFromKey(check)]);
	
	return 1;
}
int lua_get_key_pressed(lua_State *lua_instance) {
	SDL_Keycode check;
	const char *key = lua_tolstring(lua_instance, 1, NULL);
	check = SDL_GetKeyFromName(key);
	
	lua_pushboolean(lua_instance, gEngine->key_states.pressed[SDL_GetScancodeFromKey(check)]);
	
	return 1;
}
int lua_get_key_released(lua_State *lua_instance) {
	SDL_Keycode check;
	const char *key = lua_tolstring(lua_instance, 1, NULL);
	check = SDL_GetKeyFromName(key);
	
	lua_pushboolean(lua_instance, gEngine->key_states.released[SDL_GetScancodeFromKey(check)]);
	
	return 1;
}
int lua_get_mouse_pressed(lua_State *lua_instance) {
	const char *button = lua_tolstring(lua_instance, 1, NULL);
	
	if (strcmp(button, "left") == 0) {
		lua_pushboolean(lua_instance, gEngine->mouse_states.pressed[SDL_BUTTON(SDL_BUTTON_LEFT)-1]);
	} else if (strcmp(button, "right") == 0) {
		lua_pushboolean(lua_instance, gEngine->mouse_states.pressed[SDL_BUTTON(SDL_BUTTON_RIGHT)-1]);
	} else if (strcmp(button, "middle") == 0) {
		lua_pushboolean(lua_instance, gEngine->mouse_states.pressed[SDL_BUTTON(SDL_BUTTON_MIDDLE)-1]);
	}
	
	return 1;
}
int lua_get_mouse_released(lua_State *lua_instance) {
	const char *button = lua_tolstring(lua_instance, 1, NULL);
	
	if (strcmp(button, "left") == 0) {
		lua_pushboolean(lua_instance, gEngine->mouse_states.released[SDL_BUTTON(SDL_BUTTON_LEFT)-1]);
	} else if (strcmp(button, "right") == 0) {
		lua_pushboolean(lua_instance, gEngine->mouse_states.released[SDL_BUTTON(SDL_BUTTON_RIGHT)-1]);
	} else if (strcmp(button, "middle") == 0) {
		lua_pushboolean(lua_instance, gEngine->mouse_states.released[SDL_BUTTON(SDL_BUTTON_MIDDLE)-1]);
	}
	
	return 1;
}

int lua_stop(lua_State *lua_instance) {
	
	gEngine->stop();
	
	return 0;
}

int lua_get_ticks(lua_State *lua_instance) {
	lua_pushnumber(lua_instance, SDL_GetTicks());

	return 1;
}

int lua_enable_cursor(lua_State *lua_instance) {
	SDL_ShowCursor();
	
	return 0;
}
int lua_disable_cursor(lua_State *lua_instance) {
	SDL_HideCursor();
	
	return 0;
}
int lua_disable_resizing(lua_State *lua_instance) {
	SDL_SetWindowResizable(gEngine->window, SDL_FALSE); // ensure resizable is set.
	
	return 0;
}

int lua_enable_resizing(lua_State *lua_instance) {
	SDL_SetWindowResizable(gEngine->window, SDL_TRUE); // ensure resizable is set.
	
	return 0;
}

int main(int argc, char *argv[]) {
	engine Engine = engine();
	gEngine = &Engine;
	
	if (gEngine->initialize() == 0) {
		gEngine->begin();
	} else {
		printf("engine.cpp: gEngine->initialize() failed.\n");
	}
	fflush(stdout);
	return 0;
}

engine::engine() {
	for (int i = 0; i < MAX_TEXTURES; i++) {
		this->Textures[i] = NULL;
	}
	for (int i = 0; i < MAX_SUBTEXTURES; i++) {
		this->Subtextures[i] = NULL;
	}
	for (int i = 0; i < MAX_FONTS; i++) {
		this->Fonts[i] = NULL;
	}
}

int engine::loop_function() {
	// Handle the engine loop function
	
	#ifndef __EMSCRIPTEN__
		while (this->running) {
	#endif
	this->current_tick = SDL_GetTicks();
	
	this->handle_events();
	this->render_function();
	fflush(stdout);
	#ifndef __EMSCRIPTEN__
		}
		printf("engine.cpp: engine stopped.\n");
		fflush(stdout);
		this->cleanup();
		return 0; // Things stopped cleanly.
	#else
		return 0;
	#endif
}


#ifndef __EMSCRIPTEN__
int update_thread_function(void *data) {
	while (gEngine->running) {
		gEngine->update_function();
	}
	return 0;
}
#endif

#ifdef __EMSCRIPTEN__
void engine_loop() {
	gEngine->loop_function();
}
#endif

int engine::begin() {
	SDL_ShowWindow(this->window);
	// Start the engine after everything has been initialized.
	this->running = true;
	printf("engine.cpp: engine loop begin.\n");
	fflush(stdout);
	#ifndef __EMSCRIPTEN__
		SDL_Thread *update_thread = SDL_CreateThread(update_thread_function, "update_thread", (void *)NULL);
		this->loop_function();
		printf("engine.cpp: engine loop finished.\n");
		fflush(stdout);
		return 0;
	#else
		printf("engine.cpp: setting emscripten main loop.\n");
		emscripten_set_main_loop(engine_loop, 60, 1);
	#endif
	return 0;
}

int engine::initialize() {
	// Set up pre-requisets and do the things.
	
	// initialize sdl cores
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 ) // Initialize SDL with video and audio flags.
	{
		// If initialization fails, don't set initialized to true, and the rest of the function will not run.
		printf( "engine.cpp: SDL_INIT_VIDEO produced SDL_Error: %s\n", SDL_GetError() );
		fflush(stdout);
	} else {
		this->initialized = true; // next step should process
	}
	
	// create window handle
	if ( this->initialized ) {
		// middle of screen, 1000x700px, resizable
		this->window = SDL_CreateWindow( "void.GEN 2.0", this->screen_width, this->screen_height, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);
		if( this->window == NULL )
		{ // failed to create window
			SDL_Quit(); // quit sdl
			printf( "engine.cpp: SDL_CreateWindow produced SDL_Error: %s\n", SDL_GetError() );
			this->initialized = false; // ignore all further steps.
		} else
		{ // window created
			SDL_SetWindowResizable(this->window, SDL_TRUE); // ensure resizable is set.
		}
	}
	
	// create renderer
	if ( this->initialized ) {
		// no vsync
		this->renderer = SDL_CreateRenderer(this->window, NULL);
		if (this->renderer == NULL)
		{ // failed to create renderer
			printf("engine.cpp: Failed to create renderer.\n");
			fflush(stdout);
			SDL_Quit(); // quit sdl
			this->initialized = false; // ignore all further steps
		} else
		{	// renderer created
			SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255); // set the draw color to white
			SDL_SetRenderDrawBlendMode(this->renderer, SDL_BLENDMODE_BLEND);
		}
	}
	
	// intialize audio
	if (this->initialized) {

	}
	
	// initialize image
	if (this->initialized) {
		// PNG support ONLY
		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		{ // init failed
			printf("engine.cpp: IMG_Init produced SDL_image Error: %s\n", IMG_GetError());
			this->initialized = false;
		}
	}
	
	// initialize font renderer
	if (this->initialized) {
		if( TTF_Init() == -1 )
		{ // failed
			printf("engine.cpp: TTF_Init produced SDL_image Error: %s\n", TTF_GetError() );
			this->initialized = false;
		}
	}
	
	if (this->initialized) {
		this->lua_instance = luaL_newstate();
		
		luaL_openlibs(this->lua_instance);
	

		
		lua_register(this->lua_instance, "create_subtexture", lua_create_sub_texture);
		lua_register(this->lua_instance, "disable_screen_resize", lua_disable_resizing);
		lua_register(this->lua_instance, "enable_screen_resize", lua_enable_resizing);
		lua_register(this->lua_instance, "load_texture", lua_load_texture);
		lua_register(this->lua_instance, "load_font", lua_load_font);
		lua_register(this->lua_instance, "render_texture", lua_render_texture);
		lua_register(this->lua_instance, "render_subtexture", lua_render_subtexture);
		lua_register(this->lua_instance, "render_rectangle", lua_render_rectangle);
		lua_register(this->lua_instance, "render_border", lua_render_border);
		lua_register(this->lua_instance, "render_line", lua_render_line);
		lua_register(this->lua_instance, "render_text", lua_render_text);
		lua_register(this->lua_instance, "stop", lua_stop);
		lua_register(this->lua_instance, "get_screen_dimensions", lua_get_screen_dimensions);
		lua_register(this->lua_instance, "set_screen_dimensions", lua_set_screen_dimensions);
		lua_register(this->lua_instance, "get_mouse_position", lua_get_mouse_position);
		lua_register(this->lua_instance, "get_mouse_pressed", lua_get_mouse_pressed);
		lua_register(this->lua_instance, "get_mouse_released", lua_get_mouse_released);
		lua_register(this->lua_instance, "get_ticks", lua_get_ticks);
		lua_register(this->lua_instance, "get_key_down", lua_get_key_down);
		lua_register(this->lua_instance, "get_key_pressed", lua_get_key_pressed);
		lua_register(this->lua_instance, "get_key_released", lua_get_key_released);
		lua_register(this->lua_instance, "hide_cursor", lua_disable_cursor);
		lua_register(this->lua_instance, "show_cursor", lua_enable_cursor);
		
		
		if (file_exists("./pre_init.lua")) {
			luaL_dofile(this->lua_instance, "./pre_init.lua");
			#ifndef __EMSCRIPTEN__
				this->lua_thread = lua_newthread(this->lua_instance);
			#endif
			fflush(stdout);
		} else {
			printf("engine.cpp: No pre_init.lua found.\n");
			fflush(stdout);
			this->initialized = false;
		}
	}
	
	if (this->initialized) {
		for (int i =0; i< 256; i++) {
			this->key_states.pressed[i] = false;
			this->key_states.released[i] = false;
			this->key_states.down[i] = false;
		}
		for (int i = 0; i < 4; i++) {
			this->mouse_states.pressed[i] = false;
			this->mouse_states.released[i] = false;
			this->mouse_states.down[i] = false;
		}
	}
	
	// all done!
	if (this->initialized) {
		this->input_mutex = SDL_CreateMutex();
		this->can_update_input = SDL_CreateCondition();
		this->can_process_input = SDL_CreateCondition();
		printf("engine.cpp: engine::initialize() success.\n");
		fflush(stdout);
		return 0;
	} else {
		printf("engine.cpp: engine::initialize() failure.\n");
		fflush(stdout);
		return 1;
	}
}

void engine::stop() {
	// Cleanly stop the engine.
	this->running = false;
	printf("engine.cpp: engine stoping.\n");
	fflush(stdout);
}

int engine::cleanup() {
	// Clean up the engine itself.
	
	
	SDL_Quit(); // Quit SDL2
	printf("engine.cpp: engine cleaned up.\n");
	fflush(stdout);
	return 0;
}

int engine::render_function() {
	// gate the function to only execute render calls if within the FPS target.
	//if  (SDL_GetTicks() - this->last_render < 1000/TARGET_FPS) {
	//	return 1; // did not render, consider finding a way to limit this return value happening (efficiency?)
	//}
	// run the render calls
	
	this->frame_delta = SDL_GetTicks() - this->last_render;
	if (this->frame_delta < 1000/this->frame_rate_target) {
		SDL_Delay(1000/this->frame_rate_target - this->frame_delta);
	} else {
		SDL_SetRenderDrawColor(this->renderer, 0,  0, 0, 255); // set the draw color to white
		SDL_RenderClear(this->renderer); // clear the screen
		
		
		lua_getglobal(this->lua_instance, "render");
		lua_call(this->lua_instance, 0, 0);
		// render the things here
		// ..
		
		SDL_RenderPresent(this->renderer); // present the display
		this->last_render = SDL_GetTicks(); // update the last render time.
	}
	return 0;	
}

int engine::handle_events() {
	if (this->update_input) {
		if (this->input_handled) {
			for (int i =0; i< 256; i++) {
				this->key_states.pressed[i] = false;
				this->key_states.released[i] = false;
			}
			for (int i = 0; i < 4; i++) {
				this->mouse_states.pressed[i] = false;
				this->mouse_states.released[i] = false;
			}
		}
	}
	// process SDL events.
	SDL_Event e;
	while( SDL_PollEvent( &e ) ){
		if( e.type == SDL_EVENT_QUIT ) {
			this->stop();
		} else if (e.type == SDL_EVENT_WINDOW_RESIZED) {
			//
		} else if (e.type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED) {
			this->screen_height = e.window.data2;
			this->screen_width = e.window.data1;
			SDL_SetRenderViewport(this->renderer, NULL);
		} else if (this->update_input) {
			if (e.type == SDL_EVENT_KEY_DOWN) {
				this->key_states.pressed[e.key.keysym.scancode] = true;
				this->key_states.down[e.key.keysym.scancode] = true;
			} else if (e.type == SDL_EVENT_KEY_UP) {
				this->key_states.released[e.key.keysym.scancode] = true;
				this->key_states.down[e.key.keysym.scancode] = false;
			} else if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
				this->mouse_states.pressed[e.button.button-1] = true;
				this->mouse_states.down[e.button.button-1] = true;
			} else if (e.type == SDL_EVENT_MOUSE_BUTTON_UP) {
				this->mouse_states.released[e.button.button-1] = true;
				this->mouse_states.down[e.button.button-1] = false;
			}
		}
	}
	if (this->update_input) {
		SDL_SignalCondition(this->can_process_input);
		this->input_handled = false;
	}
	
	return 0;
}

int engine::update_function() {
	// gate the function to only execute render calls if within the TPS target.
	//if  (SDL_GetTicks() - this->last_update < 1000/TARGET_TPS) {
	//	return 1; // did not update, consider finding a way to limit this return value happening (efficiency?)
	//}
	
	this->tick_delta = SDL_GetTicks() - this->last_update;
	if (this->tick_delta < 1000/this->tick_rate_target) {
		SDL_Delay(1000/this->tick_rate_target - this->tick_delta);	
	} else {
		SDL_WaitCondition(this->can_process_input, this->input_mutex);
		#ifdef __EMSCRIPTEN__
		lua_getglobal(this->lua_instance, "update");
		lua_call(this->lua_instance, 0, 0);
		#endif
		#ifndef __EMSCRIPTEN__
		lua_getglobal(this->lua_thread, "update");
		lua_call(this->lua_thread, 0, 0);
		#endif
		this->last_update = SDL_GetTicks();
		this->update_input = true;
		this->input_handled = true;
	}
	return 0;
}

int engine::load_texture(const char *id, const char *file_name) {
	int loading_at = 0; // where in the texture list to load to
	// if textures are destroyed at any point and become null,
	// this will fill those spaces first.
	for (int i = 0; i < MAX_TEXTURES; i++) {
		// if the texture is null
		if (this->Textures[i] == NULL) {
			// load here
			loading_at = i;
			break;
		// if the texture has the target id, it is already loaded and nothing needs to be done.
		} else if (this->Textures[i]->id == std::string(id)) {
			return 1; // already loaded
		}
	}
	
	// Create a new voidgen texture with the id from file_name
	this->Textures[loading_at] = new texture(id, file_name);
	return 0;
}


int engine::create_subtexture(const char *id, const char *texture_source, int sx, int sy, int w, int h) {
	int loading_at = 0; // where in the texture list to load to
	// if textures are destroyed at any point and become null,
	// this will fill those spaces first.
	for (int i = 0; i < MAX_SUBTEXTURES; i++) {
		// if the texture is null
		if (this->Subtextures[i] == NULL) {
			// load here
			loading_at = i;
			break;
		// if the texture has the target id, it is already loaded and nothing needs to be done.
		} else if (this->Subtextures[i]->id == std::string(id)) {
			return 1; // already loaded
		}
		if (i == MAX_SUBTEXTURES - 1) {
			printf("MAX SUB TEXTURES REACHED\n");
			fflush(stdout);
		}
	}
	
	// Create a new voidgen texture with the id from file_name
	this->Subtextures[loading_at] = new subtexture(id, texture_source, sx, sy, w, h);
	return 0;
}

int engine::render_texture(const char *id, int x, int y, double scale_x, double scale_y, bool centered, double rotation) {
	// search for texture in textures
	for (int i = 0; i < MAX_TEXTURES; i++) {
		if (this->Textures[i] == NULL) {
			
		} else if (this->Textures[i]->id == std::string(id)) {
			// if Textures[i] matches target id, draw it.
			this->Textures[i]->render_at(x, y, scale_x, scale_y, centered, rotation);
			return 0;
		} else {
		}
	}
	return 1;
}
int engine::render_subtexture(const char *id, int x, int y, double scale_x, double scale_y, bool centered, double rotation) {
	// search for texture in textures
	for (int i = 0; i < MAX_SUBTEXTURES; i++) {
		if (this->Subtextures[i] == NULL) {
			
		} else if (this->Subtextures[i]->id == std::string(id)) {
			// if Textures[i] matches target id, draw it.
			this->Subtextures[i]->render_at(x, y, scale_x, scale_y, centered, rotation);
			return 0;
		}
	}
	return 1;
}

int engine::load_font(const char *id, const char *file_name, int size) {
	int loading_at = 0;
	for (int i = 0; i < MAX_FONTS; i++) {
		// if the font is null
		if (this->Fonts[i] == NULL) {
			// load here
			loading_at = i;
			break;
		// if the texture has the target id, it is already loaded and nothing needs to be done.
		} else if (strcmp(this->Fonts[i]->id, id) == 0) {
			return 1; // already loaded
		}
	}
	
	// Create a new voidgen texture with the id from file_name
	this->Fonts[loading_at] = new font(id, file_name, size);
	return 0;
	
}

int engine::render_text(const char *id, const char *text, int x, int y, int r, int g, int b, bool centered=false, double rotation=0) {
	for (int i = 0; i < MAX_FONTS; i++) {
		// if the font is null
		if (this->Fonts[i] == NULL) {
			
		// if the texture has the target id, it is already loaded and nothing needs to be done.
		} else {
			if (strcmp(this->Fonts[i]->id, id) == 0) {
				this->Fonts[i]->render_at(text, x, y, r, g, b, centered, rotation);
				return 0;
			}
			fflush(stdout);
		}
	}
	return 1;
}

void engine::render_line(int x1, int y1, int x2, int y2, int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(this->renderer, r, g, b, a);
	SDL_RenderLine(this->renderer, x1, y1, x2, y2);
}

void engine::render_rectangle(int x, int y, int w, int h, int r, int g, int b, int a, bool centered) {
	if (centered) {
		x = x - w / 2;
		y = y - h / 2;
	}
	SDL_FRect draw_rect = {x, y, w, h};
	SDL_SetRenderDrawColor(this->renderer, r, g, b, a);
	SDL_RenderFillRect(this->renderer, &draw_rect);
}

void engine::render_rectangle_border(int x, int y, int w, int h, int r, int g, int b, int a, bool centered) {
	if (centered) {
		x = x - w / 2;
		y = y - h / 2;
	}
	this->render_line(x, y, x+w, y, r, g, b, a);
	
	this->render_line(x, y+h, x+w, y+h, r, g, b, a);
	
	this->render_line(x+w, y, x+w, y+h, r, g, b, a);
	
	this->render_line(x, y, x, y+h, r, g, b, a);
}

/**

	END GAME ENGINE CORE.
	
	BEGIN HANDLERS.

**/

// Loads an image into a surface and returns it as an sdl texture
SDL_Texture *load_image(const char *file_name) {
	SDL_Texture* loaded_texture = NULL;
	
	// load the image
	SDL_Surface* loaded_surface = IMG_Load(file_name);
	
	if (loaded_surface == NULL)
	{ // image loading failed.
		printf("engine.cpp: IMG_Load('%s') produced SDL_Image error: '%s.'\n", file_name, IMG_GetError());
		// do nothing and return null
	} else {
		// store the image as an actual texture;
		loaded_texture = SDL_CreateTextureFromSurface(gEngine->renderer, loaded_surface);
		SDL_DestroySurface(loaded_surface);
	}
	return loaded_texture;
}

// returns the size of a texture as a sdl point
SDL_Point getsize(SDL_Texture *texture) {
    SDL_Point size;
    SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
    return size;
}


/// texture class

// clean up the texture at the end.
texture::~texture() {
	fflush(stdout);
	SDL_DestroyTexture(this->data);
}
texture::texture() {}

// the texture itself
texture::texture(const char *id, const char *file_name) {
	// the id to reference by
	this->id = std::string(id);
	// load the image
	this->data = load_image(file_name);
	// get the size of the texture
	SDL_Point size = getsize(this->data);
	// store it.
	this->width = size.x;
	this->height = size.y;
	
	SDL_SetTextureScaleMode(this->data, SDL_SCALEMODE_NEAREST);
}

// renders the texture at x,y with a size of scale_x,scale_y, centered around x+w/2,y+h/2 or not, with a rotation.
int texture::render_at(int x, int y, double scale_x=0, double scale_y=0, bool centered=false, double rotation=0) {
	// The area to draw to.
	SDL_FRect target_rect;
	
	// if the scale is set for x
	if (scale_x != 0) {
		// width of target area is scale_x
		target_rect.w = scale_x;
		
		// if centered is set
		if (centered) {
			// target area is drawn with corner at x - scale_x / 2 to render with center at x
			target_rect.x = x - (scale_x) / 2;
		} else {
			// else target area is drawn with corner at x
			target_rect.x = x;
		}
	} else {
		// if the scale is not set for x, the width of target area is textures width
		target_rect.w = this->width;
		// if centered
		if (centered) {
			// draw with corner at x - width/2 for center at x
			target_rect.x = x - (this->width) /2;
		} else {
			// else draw with corner at x
			target_rect.x = x;
		}
	}
	// for comments see above.
	if (scale_y != 0) {
		target_rect.h = scale_y;
		if (centered) {
			target_rect.y = y - (scale_y) / 2;
		} else {
			target_rect.y = y;
		}
	} else {
		target_rect.h = this->height;
		if (centered) {
			target_rect.y = y - (this->height) /2;
		} else {
			target_rect.y = y;
		}
	}
	fflush(stdout);
	SDL_RenderTextureRotated(gEngine->renderer, this->data, NULL, &target_rect, rotation, NULL, SDL_FLIP_NONE);
	return 0;
}

subtexture::subtexture(const char *id, const char *source, int source_x, int source_y, int w, int h) {
	this->id = std::string(id);
	for (int i = 0; i < MAX_TEXTURES; i++) {
		if (gEngine->Textures[i] == NULL) {
			
		} else {
			fflush(stdout);
			if (gEngine->Textures[i]->id == std::string(source)) {
			// if Textures[i] matches target id, draw it.
				this->texture_source = gEngine->Textures[i];
				break;
			}
		}
	}
	if (this->texture_source == NULL) {
		return;
	}
	this->source_x = source_x;
	this->source_y = source_y;
	this->width = w;
	this->height = h;
}

int subtexture::render_at(int x, int y, double scale_x=0, double scale_y=0, bool centered=false, double rotation=0) {
	SDL_FRect source_rect;
	source_rect.x = this->source_x;
	source_rect.y = this->source_y;
	source_rect.w = this->width;
	source_rect.h = this->height;
	SDL_FRect target_rect;
	if (scale_x != 0) {
		target_rect.w = scale_x;
		if (centered) {
			target_rect.x = x - (scale_x) / 2;
		} else {
			target_rect.x = x;
		}
	} else {
		target_rect.w = this->texture_source->width;
		if (centered) {
			target_rect.x = x - (this->texture_source->width) /2;
		} else {
			target_rect.x = x;
		}
	}
	if (scale_y != 0) {
		target_rect.h = scale_y;
		if (centered) {
			target_rect.y = y - (scale_y) / 2;
		} else {
			target_rect.y = y;
		}
	} else {
		target_rect.h = this->texture_source->height;
		if (centered) {
			target_rect.y = y - (this->texture_source->height) /2;
		} else {
			target_rect.y = y;
		}
	}
	SDL_RenderTextureRotated(gEngine->renderer, this->texture_source->data, &source_rect, &target_rect, rotation, NULL, SDL_FLIP_NONE);
	return 0;
}

TTF_Font* load_font(const char *path, int size) {
	TTF_Font* new_font = TTF_OpenFont( path, size );
    if( new_font == NULL )
    {
        printf( "TTF_OpenFont('%s') produced SDL_ttf error: '%s.'\n", path, TTF_GetError() );
    }
    return new_font;
}

font::font() {
	
}
font::font(const char *id, const char *file, int size) {
	this->id = id;
	this->data = load_font(file, size);
}

int font::render_at(const char *text, int x, int y, int r, int g, int b, bool centered, double rotation) {
	SDL_Color text_color = {static_cast<Uint8>(r),static_cast<Uint8>(g),static_cast<Uint8>(b)};
	fflush(stdout);
	SDL_Surface* textSurface = TTF_RenderText_Solid( this->data, text, text_color);
	SDL_Texture* loaded_texture = SDL_CreateTextureFromSurface(gEngine->renderer, textSurface);
	SDL_Point size = getsize(loaded_texture);
	SDL_FRect target_rect;
	target_rect.w = size.x;
	target_rect.h = size.y;

	if (centered) {
		target_rect.x = x - (size.x) /2;
	} else {
		target_rect.x = x;
	}
	if (centered) {
		target_rect.y = y - (size.y) /2;
	} else {
		target_rect.y = y;
	}
	SDL_RenderTextureRotated(gEngine->renderer, loaded_texture, NULL, &target_rect, rotation, NULL, SDL_FLIP_NONE);
	
	SDL_DestroySurface(textSurface);
	SDL_DestroyTexture(loaded_texture);
	return 0;
}

/// end classes

