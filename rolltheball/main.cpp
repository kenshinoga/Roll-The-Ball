#include "DxLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "variable.h"
#include "func.h"
#include "Solver.h"



void GenerateStage(int* sta) {
    int start, startnum, goal, goalnum, spacenum[PuzzleSize/2];
    bool IsSpaceGenerate = FALSE;
    const int startmin = 13, startmax = 16; //スタートパネルの番号(13～16)
    const int goalmin = 17, goalmax = 20; //ゴールパネルの番号(17～20)
    
    
    
    while (1) {
        trycount++;

        for (int i = 0; i < PuzzleSize * PuzzleSize; i++) {
            sta[i] = 0;
        }
        start = (rand() % (startmax - startmin + 1)) + startmin; //startパネルの生成
        startnum = (rand() % ((PuzzleSize * PuzzleSize -1) - 0 + 1)) + 0;
        stage[startnum] = start;

        goal = (rand() % (goalmax - goalmin + 1)) + goalmin; //goalパネルの生成
        while (1) { //スタートパネルと異なる番号を探す
            goalnum = (rand() % ((PuzzleSize * PuzzleSize -1) - 0 + 1)) + 0;
            if (goalnum != startnum && distance(goalnum, startnum) >= PuzzleSize)break;
        }
        stage[goalnum] = goal;

        /*PuzzleSize/2個の空白パネルを生成*/
        for (int i = 0; i < PuzzleSize / 2; i++) {
            IsSpaceGenerate = TRUE;
            while (IsSpaceGenerate) { //さらに異なる番号を探して空白を生成
                spacenum[i] = (rand() % ((PuzzleSize * PuzzleSize - 1) - 0 + 1)) + 0;
                if (spacenum[i] == startnum || spacenum[i] == goalnum)continue;       //スタートかゴールと被ったら生成やり直し
                IsSpaceGenerate = FALSE;
                for (int j = 0; j < i; j++) {
                    if (spacenum[i] == spacenum[i - j - 1]) {
                        IsSpaceGenerate = TRUE;
                        break;
                    }
                }
            }
            stage[spacenum[i]] = 22;
        }

        /*残りの座標をその他のランダムなパネルで埋める*/
        for (int i = 0; i < PuzzleSize * PuzzleSize; i++) {

            if (stage[i] == start || stage[i] == goal || stage[i] == 22)continue;

            int num;
            num = (rand() % (13 - 1 + 1)) + 1;
            if (num == 13)num = 21; //ノーマルパネル

            stage[i] = num;
        }

        if (CheckClear() == FALSE && dfsSolver_id() == 1) {
            dfsflg = 0;
            break;
        }
    }

}

void Title() {
    //////////BGM再生//////////////////////////////////////////////////////

    if (CheckSoundMem(sound_title) == 0) {
        PlaySoundMem(sound_title, DX_PLAYTYPE_LOOP);
    }

    /////////タイトル画像//////////////////////////////////////////////////

    DrawExtendGraph(0, 0, WindowSize_x, WindowSize_y, pic_title, FALSE);

    ///////////////////////////////////////////////////////////////////////

    // マウスの入力を待つ
    MouseInput = GetMouseInput();

    if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {  //左クリックしたらフラグを立てる
        KEYDOWNflg = 1;
        mouseflg = TRUE;
        KEYDOWNflg = 0;
    }

    if (mouseflg == TRUE)framecount++;  //左クリックしたらフレームを数える

    if (framecount == 1) { //左クリックした時の効果音
        PlaySoundBack(sound_title_enter,TRUE);
    }

    
    if (framecount==0||(framecount >= 20 && framecount <=40)||(framecount >= 60 && framecount <= 80)) { //左クリックしたら点滅させる
        DrawExtendGraph(WindowSize_x / 11*4, WindowSize_y / 7 * 5, WindowSize_x / 11 * 7, WindowSize_y / 7 * 5 + 70, pic_startbutton, FALSE); //スタートボタン画像
    }


    if (framecount > 80) {
        mouseflg = FALSE;
        framecount = 0;
        status = MENU;
        Sleep(200);
    }
}

