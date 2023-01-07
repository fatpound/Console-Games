/*******************************************************************************/
/*                                                                             */
/*              :::::::                                                        */
/*            :+:    :+:                                                       */
/*           +:+                                                               */
/*          +#+                                            :::      ::::::::   */
/*         +#+                                           :+:      :+:    :+:   */
/*        #+#     #+#                                  +:+  +:+        +:+     */
/*   OK101.########                                   +#+  +:+       +#+       */
/*                                                  +#+#+#+#+#+   +#+          */
/*                                                       #+#    #+#            */
/*   By: fatpound                                       ###   ########.tr      */
/*                                                                             */
/*   Created: 10/03/2022 13:00:11 by fatpound with yunnsbz                     */
/*   Updated: 01/01/2023 12:32:22 by fatpound                                  */
/*                                                                             */
/*******************************************************************************/

#pragma warning(disable:4996)

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
// #include <string.h>

#include "definer.h"
#include "textlib.h"

unsigned int zaman;

int i, j, k, m, t, rg[5], d_index[4];

int zerocount = 0,
      started = 0,
        score = 0,
        sayac = 0,
       escape = 0,
     gameover = 0;

int    s1[22] = { 0 },
       s2[22] = { 0 },
    move1[22] = { 0 },
    move2[22] = { 0 };

int   pc[2][11][3][2],
    pc_y[2][11][3][2],
   board[2][11][2],
 board_y[2][11][2],
  taslar[8][13][2],
taslar_y[8][13][2];

char a, c, d, e, y, z, option = ENTER, file_w, file_r, name[MAX_NAME_LEN];

int Seeder()
{
    return (zaman = (unsigned int)time(NULL));
}

void StartGame()
{
    score = 0;

    for (i = 0; i < 22; i++)
    {
        move1[i] = 0;
        move2[i] = 0;
    }

    // Ortadaki Taslarin Sifirlanmasi
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 13; j++)
        {
            for (k = 0; k < 2; k++)
            {
                taslar_y[i][j][k] = taslar[i][j][k] = 0;
            }
        }
    }

    // Istakanin Sifirlanmasi
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 11; j++)
        {
            for (k = 0; k < 2; k++)
            {
                board_y[i][j][k] = board[i][j][k] = 0;
            }
        }
    }

    // PC Dizisinin Sifirlanmasi
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 11; j++)
        {
            for (k = 0; k < 3; k++)
            {
                for (m = 0; m < 2; m++)
                {
                    pc_y[i][j][k][m] = pc[i][j][k][m] = 0;
                }
            }
        }
    }

    // Taslarin Sifirlanip Renklerinin Belirlenmesi
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 13; j++)
        {
            ORTATAS = 0;
            ORTATAS_R = (i < 2 ? 1 : (i < 4 ? 2 : (i < 6 ? 3 : 0)));
        }
    }

    // Taslarin Yerlestirilmesi
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 13; j++)
        {
            for (taslar[i][j][k = 0] = rand() % 13 + 1; k < j; k++)
            {
                if (taslar[i][k][0] == ORTATAS)
                {
                    j--;
                    break;
                }
            }
        }
    }
}

void ColorSort()
{
    for (i = 0; i < 21; i++)
    {
        for (j = i; j < 22; j++)
        {
            if (s1[i] == s1[j] && s2[i] > s2[j])
            {
                SWAP(s1[j], s1[i]);
                SWAP(s2[j], s2[i]);
            }
        }
    }
}

void SelectionSort()
{
    for (i = 0; i < 21; i++)
    {
        for (j = i + 1, m = i; j < 22; j++) // m -> min
        {
            if (s1[m] > s1[j])
            {
                m = j;
            }
        }

        SWAP(s1[i], s1[m]);
        SWAP(s2[i], s2[m]);
    }
}

