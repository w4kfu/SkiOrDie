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

* ![CPSHOP.LZW_0][2] : "AP"
* ![CPSHOP.LZW_1][3] : "BB"
* ![CPSHOP.LZW_2][4] : "GP"
* ![CPSHOP.LZW_3][5] : "ST"
* ![CPSHOP.LZW_4][6] : "PZ"
* ![CPSHOP.LZW_5][7] : "AS"
* ![CPSHOP.LZW_6][8] : "GM"
* ![CPSHOP.LZW_7][9] : "KB"
* ![CPSHOP.LZW_8][10] : "BA"
* ![CPSHOP.LZW_9][11] : "MT"

# Files Information

Files uses the extension ".lzw", but the compression algorithm is LZSS !

All images must be flip it horizontaly.

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
[2]:http://w4kfu.com/misc/skiordie/status/CPSHP.LZW/CPSHP.LZW_0.bmp
[3]:http://w4kfu.com/misc/skiordie/status/CPSHP.LZW/CPSHP.LZW_1.bmp
[4]:http://w4kfu.com/misc/skiordie/status/CPSHP.LZW/CPSHP.LZW_2.bmp
[5]:http://w4kfu.com/misc/skiordie/status/CPSHP.LZW/CPSHP.LZW_3.bmp
[6]:http://w4kfu.com/misc/skiordie/status/CPSHP.LZW/CPSHP.LZW_4.bmp
[7]:http://w4kfu.com/misc/skiordie/status/CPSHP.LZW/CPSHP.LZW_5.bmp
[8]:http://w4kfu.com/misc/skiordie/status/CPSHP.LZW/CPSHP.LZW_6.bmp
[9]:http://w4kfu.com/misc/skiordie/status/CPSHP.LZW/CPSHP.LZW_7.bmp
[10]:http://w4kfu.com/misc/skiordie/status/CPSHP.LZW/CPSHP.LZW_8.bmp
[11]:http://w4kfu.com/misc/skiordie/status/CPSHP.LZW/CPSHP.LZW_9.bmp
