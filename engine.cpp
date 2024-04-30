#include <engine.h>
#include <stdio.h>

engine* gEngine = NULL;

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
	// Hello :.
}

int engine::loop_function() {
	// Handle the engine loop function
	while (this->running) {
		this->current_tick = SDL_GetTicks();
		this->update_function();
		this->render_function();
	}
	printf("engine.cpp: engine stopped.\n");
	fflush(stdout);
	this->cleanup();
	return 0; // Things stopped cleanly.
}

int engine::begin() {
	// Start the engine after everything has been initialized.
	this->running = true;
	printf("engine.cpp: engine loop begin.\n");
	fflush(stdout);
	this->loop_function();
	printf("engine.cpp: engine loop finished.\n");
	fflush(stdout);
	return 0;
}

int engine::initialize() {
	// Set up pre-requisets and do the things.
	
	if( SDL_Init( SDL_INIT_VIDEO) < 0 ) // Initialize SDL with video libraries.
	{
		// If initialization fails, don't set initialized to true, and the rest of the function will not run.
		printf( "engine.cpp: SDL_INIT_VIDEO produced SDL_Error: %s\n", SDL_GetError() );
		fflush(stdout);
	} else {
		this->initialized = true; // next step should process
	}
	
	if ( this->initialized ) {
		this->window = SDL_CreateWindow( "void.GEN 2.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 700, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if( this->window == NULL )
		{
			SDL_Quit(); // quit sdl
			printf( "SDL_CreateWindow produced SDL_Error: %s\n", SDL_GetError() );
			this->initialized = false; // ignore all further steps.
		} else {
			SDL_SetWindowResizable(this->window, SDL_TRUE);
			this->initialized = true; // next step should process
		}
	}
	
	if ( this->initialized ) {
		this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_PRESENTVSYNC);
		if (this->renderer == NULL) {
			SDL_Quit(); // quit sdl
			this->initialized = false; // ignore all further steps
		} else {
			SDL_SetRenderDrawColor(this->renderer, 0,  0, 0, 255); // set the draw color to black
			this->initialized = true; // next step should process
		}
	}
	
	if (this->initialized) {
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
	if  (this->current_tick - this->last_render < 1000/TARGET_FPS) {
		return 1; // did not render, consider finding a way to limit this return value (efficiency?)
	}
	// run the render calls
	
	SDL_SetRenderDrawColor(this->renderer, 255,  255, 255, 255); // set the draw color to white
	SDL_RenderClear(this->renderer); // clear the screen
	
	// render the things here
	// ..
	
	
	SDL_RenderPresent(this->renderer); // present the display
	this->last_render = this->current_tick; // update the last render time.
	return 0;	
}

int engine::update_function() {
	// gate the function to only execute render calls if within the TPS target.
	if  (this->current_tick - this->last_update < 1000/TARGET_TPS) {
		return 1; // did not update, consider finding a way to limit this return value (efficiency?)
	}
	
	// process SDL events.
	SDL_Event e;
	while( SDL_PollEvent( &e ) ){
		if( e.type == SDL_QUIT ) this->stop();
		else if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_ESCAPE) {
				this->stop();
			} else {
				
			}
		}
	}
	
	this->last_update = this->current_tick;
	return 0;
}
