#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


using namespace std;

void playerRenderer(SDL_Renderer* renderer, SDL_Rect player, int x, int y, int scale, vector<int> tailX, vector<int> tailY, int tailLength){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    player.w = scale;
    player.h = scale;


    for(int i = 0; i < tailLength; i++){
        player.x = tailX[i];
        player.y = tailY[i];
        SDL_RenderFillRect(renderer, &player);

    }

    player.x = x;
    player.y = y;

    SDL_RenderFillRect(renderer, &player);
}


void foodRenderer(SDL_Renderer* renderer, SDL_Rect food){
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &food);

}

void scoreRenderer(SDL_Renderer* renderer, int tailLength, int scale, int wScale){
    SDL_Color Black = {0, 0, 0};


    TTF_Font* font = TTF_OpenFont((char*)"arial.ttf", 10);
    if(font == NULL){
        cout << "Font loading error" << endl;
        return;
    }

    SDL_Surface* score = TTF_RenderText_Solid(font, (string("Score: ") + to_string(tailLength * 10)).c_str(), Black);
	SDL_Texture* scoreMessage = SDL_CreateTextureFromSurface(renderer, score);
	SDL_Rect scoreRect;
	scoreRect.w = 100;
	scoreRect.h = 30;
	scoreRect.x = ((scale*wScale) / 2) - (scoreRect.w / 2);
	scoreRect.y = 0;
	SDL_RenderCopy(renderer, scoreMessage, NULL, &scoreRect);

	TTF_CloseFont(font);

}

bool checkCollision(int foodx, int foody, int playerx, int playery){

    if (playerx == foodx && playery == foody){
        return true;
    }

    return false;
}


pair<int, int> foodSpawn(vector<int> tailX, vector<int> tailY, int playerX, int playerY, int scale, int wScale, int tailLength){
    bool valid = false;
    int x = 0;
    int y = 0;
    srand(time(0));
    x = scale * (rand() % wScale);
    y = scale * (rand() % wScale);
    valid = true;


    for(int i = 0; i < tailLength; i++){

        if((x == tailX[1] && y == tailY[1]) || (x == playerX && y == playerY)){
            valid = false;
        }

    }

    if (!valid){
        pair<int, int> foodLoc;
        foodLoc = make_pair(-100, -100);
        return foodLoc;
    }

    pair<int, int> foodLoc;
    foodLoc = make_pair(x, y);

    return foodLoc;

}

void gameOver(SDL_Renderer* renderer, SDL_Event event, int scale, int wScale, int tailLength) {
	SDL_Color Red = { 255, 0, 0 };
	SDL_Color White = { 255, 255, 255 };
	SDL_Color Black = { 0, 0, 0 };

	// Get the font used for displaying text
	TTF_Font* font = TTF_OpenFont((char*)"arial.ttf", 10);
	if (font == NULL) {
		cout << "Font loading error" << endl;
		return;
	}

	SDL_Surface* gameover = TTF_RenderText_Solid(font, "Game Over", Red);
	SDL_Surface* retry = TTF_RenderText_Solid(font, "Press Enter to retry", White);
	SDL_Surface* score = TTF_RenderText_Solid(font, (string("Score: ") + to_string(tailLength * 10)).c_str(), Black);
	SDL_Texture* gameoverMessage = SDL_CreateTextureFromSurface(renderer, gameover);
	SDL_Texture* retryMessage = SDL_CreateTextureFromSurface(renderer, retry);
	SDL_Texture* scoreMessage = SDL_CreateTextureFromSurface(renderer, score);
	SDL_Rect gameoverRect;
	SDL_Rect retryRect;
	SDL_Rect scoreRect;
	gameoverRect.w = 200;
	gameoverRect.h = 100;
	gameoverRect.x = ((scale*wScale) / 2)-(gameoverRect.w/2);
	gameoverRect.y = ((scale*wScale) / 2)-(gameoverRect.h/2)-50;
	retryRect.w = 300;
	retryRect.h = 50;
	retryRect.x = ((scale*wScale) / 2) - ((retryRect.w / 2));
	retryRect.y = (((scale*wScale) / 2) - ((retryRect.h / 2))+150);
	scoreRect.w = 100;
	scoreRect.h = 30;
	scoreRect.x = ((scale*wScale) / 2) - (scoreRect.w / 2);
	scoreRect.y = 0;
	SDL_RenderCopy(renderer, gameoverMessage, NULL, &gameoverRect);
	SDL_RenderCopy(renderer, retryMessage, NULL, &retryRect);
	SDL_RenderCopy(renderer, scoreMessage, NULL, &scoreRect);

	TTF_CloseFont(font);

	// Show game over screen while space has not been pressed
	while (true) {
		SDL_RenderPresent(renderer);

		if (SDL_PollEvent(&event)) {

			if (event.type == SDL_QUIT) {
				exit(0);
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
				return;
			}

		}

	}

}


