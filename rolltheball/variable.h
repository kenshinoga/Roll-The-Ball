#pragma once
#define PuzzleSize 6  //パズルの一辺の長さ
#define id 1
#define idastar1 2
#define idastar2 3
#define stage_sum 7

// 変数
const int WindowSize_x = 960;
const int WindowSize_y = 640;
unsigned int Color = GetColor(255, 255, 255);
unsigned int Color2 = GetColor(255, 0, 255);
unsigned int Color3 = GetColor(0, 0, 0);
char filename[500];
enum st {TITLE, MENU, METHOD, STAGE, RANDUM, START, MAIN, OPTION };
clock_t start_clock, end_clock;

int status = RANDUM;
int MouseInput;
int MouseX = 0, MouseY = 0;
int menucursor = 0;
int dfscount = 0;
int framecount = 0;
bool dfsflg = 0;
bool mouseflg = FALSE;
int count = 0;
int stage_num = 1;
bool KEYDOWNflg = 0;
bool IsPlaying = FALSE;
bool IsGameOver = FALSE;

int trycount = 0;
int count2 = 0;
bool animeflg = 0;
int method_num = 1;
int stage[PuzzleSize * PuzzleSize] = {};
int stage_clear[16] = {};

const int generatenum = 5;
int generated_stage[generatenum][PuzzleSize * PuzzleSize] = { 0 };

const int RandumPuzzleSize = 474; //耐久パズルのピクセルでの一辺の長さ
const int RandumPuzzleOneSize = RandumPuzzleSize / PuzzleSize;
const int RandumPuzzleGap_x = 50, RandumPuzzleGap_y = 120;
int Button;
int MouseLogType;
bool IsClick = FALSE;
int DownPanel_x, DownPanel_y;


//////音と画像メモリ用ハンドル/////////
int pic_road[25];
int pic_title;
int pic_startbutton;
int pic_randumstage;
int pic_menuselect[4];
int pic_menucursor;

int sound_title;
int sound_title_enter;
int sound_menu_cursor;
int sound_cancel;
int sound_randumpuzzle;
int sound_gameover;



/////////////////////

FILE* fp2;
int Stage[20][16] = { { 22,21,21,21,     /*2手問題*/
                         22, 2, 2,16,
                          6, 2,18,22,
                          5,21,22,21 },

                       {22,22,22,22,     /*5手問題*/
                         2, 6,18, 3,
                         5, 2, 2,22,
                        14, 8, 2, 4 },

                       { 2,22, 1, 3,       /*7手問題*/
                        22,14, 8,22,
                         6, 2, 2, 4,
                         2, 5, 2,18 },

                       { 2, 2, 2,17,      /*9手問題*/
                        12, 4, 2,22,
                         5,22,22, 4,
                        14, 2, 2, 3 },

                       { 6, 1, 9,15,      /*17手問題*/
                        17, 1, 1, 7,
                         4, 5, 1,22,
                         5, 4, 1, 1 },

                       { 22, 1,22,22,      /*15手問題*/
                          2,15,22,22,
                          6, 1, 7, 3,
                          4, 5,19, 4 },

                       { 15, 6,22, 3,
                         22,22,19,21,
                          1, 7, 4,21,
                          1, 1, 5,21 } };

int Stage_clear[20][16] =    /*2手問題*/
{ { 0, 0, 0, 0,
    6, 2, 2,16,
    5, 2,18, 0,
    0, 0, 0, 0 }, //0は任意のパネル

       /*5手問題*/
{  0, 0, 0, 0,
   6, 2,18, 0,
   5, 2, 2, 3,
  14, 8, 2, 4 },
    /*7手問題*/
{ 0, 0, 0, 0,
   0,14, 8, 3,
   6, 2, 2, 4,
   5, 2, 2,18 },
    /*9手問題*/
{ 0, 0, 0,17,
 12, 2, 2, 4,
  5, 3, 0, 0,
 14, 4, 0, 0 },
    /*17手問題*/
{ 0, 6, 9,15,
 17, 1, 1, 7,
  1, 1, 1, 1,
  5, 4, 5, 4 },
    /*15手問題*/
{  6, 2, 3, 0,
   1,15, 1, 0,
   5, 4, 7, 0,
   0, 0,19, 0 },

{15, 6, 3, 0,
  1, 1,19, 0,
  1, 7, 0, 0,
  5, 4, 0, 0 } };