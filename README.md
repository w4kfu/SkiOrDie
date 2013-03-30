# CopyProtection

Game downloaded from [AbandonWareFrance][1] is already patched to avoid copy protection questions, that's sad for someone who want to study the protection, so here is the original code :


## Original code from SKIEGA unpacked version :

	seg000:0532                 mov     byte_1EE21, 1Ch
	seg000:0537                 push    es
	seg000:0538                 mov     ax, OffsetDataRead
	...
	seg000:054F                 mov     bCopyProtection, 0
	seg000:0554                 mov     bCopyProtection2, 0
	seg000:0559
	seg000:0559 loc_10559:
	seg000:0559                 mov     al, ColorBlack

## Patched (cracked?) version :

	seg000:0532                 jmp     short loc_1054F
	seg000:0534 ; ---------------------------------------------------------------------------
	seg000:0534                 xchg    ax, cx
	seg000:0535                 insb
	seg000:0536                 sbb     al, 6
	...
	seg000:054F                 mov     bCopyProtection, 1
	seg000:0554                 mov     bCopyProtection2, 1
	seg000:0559
	seg000:0559 locret_10559:
	seg000:0559                 retn

## Code for copy protection

* ![CPSHOP0][2] : "AP"
* ![CPSHOP1][3] : "BB"
* ![CPSHOP2][4] : "GP"
* ![CPSHOP3][5] : "ST"
* ![CPSHOP4][6] : "PZ"
* ![CPSHOP5][7] : "AS"
* ![CPSHOP6][8] : "GM"
* ![CPSHOP7][9] : "KB"
* ![CPSHOP8][10] : "BA"
* ![CPSHOP9][11] : "MT"

# Files Information

Files uses the extension ".lzw", but the compression algorithm is LZSS !

All images must be fliped horizontaly.

## "*BM.LZW"

Multiple sprites of 4-Bit image

	+0x00 : Width
	+0x01 : Height
	+0x02 : Data

Data Layout for each line (X * height) :

	+0x00 : Gap Start X position
	+0x01 : Number of pixels
	+0x02 : 4-bit color <Number of pixels * 0x02>

### Example

Entry 17 (0x11) of the file "MNFBM.LZW"

	[    0000]   0E 1A 00 0C CC CC CC CC   CC CC CC CC CC CC CC CC   ........ ........
	[    0010]   00 0C CC 99 99 99 C9 9C   CC 99 CC 99 99 CC 00 0C   ........ ........
	[    0020]   C9 91 11 11 C9 9C C9 91   CC 19 91 CC 00 0C C1 99   ........ ........
	[    0030]   99 9C C9 99 99 1C CC C9   9C CC 00 0E CC 11 11 99   ........ ........
	[    0040]   C9 91 19 9C CC C9 9C CC   44 00 00 0E C9 99 99 91   ........ D.......
	[    0050]   C9 9C C1 99 CC 99 99 CC   44 00 00 0E C1 11 11 1C   ........ D.......
	[    0060]   C1 1C CC 11 CC 11 11 CC   44 00 00 0E CC CC CC CC   ........ D.......
	[    0070]   CC CC CC CC CC CC CC CC   44 00 00 0E CC CC CC C8   ........ D.......
	[    0080]   7C CC CC CC CC CC CC CC   44 00 00 0E CC CC CC 88   |....... D.......
	[    0090]   87 CC C9 99 99 9C CC CC   44 00 00 0E CC CC C8 88   ........ D.......
	[    00a0]   88 7C C9 91 11 99 CC CC   44 00 00 0E CC CC 88 88   .|...... D.......
	[    00b0]   88 87 C9 99 99 91 CC CC   44 00 00 0E CC CC 88 88   ........ D.......
	[    00c0]   88 87 C9 91 11 99 CC CC   44 00 00 0E CC CC C8 88   ........ D.......
	[    00d0]   88 7C C9 9C CC 99 CC CC   44 00 00 0E CC CC CC 88   .|...... D.......
	[    00e0]   87 CC C1 1C CC 11 CC CC   44 00 00 0E CC CC CC C8   ........ D.......
	[    00f0]   7C CC CC CC CC CC CC CC   44 00 00 0E CC CC CC CC   |....... D.......
	[    0100]   CC CC CC CC CC CC CC CC   44 00 00 0E C9 99 99 9C   ........ D.......
	[    0110]   C9 99 9C C9 99 99 99 CC   44 00 00 0E C9 91 11 99   ........ D.......
	[    0120]   C1 99 1C C9 91 11 11 CC   44 00 00 0E C9 9C CC 99   ........ D.......
	[    0130]   CC 99 CC C9 99 99 CC CC   44 00 00 0E C9 9C CC 99   ........ D.......
	[    0140]   CC 99 CC C9 91 11 CC CC   44 00 00 0E C9 99 99 91   ........ D.......
	[    0150]   C9 99 9C C9 99 99 99 CC   44 00 00 0E C1 11 11 1C   ........ D.......
	[    0160]   C1 11 1C C1 11 11 11 CC   44 00 00 0E CC CC CC CC   ........ D.......
	[    0170]   CC CC CC CC CC CC CC CC   44 00 01 0C 44 44 44 44   ........ D...DDDD
	[    0180]   44 44 44 44 44 44 44 44   01 0C 44 44 44 44 44 44   DDDDDDDD ..DDDDDD
	[    0190]   44 44 44 44 44 44                                   DDDDDD