void youWin(SDL_Renderer* renderer, SDL_Event event, int scale, int wScale, int tailLength) {
	SDL_Color Red = { 255, 0, 0 };
	SDL_Color White = { 255, 255, 255 };
	SDL_Color Black = { 0, 0, 0 };
	SDL_Color Yellow = { 255, 255, 0 };

	// Get the font used for displaying text
	TTF_Font* font = TTF_OpenFont((char*)"arial.ttf", 10);
	if (font == NULL) {
		cout << "Font loading error" << endl;
		return;
	}

	SDL_Surface* gameover = TTF_RenderText_Solid(font, "You won!", Yellow);
	SDL_Surface* retry = TTF_RenderText_Solid(font, "Press Enter to play again", White);
	SDL_Surface* score = TTF_RenderText_Solid(font, (string("Score: ") + to_string(tailLength * 10)).c_str(), Black);
	SDL_Texture* gameoverMessage = SDL_CreateTextureFromSurface(renderer, gameover);
	SDL_Texture* retryMessage = SDL_CreateTextureFromSurface(renderer, retry);
	SDL_Texture* scoreMessage = SDL_CreateTextureFromSurface(renderer, score);
	SDL_Rect gameoverRect;
	SDL_Rect retryRect;
	SDL_Rect scoreRect;
	gameoverRect.w = 200;
	gameoverRect.h = 100;
	gameoverRect.x = ((scale*wScale) / 2) - (gameoverRect.w / 2);
	gameoverRect.y = ((scale*wScale) / 2) - (gameoverRect.h / 2) - 50;
	retryRect.w = 300;
	retryRect.h = 50;
	retryRect.x = ((scale*wScale) / 2) - ((retryRect.w / 2));
	retryRect.y = (((scale*wScale) / 2) - ((retryRect.h / 2)) + 150);
	scoreRect.w = 100;
	scoreRect.h = 30;
	scoreRect.x = ((scale*wScale) / 2) - (scoreRect.w / 2);
	scoreRect.y = 0;
	SDL_RenderCopy(renderer, gameoverMessage, NULL, &gameoverRect);
	SDL_RenderCopy(renderer, retryMessage, NULL, &retryRect);
	SDL_RenderCopy(renderer, scoreMessage, NULL, &scoreRect);

	TTF_CloseFont(font);

	// Show victory screen while space has not been pressed
	while (true) {
		SDL_RenderPresent(renderer);

		if (SDL_PollEvent(&event)) {

			if (event.type == SDL_QUIT) {
				exit(0);
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
				return;
			}

		}

	}

}


