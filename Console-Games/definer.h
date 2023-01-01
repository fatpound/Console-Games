/*******************************************************************************/
/*                                                                             */
/*                 >::     ::<                                                 */
/*                :+:     :+:                                                  */
/*               +:+     +:+                                                   */
/*              +##+###+##+                                :::      ::::::::   */
/*             +#+     +#+                               :+:      :+:    :+:   */
/*            #+#     #+#                              +:+ +:+         +:+     */
/*   definer.###     ###                              +#+  +:+       +#+       */
/*                                                  +#+#+#+#+#+   +#+          */
/*                                                       #+#    #+#            */
/*   By: fatpound                                       ###   ########.tr      */
/*                                                                             */
/*   Created: 06/06/2022 17:40:22 by fatpound                                  */
/*   Updated: 07/06/2022 15:09:29                                              */
/*                                                                             */
/*******************************************************************************/

#pragma once

#define SWAP(x, y)   (x == y ? 0 : (x ^= y ^= x ^= y))
#define SWAP_P(x, y) (*(x) == *(y) ? 0 : (*(x) ^= *(y) ^= *(x) ^= *(y)))

#define MAX_NAME_LEN 0x100

// KEYBOARD COMMANDS

#define ESC          0x1B
#define ENTER        0xD

// COLOURS

#define RED        4
#define BLUE       1
#define YELLOW     6
#define GREEN      2
#define GRAY       8
#define CYAN       11
#define PURPLE     13
#define WHITE      15

#define L_RED      12
#define L_BLUE     3
#define L_YELLOW   14
#define L_GREEN    10

#define NBLUE      9

// IN TURKISH

#define KIRMIZI    RED
#define MAVI       BLUE
#define SARI       YELLOW
#define YESIL      GREEN
#define GRI        GRAY
#define TURKUAZ    CYAN
#define MOR        PURPLE
#define BEYAZ      WHITE

#define A_KIRMIZI  L_RED
#define A_MAVI     L_BLUE
#define A_SARI     L_YELLOW
#define A_YESIL    L_GREEN

// TASLAR

#define RENK_0     YESIL
#define RENK_1     KIRMIZI
#define RENK_2     MAVI
#define RENK_3     SARI

//////////////////////////////////////////

#define bos_satir_cerceve(x) for(i = 0; i < x; i++)   printf("%c                                                                                                       %c\n", 186, 186)

// #define ust_cerceve1         for(i = 0; i < 105; i++) printf("%c%s", i ? (i == 2 ? 185 : (i == 3 ? 'x' : (i == 4 ? 204 : (i == 69 ? 203 : (i == 104 ? 187 : 205))))) : 201, i == 104 ? "\n" : "")

#define ust_cerceve1         for(i = 0; i < 102; i++) printf("%c%s%s", i ? (i == 2 ? 185 : (i == 3 ? 204 : (i == 66 ? 203 : (i == 101 ? 187 : 205)))) : 201, i == 2 ? "ESC" : "", i == 101 ? "\n" : "")
#define ust_cerceve2         for(i = 0; i < 105; i++) printf("%c%s", i ? (i == 104 ? 187 : 205) : 201, i == 104 ? "\n" : "")
#define ust_cerceve3         for(i = 0; i < 105; i++) printf("%c%s", i ? (i == 2 ? 185 : (i == 3 ? 'x' : (i == 4 ? 204 : (i == 104 ? 187 : 205)))) : 201, i == 104 ? "\n" : "")

#define ustel_frame          for(i = 0; i < 105; i++) printf("%c%s", (!i || i == 104 || i == 69) ? 186 : 32, i == 104 ? "\n" : "")

#define alt_cerceve1         for(i = 0; i < 105; i++) printf("%c%s", i ? (i == 104 ? 188 : 205) : 200, i == 104 ? "\n" :"" )
#define alt_cerceve2         for(i = 0; i < 105; i++) printf("%c%s", i ? (i == 69 ? 202 : (i == 104 ? 188 : 205)) : 200, i == 104 ? "\n" : "")

#define istaka_ust_cerceve   for(i = 0; i < 66; i++)  printf("%c", i ? (i == 65 ? 187 : 205) : (SetConsoleTextAttribute(h, 15), 201))
#define istaka_ort_cerceve   for(i = 0; i < 66; i++)  printf("%c", i ? (i == 65 ? 185 : 205) : (SetConsoleTextAttribute(h, 15), 204))
#define istaka_alt_cerceve   for(i = 0; i < 66; i++)  printf("%c", i ? (i == 65 ? 188 : 205) : (SetConsoleTextAttribute(h, 15), 200))

//////////////////////////////////////////

#define ORTATAS     taslar[i][j][0]
#define ORTATAS_R   taslar[i][j][1]

#define ISTAKA      board[i][j][0] // Istaka
#define ISTAKA_R    board[i][j][1]

#define PC          pc[i][j][k][0] // PC Tasi
#define PC_R        pc[i][j][k][1] // Renk