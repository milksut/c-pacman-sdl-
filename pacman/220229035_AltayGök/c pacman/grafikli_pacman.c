#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#define screen_width 1440
#define screen_height 720


//TEST ZONE




/*int my_initilazer(SDL_Window** window,SDL_Surface** screenSurface)//startup
{
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }
    else
    {
        //pencereyi oluþturma, ilk ikisi pencerenin ekrandaki konumunu belirtiyor diðer ikisi pencerenin büyklüðünü sonuncusu durumunu(açýk,altta vb.)
        *window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            return 1;
        }
        else
        {
            int imgflag = IMG_INIT_PNG;//png itemisl eden deðiþken
            if(!(IMG_Init(imgflag)&imgflag))//düzgün yüklenenlerle png yi karþýlaþtýrýyoruz
            {
                 printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                 return 2;
            }
            else
            {
                *screenSurface = SDL_GetWindowSurface( *window );//pencerenin gösterdiði yüzeyi bir kullana bilmek için bir deðiþkene atadýk
                return 0;
            }
        }
    }
}
int resim_olustur(SDL_Surface** resim ,char konum[],SDL_Surface** ekran)//dýþ dosyadan resmi alýp bir deðiþke atýyoruz (konmu alýrken \ yerine \\ kullan)
{
    //*resim = SDL_LoadBMP(konum);     //png kullanabilidðim için bmp kullanmayý býraktým
    *resim = IMG_Load(konum);
    if( *resim == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n",konum, IMG_GetError() );
        return -1;
    }
    else
    {
       *resim = SDL_ConvertSurface( *resim, (*ekran)->format,0);
       if (*resim==NULL)
       {
           printf( "Unable to optimize image %s! SDL Error: %s\n", konum, SDL_GetError() );
           return -2;
       }
           return 0;
    }
}
void pacman_anim_yukle(SDL_Surface* pacman_anim[8],SDL_Surface** ekran)
{
    resim_olustur(&pacman_anim[0],"textures\\pacman animation\\pacman_0.png",ekran);
    resim_olustur(&pacman_anim[1],"textures\\pacman animation\\pacman_1.png",ekran);
    resim_olustur(&pacman_anim[2],"textures\\pacman animation\\pacman_2.png",ekran);
    resim_olustur(&pacman_anim[3],"textures\\pacman animation\\pacman_3.png",ekran);
    resim_olustur(&pacman_anim[4],"textures\\pacman animation\\pacman_4.png",ekran);
    resim_olustur(&pacman_anim[5],"textures\\pacman animation\\pacman_3.png",ekran);
    resim_olustur(&pacman_anim[6],"textures\\pacman animation\\pacman_2.png",ekran);
    resim_olustur(&pacman_anim[7],"textures\\pacman animation\\pacman_1.png",ekran);
}
int main( int argc,char* argv[])
{
    //char* yazdir= SDL_GetBasePath();
    //printf("%s",yazdir);
    //The window we'll be rendering to
    SDL_Window* pencere = NULL;

    //The surface contained by the window
    SDL_Surface* ekran = NULL;
    //resim
    SDL_Surface* resimler[8] = {NULL};
    printf("%d",screen_width/40);

    if(my_initilazer(&pencere,&ekran));
    else
    {
        pacman_anim_yukle(resimler,&ekran);
        SDL_Event e;
        char quit = 'f';
        int i=0;
        SDL_Rect pacman_pozisyon;
            pacman_pozisyon.x = 0;
            pacman_pozisyon.y = 0;
            pacman_pozisyon.w = screen_width/40;
            pacman_pozisyon.h = screen_height/20;
        while( quit == 'f' )
        {
            SDL_BlitScaled(resimler[i%8],NULL,ekran,&pacman_pozisyon);
            SDL_UpdateWindowSurface( pencere );
            if(pacman_pozisyon.x<screen_width-screen_width/40)
            {
                pacman_pozisyon.x+=36;
            }
            else
            {
                pacman_pozisyon.y+=screen_height/20;
                pacman_pozisyon.x=0;
            }
            i++;
            Sleep(100);
            while( SDL_PollEvent( &e ) )
            {
                if( e.type == SDL_KEYDOWN || e.type == SDL_QUIT )
                    quit = 't';
            }
        }
    }
    return 0;
}*/