void DistrubutePC()
{
    for (i = 0; i < 66; i++) // 21 * 3 + 3
    {
        rg[0] = rand() % 2;
        rg[1] = rand() % 11;
        rg[2] = rand() % 8;
        rg[3] = rand() % 13;
        rg[4] = rand() % 3;

        if (taslar[rg[2]][rg[3]][0] && !pc[rg[0]][rg[1]][rg[4]][0])
        {
            pc[rg[0]][rg[1]][rg[4]][0] = taslar[rg[2]][rg[3]][0];
            pc[rg[0]][rg[1]][rg[4]][1] = taslar[rg[2]][rg[3]][1];

            taslar[rg[2]][rg[3]][0] = 0;
        }
        else i--;
    }
}

void Distrubute()
{
    // 22 yerine 21 yazarsa oyuna bilgisayar baslar, zorluk seviyesi koyulabilir
    for (i = 0; i < 22; i++)
    {
        rg[0] = rand() % 2;
        rg[1] = rand() % 11;
        rg[2] = rand() % 8;
        rg[3] = rand() % 13;

        if (taslar[rg[2]][rg[3]][0] && !board[rg[0]][rg[1]][0])
        {
            board[rg[0]][rg[1]][0] = taslar[rg[2]][rg[3]][0];
            board[rg[0]][rg[1]][1] = taslar[rg[2]][rg[3]][1];

            taslar[rg[2]][rg[3]][0] = 0;
        }
        else i--;
    }
}

void RotateToRight(int x, int y)
{
    for (j = x; j < y; j++)
    {
        SWAP(s1[j], s1[j + 1]);
        SWAP(s2[j], s2[j + 1]);
    }
}

void RotateToLeft(int x, int y) // Sagdan Sola Cekim
{
    for (j = y; j > x; j--)
    {
        SWAP(s1[j], s1[j - 1]);
        SWAP(s2[j], s2[j - 1]);
    }
}

void Aktarim()
{
    for (i = 0, sayac = 0; i < 2; i++)
    {
        for (j = 0; j < 11; j++)
        {
            s1[sayac] = board[i][j][0];
            s2[sayac++] = board[i][j][1];
        }
    }
}

void Duzenle()
{
    for (i = 0, sayac = 0; i < 2; i++)
    {
        for (j = 0; j < 11; j++)
        {
            s1[sayac] = board[i][j][0];
            s2[sayac++] = board[i][j][1];
        }
    }

    SelectionSort();
    ColorSort();

    if (c != 'd') RotateToRight(0, 22);
}

void DizimSonu()
{
    for (i = 0, sayac = 0; i < 2; i++) // Gecici Diziden ISTAKAya Aktarim
    {
        for (j = 0; j < 11; j++)
        {
            board[i][j][0] = s1[sayac];
            board[i][j][1] = s2[sayac++];
        }
    }
}

/////////////////////////////////////////////
// HAMLEYI GERI ALMAK

void SaveMove()
{
    for (i = sayac = 0; i < 2; i++)
    {
        for (j = 0; j < 11; j++)
        {
            move1[sayac] = board[i][j][0];
            move2[sayac++] = board[i][j][1];
        }
    }

    // PC Dizisinin Kopyalanmasi
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 11; j++)
        {
            for (k = 0; k < 3; k++)
            {
                for (m = 0; m < 2; m++)
                {
                    pc_y[i][j][k][m] = pc[i][j][k][m];
                }
            }
        }
    }

    // Ortadaki Taslarin Kopyalanmasi
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 13; j++)
        {
            for (k = 0; k < 2; k++)
            {
                taslar_y[i][j][k] = taslar[i][j][k];
            }
        }
    }
}

// Geri alim
void Undo()
{
    for (i = sayac = 0; i < 2; i++)
    {
        for (j = 0; j < 11; j++)
        {
            board[i][j][0] = move1[sayac];
            board[i][j][1] = move2[sayac++];
        }
    }
}
/////////////////////////////////////////////

void Mix()
{
    Aktarim();

    for (i = 0; i < 100; i++)
    {
        rg[0] = rand() % 22;
        rg[1] = rand() % 22;

        SWAP(s1[rg[0]], s1[rg[1]]);
        SWAP(s2[rg[0]], s2[rg[1]]);
    }

    DizimSonu();
}

void ZeroCount()
{
    int temp = 0;

    for (i = 0; i < 22; i++)
    {
        if (!s1[i])
        {
            temp++;
        }
    }

    if (zerocount != temp)
    {
        zerocount = temp;
    }
}