* Widht = 0x0E * 2
* Height = 0x1A

Line 0 :

* Gap = 0x00
* Number of pixels : 0x0C * 2

Gap, pixels, data pixels :

	00 0C CC CC CC CC CC CC CC CC CC CC CC CC

Line 1, 2, 3, 4 :

	00 0C CC 99 99 99 C9 9C CC 99 CC 99 99 CC
	00 0C C9 91 11 11 C9 9C C9 91 CC 19 91 CC
	00 0C C1 99 99 9C C9 99 99 1C CC C9 9C CC
	00 0E CC 11 11 99 C9 91 19 9C CC C9 9C CC 44 00

etc ...

## SPLASH.LZW

4-Bit image for SplashScreen.

## MNSHP.LZE

0xB (11) 4-Bit image used for ski station animation (3 for "Rodney's" sign, 8 for ski lift).

## HISCORE.LZW

4-Bit image for HighScores screen

## TSQUARE.LZW

4-Bit image for ski resort

## DHSHP.LZW

0xA (10) 4-Bit image for .... (TODO)

## SBSHP.LZW

0x12 (18) 4-Bit image for ... (TODO)

## SHOP.LZW

4-Bit image for Main Screen

## SFSHP.LZW

0x17 (23) 4-Bit image for ... (TODO)

## ACROJUMP.LZW

4-Bit image for Acro Aerials game

## SNOWFORT.LZW

4-Bit image for Snowball Blast game

## SBTUBE.LZW

4-Bit image for for SnowBoard HalfPipe game

## AJSHP.LZW

0x16 (22) 4-Bit image for ... (TODO)

## TBSHP.LZW

0x7 (7) 4-Bit image for ... (TODO)

## SIGNUP.LZW

4-Bit image to SignIn competition

## CPSHP.LZW

0x9 (9) 4-Bit image usef for game protection ... TODO


[1]:http://www.abandonware-france.org/ltf_abandon/ltf_jeu.php?id=624&fic=liens
[2]:http://w4kfu.com/misc/skiordie/status/CPSHP.LZW/CPSHP.LZW_0.bmp "code1"
[3]:http://w4kfu.com/misc/skiordie/status/CPSHP.LZW/CPSHP.LZW_1.bmp "code2"
[4]:http://w4kfu.com/misc/skiordie/status/CPSHP.LZW/CPSHP.LZW_2.bmp "code3"
[5]:http://w4kfu.com/misc/skiordie/status/CPSHP.LZW/CPSHP.LZW_3.bmp "code4"
[6]:http://w4kfu.com/misc/skiordie/status/CPSHP.LZW/CPSHP.LZW_4.bmp "code5"
[7]:http://w4kfu.com/misc/skiordie/status/CPSHP.LZW/CPSHP.LZW_5.bmp "code6"
[8]:http://w4kfu.com/misc/skiordie/status/CPSHP.LZW/CPSHP.LZW_6.bmp "code7"
[9]:http://w4kfu.com/misc/skiordie/status/CPSHP.LZW/CPSHP.LZW_7.bmp "code8"
[10]:http://w4kfu.com/misc/skiordie/status/CPSHP.LZW/CPSHP.LZW_8.bmp "code9"
[11]:http://w4kfu.com/misc/skiordie/status/CPSHP.LZW/CPSHP.LZW_9.bmp "code10"
