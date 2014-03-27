#include <allegro.h>
#include <vector>

struct position
{
	int x;
	int y;
};

void respondToKeyboard(void);
void bombAnim(void);
bool girderCollision();
SAMPLE *music;
BITMAP *ground;
BITMAP *bomb;
BITMAP *hole;
BITMAP *player;
BITMAP *pusher;
BITMAP *girder;
BITMAP *buffer;//used for double buffering
volatile position playerXY;
volatile int playerAnimY;
volatile int playerAnimX;
volatile int bombAnimX;
std::vector<position> girderPosition;
std::vector<position> bombPosition;

int main(void)
{
	allegro_init(); //Initialize Allegro
	install_keyboard();//Allow keyboard input
	install_sound( DIGI_AUTODETECT, MIDI_AUTODETECT, NULL );
	install_timer();
	set_color_depth(32);//Set the colour depth to 32 bit
	set_gfx_mode( GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0 ); //Sets the graphics mode
	buffer = create_bitmap(SCREEN_W,SCREEN_H);//for double buffer
	music = load_sample( "killingTime.wav" );
	ground = load_bitmap( "floor.bmp", NULL );
	bomb = load_bitmap( "bomb.bmp", NULL );
	hole = load_bitmap( "hole.bmp", NULL );
	player = load_bitmap( "remotePusher.bmp", NULL );
	pusher = load_bitmap( "pusher.bmp", NULL );
	girder = load_bitmap( "girder.bmp", NULL );
	//play_sample( music, 255, 128, 1000, 1 );
	playerXY.x = 32;
	playerXY.y = 32;
	playerAnimY = 0;
	playerAnimX = 0;
	bombAnimX = 2;
	install_int( bombAnim,100 );
	install_int( respondToKeyboard,10 );
	girderPosition.resize(66);
	bombPosition.resize(2);
	int a = 0;
	for (int i = 0;i < 20; i++)
	{
		girderPosition[i].x = (a*32);
		girderPosition[i].y = 0;
		a++;
	}
	a = 0;
	for (int i = 20;i < 40; i++)
	{
		girderPosition[i].x = (a*32);
		girderPosition[i].y = 448;
		a++;
	}
	a = 1;
	for (int i = 40; i < 53; i++)
	{
		girderPosition[i].x = 0;
		girderPosition[i].y = (a*32);
		a++;
	}
	a = 1;
	for (int i = 53;i < 66; i++)
	{
		girderPosition[i].x = 608;
		girderPosition[i].y = (a*32);
		a++;
	}
	bombPosition[0].x = 64;
	bombPosition[0].y = 64;
	bombPosition[1].x = 128;
	bombPosition[1].y = 128;
	while(!key[KEY_ESC])
	{	
		blit( ground,buffer, 0, 0, 0, 0, 640, 480 );		
		masked_blit( hole,buffer, 0, 0, 32, 64, 32, 32 );
		for (int i = 0;i < 2; i++)
		{
			masked_blit( bomb,buffer, bombAnimX, 2, bombPosition[i].x, bombPosition[i].y, 28, 28 );
		}
		masked_blit( pusher,buffer, 0, 0, 32, 96, 32, 32 );
		for (int i = 0;i < 66; i++)
		{
			masked_blit( girder,buffer, 0, 0, girderPosition[i].x, girderPosition[i].y, girder->w, girder->h );
		}
		masked_blit( player,buffer, playerAnimX, playerAnimY, playerXY.x, playerXY.y, 32, 32 );
		blit( buffer,screen,0,0,0,0,buffer->w,buffer->h );
	}
	destroy_sample( music );
	destroy_bitmap( ground );
	destroy_bitmap( bomb );
	destroy_bitmap( hole );
	destroy_bitmap( player );
	destroy_bitmap( pusher );
	destroy_bitmap( girder );
	remove_int(bombAnim);
	remove_int(respondToKeyboard);
	return 0;
}
END_OF_MAIN()

int collision(int object1X, int object1Y, int object1Width, int object1Height, int object2X, int object2Y, int object2Width, int object2Height)//made using http://wiki.allegro.cc/index.php?title=Bounding_Box
{ 
    if ((object1X > object2X + object2Width - 1) || // check if object 1 is to the right of object 2
        (object1Y > object2Y + object2Height - 1) || // check if object 1 is under object 2
        (object2X > object1X + object1Width - 1) || // check if object 2 is to the right of object 1
        (object2Y > object1Y + object1Height - 1))   // check if object 2 is under object 1
    {
        // no collision
        return 0;
    }
 
    // collision
    return 1;
}