int FirstZeroLocation()
{
    for (i = 0; i < 22; i++)
    {
        if (!s1[i])
        {
            return i;
        }
    }

    return -1;
}

void ShiftZeros()
{
    Aktarim();

    int i = 0;

    for (ZeroCount(); i < zerocount; i++)
    {
        if (FirstZeroLocation() != -1)
        {
            RotateToRight(FirstZeroLocation(), 22);
        }
    }

    DizimSonu();
}

void DrawPC(HANDLE h, WORD wOldColorAttrs)
{
    system("CLS");

    SetConsoleTextAttribute(h, BEYAZ);
    ust_cerceve1;

    for (j = 0; j < 3; j++)
    {
        ustel_frame;
    }

    for (k = 0; k < 3; k++)
    {
        for (i = 0; i < 2; i++)
        {
            SetConsoleTextAttribute(h, BEYAZ);
            printf("%c              %cPC %d : ", 186, i ? 0x20 : '*', k + 1);

            for (j = 0; j < 11; j++)
            {
                SetConsoleTextAttribute(h, PC ? (PC_R ? PC_R == 1 ? RENK_1 : (PC_R == 2 ? RENK_2 : RENK_3) : RENK_0) : wOldColorAttrs);
                printf("%s%d", j ? (PC >= 10 ? " " : "  ") : (PC >= 10 ? "" : " "), PC);
            }

            SetConsoleTextAttribute(h, BEYAZ);
            printf("              %c                                  %c\n", 186, 186);
        }

        ustel_frame;
    }
}

void DrawTas(HANDLE h, WORD wOldColorAttrs)
{
    ustel_frame;
    ustel_frame;

    for (i = 0; i < 8; i++)
    {
        SetConsoleTextAttribute(h, BEYAZ);
        printf("%c               ", 186);

        for (j = 0; j < 13; j++)
        {
            SetConsoleTextAttribute(h, ORTATAS_R ? (ORTATAS_R == 1 ? RENK_1 : (ORTATAS_R == 2 ? RENK_2 : RENK_3)) : RENK_0);
            printf("%s%d", j ? (ORTATAS >= 10 ? " " : "  ") : (ORTATAS >= 10 ? "" : " "), ORTATAS);
        }

        SetConsoleTextAttribute(h, BEYAZ);
        printf("               %c                                  %c\n", 186, 186);
    }

    SetConsoleTextAttribute(h, WHITE);

    for (j = 0; j < 8; j++) ustel_frame;
}

void Istaka(HANDLE h, WORD wOldColorAttrs)
{
    for (i = 0; i < 2; i++)
    {
        printf("%c %c                ", 186, 186);

        for (j = 0; j < 11; j++)
        {
            SetConsoleTextAttribute(h, ISTAKA ? (ISTAKA_R ? (ISTAKA_R == 1 ? RENK_1 : (ISTAKA_R == 2 ? RENK_2 : RENK_3)) : RENK_0) : BEYAZ);
            printf("%s%d", j ? (ISTAKA >= 10 ? " " : "  ") : (ISTAKA >= 10 ? "" : " "), ISTAKA);
        }

        SetConsoleTextAttribute(h, BEYAZ);
        printf("                %c %c                                  %c\n", 186, 186, 186);
    }
}

