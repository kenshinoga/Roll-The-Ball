#pragma once
#include "variable.h"



typedef struct {
    int dir1;
    int dir2;
}dir;

//�S�p�l���̕�������
dir p_dir[23] =
{
    {NULL,NULL},
    {-PuzzleSize,PuzzleSize},
    {1,-1},
    {PuzzleSize,-1},
    {-PuzzleSize,-1},
    {-PuzzleSize,1},
    {1,PuzzleSize},

    {-PuzzleSize,PuzzleSize},
    {1,-1},
    {PuzzleSize,-1},
    {-PuzzleSize,-1},
    {-PuzzleSize,1},
    {1,PuzzleSize},

    {-PuzzleSize,NULL},
    {1,NULL},
    {PuzzleSize,NULL},
    {-1,NULL},
    {PuzzleSize,NULL},
    {-1,NULL},
    {-PuzzleSize,NULL},
    {1,NULL},
    {NULL,NULL},
    {NULL,NULL},
};

void PlaySoundBack(int Handle, bool doCheck) {
    if (doCheck == TRUE) {
        if (CheckSoundMem(Handle) == 0) {
            PlaySoundMem(Handle, DX_PLAYTYPE_BACK);
        }
    }
    else {
        PlaySoundMem(Handle, DX_PLAYTYPE_BACK);
    }
}

void DrawPanel(int* sta) {
    for (int i = 0; i < PuzzleSize * PuzzleSize; i++) {
        DrawExtendGraph((i % PuzzleSize) * 80, (i / PuzzleSize) * 80, (i % PuzzleSize + 1) * 80, (i / PuzzleSize + 1) * 80, pic_road[sta[i]], FALSE);
    }
}

void DrawRandumPanel(int* sta) {
    for (int i = 0; i < PuzzleSize * PuzzleSize; i++) {
        DrawExtendGraph((i % PuzzleSize) * 80 + RandumPuzzleGap_x, (i / PuzzleSize) * 80 + RandumPuzzleGap_y, (i % PuzzleSize + 1) * 80 + RandumPuzzleGap_x, (i / PuzzleSize + 1) * 80 + RandumPuzzleGap_y, pic_road[sta[i]], FALSE);
    }
}

void change_x_y(int p, int* x, int* y) {
    //�p�l���ԍ���x,y�ɒ���
    *x = 0, * y = 0;
    while (1) {
        if (p - PuzzleSize < 0) {
            *x = p;
            break;
        }
        p -= PuzzleSize;
        *y += 1;
    }
}

//�Q�p�l���Ԃ̃��[�N���b�h����
int distance(int p1, int p2) {
    int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    change_x_y(p1, &x1, &y1);
    change_x_y(p2, &x2, &y2);
    return abs(x1 - x2) + abs(y1 - y2);
}

// �I�������p�l���Q�������ւ���
void change(int x1, int y1, int x2, int y2, int* stage__) {
    //�X�e�[�W�z��̓Y�����ɑΉ�������
    int p1 = y1 * PuzzleSize + x1;
    int p2 = y2 * PuzzleSize + x2;;
    int tmp;

    //�p�l�����ׂ荇���Ă��邩�ǂ���
    if (p2 == p1 - 1 || p2 == p1 + 1 || p2 == p1 - PuzzleSize || p2 == p1 + PuzzleSize) {
        tmp = stage__[p1];
        stage__[p1] = stage__[p2];
        stage__[p2] = tmp;
    }
}

int getPuzzleNum_Y(int mouse_y)
{
    if (mouse_y - RandumPuzzleGap_y < 0)
        return -1;
    int index = (mouse_y - RandumPuzzleGap_y) / RandumPuzzleOneSize;
    if (index >= PuzzleSize)
        return -1;
    if ((mouse_y - RandumPuzzleGap_y) % RandumPuzzleOneSize == 0)
        return -1;
    return index;
}

int getPuzzleNum_X(int mouse_x)
{
    if ((mouse_x - RandumPuzzleGap_x) % RandumPuzzleOneSize == 0)
        return -1;
    int index = ( mouse_x - RandumPuzzleGap_x ) / RandumPuzzleOneSize;
    if (index < 0 || index >= PuzzleSize)
        return -1;
    return index;
}