void Menu() {
    //////////BGM再生//////////////////////////////////////////////////////

    //if (CheckSoundMem(sound_title) == 0) {
    //    //PlaySoundMem(sound_title, DX_PLAYTYPE_LOOP);
    //}

    /////////背景画像//////////////////////////////////////////////////
    
        DrawExtendGraph(0, 0, WindowSize_x, WindowSize_y, pic_menuselect[0], FALSE);
        if (MouseX != 0) {
            if (framecount == 0 || (framecount >= 20 && framecount <= 40) || (framecount >= 60 && framecount <= 80)) { //左クリックしたら点滅させる
                if (menucursor == 1)DrawExtendGraph(83, 118, 347, 392, pic_menucursor, FALSE);
                else if (menucursor == 2)DrawExtendGraph(350, 118, 611, 392, pic_menucursor, FALSE);
                else if (menucursor == 3)DrawExtendGraph(615, 118, 883, 392, pic_menucursor, FALSE);
            }
        }

    ///////////////////////////////////////////////////////////////////////

    // マウスの入力を待つ
    MouseInput = GetMouseInput();

    // マウスの位置を取得
    GetMousePoint(&MouseX, &MouseY);
    if (MouseY >= 165 && MouseY <= 331) {
        if (MouseX >= 98 && MouseX <= 327) {
            if (menucursor != 1)
                PlaySoundBack(sound_menu_cursor, FALSE);
            menucursor = 1;
        }
        else if (MouseX >= 365 && MouseX <= 596) {
            if (menucursor != 2)
                PlaySoundBack(sound_menu_cursor, FALSE);
            menucursor = 2;
        }
        else if (MouseX >= 633 && MouseX <= 863) {
            if (menucursor != 3)
                PlaySoundBack(sound_menu_cursor, FALSE);
            menucursor = 3;
        }       
    }else menucursor = 0;

    if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {  
        if (MouseX >= 790 && MouseX <= 862 && MouseY >= 58 && MouseY <= 104) {
            PlaySoundBack(sound_cancel, FALSE);
            status = TITLE;
            Sleep(500);
        }
        else if (menucursor != 0) {
            mouseflg = TRUE;
        }
    }

    if (mouseflg == TRUE)framecount++;  //左クリックしたらフレームを数える

    if (CheckSoundMem(sound_title_enter) == 0 && framecount == 1) { //左クリックした時の効果音
        PlaySoundMem(sound_title_enter, DX_PLAYTYPE_BACK);
    }


    if (framecount > 80) {
        mouseflg = FALSE;
        framecount = 0;
        status = RANDUM;
        StopSoundMem(sound_title);  //現在のBGMをとめる
        srand((unsigned int)time(NULL));  //乱数の初期化
        stage_num = (rand() % ((generatenum - 1) - 0 + 1)) + 0; //読み込むステージをランダム選択
        Sleep(200);
    }
}