void DrawBoard(HANDLE h, WORD wOldColorAttrs)
{
    SetConsoleTextAttribute(h, BEYAZ);
    printf("%c ", 186);
    istaka_ust_cerceve;

    printf(" %c                                  %c\n", 186, 186);
    printf("%c %c                                                                %c %c                                  %c\n", 186, 186, 186, 186, 186);
    Istaka(h, WHITE);

    printf("%c %c                                                                %c %c                                  %c\n%c ", 186, 186, 186, 186, 186, 186);
    istaka_ort_cerceve;
    printf(" %c                                  %c", 186, 186);

    Aktarim();

    for (k = 0; k < 2; k++)
    {
        for (i = 0; i < 3; i++)
        {
            SetConsoleTextAttribute(h, BEYAZ);
            printf("\n%c %c     ", 186, 186);
            SetConsoleTextAttribute(h, s1[k ? 11 : 0] ? (s2[k ? 11 : 0] ? (s2[k ? 11 : 0] == 1 ? RENK_1 : (s2[k ? 11 : 0] == 2 ? RENK_2 : RENK_3)) : RENK_0) : wOldColorAttrs);

            for (j = 0, t = (k ? 12 : 1); j < 54; j++)
            {
                if ((j + 1) % 5 == 0)
                {
                    SetConsoleTextAttribute(h, s1[t] ? (s2[t] ? (s2[t] == 1 ? RENK_1 : (s2[t] == 2 ? RENK_2 : RENK_3)) : RENK_0) : wOldColorAttrs);
                    t++;
                    printf(" ");
                }
                else if ((j + 2) % 5 == 0 || j % 5 == 0) printf("%c", ((j + 2) % 5 == 0) ? (i == 2 ? 188 : (i ? 186 : 187)) : (i == 2 ? 200 : (i ? 186 : 201)));
                else if (i != 1) printf("%c", 205);
                else
                {
                    if (s1[--t])
                    {
                        printf("%s%d", s1[t] >= 10 ? "" : " ", s1[t]);
                    }
                    else printf("  ");

                    j++;
                    t++;
                }
            }

            SetConsoleTextAttribute(h, s1[k ? 11 : 0] ? (s2[k ? 11 : 0] ? (s2[k ? 11 : 0] == 1 ? RENK_1 : (s2[k ? 11 : 0] == 2 ? RENK_2 : RENK_3)) : RENK_0) : wOldColorAttrs);
            SetConsoleTextAttribute(h, BEYAZ);
            printf("     %c %c                                  %c", 186, 186, 186);
        }
    }

    printf("\n%c ", 186);
    istaka_alt_cerceve;
    printf(" %c                                  %c\n", 186, 186);

    SetConsoleTextAttribute(h, BEYAZ);

    if (option != 'f')
    {
        ustel_frame;

        for (i = 0; i < 5; i++)
        {
            (SetConsoleTextAttribute(h, BEYAZ), printf("%c       ", 186));
            (SetConsoleTextAttribute(h, wOldColorAttrs), printf("%s       ", playoptions[i]));
            (SetConsoleTextAttribute(h, BEYAZ), printf("%c                                  %c\n", 186, 186));
        }

        (SetConsoleTextAttribute(h, BEYAZ), printf("%c", 186));
        (SetConsoleTextAttribute(h, wOldColorAttrs), printf("       [k] -> karistir                        "));
        (SetConsoleTextAttribute(h, A_SARI), printf("duraklat <- [p]"));
        (SetConsoleTextAttribute(h, BEYAZ), printf("       %c                                  %c\n", 186, 186));

        ustel_frame;
        alt_cerceve2;
    }
    else alt_cerceve2;
}