int main(int argc, char* argv[]){
    
    SDL_Init(SDL_INIT_EVERYTHING);

    if (TTF_Init() < 0){

        cout << "Error: " << TTF_GetError() << endl;

    }

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;


    SDL_Rect player;
    player.x = 0;
    player.y = 0;
    player.h = 0;
    player.w = 0;

    int tailLength = 0;


    vector<int> tailX;
    vector<int> tailY;


    int scale = 24;
    int wScale = 24;


    int x = 0;
    int y = 0;
    int prevX = 0;
    int prevY = 0;

    bool up = false;
    bool down = false;
    bool right = false;
    bool left = false;

    bool inputThisFrame = false;
    bool redo = false;

    SDL_Rect food;
    food.w = scale;
    food.h = scale;
    food.x = 0;
    food.y = 0;

    pair<int, int> foodLoc = foodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
    food.x = foodLoc.first;
    food.y = foodLoc.second;

    window = SDL_CreateWindow("Snake-SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, scale*wScale+1, scale*wScale+1, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    float time = SDL_GetTicks() / 100;


    while(true){
        float newTime = SDL_GetTicks() / 75;
        float delta = newTime - time;
        time = newTime;


        inputThisFrame = false;

        if(tailLength >= 575){
            youWin(renderer, event, scale, wScale, tailLength);
            x = 0;
            y = 0;
            up = false;
            left = false;
            right = false;
            down = false;
            tailX.clear();
            tailY.clear();
            tailLength = 0;
            redo = false;
            foodLoc = foodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);

            if(food.x == -100 && food.y == -100){
                redo = true;
            }

            food.x = foodLoc.first;
            food.y = foodLoc.second;
        } 
        
        if (SDL_PollEvent(&event)){
            
            if (event.type == SDL_QUIT){
                exit(0);
            }
			if (event.type == SDL_KEYDOWN && inputThisFrame == false) {

				if (down == false && event.key.keysym.scancode == SDL_SCANCODE_UP) {
					up = true;
					left = false;
					right = false;
					down = false;
					inputThisFrame = true;
				}
				else if (right == false && event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
					up = false;
					left = true;
					right = false;
					down = false;
					inputThisFrame = true;
				}
				else if (up == false && event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
					up = false;
					left = false;
					right = false;
					down = true;
					inputThisFrame = true;
				}
				else if (left == false && event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
					up = false;
					left = false;
					right = true;
					down = false;
					inputThisFrame = true;
				}

			}
    
        }

        prevX = x;
        prevY = y;

        if(up){
            y -= delta * scale;
        }

        else if (left){
            x -= delta * scale;

        }
        
        else if (right){
            x += delta * scale;
        }

        else if (down){
            y += delta * scale;
        }


        if (redo == true){


            redo = false;
            foodLoc = foodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
            food.x = foodLoc.first;
            food.y = foodLoc.second;
            

            if(food.x == -100 && food.y == -100){
                redo = true;
            }
        }

        
        if (checkCollision(food.x, food.y, x, y)){
            foodLoc = foodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
            food.x = foodLoc.first;
            food.y = foodLoc.second;

            if (food.x == -100 && food.y == -100){
                redo = true;
            }
            
            tailLength++;
        }

        if (delta * scale == 24){
        
            if (tailX.size() != tailLength){
                tailX.push_back(prevX);
                tailY.push_back(prevY);
            }
            
            for (int i = 0; i < tailLength; i++){

                if (i > 0){
                    tailX[i - 1] = tailX[i];
                    tailY[i - 1] = tailY[i];
                }
            }

            if (tailLength > 0){
                tailX[tailLength - 1] = prevX;
                tailY[tailLength - 1] = prevY;
            }


        }

        for (int i = 0; i < tailLength; i++) {
            
            if (x == tailX[i] && y == tailY[i]){
                gameOver(renderer, event, scale, wScale, tailLength);
                x = 0;
                y = 0;
                up = false;
                left = false;
                right = false;
                down = false;
                tailX.clear();
                tailY.clear();
                tailLength = 0;
                redo = false;
                
                foodLoc = foodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
                if (food.x == -100 && food.y == -100){
                    redo = true;
                }

                
                food.x = foodLoc.first;
                food.y = foodLoc.second;

            }

        }
        
        if (x < 0 || y < 0 || x > scale * wScale - scale || y > scale * wScale - scale){

            gameOver(renderer, event, scale, wScale, tailLength);
            x = 0;
            y = 0;
            up = false;
            left = false;
            right = false;
            down = false;
            tailX.clear();
            tailY.clear();
            tailLength = 0;
            redo = false;
            foodLoc = foodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
            food.x = foodLoc.first;
            food.y = foodLoc.second;

            if (food.x == -100 && food.y == -100){
                redo = true;
            }


        }
        
        foodRenderer(renderer, food);
        playerRenderer(renderer, player, x, y, scale, tailX, tailY, tailLength);
        scoreRenderer(renderer, tailLength, scale, wScale);


        SDL_RenderDrawLine(renderer, 0, 0, 0, 24 * 24);
        SDL_RenderDrawLine(renderer, 0, 24*24, 24 * 24, 24 * 24);
		SDL_RenderDrawLine(renderer, 24*24, 24 * 24, 24*24, 0);
		SDL_RenderDrawLine(renderer, 24*24, 0, 0, 0);
		

        SDL_RenderPresent(renderer);

		SDL_SetRenderDrawColor(renderer, 105, 105, 105, 255);
		SDL_RenderClear(renderer);
    }


    SDL_DestroyWindow(window);

    TTF_Quit();

    SDL_Quit();

    return 0;
}