void RandumPuzzle(){
    if (IsPlaying == FALSE) {        
        CopyArr(stage, generated_stage[stage_num]);
        DrawExtendGraph(0, 0, WindowSize_x, WindowSize_y, pic_randumstage, FALSE);
        DrawRandumPanel(stage); //パズル描画
        if (CheckSoundMem(sound_randumpuzzle) == 0) {
            PlaySoundMem(sound_randumpuzzle, DX_PLAYTYPE_LOOP);
        }    
        //ここにカウントダウン処理を入れる
        SetFontSize(64);
        DrawFormatString(270, 50, Color_black, "%d", 5 - count);
        Sleep(1000);
        count++;


        if (count == 6) {
            DrawExtendGraph(0, 0, WindowSize_x, WindowSize_y, pic_randumstage, FALSE);
            DrawRandumPanel(stage); //パズル描画            
            IsPlaying = TRUE;
            count = 100;            
        }
    }
    else if (IsPlaying == TRUE && IsGameOver == FALSE) {
        framecount++;        
        DrawExtendGraph(0, 0, WindowSize_x, WindowSize_y, pic_randumstage, FALSE);  //背景描画
        DrawRandumPanel(stage); //パズル描画
        if (framecount < 50) {  //50フレーム表示
            DrawString(210, 50, "START", Color_black);
        }
        else if (framecount >= 50 && count != -1) {  //50フレーム後表示
            DrawFormatString(270, 50, Color_black, "%d", count / 50); //残り時間表示
            count--;
        }else if (count == -1) {
            PlaySoundBack(sound_gameover, TRUE);
            DrawString(150, 50, "GAME OVER", Color_black);
            IsGameOver = TRUE;
            Sleep(1000);
        }
        
        
        // マウスの位置と状態を取得
        GetMousePoint(&MouseX, &MouseY);
        MouseInput = GetMouseInput();
        //// マウスの位置とログを取得
        if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && IsClick == FALSE) {  //左クリックしたら
            if (getPuzzleNum_X(MouseX) != -1 && getPuzzleNum_Y(MouseY) != -1 && WithSpace(getPuzzleNum_X(MouseX) + getPuzzleNum_Y(MouseY) * PuzzleSize, getPuzzleNum_X(MouseX), getPuzzleNum_Y(MouseY), stage) == 1 && CheckFixed(getPuzzleNum_X(MouseX), getPuzzleNum_Y(MouseY), stage) == 1) {   //それがパズル上かつ空白パネルと隣接しているかつ固定パネルでないなら
                DownPanel_x = getPuzzleNum_X(MouseX);  //クリックしたパネルの座標を取得
                DownPanel_y = getPuzzleNum_Y(MouseY);
                IsClick = TRUE;  //マウスダウンフラグを立てる
            }
        }
        else if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0 && IsClick == TRUE){  //ダウンフラグが立っていて左クリックを離したら
            
            if (stage[getPuzzleNum_X(MouseX) + getPuzzleNum_Y(MouseY) * PuzzleSize] == 22) {  //マウスを離したところが空白パネルなら
                change(DownPanel_x, DownPanel_y, getPuzzleNum_X(MouseX), getPuzzleNum_Y(MouseY), stage);  //パネルと空白パネルを入れ替える
            }
            IsClick = FALSE;  //マウスダウンフラグを下げる
            
        }
            
        if (CheckClear() == 1) {       
            stage_num = (rand() % ((generatenum - 1) - 0 + 1)) + 0;  //ステージ再生成
            CopyArr(stage, generated_stage[stage_num]);
            count = 1000;
        }
        
    }
    else if (IsGameOver == TRUE) {
        DrawExtendGraph(0, 0, WindowSize_x, WindowSize_y, pic_randumstage, FALSE);  //背景描画
        DrawRandumPanel(stage); //パズル描画
        DrawExtendGraph(WindowSize_x/7, WindowSize_y/7, WindowSize_x/7*6, WindowSize_y/7*6, pic_result, TRUE);  //背景描画

        GetMousePoint(&MouseX, &MouseY);

        count = 1000;
        //Sleep(3000);
        WaitKey();
    }


}

//Solverの選択
void selectMETHOD() {
    
    if (CheckHitKey(KEY_INPUT_RETURN) == 1) {
        KEYDOWNflg = 0;
        status = STAGE;
        Sleep(200);
    }
    if (CheckHitKey(KEY_INPUT_Q) == 1) {
        KEYDOWNflg = 0;
        status = OPTION;
        Sleep(200);
    }
    // 文字の描画
    DrawString(80, 40, "使うSolverを選んでね", Color_white);
    DrawString(120, 110, "反復深化法", Color2);
    DrawString(120, 160, "IDASTAR 1(優秀)", Color2);
    DrawString(120, 210, "IDASTAR 2(ザコ)", Color2);
    DrawString(80, 60+method_num * 50, "⇒", Color_white);
    DrawString(20, 270, "q:探索設定", Color_white);

    if (CheckHitKey(KEY_INPUT_DOWN) == 1 && KEYDOWNflg==0)
    {
        KEYDOWNflg = 1;
        if (method_num == idastar2)method_num = id;
        else method_num++;
        Sleep(200);
        KEYDOWNflg = 0;
    }
    if (CheckHitKey(KEY_INPUT_UP) == 1 && KEYDOWNflg == 0)
    {
        KEYDOWNflg = 1;
        if (method_num == id)method_num = idastar2;
        else method_num--;
        Sleep(200);
        KEYDOWNflg = 0;
    }

}

