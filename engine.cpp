#include <engine.h>
#include <stdio.h>

engine* gEngine = NULL;

int main() {
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
	
	printf("engine.cpp: engine::initialize() success.\n");
	fflush(stdout);
	return 0;
}

void engine::stop() {
	// Cleanly stop the engine.
	this->running = false;
	printf("engine.cpp: engine stoping.\n");
	fflush(stdout);
}

int engine::cleanup() {
	// Clean up the engine itself.
	printf("engine.cpp: engine cleaned up.\n");
	fflush(stdout);
	return 0;
}

int engine::render_function() {
	// Called *fps* times per second
	printf("engine.cpp: rendering\n");
	fflush(stdout);
	return 0;	
}

int engine::update_function() {
	// Called *tps* times per second
	printf("engine.cpp: updating\n");
	if (this->current_tick == 3) {
		this->stop();
	} else {
		this->current_tick += 1;
	}
	fflush(stdout);
	return 0;
}