bool girderCollision()
{
	bool crash = false;
	for (int i = 0; i < 66; i++)
	{
		if(collision(playerXY.x, playerXY.y, 32, 32, girderPosition[i].x, girderPosition[i].y, 32, 32) == 1)
		{
			crash = true;
		}
	}
	return crash;
}

bool bombGirderCollision(int bomb)
{
	bool crash = false;
	for (int i = 0; i < 66; i++)
	{
		if(collision(bombPosition[bomb].x, bombPosition[bomb].y, 28, 28, girderPosition[i].x, girderPosition[i].y, 32, 32) == 1)
		{
			crash = true;
		}
	}
	return crash;
}

bool bombCollision()
{
	bool crash = false;
	for (int i = 0; i < 2; i++)
	{
		if(collision(playerXY.x, playerXY.y, 32, 32, bombPosition[i].x, bombPosition[i].y, 28, 28) == 1)
		{
			crash = true;
		}
	}
	return crash;
}

bool bombBombCollision()
{
	bool crash = false;
	if(collision(bombPosition[0].x, bombPosition[0].y, 28, 28, bombPosition[1].x, bombPosition[1].y, 28, 28) == 1)
		{
			crash = true;
		}
	return crash;
}

void bombAnim()
{
	switch(bombAnimX)
	{
	case 2:
		bombAnimX = 34;
		break;
	case 34:
		bombAnimX = 66;
		break;
	case 66:
		bombAnimX = 98;
		break;
	case 98:
		bombAnimX = 2;
	break;
	}
}

void respondToKeyboard()
{
	if(key[KEY_W])
	{	
		playerXY.y--;
		if(girderCollision() == false)
		{
		}
		else
		{
			playerXY.y++;
		}
		if(bombCollision() == false)
		{
		}
		else
		{
			for (int i = 0; i < 2; i++)
			{
				bombPosition[i].y--;
				if(bombGirderCollision(i) == false && bombBombCollision() == false)
				{
				}
				else
				{
					bombPosition[i].y++;
					playerXY.y++;
				}
			}
		}
		playerAnimY = 0;
		playerAnimX += 32;
		if(playerAnimX > 64 )
		{
			playerAnimX = 0;
		}
	}
	if(key[KEY_S])
	{
		playerXY.y++;
		if(girderCollision() == false)
		{
		}
		else
		{
			playerXY.y--;
		}
		if(bombCollision() == false)
		{
		}
		else
		{
			for (int i = 0; i < 2; i++)
			{
				bombPosition[i].y++;
				if(bombGirderCollision(i) == false && bombBombCollision() == false)
				{
				}
				else
				{
					bombPosition[i].y--;
					playerXY.y--;
				}
			}
		}
		playerAnimY = 96;
		playerAnimX += 32;
		if(playerAnimX > 64 )
		{
			playerAnimX = 0;
		}
	}

	if(key[KEY_A])
	{
		playerXY.x--;
		if(girderCollision() == false)
		{
		}
		else
		{
			playerXY.x++;
		}
		if(bombCollision() == false)
		{
		}
		else
		{
			for (int i = 0; i < 2; i++)
			{
				bombPosition[i].x--;
				if(bombGirderCollision(i) == false && bombBombCollision() == false)
				{
				}
				else
				{
					bombPosition[i].x++;
					playerXY.x++;
				}
			}
		}
		playerAnimY = 64;
		playerAnimX += 32;
		if(playerAnimX > 64 )
		{
			playerAnimX = 0;
		}
	}
	if(key[KEY_D])
	{
		playerXY.x++;
		if(girderCollision() == false)
		{
		}
		else
		{
			playerXY.x--;
		}
		if(bombCollision() == false)
		{
		}
		else
		{
			for (int i = 0; i < 2; i++)
			{
				bombPosition[i].x++;
				if(bombGirderCollision(i) == false && bombBombCollision() == false)
				{
				}
				else
				{
					playerXY.x--;
					bombPosition[i].x--;
					
				}
			}
		}
		playerAnimY = 32;
		playerAnimX += 32;
		if(playerAnimX > 64 )
		{
			playerAnimX = 0;
		}
	}
	if(key[KEY_R])
	{
		playerXY.x = 32;
		playerXY.y = 32;
		playerAnimY = 0;
		playerAnimX = 0;
		bombAnimX = 2;
		bombPosition[0].x = 64;
		bombPosition[0].y = 64;
		bombPosition[1].x = 128;
		bombPosition[1].y = 128;
	}
}