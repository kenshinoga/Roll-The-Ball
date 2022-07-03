#pragma once
#include "variable.h"
#include"func.h"


int stage_[PuzzleSize * PuzzleSize] = {};
int move_panel[1000];
int move_space[1000];
FILE* fp;


//���m�[�h����S�[���܂ł̐����l
int h_2() {
    int cost = 0, x1, y1, x2, y2;
    for (int i = 0; i < PuzzleSize * PuzzleSize; i++) {
        for (int j = 0; j < PuzzleSize * PuzzleSize; j++) {
            /*�����̃��[�g�ォ�Œ肶��Ȃ��p�l���Ȃ�*/
            if (stage_clear[j] != 0 && CheckFixed2(j, stage_clear) == 1) {
                if (stage[i] == stage_clear[j]) {
                    change_x_y(i, &x1, &y1);
                    change_x_y(j, &x2, &y2);
                    cost += abs(x1 - x2) + abs(y1 - y2);
                    break;
                }
            }
        }
    }
    return cost;
}

int h_1() {
    int cost = 0;
    for (int i = 0; i < PuzzleSize * PuzzleSize; i++) {
        if (stage[i] != 0 && stage[i] != stage_clear[i])
            cost++;
    }
    return cost;
}


void dfs_idastar(int limit, int move) {
    int num = 0;
    //�m�[�h�����ŏ�������
    dfscount++;
    if (dfscount % 10000000 == 0) {

        //��������
        fprintf(fp, "�T���m�[�h��%d limit�l%d\n", dfscount, move);

    }
    else {
        if (method_num == idastar1)num = move + h_1();
        else if (method_num == idastar2)num = move + h_2();
        if (num <= limit) {

            if (CheckClear() == 1) {
                count += 1;

                //��������
                fprintf(fp, "\n�萔:%d\n", move);
                int i = 1;
                while (move_panel[i] != -1) {
                    fprintf(fp, "%d -> %d\n", move_panel[i], move_space[i]);
                    i++;
                }


                CopyArr(stage_, stage);
            }

            else {
                for (int i = 0; i < PuzzleSize * PuzzleSize; i++) {
                    //�p�Y�����̋󔒃p�l����T��
                    if (stage[i] == 22) {
                        //�א�4�������ׂ�
                        for (int j = 1; j <= 4; j++) {
                            int p, x;
                            if (j == 1) {
                                if (i >= 0 && i <= PuzzleSize - 1)continue;
                                x = i - PuzzleSize;
                            }
                            else if (j == 2) {
                                if ((i + 1) % PuzzleSize == 0)continue;
                                x = i + 1;
                            }
                            else if (j == 3) {
                                if (i >= PuzzleSize * PuzzleSize - PuzzleSize && i <= PuzzleSize * PuzzleSize - 1)continue;
                                x = i + PuzzleSize;
                            }
                            else if (j == 4) {
                                if (i % PuzzleSize == 0)continue;
                                x = i - 1;
                            }

                            p = stage[x];
                            if (move_space[move] == x)continue;
                            if ((stage[x] >= 7 && stage[x] <= 20) || stage[x] == 22)continue;

                            //�p�l���𓮂���
                            stage[i] = p;
                            stage[x] = 22;

                            if (animeflg == true) {
                                // �p�l���̕`��
                                DrawPanel(stage);
                                DrawFormatString(20, 50, Color2, "�T�����ł��c�c");
                                ScreenFlip();
                                //Sleep(20);
                            }

                            //�菇�L�^
                            move_panel[move + 1] = x;
                            move_space[move + 1] = i;
                            //�ċN
                            dfs_idastar(limit, move + 1);
                            //���ɖ߂�
                            stage[i] = 22;
                            stage[x] = p;
                        }
                    }
                }
            }
        }
    }
}

int dfsSolver_idastar() {
    count = 0;
    int i = 0;
    if (method_num == idastar1)i = h_1();
    else if (method_num == idastar2)i = h_2();

    for (i <= 30; i++;) {
        fp = fopen("movelog.txt", "w");
        if (fp == NULL)
        {
            printf("�t�@�C���̃I�[�v���Ɏ��s���܂���\n");
        }
        dfs_idastar(i, 0);
        fclose(fp);
        if (count > 0) {
            return 1;
        }
    }
    return 0;
}

void dfs_id(int limit, int move) {
    dfscount++;
    if (move == limit) {
        if (CheckClear() == 1) {
            count += 1;

            //��������
            fprintf(fp, "\n�萔:%d\n", limit);

            int i = 1;
            while (move_panel[i] != -1) {
                fprintf(fp, "%d -> %d\n", move_panel[i], move_space[i]);
                i++;
            }


            CopyArr(stage_, stage);
        }
    }
    else {
        for (int i = 0; i < PuzzleSize * PuzzleSize; i++) {
            //�p�Y�����̋󔒃p�l����T��
            if (stage[i] == 22) {
                //�א�4�������ׂ�
                for (int j = 1; j <= 4; j++) {
                    int p, x;
                    if (j == 1) {
                        if (i >= 0 && i <= PuzzleSize - 1)continue;
                        x = i - PuzzleSize;
                    }
                    else if (j == 2) {
                        if ((i + 1) % PuzzleSize == 0)continue;
                        x = i + 1;
                    }
                    else if (j == 3) {
                        if (i >= PuzzleSize * PuzzleSize - PuzzleSize && i <= PuzzleSize * PuzzleSize - 1)continue;
                        x = i + PuzzleSize;
                    }
                    else if (j == 4) {
                        if (i % PuzzleSize == 0)continue;
                        x = i - 1;
                    }

                    p = stage[x];
                    if (move_space[move] == x)continue;
                    if ((stage[x] >= 7 && stage[x] <= 20) || stage[x] == 22)continue;

                    //�p�l���𓮂���
                    stage[i] = p;
                    stage[x] = 22;

                    if (animeflg == true) {
                        // �p�l���̕`��
                        DrawPanel(stage);
                        DrawFormatString(20, 50, Color2, "�T�����ł��c�c");
                        ScreenFlip();
                        Sleep(20);
                    }

                    //�菇�L�^
                    move_panel[move + 1] = x;
                    move_space[move + 1] = i;
                    //�ċN
                    dfs_id(limit, move + 1);
                    //���ɖ߂�
                    stage[i] = 22;
                    stage[x] = p;
                }
            }
        }
    }

}


int dfsSolver_id() {
    count = 0;

    for (int i = 1; i <= 10; i++) {
        fp = fopen("movelog.txt", "w");
        if (fp == NULL)
        {
            printf("�t�@�C���̃I�[�v���Ɏ��s���܂���\n");
        }
        dfs_id(i, 0);
        fclose(fp);
        if (count > 0) {
            return 1;
        }
    }
    return 0;
}
