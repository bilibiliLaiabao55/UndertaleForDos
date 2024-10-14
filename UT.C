#include "resource.c"
#include <graphics.h>
#include <stdio.h>
#include <math.h>
float player_x=0,player_y=0, player_frame=0,player_frame_delay=0,player_face=0;
int done=0;
int temp0=0;
int camera_pos[2]={0, 0};
const double FPS = 1/30;

const int *frisk_down[4]={
	frisk_down00,
	frisk_down01,
	frisk_down00,
	frisk_down02
};
const int *frisk_left[4]={
	frisk_left00,
	frisk_left01,
	frisk_left00,
	frisk_left01
};
const int *frisk_up[4]={
	frisk_up00,
	frisk_up01,
	frisk_up00,
	frisk_up02
};
const int **frisk_images[4]={
	frisk_down,
	frisk_left,
	frisk_left,
	frisk_up
};
void draw(const int* pixelData, int width, int height, int x, int y, int flipX) {
    int y1, x1;
    for (x1 = 0; x1 < width; ++x1) {
		for (y1 = 0; y1 < height; ++y1) {
			temp0 = pixelData[y1*width+x1];
			if(flipX==1){temp0 = pixelData[y1*width+(width-1-x1)];}
			if(temp0==255){
				continue;
			}
			putpixel(x1+x-camera_pos[0], y1+y-camera_pos[1], temp0);
		}
    }
}

void play_anim(){
	if(player_frame_delay<=0){
		if(player_frame<3)
			++player_frame;
		else
			player_frame=0;
		player_frame_delay=120;
	}else
	--player_frame_delay;
}
void camera_scroll(){
	//0x330
	setviewport(camera_pos[0], camera_pos[1], getmaxx(), getmaxy(), 0);
}
int gdriver = DETECT;
int gmode = MCGAHI;
void main() {
	registerbgidriver(EGAVGA_driver);
    initgraph(&gdriver, &gmode, "");
    setbkcolor(EGA_MAGENTA);
    while(!done){
		delay(FPS);
		//camera_scroll();
		draw(frisk_images[player_face][player_frame],20,30,player_x,player_y, (player_face==2));
		if(inportb(0x60)==1){
			done=1;
		}
		if(inportb(0x60)==72){
			play_anim();
			player_face=3;
			player_y-=0.1;
		}

		if(inportb(0x60)==75){
			play_anim();
			player_face=1;
			player_x-=0.1;
		}
		if(inportb(0x60)==77){
			play_anim();
			player_face=2;
			player_x+=0.1;
		}
		if(inportb(0x60)==80){
			play_anim();
			player_face=0;
			player_y+=0.1;
		}
	}
	clrscr();
    closegraph();
}