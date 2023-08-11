#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#define screen_width 1440
#define screen_height 720
#define map_x 41
#define map_y 20
#define ghost_amount 4
#define points_c '.'
#define ghost_symbol 'n'
#define player_symbol 'c'
#define wall_symbol '#'
#define sleep_time 25 //miliseconds btween animatioan frames
#define ghost_turn_chance 2// 1/x
int player_x=20,player_y=-8,is_alive=1;//use y as negative
int points=0;//the points on the map also (#) means wall
char player_direction='0';//player goes to a direction non stop even the button isnt pressed
struct inital_pozitions{
    int pre_ghost_x[ghost_amount];
    int pre_ghost_y[ghost_amount];
    int pre_player_x;
    int pre_player_y;
};
void draw_map(char harita[map_y][map_x])
{
    system("cls");
    for(int i=0;i<map_y;i++)
    {
        printf("%s\n",*(harita+i));
    }
}
void map_maker(char harita[][map_x])
{
        for(int i=0;i<map_x-1;i++)
        {
            harita[0][i]=wall_symbol;
            harita[map_y-1][i]=wall_symbol;
        }
        harita[0][map_x-1]='\0';
        for(int i=1;i<map_y-1;i++)
        {
            harita[i][0]=wall_symbol;
            harita[i][map_x-1]='\0';
            harita[i][map_x-2]=wall_symbol;
            if(!(i==5||i==8||i==11||i==14))
            {
                harita[i][19]=wall_symbol;
                harita[i][20]=wall_symbol;
                if(i==2||i==17)
                {
                    for(int j=2;j<=8;j++)
                    {
                        harita[i][j]=wall_symbol;
                        harita[i][j+29]=wall_symbol;
                    }
                }
                else if(i==9||i==10)
                {
                    for(int j=2;j<=6;j++)
                    {
                        harita[i][j]=wall_symbol;
                        harita[i][j+31]=wall_symbol;
                    }
                    if(i==9)
                    {
                        harita[i][12]=wall_symbol;
                        harita[i][16]=wall_symbol;
                        harita[i][23]=wall_symbol;
                        harita[i][27]=wall_symbol;
                    }
                    else
                    {
                        harita[i][10]=wall_symbol;
                        harita[i][14]=wall_symbol;
                        harita[i][25]=wall_symbol;
                        harita[i][29]=wall_symbol;
                    }
                }
            }
            if(!(i==1||i==4||i==7||i==9||i==10||i==12||i==15||i==18))
            {
                 for(int j=10;j<=17;j++)
                {
                    harita[i][j]=wall_symbol;
                    harita[i][j+12]=wall_symbol;
                }
                if(i==8||i==11)
                {
                    harita[i][5]=wall_symbol;
                    harita[i][9]=wall_symbol;
                    harita[i][30]=wall_symbol;
                    harita[i][34]=wall_symbol;
                }
            }
            if(!(i==1||i==3||i==10||i==16||i==18))
            {
                harita[i][8]=wall_symbol;
                harita[i][31]=wall_symbol;
            }
            if(i>=3&&i<=7)
            {
                harita[i][2]=wall_symbol;
                harita[i][37]=wall_symbol;
                harita[i+9][2]=wall_symbol;
                harita[i+9][37]=wall_symbol;
                if(i==4||i==5||i==6)
                {
                    harita[i][4]=wall_symbol;
                    harita[i][6]=wall_symbol;
                    harita[i][33]=wall_symbol;
                    harita[i][35]=wall_symbol;
                    harita[i+9][4]=wall_symbol;
                    harita[i+9][6]=wall_symbol;
                    harita[i+9][33]=wall_symbol;
                    harita[i+9][35]=wall_symbol;
                    if(i==4)
                    {
                        harita[i][5]=wall_symbol;
                        harita[i][34]=wall_symbol;
                        harita[i+11][5]=wall_symbol;
                        harita[i+11][34]=wall_symbol;
                    }
                }
            }
        }
        harita[10][38]=points_c;//i dont know why there is a wall
        for(int i=0;i<map_y;i++)
        {
            for(int j=0;j<map_x-1;j++)
            {
                if(harita[i][j]!=wall_symbol)
                {
                    harita[i][j]=points_c;
                }
            }
        }
}
int check_x(char harita[][map_x],int direction)
{
    if(harita[-1*player_y][player_x+direction]==wall_symbol)
        return 0;
    else if (harita[-1*player_y][player_x+direction]==ghost_symbol)
        return -1;
    else
        return 1;
}
int check_y(char harita[][map_x],int direction)
{
    if(harita[-1*(player_y+direction)][player_x]==wall_symbol)
        return 0;
    else if(harita[-1*(player_y+direction)][player_x]==ghost_symbol)
        return -1;
    else
        return 1;
}
void girdi(char harita[][map_x])
{
    SDL_Event e;
    while( SDL_PollEvent( &e ) )
    {
        if( e.type == SDL_KEYDOWN)
        {
            switch( e.key.keysym.sym )
            {
                case SDLK_a:
                    if(check_x(harita,-1)==1)
                        player_direction ='a';
                    break;
                case SDLK_s:
                    if(check_y(harita,-1)==1)
                        player_direction ='s';
                    break;
                case SDLK_d:
                    if(check_x(harita,1)==1)
                        player_direction ='d';
                    break;
                case SDLK_w:
                    if(check_y(harita,1)==1)
                        player_direction ='w';
                    break;
                case SDLK_ESCAPE:
                    player_direction =27;
                    break;
            }
        }
        else if(e.type == SDL_QUIT)
        {
                player_direction='q';
                is_alive=0;
        }
    }
}
void move_x(char harita[][map_x],int previus_point_direction)
{
   if(harita[-1*player_y][player_x]==points_c)
        points++;
   harita[-1*player_y][player_x]=player_symbol;
   harita[-1*player_y][player_x+previus_point_direction]=' ';
}
void move_y(char harita[][map_x],int previus_point_direction)
{
   if(harita[-1*player_y][player_x]==points_c)
        points++;
   harita[-1*player_y][player_x]=player_symbol;
   harita[-1*(player_y+previus_point_direction)][player_x]=' ';
}
void player_update(char harita[][map_x])
{
    if(player_direction=='w'||player_direction=='W')
    {
        if(check_y(harita,+1)==1)
        {
            player_y++;
            move_y(harita,-1);
        }
        else if(check_y(harita,+1)==-1)
        {
            is_alive=0;
        }
    }
    else if(player_direction=='a'||player_direction=='A')
    {
        if(check_x(harita,-1)==1)
        {
            player_x--;
            move_x(harita,+1);
        }
        else if(check_x(harita,-1)==-1)
        {
            is_alive=0;
        }
    }
    else if(player_direction=='s'||player_direction=='S')
    {
        if(check_y(harita,-1)==1)
        {
            player_y--;
            move_y(harita,+1);
        }
        else if(check_y(harita,-1)==-1)
        {
            is_alive=0;
        }
    }
    else if(player_direction=='d'||player_direction=='D')
    {
        if(check_x(harita,+1)==1)
        {
            player_x++;
            move_x(harita,-1);
        }
        else if(check_x(harita,+1)==-1)
        {
            is_alive=0;
        }
    }
    //maybe more keys?
}
int ghost_check_x(char harita[][map_x],int ghost_x,int ghost_y,char *direction)
{
    if(harita[-1*(ghost_y)][ghost_x+1]!=wall_symbol)
    {
        int temp=rand()%ghost_turn_chance;
        if(temp==0)
        {
            *direction='d';
            return 1;
        }
        else if(harita[-1*(ghost_y)][ghost_x-1]!=wall_symbol)
        {
            int temp=rand()%ghost_turn_chance;
            if(temp==0)
            {
                *direction='a';
                return 1;
            }
        }
    }
    else if(harita[-1*(ghost_y)][ghost_x-1]!=wall_symbol)
    {
        int temp=rand()%ghost_turn_chance;
        if(temp==0)
        {
            *direction='a';
            return 1;
        }
    }
    return 0;
}
int ghost_check_y(char harita[][map_x],int ghost_x,int ghost_y,char *direction)
{
    if(harita[-1*(ghost_y+1)][ghost_x]!=wall_symbol)
    {
        int temp=rand()%ghost_turn_chance;
        if(temp==0)
        {
            *direction='w';
            return 1;
        }
        else if(harita[-1*(ghost_y-1)][ghost_x]!=wall_symbol)
        {
            int temp=rand()%ghost_turn_chance;
            if(temp==0)
            {
                *direction='s';
                return 1;
            }
        }
    }
    else if(harita[-1*(ghost_y-1)][ghost_x]!=wall_symbol)
    {
        int temp=rand()%ghost_turn_chance;
        if(temp==0)
        {
            *direction='s';
            return 1;
        }
    }
    return 0;
}
int ghost_check_and_move(char harita[][map_x],int *ghost_x,int *ghost_y,char *direction,char *previus)
{
    if(*direction=='w'||*direction=='s')
        ghost_check_x(harita,*ghost_x,*ghost_y,direction);//chance to turn
    else if(*direction=='a'||*direction=='d')
        ghost_check_y(harita,*ghost_x,*ghost_y,direction);//chance to turn
     if(*direction=='w')
     {
         if(harita[-1*(*ghost_y+1)][*ghost_x]==wall_symbol)//checks if there is wall in front of it
            return 0;
         else if(harita[-1*(*ghost_y+1)][*ghost_x]==ghost_symbol)//checks if there is a another ghost in front of it otherwise they clon themselfs
            return 0;
         else if(harita[-1*(*ghost_y+1)][*ghost_x]==player_symbol)//checks if player in front of it then unalives the player
         {
            is_alive=0;
            return 1;
         }
         else//keeps going
         {
             harita[-1*(*ghost_y)][*ghost_x]=*previus;
             *ghost_y+=1;
             *previus=harita[-1*(*ghost_y)][*ghost_x];
             harita[-1*(*ghost_y)][*ghost_x]=ghost_symbol;
             return 1;
         }
     }
     else if(*direction=='a')
     {
         if(harita[-1*(*ghost_y)][*ghost_x-1]==wall_symbol)
            return 0;
         else if(harita[-1*(*ghost_y)][*ghost_x-1]==ghost_symbol)
            return 0;
         else if(harita[-1*(*ghost_y)][*ghost_x-1]==player_symbol)
         {
            is_alive=0;
            return 1;
         }
         else
            {
             harita[-1*(*ghost_y)][*ghost_x]=*previus;
             *ghost_x-=1;
             *previus=harita[-1*(*ghost_y)][*ghost_x];
             harita[-1*(*ghost_y)][*ghost_x]=ghost_symbol;
             return 1;
            }
     }
     else if(*direction=='s')
     {
         if(harita[-1*(*ghost_y-1)][*ghost_x]==wall_symbol)
            return 0;
         else if(harita[-1*(*ghost_y-1)][*ghost_x]==ghost_symbol)
            return 0;
         else if(harita[-1*(*ghost_y-1)][*ghost_x]==player_symbol)
         {
            is_alive=0;
            return 1;
         }
         else
         {
             harita[-1*(*ghost_y)][*ghost_x]=*previus;
             *ghost_y-=1;
             *previus = harita[-1*(*ghost_y)][*ghost_x];
             harita[-1*(*ghost_y)][*ghost_x]=ghost_symbol;
             return 1;
         }
     }
     else if(*direction=='d')
     {
         if(harita[-1*(*ghost_y)][*ghost_x+1]==wall_symbol)
            return 0;
         else if(harita[-1*(*ghost_y)][*ghost_x+1]==ghost_symbol)
            return 0;
         else if(harita[-1*(*ghost_y)][*ghost_x+1]==player_symbol)
         {
            is_alive=0;
            return 1;
         }
         else
         {
             harita[-1*(*ghost_y)][*ghost_x]=*previus;
             *ghost_x+=1;
             *previus=harita[-1*(*ghost_y)][*ghost_x];
             harita[-1*(*ghost_y)][*ghost_x]=ghost_symbol;
             return 1;
         }
     }
}
void turntable(char *direction)//turns the ghost
{
    if(*direction=='w')
    {
        if(!(rand()%ghost_turn_chance))
            *direction='d';
        else
            *direction='a';
    }

    else if(*direction=='d')
    {
        if(!(rand()%ghost_turn_chance))
            *direction='s';
        else
            *direction='w';
    }
    else if(*direction=='s')
    {
        if(!(rand()%ghost_turn_chance))
            *direction='a';
        else
            *direction='d';
    }
    else if(*direction=='a')
    {
        if(!(rand()%ghost_turn_chance))
            *direction='w';
        else
            *direction='s';
    }
}
void ghost_colony(char harita[][map_x],int ghostAmount,int ghost_x_points[],int ghost_y_points[],char ghost_directions[],char ghost_previus[])//manages ghosts
{
    for(int i=0;i<ghostAmount;)
    {
        int a=ghost_check_and_move(harita,&ghost_x_points[i],&ghost_y_points[i],&ghost_directions[i],&ghost_previus[i]);
        if(a)
        {
            i++;
        }
        else
            turntable(&ghost_directions[i]);
    }
}
int my_initilazer(SDL_Window** window,SDL_Surface** screenSurface)//startup
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
void anim_yukle(SDL_Surface* pacman_anim[8],SDL_Surface* ghost_anim[8],SDL_Surface** ekran,SDL_Surface* sayilar[11])
{
    //pacman animation frames
    resim_olustur(&pacman_anim[0],"textures\\pacman animation\\pacman_0.png",ekran);
    resim_olustur(&pacman_anim[1],"textures\\pacman animation\\pacman_1.png",ekran);
    resim_olustur(&pacman_anim[2],"textures\\pacman animation\\pacman_2.png",ekran);
    resim_olustur(&pacman_anim[3],"textures\\pacman animation\\pacman_3.png",ekran);
    resim_olustur(&pacman_anim[4],"textures\\pacman animation\\pacman_4.png",ekran);
    resim_olustur(&pacman_anim[5],"textures\\pacman animation\\pacman_3.png",ekran);
    resim_olustur(&pacman_anim[6],"textures\\pacman animation\\pacman_2.png",ekran);
    resim_olustur(&pacman_anim[7],"textures\\pacman animation\\pacman_1.png",ekran);
    //ghost animation frames
    resim_olustur(&ghost_anim[0],"textures\\ghost animation\\ghost(0).png",ekran);
    resim_olustur(&ghost_anim[1],"textures\\ghost animation\\ghost(1).png",ekran);
    resim_olustur(&ghost_anim[2],"textures\\ghost animation\\ghost(2).png",ekran);
    resim_olustur(&ghost_anim[3],"textures\\ghost animation\\ghost(3).png",ekran);
    resim_olustur(&ghost_anim[4],"textures\\ghost animation\\ghost(4).png",ekran);
    resim_olustur(&ghost_anim[5],"textures\\ghost animation\\ghost(3).png",ekran);
    resim_olustur(&ghost_anim[6],"textures\\ghost animation\\ghost(2).png",ekran);
    resim_olustur(&ghost_anim[7],"textures\\ghost animation\\ghost(1).png",ekran);
    //numbers
    resim_olustur(&sayilar[0],"textures\\numbers\\0.png",ekran);
    resim_olustur(&sayilar[1],"textures\\numbers\\1.png",ekran);
    resim_olustur(&sayilar[2],"textures\\numbers\\2.png",ekran);
    resim_olustur(&sayilar[3],"textures\\numbers\\3.png",ekran);
    resim_olustur(&sayilar[4],"textures\\numbers\\4.png",ekran);
    resim_olustur(&sayilar[5],"textures\\numbers\\5.png",ekran);
    resim_olustur(&sayilar[6],"textures\\numbers\\6.png",ekran);
    resim_olustur(&sayilar[7],"textures\\numbers\\7.png",ekran);
    resim_olustur(&sayilar[8],"textures\\numbers\\8.png",ekran);
    resim_olustur(&sayilar[9],"textures\\numbers\\9.png",ekran);
    resim_olustur(&sayilar[10],"textures\\numbers\\iki_nokta.png",ekran);

}
void animations(int ghostAmount,int ghost_x_points[],int ghost_y_points[],char ghost_previus[],struct inital_pozitions *struct_name,SDL_Surface* pacman_anim[8]
                ,SDL_Surface* ghost_anim[8],SDL_Surface** background_img,SDL_Surface** point_img,SDL_Surface** wall_img,SDL_Surface** pencere,SDL_Surface** ekran)
{
    int change =0;
    SDL_Rect render_pozisyon;//renderlanacak bölge
            render_pozisyon.x = 0;
            render_pozisyon.y = 0;
            render_pozisyon.w = screen_width/40;
            render_pozisyon.h = screen_height/20;
    for(int i=0;i<8;i++)//for every frame of animation
    {
        if(i%2==0)
            change+=4;
        else
            change+=5;
        SDL_Rect pre_render_pozisyon;//arkada kalanları silmek için arkada kalan alan, ilk olarak oyuncuya renderlı başlıyor hayaletler kendileri için değiştiriyor
            pre_render_pozisyon.x = struct_name->pre_player_x*36;
            pre_render_pozisyon.y = struct_name->pre_player_y*-36;
            pre_render_pozisyon.w = screen_width/40;
            pre_render_pozisyon.h = screen_height/20;
        if(player_x!=struct_name->pre_player_x)
        {
            render_pozisyon.y=(-1*player_y)*36;
            if(player_x<struct_name->pre_player_x)//sola gitti
            {
                render_pozisyon.x=(struct_name->pre_player_x*36)-change;
                SDL_BlitScaled(*background_img,NULL,*ekran,&pre_render_pozisyon);
                SDL_BlitScaled(pacman_anim[i],NULL,*ekran,&render_pozisyon);

            }
            else//saða gitti
            {
                render_pozisyon.x=(struct_name->pre_player_x*36)+change;
                SDL_BlitScaled(*background_img,NULL,*ekran,&pre_render_pozisyon);
                SDL_BlitScaled(pacman_anim[i],NULL,*ekran,&render_pozisyon);
            }
        }
        else
        {
            render_pozisyon.x=player_x*36;
            if(player_y!=struct_name->pre_player_y)
            {
                if(player_y<struct_name->pre_player_y)//aşağı gitti
                {
                    render_pozisyon.y=(struct_name->pre_player_y*-36)+change;
                    SDL_BlitScaled(*background_img,NULL,*ekran,&pre_render_pozisyon);
                    SDL_BlitScaled(pacman_anim[i],NULL,*ekran,&render_pozisyon);
                }
                else//yukarya gitti
                {
                    render_pozisyon.y=(struct_name->pre_player_y*-36)-change;
                    SDL_BlitScaled(*background_img,NULL,*ekran,&pre_render_pozisyon);
                    SDL_BlitScaled(pacman_anim[i],NULL,*ekran,&render_pozisyon);
                }
            }
            else//haraket etmedi
            {
                render_pozisyon.y=(-1*player_y)*36;
                SDL_BlitScaled(pacman_anim[i],NULL,*ekran,&render_pozisyon);
            }
        }
        for(int j=0;j<ghostAmount;j++)//for ghost
        {
            pre_render_pozisyon.x = struct_name->pre_ghost_x[j]*36;
            pre_render_pozisyon.y = struct_name->pre_ghost_y[j]*-36;
            if(ghost_x_points[j]!=struct_name->pre_ghost_x[j])
            {
                render_pozisyon.y=pre_render_pozisyon.y;
                if(ghost_x_points[j]<struct_name->pre_ghost_x[j])//sola gitti
                {
                    render_pozisyon.x=pre_render_pozisyon.x-change;
                    if(ghost_previus[j]==' ')
                    {
                        SDL_BlitScaled(*background_img,NULL,*ekran,&pre_render_pozisyon);
                    }
                    else
                    {
                        SDL_BlitScaled(*point_img,NULL,*ekran,&pre_render_pozisyon);
                    }
                    SDL_BlitScaled(ghost_anim[i],NULL,*ekran,&render_pozisyon);
                }
                else//saða gitti
                {
                    render_pozisyon.x=pre_render_pozisyon.x+change;
                    if(ghost_previus[j]==' ')
                    {
                        SDL_BlitScaled(*background_img,NULL,*ekran,&pre_render_pozisyon);
                    }
                    else
                    {
                        SDL_BlitScaled(*point_img,NULL,*ekran,&pre_render_pozisyon);
                    }
                    SDL_BlitScaled(ghost_anim[i],NULL,*ekran,&render_pozisyon);
                }
            }
            else
            {
                render_pozisyon.x=pre_render_pozisyon.x;
                if(ghost_y_points[j]<struct_name->pre_ghost_y[j])//aşağı gitti
                {
                    render_pozisyon.y=pre_render_pozisyon.y+change;
                    if(ghost_previus[j]==' ')
                    {
                        SDL_BlitScaled(*background_img,NULL,*ekran,&pre_render_pozisyon);
                    }
                    else
                    {
                        SDL_BlitScaled(*point_img,NULL,*ekran,&pre_render_pozisyon);
                    }
                    SDL_BlitScaled(ghost_anim[i],NULL,*ekran,&render_pozisyon);
                }
                else//yukarıya
                {
                    render_pozisyon.y=pre_render_pozisyon.y-change;
                    if(ghost_previus[j]==' ')
                    {
                        SDL_BlitScaled(*background_img,NULL,*ekran,&pre_render_pozisyon);
                    }
                    else
                    {
                        SDL_BlitScaled(*point_img,NULL,*ekran,&pre_render_pozisyon);
                    }
                    SDL_BlitScaled(ghost_anim[i],NULL,*ekran,&render_pozisyon);
                }
            }
        }
        SDL_UpdateWindowSurface( *pencere );
        Sleep(sleep_time);
    }
    for(int i=0;i<ghostAmount;i++)
    {
        struct_name->pre_ghost_x[i]=ghost_x_points[i];
        struct_name->pre_ghost_y[i]=ghost_y_points[i];
    }
    struct_name->pre_player_x=player_x;
    struct_name->pre_player_y=player_y;
    Sleep(sleep_time/5);
}
void pre_draw_map(char harita[][map_x],SDL_Surface** background_img,SDL_Surface** point_img,SDL_Surface** wall_img,SDL_Surface** ekran)
{
    SDL_Rect render_pozisyon;//renderlanacak bölge
            render_pozisyon.x = 0;
            render_pozisyon.y = 0;
            render_pozisyon.w = screen_width/40;
            render_pozisyon.h = screen_height/20;
    for(int i=0;i<map_y;i++)
        {
            render_pozisyon.y=i*36;
            for(int j=0;j<map_x-1;j++)
            {
                if((i==0&&(j==19||j==20))||(i==19&&(j==19||j==20)))
                    continue;
                render_pozisyon.x=j*36;
                if(harita[i][j]==wall_symbol)
                {
                    SDL_BlitScaled(*wall_img,NULL,*ekran,&render_pozisyon);
                }
                else if(harita[i][j]==points_c)
                {
                    SDL_BlitScaled(*point_img,NULL,*ekran,&render_pozisyon);
                }
                else
                {
                    SDL_BlitScaled(*background_img,NULL,*ekran,&render_pozisyon);
                }
            }
        }
}
void time_and_point_draw(SDL_Surface* sayilar[11],int time,int points_,SDL_Surface** ekran,SDL_Surface** pencere)
{
    SDL_Rect render_pozisyon;//renderlanacak bölge
            render_pozisyon.x = 36*19;
            render_pozisyon.y = 0;
            render_pozisyon.w = 17;
            render_pozisyon.h = 36;
    //zaman yenile
    SDL_BlitScaled(sayilar[time/600],NULL,*ekran,&render_pozisyon);//dakika 10 lar basamağı
    render_pozisyon.x+=17;
    SDL_BlitScaled(sayilar[(time/60)%10],NULL,*ekran,&render_pozisyon);//dakika 1 ler basamağı
    render_pozisyon.x+=17;
    render_pozisyon.w=4;
    SDL_BlitScaled(sayilar[10],NULL,*ekran,&render_pozisyon);// : koyuyor
    render_pozisyon.x+=4;
    render_pozisyon.w=17;
    SDL_BlitScaled(sayilar[(time%60)/10],NULL,*ekran,&render_pozisyon);//saniye 10lar basamağı
    render_pozisyon.x+=17;
    SDL_BlitScaled(sayilar[time%10],NULL,*ekran,&render_pozisyon);//saniye 1ler basamağı
    // puanları yenile
    render_pozisyon.x = 36*19;
    render_pozisyon.y = 36*19;
    SDL_BlitScaled(sayilar[points_/1000],NULL,*ekran,&render_pozisyon);//dakika 10 lar basamağı
    render_pozisyon.x+=18;
    SDL_BlitScaled(sayilar[(points_/100)%10],NULL,*ekran,&render_pozisyon);//dakika 10 lar basamağı
    render_pozisyon.x+=18;
    SDL_BlitScaled(sayilar[(points_/10)%10],NULL,*ekran,&render_pozisyon);//dakika 10 lar basamağı
    render_pozisyon.x+=18;
    SDL_BlitScaled(sayilar[points_%10],NULL,*ekran,&render_pozisyon);//dakika 10 lar basamağı
    //ekranı yenile
    SDL_UpdateWindowSurface( *pencere );
}
int main(int argc,char* argv[])
{
    time_t zaman =time(0),kayip_zaman=0;
    char harita[map_y][map_x];
    map_maker(harita);
    int ghost_x_points[ghost_amount]={5,34,5,34};
    int ghost_y_points[ghost_amount]={-5,-5,-14,-14};
    char ghost_previus[ghost_amount]={points_c,points_c,points_c,points_c};//what was there before ghost came
    char ghost_directions[ghost_amount]={'s','s','w','w'};//not a string !!!dont try to read whit %s or similar!!!
    harita[player_x][-1*player_y] = player_symbol;
    struct inital_pozitions struct_name={{5,34,5,34},{-5,-5,-14,-14},player_x,player_y};
    // pencere
    SDL_Window* pencere = NULL;

    //The surface contained by the window
    SDL_Surface* ekran = NULL;
    //resim
    SDL_Surface* pacman_animasyon_kareler[8] = {NULL};
    SDL_Surface* ghost_animasyon_kareler[8] = {NULL};
    SDL_Surface* sayilar[11] = {NULL};
    SDL_Surface* wall_img=NULL;
    SDL_Surface* background_img=NULL;
    SDL_Surface* point_img=NULL;
    SDL_Surface* Game_over_img=NULL;

    if(my_initilazer(&pencere,&ekran));
    else
    {
        anim_yukle(pacman_animasyon_kareler,ghost_animasyon_kareler,&ekran,sayilar);
        resim_olustur(&wall_img,"textures\\wall.png",&ekran);
        resim_olustur(&background_img,"textures\\back_ground.png",&ekran);
        resim_olustur(&point_img,"textures\\point.png",&ekran);
        resim_olustur(&Game_over_img,"textures\\game_over.png",&ekran);
    }
    pre_draw_map(harita,&background_img,&point_img,&wall_img,&ekran);
    SDL_UpdateWindowSurface( pencere );
    int non_repat=0;
    while(is_alive)//gameloop
    {
        //make a map
        ghost_colony(harita,ghost_amount,ghost_x_points,ghost_y_points,ghost_directions,ghost_previus);
        if(!is_alive)
        {
            //draw_map(harita);
            break;
        }
        player_update(harita);
        //draw_map(harita);
        animations(ghost_amount,ghost_x_points,ghost_y_points,ghost_previus,&struct_name,pacman_animasyon_kareler
                    ,ghost_animasyon_kareler,&background_img,&point_img,&wall_img,&pencere,&ekran);
        time_and_point_draw(sayilar,(time(0)-zaman)-kayip_zaman,points,&ekran,&pencere);
        //system("cls");
        //printf("\ntime:%ds  points:%d",(time(0)-zaman)-kayip_zaman,points);
        girdi(harita);
        if((int)(time(0)-zaman)%10==0&&non_repat!=(int)(time(0)-zaman))
        {
            non_repat=(int)(time(0)-zaman);
            pre_draw_map(harita,&background_img,&point_img,&wall_img,&ekran);
        }
        if(player_direction==27)
        {
            time_t temp_zaman = time(0);
            printf("\nGAME IS STOPPED");
            while(player_direction==27)
            {
                girdi(harita);
            }
            kayip_zaman += time(0)-temp_zaman;
        }
        //add big point makes you eat ghost
        //add winning condition
        //add score board maybe?
        //add sounds
        //makke better graficks
        //find a way to not compress images if cant, make new images as 36X36
    }
    printf("\nYou are dead! Game is over.");
    SDL_Rect render_pozisyon;//renderlanacak bölge
            render_pozisyon.x = 0;
            render_pozisyon.y = 36;
            render_pozisyon.w = screen_width;
            render_pozisyon.h = screen_height-72;
    SDL_BlitScaled(Game_over_img,NULL,ekran,&render_pozisyon);
    SDL_UpdateWindowSurface( pencere );
    while(player_direction!='q')
    {
        SDL_Event e;
        SDL_PollEvent(&e);
        if(e.type == SDL_QUIT)
        {
            player_direction='q';
        }
    }
    return 0;
}
