#include<iostream>
#include<vector>
#include<string>
#include<ctime>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>


using namespace std;

void playerRenderer(SDL_Renderer* renderer, SDL_Rect player, int x, int y, int scale, vector<int> tailX, vector<int> tailY, int tailLength){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    player.w = scale;
    player.h = scale;


    for(int i = 0; i < tailLength; i++){
        player.x = tailX[1];
        player.y = tailY[1];
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

}



int main(){
    cout << "Hello World" << endl;
    return 0;
}
