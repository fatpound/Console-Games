#pragma once

#include <stdio.h>

#define IMZA "\n\n\n#fatpound & yunns\nCOPYRIGHT \xB8 2022#\n"

char *howto[] =
{
    "   101 Okey dort oyuncu ile birden fazla turda oynanir (Tur sayisini sen belirliyorsun). Bu oyunda   ",
    "amac mumkun oldugu kadar az skorla oyunu bitirmektir. Tum turlar sonunda en az skora sahip olan      ",
    "oyuncu oyunun galibidir. skorlar elde kalan taslarin uzerindeki sayilar ile belirlenir.              ",
    "   Oyun ortadan cekecek tas kalmayinca bitebilecegi gibi oyunculardan birinin elini tamamlamasi ile  ",
    "de bitebilir.                                                                                        ",
    "   oyuna baslarken 22 tasiniz olucak bu yuzden ortadan tas cekemezsiniz, elinizdeki taslardan birini ",
    "secip yana attiginizda oyun devam eder sira diger oyunculara gecer.                                  ",
    "   El acmak icin en az 34 puaniniz olmalidir. bu sayi biri elini actiginda acilan elin puaninin bir  ",
    "fazlasi olarak guncellenir. El acmak icin elinizde ayni numarali degisik renklerden 3 veya 4 adet    ",
    "set (ornek olarak siyah 5, kirmizi 5 ve bir tane de mavi 5) veya ayni renklerden sirali sayi seti    ",
    "(ornek olarak kirmizi 7,8,9) olmalidir. Bir sette minimum 3 tas olmalidir. Ayni oyun sirasinda       ",
    " hem elinizi acabilir hem de diger acilmis setlere eklemeler yapabilirsiniz. Mevcut acilmis taslara  ",
    "tas eklenebilmesi oyuncunun elini acmis olmasi gerekir. Eger oyuncu kendinden  onceki oyuncu,        ",
    "4. oyuncunun sola attigi tasi almak istiyorsa bu aldigi tasi kullanmak zorundadir. Eger bu atilan    ",
    "tasi alan oyuncu henuz elini acmamis ise bu tasi aldigi zaman elini acmali ve actigi serilerin       ",
    "birinin icinde bu alinan tas da kullanilmis olmalidir. Eger bu alinan tas ile el acamiyorsaniz       ",
    "veya el acmadiysaniz sistem yandan tas cekemenize izin vermez.                                       ",
    "   Eli acmak icin bir baska yol da en az bes cift tas biriktirmektir. Ciftten anlasilan benzer iki   ",
    "tastir. Eger oyuncu bir kez cifte giderek oyun acarsa bu oyunda bir daha normal bir set acamaz. Ancak",
    "diger oyuncularin acmis olduklari masadaki setlere tas ekleyebilir. Eger masadaki dort oyuncu da ayni",
    "oyun icinde cift acarsa bu tur iptal olur ve yeni oyuna baslanir.                                    "
},

*playoptions[] =
{
    "[o] -> ortadan tas cek                  seri ac <- [1]",
    "[s] -> seri diz                         cift ac <- [2]",
    "[c] -> cift diz                        tas isle <- [3]",
    "[t] -> tas at                    sifiri sona al <- [0]",
    "[z] -> geri al                   duzenli sirala <- [d]",
};