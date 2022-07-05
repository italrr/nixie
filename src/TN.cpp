#include <signal.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <gl/GL.h>
#include <chrono>

#include "TN.hpp"

static SDL_Window* window = NULL;
static bool running = false;
static nx::v2<int> windowRealSize;
static nx::v2<int> windowSize;
static nx::v2<int> windowScale;
static nx::Color currentColor = nx::Color(255, 255, 255, 255);
static auto deltaTimeStart = std::chrono::system_clock::now();
static float deltaElapsedTime;

static const int tnKeys[] = {
	SDLK_a,SDLK_b,SDLK_c,SDLK_d,SDLK_e,SDLK_f,SDLK_g,SDLK_h,SDLK_i,
	SDLK_j,SDLK_k,SDLK_l,SDLK_m,SDLK_n,SDLK_o,SDLK_p,SDLK_q,SDLK_r,
	SDLK_s,SDLK_t,SDLK_u,SDLK_v,SDLK_w,SDLK_x,SDLK_y,SDLK_z,SDLK_0,
	SDLK_1,SDLK_2,SDLK_3,SDLK_4,SDLK_5,SDLK_6,SDLK_7,SDLK_8,SDLK_9,
	SDLK_ESCAPE,SDLK_LCTRL,SDLK_LSHIFT,SDLK_LALT,SDLK_LGUI,SDLK_RCTRL,
	SDLK_RSHIFT,SDLK_RALT,SDLK_RGUI,SDLK_MENU,SDLK_LEFTBRACKET,
	SDLK_RIGHTBRACKET,SDLK_SEMICOLON,SDLK_COMMA,SDLK_PERIOD,SDLK_QUOTE,
	SDLK_SLASH,SDLK_BACKSLASH,SDLK_BACKQUOTE,SDLK_EQUALS,SDLK_SPACE,SDLK_SPACE,
	SDLK_RETURN,SDLK_BACKSPACE,SDLK_TAB,SDLK_PAGEUP,SDLK_PAGEDOWN,SDLK_END,
	SDLK_HOME,SDLK_INSERT,SDLK_DELETE,SDLK_PLUS,SDLK_MINUS,SDLK_ASTERISK,
	SDLK_SLASH,SDLK_LEFT,SDLK_RIGHT,SDLK_UP,SDLK_DOWN,SDLK_KP_0,SDLK_KP_1,
	SDLK_KP_2,SDLK_KP_3,SDLK_KP_4,SDLK_KP_5,SDLK_KP_6,SDLK_KP_7,SDLK_KP_8,
	SDLK_KP_9,SDLK_F1,SDLK_F2,SDLK_F3,SDLK_F4,SDLK_F5,SDLK_F6,SDLK_F7,
	SDLK_F8,SDLK_F9,SDLK_F10,SDLK_F11,SDLK_F12,SDLK_F13,SDLK_F14,SDLK_F15,
	SDLK_PAUSE
};
static const unsigned tnKeysn = sizeof(tnKeys)/sizeof(int);

static std::unordered_map<unsigned, unsigned> SDLKeys;

static unsigned getKey(unsigned key){
	return SDLKeys[key];
}

static bool KeysState [tnKeysn];
static bool KeysCheck [tnKeysn];
static bool KeysStatePressed [tnKeysn];
static bool isKeysStatePressed [tnKeysn];
static bool KeysStateReleased [tnKeysn];
static bool isKeysStateReleased [tnKeysn];

bool nx::kbCheck(unsigned key){
	SDL_Scancode k = SDL_GetScancodeFromKey(tnKeys[key]);
	static const Uint8 *state = SDL_GetKeyboardState(NULL);
	return (key >= tnKeysn-1 ? 0 : state[k]);
}

bool nx::kbPress(unsigned key){
	return (key >= tnKeysn-1 ? 0 : KeysCheck[key]);
}

