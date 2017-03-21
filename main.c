//*****************************************************************************
// main.c
// Authors: Nick Berkhout, James Earley, Justin Knapp, Evan Williams
//*****************************************************************************
#include "lab_buttons.h"

#define MOVE_PIXELS   1

// Turn Debugging off
#undef DEBUG

#ifdef DEBUG
#define DEBUG_PRINT(x) printf x
#else
#define DEBUG_PRINT(x) do {} while (0)
#endif

#define BUTTON_UP 0x01
#define BUTTON_DOWN 0x02
#define BUTTON_LEFT 0x04
#define BUTTON_RIGHT 0x08
#define GREEN			0x01
#define BLUE			0x02
	
/*****************************************************************************
 * function declarations These declarations need to be stated before they
 * are used in the main routine. Up here is a good place to declare them.
 ****************************************************************************/
	
void updateCoordinates(uint16_t xPos, uint16_t yPos, uint8_t butPressed, int playerNumber);
void updateCollision(uint16_t xPos, uint16_t yPos, int playerNumber);
void updateDraw(void);
uint8_t updateP1Direction(void);
void updateP2Direction(void);
void countdown(void);
void drawBorder(void);
void createBoard(void);

/******************************************************************************
 * Global Variables
 *****************************************************************************/

uint8_t buttons;
bool Ready = false;
bool titleLoop = false;
bool gameOver = false;
bool playGame = true;
bool checkPlayGame = true;
uint32_t time_delay = 1000;
uint16_t player1x;
uint16_t player1y;
uint16_t player2x;
uint16_t player2y;
uint8_t player1but;
uint8_t player2but;
uint32_t player1Color;
uint32_t player2Color;
bool P1Win = false;
bool P2Win = false;
int scalePixel = 6;
int arraySize = 40;

uint8_t recent[2] = { BUTTON_UP, BUTTON_DOWN};
//Create 30 x 30 grid
bool color[40][40];


