// soubor na disku formatu ScopeWin Bin (*.w, *.m) ma nasledujici strukturu :
//          1. kanal       2.kanal       ....
// IG  HG  FG1 XXXXXXXXXX  FG2 XXXXXXXXX ....
//
//  X - float data (4 byte = float, real, ... )
//
// short - 16 bit integer
//
  #define MAXCHANNUMB 128  // povoleny pocet kanalu v souboru
  #define COMMENTDIM  300  // dimenze komentare
  //#define DATAindx  long   // Datovy typ indexu alokovaneho pole dat -- 32bit system
  #define DATAindx  int  // Datovy typ indexu alokovaneho pole dat -- 64bit system
  #define HUFA huge       // Typ ukazatele pole dat (huge,far)
  #define DPTR float      // Typ pole dat (short,float)
  #define SOFTVERSION "SCOPEWIN, B 3.0,7/95" // max 128 kanalu v hlavicce souboru
#include <string>


struct time
 {
   unsigned char ti_min;      /* minutes */
   unsigned char ti_hour;     /* hours */
   unsigned char ti_hund;     /* hundredths of seconds */
   unsigned char ti_sec;      /* seconds */
};




struct IG_s { // struktura pro identifikaci dat
		  char  SoftVersion[20]; //  "SCOPEWIN, B 3.0,7/95"
		  short   CelkovyPocetKanalu; // maximalni celkovy pocet kanalu (128), pro detekci poctu zaznamenanych kanalu 
                                              // v souboru pouzijte hodnotu PocetZaznamu v HG_s
		};

struct HG_s { // spolecna hlavicka vsem zaznamum  (kanalum) v souboru 
		  short  PocetZaznamu;
		  short  Zaznam[MAXCHANNUMB]; //BOOL  TRUE, TRUE, FALSE, FALSE, TRUE, ...
				   // prirazeni kanalu zaznamum
		  DATAindx  Size; // HG.Size - delka jednoho kanalu ve vzorcich (float 4 BYTE), pro vsechny kanaly stejna delka.
		  short  Waveform; //BOOL,  typ mereni : TRUE - wave, FALSE - mesurement (pomale mereni)
		  char  Date[12]; // datum ulozeni dat
		  short  EventDetected; //BOOL detekce udalosti pri pomalem mereni
		  DATAindx   Before;  // pocet bodu pred udalosti
		  struct time EventTime; // casova poloha udalosti
		  char  Comment[COMMENTDIM]; // uzivatelsky komentar
		};

struct FG_s { // hlavicka jednoho zaznamu (kanalu) v souboru
		  short  Freq;      // BOOL, TRUE - ve frekvencni oblasti, FALSE -  v casove
		  char  Name[30];   // jmeno zaznamu (kanalu)
		  char  SI[20];     // jmeno jednotky : K,V,Ohm,A, Celsius,, mmHg, AU, ...
		  short Unit;       // rad rednotky : 1 No U,  2 uU, 3 mU, 4 U, 5 kU, 6 MU , doporuceno Unit=4
		  char  XUnit[20];  // jednotka casove osy x [s], 
		  float XDelta;     // vzdalenost dvou vzorku v sekundach, priklad: 0.002 = 2 ms = 500Hz vzorkovani
		 };