bool nx::kbPressOnce(unsigned key){
	if (key >= tnKeysn-1) return 0;
	bool b = KeysCheck[key];
	KeysState[key] = 0;
	KeysStatePressed[key] = 0;
	isKeysStatePressed[key] = 0;
	KeysCheck[key] = 0;
	return b;
}

bool nx::kbPressed(unsigned key){
	if (key >= tnKeysn){
		return 0;
	}
	if (isKeysStatePressed[key]){
		return 1;
	}
	if (KeysStatePressed[key] && KeysState[key]){
		return 0;
	}
	if (KeysStatePressed[key]){
		KeysStatePressed[key] = 0;
		return 0;
	}
	if (!KeysStatePressed[key] && KeysState[key]){
		isKeysStatePressed[key] = 1;
		KeysStatePressed[key] = 1;
		return 1;
	}
	return 0;
}


bool nx::kbReleased(unsigned key){
	if (key >= tnKeysn){
		return 0;
	}
	if (isKeysStateReleased[key]){
		return 1;
	}
	if (KeysState[key]){
		KeysStateReleased[key] = 1;
		return 0;
	}
	if (!KeysState[key] && KeysStateReleased[key]){
		KeysStateReleased[key] = 0;
		isKeysStateReleased[key] = 1;
		return 1;
	}
	return 0;
}

static void ctrlC(int s){
    printf("Caught Ctrl+C: Requested exit\n");
	nx::exit();
}

static unsigned int Sample2DPixel = 0;

static void createSample2DPixel(){

	unsigned char *dummyTexture = new unsigned char[8 * 8 * 4];

	for(unsigned i = 0; i < 8*8*4; i += 4){
		dummyTexture[i] = 255;
		dummyTexture[i + 1] = 255;
		dummyTexture[i + 2] = 255;
		dummyTexture[i + 3] = 255;
	}

    glEnable( GL_TEXTURE_2D );
    glGenTextures( 1, &Sample2DPixel );
    glBindTexture( GL_TEXTURE_2D, Sample2DPixel );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, dummyTexture );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);		
	glBindTexture( GL_TEXTURE_2D, 0);

	delete dummyTexture;
}



bool nx::gfxInit(int w, int h, int scalex, int scaley){

    windowSize.set(w, h);
    windowScale.set(scalex, scaley);
	windowRealSize.set(w * scalex, h * scaley);

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr, "Failed to start SDL2: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(
        "G A M E",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        windowRealSize.x,
        windowRealSize.y,
        SDL_WINDOW_OPENGL
    );

    if(window == NULL){
        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_GL_CreateContext(window);

    signal(SIGINT, ctrlC);

    running = true;

	for (unsigned i=0; i<tnKeysn; i++){
		SDLKeys[tnKeys[i]] = i;
	}

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
	glViewport(0, 0, windowRealSize.x, windowRealSize.y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, windowRealSize.x, windowRealSize.y, 0, 1, -1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	createSample2DPixel();

	printf("nixie init\n");

    return true;
}

bool nx::isRunning(){
    return running;
}

void nx::exit(){
    running = false;
}

void static updateInput(){
    SDL_Event event;
	unsigned key;
	for(unsigned i=0; i< tnKeysn; i++){
		KeysCheck[i] = 0;
		isKeysStatePressed[i] = 0;
		isKeysStateReleased[i] = 0;
	}

    while (SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_KEYUP:
				KeysState[getKey(event.key.keysym.sym)] = 0;
			break;
			case SDL_KEYDOWN:
				KeysCheck[getKey(event.key.keysym.sym)] = 1;
				KeysState[getKey(event.key.keysym.sym)] = 1;
			break;
			case SDL_MOUSEBUTTONDOWN:
				// buttonState[getButton(event.button.button)] = 1;
			break;
			case SDL_MOUSEBUTTONUP:
				// buttonState[getButton(event.button.button)] = 0;
			break;
			case SDL_QUIT:
                nx::exit();
			break;
		}

    }
}

nx::v2<int> nx::gfxSize(){
	return windowSize;
}