//*****************************************************************************
//*****************************************************************************
int 
main(void) {
	ece210_initialize_board();
  	ece210_lcd_add_msg("TRON: THE GAME\n\r",TERMINAL_ALIGN_CENTER,LCD_COLOR_CYAN);
	ece210_lcd_add_msg("",TERMINAL_ALIGN_CENTER,LCD_COLOR_BLUE);
	ece210_lcd_add_msg("",TERMINAL_ALIGN_CENTER,LCD_COLOR_BLUE);
	ece210_lcd_add_msg("",TERMINAL_ALIGN_CENTER,LCD_COLOR_BLUE);
	ece210_lcd_add_msg("",TERMINAL_ALIGN_CENTER,LCD_COLOR_BLUE);
	ece210_lcd_add_msg("",TERMINAL_ALIGN_CENTER,LCD_COLOR_BLUE);
	ece210_lcd_add_msg("",TERMINAL_ALIGN_CENTER,LCD_COLOR_BLUE);
	ece210_lcd_add_msg("Ready to Play?",TERMINAL_ALIGN_CENTER,LCD_COLOR_CYAN);
	ece210_lcd_add_msg("Press the UP button.",TERMINAL_ALIGN_CENTER,LCD_COLOR_CYAN);
	ece210_lcd_add_msg("",TERMINAL_ALIGN_CENTER,LCD_COLOR_BLUE);

	player1Color = LCD_COLOR_GREEN;
	player2Color = LCD_COLOR_RED;
	ece210_lcd_add_msg("Joystick will play as GREEN",TERMINAL_ALIGN_CENTER,LCD_COLOR_GREEN);	
	ece210_lcd_add_msg("Buttons will play as RED",TERMINAL_ALIGN_CENTER,LCD_COLOR_RED);	
		
  
  while(!titleLoop)
  {
    
  	if(AlertButtons && !Ready)
    	{
      		AlertButtons = false;
     		buttons = ece210_buttons_read();
      			if(buttons == BUTTON_UP)
      			{
				ece210_lcd_add_msg("You are ready", TERMINAL_ALIGN_CENTER, LCD_COLOR_GREEN) ;
				Ready = true;
				titleLoop = true;
      			}
		
    	}
  }	
	while(playGame)
	{
	if (Ready)
		{			
			
			ece210_wait_mSec(  time_delay );
			ece210_lcd_add_msg("",TERMINAL_ALIGN_CENTER,LCD_COLOR_BLUE);
			ece210_lcd_add_msg("Game will now begin", TERMINAL_ALIGN_CENTER, LCD_COLOR_CYAN);
		
			//clear screen
			ece210_lcd_add_msg("",TERMINAL_ALIGN_CENTER,LCD_COLOR_BLUE);
			ece210_lcd_add_msg("",TERMINAL_ALIGN_CENTER,LCD_COLOR_BLUE);
			ece210_lcd_add_msg("",TERMINAL_ALIGN_CENTER,LCD_COLOR_BLUE);
			ece210_lcd_add_msg("",TERMINAL_ALIGN_CENTER,LCD_COLOR_BLUE);
			ece210_lcd_add_msg("",TERMINAL_ALIGN_CENTER,LCD_COLOR_BLUE);
			ece210_lcd_add_msg("",TERMINAL_ALIGN_CENTER,LCD_COLOR_BLUE);
			ece210_lcd_add_msg("",TERMINAL_ALIGN_CENTER,LCD_COLOR_BLUE);
			ece210_lcd_add_msg("",TERMINAL_ALIGN_CENTER,LCD_COLOR_BLUE);
			ece210_lcd_add_msg("",TERMINAL_ALIGN_CENTER,LCD_COLOR_BLUE);
			ece210_lcd_add_msg("",TERMINAL_ALIGN_CENTER,LCD_COLOR_BLUE);
			ece210_lcd_add_msg("",TERMINAL_ALIGN_CENTER,LCD_COLOR_BLUE);
			ece210_lcd_add_msg("",TERMINAL_ALIGN_CENTER,LCD_COLOR_BLUE);
			ece210_lcd_add_msg("",TERMINAL_ALIGN_CENTER,LCD_COLOR_BLUE);
			ece210_lcd_add_msg("",TERMINAL_ALIGN_CENTER,LCD_COLOR_BLUE);
			ece210_lcd_add_msg("",TERMINAL_ALIGN_CENTER,LCD_COLOR_BLUE);
			ece210_lcd_add_msg("",TERMINAL_ALIGN_CENTER,LCD_COLOR_BLUE);
			ece210_initialize_board();
			
		}
	//Create Board and Set Default Variables
	createBoard();
	player1x = arraySize /2;
	player1y = 2;
	player2x = arraySize /2;
	player2y = arraySize - 3;
	gameOver = false;
	recent[0] = BUTTON_UP;
	recent[1] = BUTTON_DOWN;
	uint8_t player1but = BUTTON_UP;
	uint8_t player2but = BUTTON_DOWN;

	//Draw Game Border
	drawBorder();
		
	//RGB LED Count Down Sequence
	countdown();
		
		while (!gameOver) {
			// joystick
			player1but = updateP1Direction();
			updateP2Direction();


			player1but = recent[0];
			player2but = recent[1];
				//player1
				updateCoordinates(player1x, player1y, player1but, 1);
				//player2
				updateCoordinates(player2x, player2y, player2but, 2);
			
			//player1
			updateCollision(player1x, player1y, 1);
			//player2
			updateCollision(player2x, player2y, 2);
			if (gameOver) {
						
						break;
			}
			updateDraw();
			ece210_wait_mSec(150);
		}		
			//Turn on the bottom LEDS
			ece210_ws2812b_write(0, 0xff, 0, 0);
			ece210_ws2812b_write(1, 0xff, 0, 0);
			ece210_ws2812b_write(2, 0xff, 0, 0);
			ece210_ws2812b_write(3, 0xff, 0, 0);
			ece210_ws2812b_write(4, 0xff, 0, 0);
			ece210_ws2812b_write(5, 0xff, 0, 0);
			ece210_ws2812b_write(6, 0xff, 0, 0);
			ece210_ws2812b_write(7, 0xff, 0, 0);

			ece210_wait_mSec(time_delay*2);
			//Turn them back off
			ece210_ws2812b_write(0, 0, 0, 0);
			ece210_ws2812b_write(1, 0, 0, 0);
			ece210_ws2812b_write(2, 0, 0, 0);
			ece210_ws2812b_write(3, 0, 0, 0);
			ece210_ws2812b_write(4, 0, 0, 0);
			ece210_ws2812b_write(5, 0, 0, 0);
			ece210_ws2812b_write(6, 0, 0, 0);
			ece210_ws2812b_write(7, 0, 0, 0);
			if (P1Win && P2Win){
				ece210_lcd_add_msg("Tie!",TERMINAL_ALIGN_CENTER,LCD_COLOR_CYAN);
			}
			else if (P1Win && !P2Win){
				ece210_lcd_add_msg("Green Wins!",TERMINAL_ALIGN_CENTER,LCD_COLOR_GREEN);
			}
			else{
				ece210_lcd_add_msg("Red Wins!",TERMINAL_ALIGN_CENTER,LCD_COLOR_RED);
			}
			ece210_lcd_add_msg("",TERMINAL_ALIGN_CENTER,LCD_COLOR_GREEN);
			ece210_lcd_add_msg("",TERMINAL_ALIGN_CENTER,LCD_COLOR_GREEN);
			ece210_lcd_add_msg("",TERMINAL_ALIGN_CENTER,LCD_COLOR_GREEN);
			ece210_lcd_add_msg("Play Again?",TERMINAL_ALIGN_CENTER,LCD_COLOR_CYAN);
			ece210_lcd_add_msg("Press UP for YES",TERMINAL_ALIGN_CENTER,LCD_COLOR_CYAN);
			checkPlayGame = true;
			P1Win = false;
			P2Win = false;
			
			while (checkPlayGame)
			{
				if(AlertButtons)
				{
				AlertButtons = false;
				buttons = ece210_buttons_read();
				if(buttons == BUTTON_UP)
				{
					playGame = true;
					checkPlayGame = false;
				}
			}
		
    	}
    }
}