void anime_OPTION() {

    if (CheckHitKey(KEY_INPUT_RETURN) == 1) {
        KEYDOWNflg = 0;
        status = METHOD;
        Sleep(200);
    }
    
    // 文字の描画
    DrawString(50, 40, "パズルのスライドを描画する", Color_white);
    DrawString(20, 70, "※する場合探索速度が格段に落ちます", Color_white);
    DrawString(140, 160, "する", Color2);
    DrawString(140, 210, "しない", Color2);
    DrawString(80, 210-animeflg*50, "⇒", Color_white);
    //DrawString(20, 270, "q:戻る", Color);

    if (CheckHitKey(KEY_INPUT_DOWN) == 1 && KEYDOWNflg == 0)
    {
        KEYDOWNflg = 1;
        if (animeflg == 1)animeflg = 0;
        else animeflg++;
        Sleep(200);
        KEYDOWNflg = 0;
    }
    if (CheckHitKey(KEY_INPUT_UP) == 1 && KEYDOWNflg == 0)
    {
        KEYDOWNflg = 1;
        if (animeflg == 1)animeflg = 0;
        else animeflg ++;
        Sleep(200);
        KEYDOWNflg = 0;
    }
}

//問題選択
void selectSTAGE() {

    dfscount = 0;
    

    if (CheckHitKey(KEY_INPUT_RETURN) == 1) {
        CopyArr(stage, Stage[stage_num - 1]);
        CopyArr(stage_clear, Stage_clear[stage_num - 1]);
        status = START;
        Sleep(200);
    }
    if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
        KEYDOWNflg = 1;
        /*ランダムステージ生成*/
        if ((fp2 = fopen("generated_stage.txt", "w")) == NULL) {
            printf("file open error!!\n");
            exit(EXIT_FAILURE);	//エラーの場合は異常終了
        }
        for (int j = 0; j < generatenum; j++) {
            srand((unsigned int)time(NULL)); //乱数の初期化。
            GenerateStage(stage);
            
            for (int i = 0; i < PuzzleSize * PuzzleSize; i++) {
                fprintf(fp2, "%d ",stage[i]);
            }
            
            fprintf(fp2, "\n");
            count2++;
        }
        fclose(fp2);
        
        status = START;
        Sleep(200);
        KEYDOWNflg = 0;
    }
    // 文字の描画
    DrawString(20, 270, "q:戻る", Color_white);
    DrawString(100, 20, "問題を選んでね", Color_white);
    DrawString(120, 60, "2手問題", Color2);
    DrawString(120, 90, "5手問題", Color2);
    DrawString(120, 120, "7手問題", Color2);
    DrawString(120, 150, "9手問題", Color2);
    DrawString(120, 180, "17手問題", Color2);
    DrawString(120, 210, "15手問題1(激むず)", Color2);
    DrawString(120, 240, "15手問題2", Color2);
    DrawString(80, 30 + stage_num * 30, "⇒", Color_white);

    if (CheckHitKey(KEY_INPUT_Q) == 1)status = METHOD;

    if (CheckHitKey(KEY_INPUT_DOWN) == 1 && KEYDOWNflg == 0)
    {
        KEYDOWNflg = 1;
        if (stage_num == stage_sum)stage_num = 1;
        else stage_num++;
        Sleep(200);
        KEYDOWNflg = 0;
    }
    if (CheckHitKey(KEY_INPUT_UP) == 1 && KEYDOWNflg == 0)
    {
        KEYDOWNflg = 1;
        if (stage_num == 1)stage_num = stage_sum;
        else stage_num--;
        Sleep(200);
        KEYDOWNflg = 0;
    }

}


// 探索前の局面を表示(クリックで探索開始)
void gameSTART() {
    dfsflg = 0;
    if (CheckHitKey(KEY_INPUT_RETURN) == 1) {
        KEYDOWNflg = 0;
        status = MAIN;
        Sleep(200);
    }

    // パネルの描画
    DrawPanel(stage);
    DrawFormatString(20, 20, Color2, "Enterで探索開始！");

}