nx::v2<int> nx::gfxRSize(){
	return windowRealSize;
}

nx::v2<int> nx::gfxScale(){
	return windowScale;
}

bool nx::Draw::Pixel(int _x, int _y, const nx::Pixel &p){

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBindTexture(GL_TEXTURE_2D, Sample2DPixel);
	
	glColor4ub(p.r, p.g, p.b, p.a);

	if(_x < 0 || _y < 0 || _x > windowSize.x || _y > windowSize.y){
		return false;
	}

	int x = _x * windowScale.x;
	int y = _y * windowScale.y;

    glBegin( GL_QUADS );
		glTexCoord2f(0, 0);
		glVertex2f(x, y);
		glTexCoord2f(1, 0);
		glVertex2f(x + windowScale.x, y);
		glTexCoord2f( 1, 1 );
		glVertex2f(x + windowScale.x, y + windowScale.y );
		glTexCoord2f( 0, 1 );
		glVertex2f( x, y + windowScale.y );
    glEnd();

	return true;
}

bool nx::Draw::Line(int x1, int y1, int x2, int y2, const nx::Pixel &p){
	int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
	dx = x2 - x1; dy = y2 - y1;
	dx1 = std::abs(dx); dy1 = std::abs(dy);
	px = 2 * dy1 - dx1;	py = 2 * dx1 - dy1;
	if (dy1 <= dx1)
	{
		if (dx >= 0)
			{ x = x1; y = y1; xe = x2; }
		else
			{ x = x2; y = y2; xe = x1;}

		// Draw(x, y, c, col);
		nx::Draw::Pixel(x, y, p);
		
		for (i = 0; x<xe; i++)
		{
			x = x + 1;
			if (px<0)
				px = px + 2 * dy1;
			else
			{
				if ((dx<0 && dy<0) || (dx>0 && dy>0)) y = y + 1; else y = y - 1;
				px = px + 2 * (dy1 - dx1);
			}
			// Draw(x, y, c, col);
			nx::Draw::Pixel(x, y, p);
			
		}
	}
	else
	{
		if (dy >= 0)
			{ x = x1; y = y1; ye = y2; }
		else
			{ x = x2; y = y2; ye = y1; }

		// Draw(x, y, c, col);
		nx::Draw::Pixel(x, y, p);

		for (i = 0; y<ye; i++)
		{
			y = y + 1;
			if (py <= 0)
				py = py + 2 * dx1;
			else
			{
				if ((dx<0 && dy<0) || (dx>0 && dy>0)) x = x + 1; else x = x - 1;
				py = py + 2 * (dx1 - dy1);
			}
			// Draw(x, y, c, col);
			nx::Draw::Pixel(x, y, p);
		}
	}
	return true;
}

float nx::gfxDelta(){
	return deltaElapsedTime;
}


void nx::gfxDraw(){

	updateInput();

	
	#if 0
		for(int x = 0; x < windowSize.x; ++x){
			static const float ranges[3][3]	= {
				{ 1.0f, 0.0f, 0.0f },
				{ 0.0f, 1.0f, 0.0f },
				{ 0.0f, 0.0f, 1.0f },
			};
			int m = unsigned((static_cast<float>(x) / static_cast<float>(windowSize.x)) * 3.0f);
			for(int y = 0; y < windowSize.y; ++y){
				float factor = static_cast<float>(y) * (255 / static_cast<float>(windowSize.y));
				nx::Draw::Pixel(x, y, nx::Pixel(factor * ranges[m][0], factor * ranges[m][1], factor * ranges[m][2], 255));
			}
		}
	#endif
	
	
    SDL_GL_SwapWindow(window);
    
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);  


	auto ctime = std::chrono::system_clock::now();
	std::chrono::duration<float> elapse = ctime - deltaTimeStart;
	deltaTimeStart = std::chrono::system_clock::now();
	deltaElapsedTime = elapse.count();
}

void nx::gfxEnd(){
    SDL_DestroyWindow(window);
    SDL_Quit();
}