//****************************************************************************************




void updateCoordinates(uint16_t xPos, uint16_t yPos, uint8_t butPressed, int playerNumber){
	
	if( playerNumber == 1)
	{
		if(butPressed == BUTTON_UP){
			player1y = yPos + 1;
		}
		else if(butPressed == BUTTON_DOWN){
			player1y = yPos - 1;
		}
		else if(butPressed == BUTTON_LEFT){
			player1x = xPos - 1;
		}
		else if(butPressed == BUTTON_RIGHT){
			player1x = xPos + 1;
		}
	}
	else if (playerNumber == 2)
	{
		if(butPressed == BUTTON_UP){
			player2y = yPos + 1;
		}
		else if(butPressed == BUTTON_DOWN){
			player2y = yPos - 1;
		}
		else if(butPressed == BUTTON_LEFT){
			player2x = xPos + 1;
		}
		else if(butPressed == BUTTON_RIGHT){
			player2x = xPos - 1;
		}
	}




	
		
}
//****************************************************************************************




void updateCollision(uint16_t xPos, uint16_t yPos, int playerNumber){
	if(color[xPos][yPos] == true){
		gameOver = true;
		
		if (playerNumber == 1){
			P2Win = true;
		}
		else {
			P1Win = true;
		}			
		
}
	else{
		color[xPos][yPos] = true;
	}
}




//*****************************************************************************************




void updateDraw(void){
	
	for(int i = 0; i < scalePixel; i++){
		for(int j = 0; j < scalePixel; j++){
			ece210_draw_pixel(((player1x * scalePixel) + i),((player1y * scalePixel) + j), player1Color);
			ece210_draw_pixel(((player2x * scalePixel) + i),((player2y * scalePixel) + j), player2Color);
		}
	}
}
//******************************************************************************************
uint8_t updateP1Direction(void){
		
	uint16_t xVal = ece210_ps2_read_x();
	uint16_t yVal = ece210_ps2_read_y();
	
	if( xVal >= PS2_THRESHOLD_X_HI && recent[0] != BUTTON_LEFT) {
		recent[0] = BUTTON_RIGHT;
		return BUTTON_RIGHT;
	}
	else if ( xVal <= PS2_THRESHOLD_X_LO  && recent[0] != BUTTON_RIGHT) {
		recent[0] = BUTTON_LEFT;
		return BUTTON_LEFT;
	}
	else if ( yVal >= PS2_THRESHOLD_Y_HI && recent[0] != BUTTON_DOWN) {
		recent[0] = BUTTON_UP;
		return BUTTON_UP;
	}
	else if( yVal <= PS2_THRESHOLD_Y_LO && recent[0] != BUTTON_UP) {
		recent[0] = BUTTON_DOWN;
		return BUTTON_DOWN;
	}
	
	return recent[0];
}