void DrawThrow(HANDLE h, WORD wOldColorAttrs)
{
    system("CLS");

    Istaka(h, wOldColorAttrs);

    Aktarim();

    for (k = 0; k < 2; k++)
    {
        SetConsoleTextAttribute(h, s1[k ? 11 : 0] && (k ? m != 11 : m != 0) ? (s2[k ? 11 : 0] ? (s2[k ? 11 : 0] == 1 ? RENK_1 : (s2[k ? 11 : 0] == 2 ? RENK_2 : RENK_3)) : RENK_0) : wOldColorAttrs);

        for (i = 0; i < 3; i++)
        {
            if (i == 2 && ((m == 0 && k == 0) || (m == 11 && k)))
            {
                SetConsoleTextAttribute(h, wOldColorAttrs);
            }

            for (j = 0, t = (k ? 12 : 1); j < 54; j++)
            {
                if ((j + 1) % 5 == 0)
                {
                    SetConsoleTextAttribute(h, s1[t] && (t != m || i == 1) ? (s2[t] ? (s2[t] == 1 ? RENK_1 : (s2[t] == 2 ? RENK_2 : RENK_3)) : RENK_0) : wOldColorAttrs);
                    t++;
                    printf(" ");
                }
                else if ((j + 2) % 5 == 0 || j % 5 == 0) printf("%c", ((j + 2) % 5 == 0) ? (i == 2 ? 188 : (i ? 186 : 187)) : (i == 2 ? 200 : (i ? 186 : 201)));
                else if (i != 1) printf("%c", 205);
                else
                {
                    if (s1[--t])
                    {
                        printf("%s%d", s1[t] >= 10 ? "" : " ", s1[t]);
                    }
                    else printf("  ");

                    j++;
                    t++;
                }
            }

            SetConsoleTextAttribute(h, s1[k ? 11 : 0] && ((t - 1 != m || i != 1) || ((m == 10 || m == 21) && i == 1)) ? (s2[k ? 11 : 0] ? (s2[k ? 11 : 0] == 1 ? RENK_1 : (s2[k ? 11 : 0] == 2 ? RENK_2 : RENK_3)) : RENK_0) : wOldColorAttrs);
            printf("\n");
        }
    }

    SetConsoleTextAttribute(h, wOldColorAttrs);
    printf("------------------------------------------------------\n");

    if (option != 'f')
    {
        printf("   [w]                               Onayla <- [ENTER]\n[a]   [d]\n   [s]");
        SetConsoleTextAttribute(h, wOldColorAttrs);
    }
}

void PauseMenu(HANDLE h, WORD wOldColorAttrs)
{
    if (z == 'r')
    {
        system("CLS");

        printf("\n\n      Oyun Duraklatildi");
        printf("\n      -----------------");
        printf("\n\n      [a] -> Oyuna Devam Et\n\n      ");

        (SetConsoleTextAttribute(h, GRAY), printf("\r      [r] -> Oyuna Yeniden Basla\n\n      "));
        (SetConsoleTextAttribute(h, wOldColorAttrs), printf("[ESC] -> Oyunu Sonlandir"));
    }
    else if (z == ESC)
    {
        (SetConsoleTextAttribute(h, GRAY), printf("\r      [ESC] -> Oyunu Sonlandir"));
    }
    else
    {
        system("CLS");

        printf("\n\n      Oyun Duraklatildi");
        printf("\n      -----------------");
        printf("\n\n      [a] -> Oyuna Devam Et");
        printf("\n\n      [r] -> Oyuna Yeniden Basla");
        printf("\n\n      [ESC] -> Oyunu Sonlandir");
    }
}

void Eminlik(HANDLE h, WORD wOldColorAttrs, int score)
{
    (SetConsoleTextAttribute(h, SARI), printf("\n\n      [["));
    (SetConsoleTextAttribute(h, NBLUE), printf("!"));
    (SetConsoleTextAttribute(h, SARI), printf("]]"));
    (SetConsoleTextAttribute(h, wOldColorAttrs), printf(" -> Emin Misiniz? "));
    (SetConsoleTextAttribute(h, A_KIRMIZI), printf("[E]"));
    (SetConsoleTextAttribute(h, wOldColorAttrs), printf("%s / %s", score ? " " : "", score ? " " : ""));
    (SetConsoleTextAttribute(h, A_YESIL), printf("[H]"));
    (SetConsoleTextAttribute(h, wOldColorAttrs), printf(" > "));
}

void DrawMenu(HANDLE h, WORD wOldColorAttrs)
{
    system("CLS");

    printf("\n\n           ");

    for (i = 0; i < 3; i++)
    {
        SetConsoleTextAttribute(h, i & 1 ? SARI : YESIL);
        printf("%d", !(i & 1));
    }

    (SetConsoleTextAttribute(h, GRAY), printf("\n         "));

    // Renkli O-K-E-Y Yazisi
    for (j = 0; j < 7; j++)
    {
        SetConsoleTextAttribute(h, j & 1 ? wOldColorAttrs : GRAY);
        printf("%c", j & 1 ? '-' : "OKEY"[j / 2]);
    }

    (SetConsoleTextAttribute(h, CYAN), printf("\n      -------------"));
    (SetConsoleTextAttribute(h, wOldColorAttrs), printf("\n\n      [ENTER] -> Oyunu Baslat"));
    (SetConsoleTextAttribute(h, wOldColorAttrs), printf("\n\n      -------"));
    (SetConsoleTextAttribute(h, wOldColorAttrs), printf("\n\n      [h] -> Nasil Oynanir?"));
    (SetConsoleTextAttribute(h, wOldColorAttrs), printf("\n\n      [s] -> Skor Tablosu\n\n"));

    if (started)
    {
        (SetConsoleTextAttribute(h, A_SARI), printf("      [f] -> "));
        (SetConsoleTextAttribute(h, MOR), printf("Oyun Masasinin Son Hali\n\n"));
    }

    SetConsoleTextAttribute(h, option == ESC ? GRAY : wOldColorAttrs);
    printf("%s      [ESC] -> Cikis", option == ESC ? "\r" : "");
}