//�p�l�����Œ肩�ǂ������ׂ�(�Œ�Ȃ�0��Ԃ�)
int CheckFixed(int x, int y, int* stage___) {
    int p = y * PuzzleSize + x;
    if (stage___[p] >= 7 && stage___[p] <= 20)return 0;
    else return 1;
}

//�p�l�����Œ肩�ǂ������ׂ�(�p�l���ԍ�������Ver.)
int CheckFixed2(int p, int* stage___) {
    if (stage___[p] >= 7 && stage___[p] <= 20)return 0;
    else return 1;
}

//�p�l�����Ȃ��ꏊ���ǂ������ׂ�(�Ȃ��Ȃ�0��Ԃ�)
int CheckSpace(int x, int y, int* stage___) {
    int p = y * PuzzleSize + x;
    if (stage___[p] == 22)return 0;
    else return 1;
}

//�p�l�����Ȃ��ꏊ�Ɨאڂ��Ă��邩���ׂ�(�אڂ��Ă���Ȃ�1��Ԃ�)
int WithSpace(int p, int x, int y, int* stage__) {
    if (y > 0 && stage__[p - PuzzleSize] == 22)
        return 1;
    if (x < PuzzleSize - 1 && stage__[p + 1] == 22)
        return 1;
    if (y < PuzzleSize - 1 && stage__[p + PuzzleSize] == 22)
        return 1;
    if (x > 0 && stage__[p - 1] == 22)
        return 1;
    return 0;
}

int CheckClear2() {
    // �N���A����(�������킩���Ă���O��)
    for (int i = 0; i < PuzzleSize * PuzzleSize; i++) {
        if (stage[i] != stage_clear[i])
            if (stage_clear[i] != 0)return 0;
    }
    return 1;
}
int CheckClear() {
    // �N���A����(�ėp)
    int p = 0, x, y, pre_d, next_d;

    //�X�^�[�g�p�l����T��
    for (int i = 0; i < PuzzleSize * PuzzleSize; i++) {
        if (stage[i] >= 13 && stage[i] <= 16) {
            p = i;
            break;
        }
    }
    change_x_y(p, &x, &y);
    //�X�^�[�g�̐悪��O�Ȃ炾��
    if (p_dir[stage[p]].dir1 == -1 && x == 0) {
        return 0;
    }
    else if (p_dir[stage[p]].dir1 == -PuzzleSize && y == 0) {
        return 0;
    }
    else if (p_dir[stage[p]].dir1 == 1 && x == PuzzleSize - 1) {
        return 0;
    }
    else if (p_dir[stage[p]].dir1 == PuzzleSize && y == PuzzleSize - 1) {
        return 0;
    }

    //�X�^�[�g�̐�̃p�l���ƂȂ����Ă��邩
    if (p_dir[stage[p + p_dir[stage[p]].dir1]].dir1 != (-1) * p_dir[stage[p]].dir1
        && p_dir[stage[p + p_dir[stage[p]].dir1]].dir2 != (-1) * p_dir[stage[p]].dir1)
        return 0;

    p += p_dir[stage[p]].dir1;
    change_x_y(p, &x, &y);
    pre_d = p_dir[stage[p]].dir1;

    while (stage[p] < 17 || stage[p]>20) {
        if (p_dir[stage[p]].dir1 == (-1) * pre_d)next_d = p_dir[stage[p]].dir2;
        else next_d = p_dir[stage[p]].dir1;

        //�p�l���̐悪��O�Ȃ炾��
        if (next_d == -1 && x == 0) {
            return 0;
        }
        else if (next_d == -PuzzleSize && y == 0) {
            return 0;
        }
        else if (next_d == 1 && x == PuzzleSize - 1) {
            return 0;
        }
        else if (next_d == PuzzleSize && y == PuzzleSize - 1) {
            return 0;
        }
        if (p_dir[stage[p + next_d]].dir1 != (-1) * next_d
            && p_dir[stage[p + next_d]].dir2 != (-1) * next_d)
            return 0;

        p += next_d;
        change_x_y(p, &x, &y);
        pre_d = next_d;
    }
    return 1;
}

//�z��R�s�[�֐� arr1��arr2
void CopyArr(int* arr1, int* arr2) {
    for (int i = 0; i < PuzzleSize * PuzzleSize; i++) {
        arr1[i] = arr2[i];
    }
}

