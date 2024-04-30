// define gaurd
#ifndef ENGINE_H_
#define ENGINE_H_
// end define gaurd

#define TARGET_FPS 60 // How many frames per second are *desired*.
#define TARGET_TPS 30 // How many update ticks per second are *desired*.

class engine {
public:
	int current_tick = 1;

	bool initialized = false;
	bool running = false;

	int loop_function(); // main loop function. calls render and update;

	int render_function(); // called every *fps* times per second;
	int update_function(); // called every update tick;

	int initialize(); // set everything up;
	int cleanup(); // clean everything up;

	int begin(); // starts and handles the main loop;
	void stop(); // called to stop the main loop;

	engine(); // kinda just exists;
};

#endif