//******************************************************************************************
void updateP2Direction(void) {
	 
		if(ece210_buttons_read() == BUTTON_UP && recent[1] != BUTTON_DOWN){
			recent[1] = BUTTON_UP;
		}
		else if(ece210_buttons_read() == BUTTON_DOWN && recent[1] != BUTTON_UP){
			recent[1] = BUTTON_DOWN;
			
		}
		else if(ece210_buttons_read() == BUTTON_LEFT && recent[1] != BUTTON_RIGHT){
			recent[1] = BUTTON_LEFT;
		}
		else if(ece210_buttons_read() == BUTTON_RIGHT && recent[1] != BUTTON_LEFT){
			recent[1] = BUTTON_RIGHT;
		}
}
 //**********************************************************************************************
void countdown(void) {
	
	//RGB LED Count Down Sequence
	ece210_ws2812b_write(0, 0, 0, 0);
	ece210_ws2812b_write(1, 0, 0, 0);
	ece210_ws2812b_write(2, 0, 0, 0);
	ece210_ws2812b_write(3, 0, 0, 0);
	ece210_ws2812b_write(4, 0, 0, 0);
	ece210_ws2812b_write(5, 0, 0, 0);
	ece210_ws2812b_write(6, 0, 0, 0);
	ece210_ws2812b_write(7, 0, 0, 0);
					
	ece210_ws2812b_write(0, 0xff, 0, 0);
	ece210_ws2812b_write(1, 0xff, 0, 0);
					
	ece210_wait_mSec( time_delay);
					
	ece210_ws2812b_write(2, 0xff, 0, 0);
	ece210_ws2812b_write(3, 0xff, 0, 0);
	ece210_ws2812b_write(4, 0xff, 0, 0);
					
	ece210_wait_mSec( time_delay);
					
	ece210_ws2812b_write(5, 0xff, 0, 0);
	ece210_ws2812b_write(6, 0xff, 0, 0);
	ece210_ws2812b_write(7, 0xff, 0, 0);
					
	ece210_wait_mSec( time_delay);
					
	ece210_ws2812b_write(0, 0, 0xff, 0);
	ece210_ws2812b_write(1, 0, 0xff, 0);
	ece210_ws2812b_write(2, 0, 0xff, 0);
	ece210_ws2812b_write(3, 0, 0xff, 0);
	ece210_ws2812b_write(4, 0, 0xff, 0);
	ece210_ws2812b_write(5, 0, 0xff, 0);
	ece210_ws2812b_write(6, 0, 0xff, 0);
	ece210_ws2812b_write(7, 0, 0xff, 0);
					
	ece210_wait_mSec( time_delay);
					
	ece210_ws2812b_write(0, 0, 0, 0);
	ece210_ws2812b_write(1, 0, 0, 0);
	ece210_ws2812b_write(2, 0, 0, 0);
	ece210_ws2812b_write(3, 0, 0, 0);
	ece210_ws2812b_write(4, 0, 0, 0);
	ece210_ws2812b_write(5, 0, 0, 0);
	ece210_ws2812b_write(6, 0, 0, 0);
	ece210_ws2812b_write(7, 0, 0, 0);
	
}




//********************************************************************************
void drawBorder(void) {
	
	for (int p = 0; p < arraySize; p += 1)
		{
			for (int q = 0; q < arraySize; q += 1)
			{
				if(color[p][q])
				{
					for (int k = 0; k < scalePixel; k += 1)
					{
						for (int o = 0; o < scalePixel; o += 1)
						{
							ece210_draw_pixel( scalePixel * p + k, scalePixel * q + o, LCD_COLOR_BLUE);
						}
					}
				}
			}
		}
	updateDraw();
}
//*********************************************************************************

void createBoard(void) {
	for (int p = 0; p < arraySize; p += 1)
		{
			for (int q = 0; q < arraySize; q += 1)
			{
				if (p == 0 || p == arraySize - 1 || q == 0 || q == arraySize -1)
				{
					color[p][q] = true;
				}
				else
				{
					color[p][q] = false;
				}
			}
		}
	}