void SaveScore(HANDLE h, WORD wOldColorAttrs)
{
    (SetConsoleTextAttribute(h, A_SARI), printf("\n\n       [!]  -> Puani Kaydet? "));
    (SetConsoleTextAttribute(h, A_KIRMIZI), printf("  [E"));
    (SetConsoleTextAttribute(h, wOldColorAttrs), printf(" / "));
    (SetConsoleTextAttribute(h, A_YESIL), printf("H]   "));
    (SetConsoleTextAttribute(h, wOldColorAttrs), printf("> "));

    while ((file_w = __getch()) != 'E' && file_w != 'H' && file_w != 'e' && file_w != 'h');

    SetConsoleTextAttribute(h, (file_w == 'E' || file_w == 'e') ? A_YESIL : A_KIRMIZI);
    printf("%c", file_w);
    SetConsoleTextAttribute(h, wOldColorAttrs);

    if (file_w == 'E' || file_w == 'e')
    {
        FILE* fp = fopen("scoreboard.txt", "a+b");

        fprintf(fp, "%3d -> %s <- %u = 0x%x\n", score, name, zaman, zaman);

        fclose(fp);
    }
}
/*
void AltEnter()
{
    keybd_event(VK_MENU, 0x38, 0, 0);
    keybd_event(VK_RETURN, 0x1c, 0, 0);
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);

    return;
}
*/
int main()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(h, &csbiInfo);
    WORD wOldColorAttrs = csbiInfo.wAttributes;

    HWND konsol = GetConsoleWindow();

    SendMessage(konsol, WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

    while (1)
    {
        DrawMenu(h, wOldColorAttrs);

        while ((option = __getch()) == ESC ? 0 : ((started ? (option != 'f') : 1) && option != ENTER && option != 's' && option != 'h'));

        if (option == ESC)
        {
            if (started)
            {
                DrawMenu(h, wOldColorAttrs);
            }
            else (SetConsoleTextAttribute(h, GRAY), printf("\r      [ESC] -> Cikis"));

            break;
        }

        SetConsoleTextAttribute(h, wOldColorAttrs);

        // SCOREBOARD
        if (option == 's')
        {
            FILE* skord = fopen("scoreboard.txt", "rb");

            if (!skord)
            {
                SetConsoleTextAttribute(h, KIRMIZI);
                printf("\n\n      Hic Oyun Oynanmamis!");
            }
            else
            {
                system("CLS");

                printf("SCOREBOARD\n----------\n");

                while ((file_r = fgetc(skord)) != EOF)
                {
                    printf("%c", file_r);
                }

                fclose(skord);
            }

            __getch();
            continue;
        }

        if (option == 'h') // HELP FILE
        {
            system("CLS");

            ust_cerceve2;
            printf("%c      101 okey nasil oynanir:                                                                          %c\n", 186, 186);
            bos_satir_cerceve(1);

            for (i = 0; i < 21; i++)
            {
                printf("%c %s %c\n", 186, howto[i], 186);
            }

            alt_cerceve1;
            printf("\nDevam etmek icin bir tusa basiniz...");

            __getch();
            continue;
        }

        ////////////////////////////////// OYUN MASASININ SON HALI
        if (option == 'f')
        {
            DrawPC(h, wOldColorAttrs);
            DrawTas(h, wOldColorAttrs);
            DrawBoard(h, wOldColorAttrs);

            // Menuye geri donus bekleme dongusu
            while ((d = __getch()) != ESC);

            DrawMenu(h, wOldColorAttrs);
        }
        else
        {
            fflush(stdin);

            (SetConsoleTextAttribute(h, A_YESIL), printf("\n\n      Oyuncu Adi "));
            (SetConsoleTextAttribute(h, CYAN), printf("> "));

            SetConsoleTextAttribute(h, GRAY);

            gets_s(name, MAX_NAME_LEN);
        }

        /////////////////////////////////////////////

        if (option == ENTER)
        {
            srand(Seeder());

            StartGame();
            Distrubute();
            DistrubutePC();

            SaveMove();
            SetConsoleTextAttribute(h, 15);

            DrawPC(h, wOldColorAttrs);
            DrawTas(h, wOldColorAttrs);
            DrawBoard(h, wOldColorAttrs);

            escape = 0;

            while (!escape && !gameover)
            {
                if (!started) started = 1;

                while ((c = __getch()) != 'o' && c != 'c' && c != 's' && c != 't' && c != 'z' && c != 'k' && c != 'd' && c != '0' && c != '1' && c != '2' && c != '3' && c != 'p' && c != ESC);

                if (c != 'p' && c != ESC)
                {
                    if (c != 'z') SaveMove();
                    if (c == 't') // Throw
                    {
                        m = 16; // SECIM TASI

                        while (a != 13)
                        {
                            DrawThrow(h, wOldColorAttrs);

                            while ((a = __getch()) != 'w' && a != 'a' && a != 's' && a != 'd' && a != 13);

                            if (a != 13 && ((a == 'w' && m > 10) || (a == 'a' && m > 0) || (a == 's' && m < 11) || (a == 'd' && m < 21)))
                            {
                                DrawThrow(h, wOldColorAttrs);

                                m += (a == 'w' ? -11 : (a == 'a' ? -1 : (a == 's' ? 11 : 1)));
                            }
                        }
                    }

                    a = 0;

                    if (c == 'z') Undo();
                    if (c == 'k') Mix();
                    if (c == 'd')
                    {
                        Duzenle();
                        DizimSonu();
                    }

                    if (c == '0')
                    {
                        ZeroCount();

                        if (zerocount)
                        {
                            ShiftZeros();
                        }
                    }

                    DrawPC(h, wOldColorAttrs);
                    DrawTas(h, wOldColorAttrs);
                    DrawBoard(h, wOldColorAttrs);

                    score++;
                }

                y = 'H';
                z = 'a';

                ////////////////////////////////////////// DURAKLATMA MENüSü
                while ((c == 'p' || c == ESC) && y == 'H')
                {
                    PauseMenu(h, wOldColorAttrs);

                    while ((z = __getch()) != 'a' && z != 27 && z != 'r');

                    if (z == 97) break;
                    if (z == ESC || z == 'r')
                    {
                        PauseMenu(h, wOldColorAttrs);
                        Eminlik(h, wOldColorAttrs, score);

                        while ((y = __getch()) != 'E' && y != 'H');

                        SetConsoleTextAttribute(h, (y == 'E' || y == 'e') ? A_YESIL : A_KIRMIZI);
                        printf("%c", y);

                        SetConsoleTextAttribute(h, wOldColorAttrs);

                        if (y == 'E')
                        {
                            if (z == ESC)
                            {
                                escape = 1;
                                break;
                            }
                            else
                            {
                                SaveScore(h, wOldColorAttrs);

                                StartGame();
                                Distrubute();
                                DistrubutePC();
                            }
                        }

                        z = 'a';
                    }
                }

                if (escape) break;
                else
                {/*
                       DrawPC(h, wOldColorAttrs);
                      DrawTas(h, wOldColorAttrs);
                    DrawBoard(h, wOldColorAttrs);*/
                }
            }

            if (score) SaveScore(h, wOldColorAttrs);
        }
    }

    SetConsoleTextAttribute(h, wOldColorAttrs);
    printf(IMZA);

    return !__getch();
}