// メイン画面
void gameMain() {
    if (dfsflg == 0) {
        // パネルの描画
        DrawPanel(stage);
        DrawFormatString(20, 50, Color2, "探索中です……");
        ScreenFlip();
    }
    else {
        // パネルの描画
        DrawPanel(stage_);
    }
    

    //探索は１度だけ
    if (dfsflg == 0) {
        /* 処理開始前のクロックを取得 */
        start_clock = clock();
        
        switch (method_num) {
        case 1:
            if (dfsSolver_id() == 1)
                dfsflg = 1;
            break;
        case 2:
            if (dfsSolver_idastar() == 1)
                dfsflg = 1;
            break;
        case 3:
            if (dfsSolver_idastar() == 1)
                dfsflg = 1;
            break;

        }

        /* 処理終了後のクロックを取得 */
        end_clock = clock();
    }
    if (dfsflg == 1) {
        DrawFormatString(0, 0, Color2, "探索成功！");
        DrawFormatString(80, 0, Color2, "探索ノード総数：%d", dfscount);
        DrawFormatString(0, 30, Color2, "処理時間：%f", (double)(end_clock - start_clock) / CLOCKS_PER_SEC);
        DrawFormatString(0, 60, Color2, "正解手は%dパターンありました", count);
        DrawFormatString(0, 90, Color2, "手順はmovelog.txtをチェック！");
    }
    else DrawFormatString(0, 0, Color2, "探索失敗！");

    DrawString(20, 270, "q:探索法選択に戻る", Color2);
    DrawString(20, 290, "w:問題選択に戻る", Color2);
    if (CheckHitKey(KEY_INPUT_Q) == 1 && KEYDOWNflg == 0)
    {
        KEYDOWNflg = 1;
        status = METHOD;
        Sleep(200);
        KEYDOWNflg = 0;
    }
    if (CheckHitKey(KEY_INPUT_W) == 1)status = STAGE;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    SetGraphMode(WindowSize_x, WindowSize_y, 32);
    ChangeWindowMode(TRUE);
    DxLib_Init();
    SetDrawScreen(DX_SCREEN_BACK);


    /*画像読み込み*/
    for (int i = 1; i <= 22; i++) {   //パネル画像読み込み
        sprintf(filename, ".\\image\\panel\\road%d.png", i);
        pic_road[i] = LoadGraph(filename);
    }
    pic_title = LoadGraph(".\\image\\title.jpg");
    pic_startbutton = LoadGraph(".\\image\\startbutton.png");
    pic_randumstage = LoadGraph(".\\image\\randumstage.jpg");
    for (int i = 0; i < 4; i++) {   //モード選択画面の背景読み込み
        sprintf(filename, ".\\image\\menuselect%d.jpg", i + 1);
        pic_menuselect[i] = LoadGraph(filename);
    }
    pic_menucursor = LoadGraph(".\\image\\menu_cursor.png");
    pic_result = LoadGraph(".\\image\\result.png");

    /*音楽読み込み*/
    sound_title = LoadSoundMem(".\\sound\\魔王魂  8bit13.mp3");
    sound_title_enter = LoadSoundMem(".\\sound\\魔王魂 効果音 システム47.mp3");
    sound_menu_cursor = LoadSoundMem(".\\sound\\魔王魂 効果音 システム27.mp3");
    sound_cancel = LoadSoundMem(".\\sound\\魔王魂 効果音 システム10.mp3");
    sound_randumpuzzle = LoadSoundMem(".\\sound\\魔王魂  サイバー44.mp3");
    sound_gameover = LoadSoundMem(".\\sound\\魔王魂  レトロ21.mp3");

    /*生成ステージ読み込み*/
    fp = fopen("generated_stage.txt", "r");
    if (fp == NULL)
    {
        printf("ファイルのオープンに失敗しました\n");
    }
    for (int i = 0; i < generatenum; i++) {
        for (int j = 0; j < PuzzleSize * PuzzleSize; j++) {
            fscanf(fp, "%d", &generated_stage[i][j]);
        }
    }
    fclose(fp);


    for (int i = 0; i < 100; i++) {  //手順記録用配列の初期化
        move_panel[i] = -1;
        move_space[i] = -1;
    }

    // マウスを表示状態にする
    SetMouseDispFlag(TRUE);
    
    while (!ProcessMessage()) {  //ゲームの遷移
        ClearDrawScreen();
        switch (status) {
        case TITLE: Title(); break;
        case MENU: Menu(); break;
        case RANDUM: RandumPuzzle(); break;
        case METHOD: selectMETHOD(); break;
        case OPTION: anime_OPTION(); break;
        case STAGE: selectSTAGE(); break;
        case START: gameSTART(); break;
        case MAIN: gameMain(); break;
        }
        ScreenFlip();
    }
    DxLib_End();
    return 0;
}