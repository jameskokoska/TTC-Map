#include <FastLED.h>
#define NUM_LEDS 150
#define DATA_PIN 6
#define BRIGHTNESS 50
#define TRAINTRAVEL 15 //10 or 1 or 15
#define STATIONWAIT 15 //10 or 0.5 or 15
#define SPEED 2 //1 or 0.5 or 2
#define COL_TRANSFER CRGB::White
#define BORDER_START 115
#define LOWER_BRIGHTNESS_OF_LINES_PERCENT 220

CRGB leds[NUM_LEDS];
int currentTransferStop = -1;
int lines[8][45] ={{0,1,2,3,4,5,6,7,8,9,10,11,12,13,15,87,18,73,22,23,24,25,26,27,28,29,30,31,32,33,35,-1},
                  {36,37,40,41,42,-1},
                  {51,53,55,57,65,-1},
                  {63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,80,82,83,84,85,86,87,89,90,91,95,96,97,98,99,100,102,103,104,105,107,108,0,0,0,-1},
                  {35,33,32,31,30,29,28,27,26,25,24,23,22,73,18,87,15,13,12,11,10,9,8,7,6,5,4,3,2,1,0,-1},
                  {42,41,40,37,36,-1},
                  {65,57,55,53,51,-1},
                  {108,107,105,104,103,102,100,99,98,97,96,95,91,90,89,87,86,85,84,83,82,80,78,77,76,75,74,73,72,71,70,69,68,67,66,65,64,63,-1}};

int transferStations[] = {15,35,65,73,87,89};
int transferStationsYellow[] = {65,73,87,89,15};
int transferStationsPurple = 65;
int transferStationsBlue = 35;
int transferStationsGreen[] = {15,89,87,73,35}; //15 and 89 are grouped
int lineSize[] = {31,6,4,38,31,6,4,38};//36


void setup() { 
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  randomSeed(analogRead(0));

  //test all leds...

  // for(int trainStop = 0; trainStop < findLength(0); trainStop++){
  //   leds[lines[0][trainStop]] = CRGB::Green;
  //   counterDelay(30);
  //   FastLED.show();
  // }
  // counterDelay(50);
  // for(int trainStop = 0; trainStop < findLength(1); trainStop++){
  //   leds[lines[1][trainStop]] = CRGB::Blue;
  //   counterDelay(30);
  //   FastLED.show();
  // }
  // counterDelay(50);
  // for(int trainStop = 0; trainStop < findLength(2); trainStop++){
  //   leds[lines[2][trainStop]] = CRGB::Purple;
  //   counterDelay(30);
  //   FastLED.show();
  // }
  // counterDelay(50);
  // for(int trainStop = 0; trainStop < findLength(3); trainStop++){
  //   leds[lines[3][trainStop]] = CRGB::Yellow;
  //   counterDelay(30);
  //   FastLED.show();
  // }
  // counterDelay(100);
  // for(int trainStop = 0; trainStop < findLength(0); trainStop++){
  //   leds[lines[0][trainStop]] = CRGB::Black;
  //   counterDelay(10);
  //   FastLED.show();
  // }
  // counterDelay(10);
  // for(int trainStop = 0; trainStop < findLength(1); trainStop++){
  //   leds[lines[1][trainStop]] = CRGB::Black;
  //   counterDelay(10);
  //   FastLED.show();
  // }
  // counterDelay(10);
  // for(int trainStop = 0; trainStop < findLength(2); trainStop++){
  //   leds[lines[2][trainStop]] = CRGB::Black;
  //   counterDelay(10);
  //   FastLED.show();
  // }
  // counterDelay(10);
  // for(int trainStop = 0; trainStop < findLength(3); trainStop++){
  //   leds[lines[3][trainStop]] = CRGB::Black;
  //   counterDelay(10);
  //   FastLED.show();
  // }
  
  // counterDelay(100);

  // for(int trainStop = 0; trainStop < findLength(7); trainStop++){
  //   leds[lines[7][trainStop]] = CRGB::Yellow;
  //   counterDelay(30);
  //   FastLED.show();
  // }
  // counterDelay(50);
  // for(int trainStop = 0; trainStop < findLength(6); trainStop++){
  //   leds[lines[6][trainStop]] = CRGB::Purple;
  //   counterDelay(30);
  //   FastLED.show();
  // }
  // counterDelay(50);
  // for(int trainStop = 0; trainStop < findLength(5); trainStop++){
  //   leds[lines[5][trainStop]] = CRGB::Blue;
  //   counterDelay(30);
  //   FastLED.show();
  // }
  // counterDelay(50);
  // for(int trainStop = 0; trainStop < findLength(4); trainStop++){
  //   leds[lines[4][trainStop]] = CRGB::Green;
  //   counterDelay(30);
  //   FastLED.show();
  // }
  // counterDelay(10);
  // for(int trainStop = 0; trainStop < findLength(7); trainStop++){
  //   leds[lines[7][trainStop]] = CRGB::Black;
  //   counterDelay(10);
  //   FastLED.show();
  // }
  // counterDelay(10);
  // for(int trainStop = 0; trainStop < findLength(6); trainStop++){
  //   leds[lines[6][trainStop]] = CRGB::Black;
  //   counterDelay(10);
  //   FastLED.show();
  // }
  // counterDelay(10);
  // for(int trainStop = 0; trainStop < findLength(5); trainStop++){
  //   leds[lines[5][trainStop]] = CRGB::Black;
  //   counterDelay(10);
  //   FastLED.show();
  // }
  // counterDelay(10);
  // for(int trainStop = 0; trainStop < findLength(4); trainStop++){
  //   leds[lines[4][trainStop]] = CRGB::Black;
  //   counterDelay(10);
  //   FastLED.show();
  // }
  // while (true){
  // for(int i=0; i< 120; i++){
  //   leds[i] = CRGB::Yellow;
  //   counterDelay(20);
  //   FastLED.show();
  // }
  //   counterDelay(5000);

  // for(int i=0; i< 120; i++){
  //   leds[i] = CRGB::Black;
  //   counterDelay(20);
  //   FastLED.show();
  // }
  // }
  // counterDelay(10000);
}

void turnOnColour(int led, int lineID){
  if (lineID == 0 || lineID == 4){
    leds[led] = CRGB::Green;
    leds[led].fadeToBlackBy(LOWER_BRIGHTNESS_OF_LINES_PERCENT);
  } else if (lineID == 1 || lineID == 5){
    leds[led] = CRGB::Blue;
    leds[led].fadeToBlackBy(LOWER_BRIGHTNESS_OF_LINES_PERCENT);
  } else if (lineID == 2 || lineID == 6){
    leds[led] = CRGB::Purple;
    leds[led].fadeToBlackBy(LOWER_BRIGHTNESS_OF_LINES_PERCENT);
  } else if (lineID == 3|| lineID == 7){
    leds[led] = CRGB::Yellow;
    leds[led].fadeToBlackBy(LOWER_BRIGHTNESS_OF_LINES_PERCENT);
  } else {
    leds[led] = CRGB::Black;
  }
}

int findLength(int lineID){
  for(int i = 0; i < sizeof(lines[lineID])/sizeof(lines[lineID][0]); i++){
    if(lines[lineID][i]==-1){
      if (lineID == 1){
        return i; //number of transfer stops not included in the line , need to subtract
      } else if (lineID == 3){
        return i-3;
      }
      return i;
    }
  }
  return 0;
}

void turnOnLine(int line[], int lineID, int onOff){
  for(int trainStop = 0; trainStop < lineSize[lineID]; trainStop++){
    if (onOff == 1){
      turnOnColour(line[trainStop], lineID);
    } else {
      turnOnColour(line[trainStop], -1);
    }
  }
}

void blinkLine(int line[], int lineID){
      for(int blinkCount = 0; blinkCount < STATIONWAIT; blinkCount++){
        turnOnLine(line, lineID, 1);
        counterDelay(500*SPEED);
        FastLED.show();
        turnOnLine(line, lineID, 0);
        counterDelay(500*SPEED);
        FastLED.show();
      }
    return;
}

int checkTransferStop(int currentStop){
  for(int transferStop = 0; transferStop < sizeof(transferStations)/sizeof(transferStations[0]); transferStop++){
    if (currentStop == transferStations[transferStop]){
      return transferStations[transferStop];
    }
  }
  return -1;
}

void showTransferStops(){
  for(int transferStop = 0; transferStop < sizeof(transferStations)/sizeof(transferStations[0]); transferStop++){
    leds[transferStations[transferStop]] = COL_TRANSFER;
    leds[transferStations[transferStop]].fadeToBlackBy(LOWER_BRIGHTNESS_OF_LINES_PERCENT);
  }
  FastLED.show();
}

void removeAll(){
  for(int led = 0; led < BORDER_START-1; led++){
    leds[led] = CRGB::Black;
    counterDelay(0);
    FastLED.show();
  }
}

uint8_t gHue = 0;

void rainbowLine() 
{
  gHue++;
  for( uint16_t i = BORDER_START; i < NUM_LEDS; ++i) {
    leds[i].nscale8(255-20);
  }
  int pos = beatsin16(6, BORDER_START, NUM_LEDS-1);
  leds[pos] += CHSV( gHue, 255, 192);
  int pos2 = beatsin16(6, BORDER_START, NUM_LEDS-1);
  leds[BORDER_START + NUM_LEDS-1 - pos2] += CHSV(gHue, 255, 192);
  FastLED.show();
}

void counterDelay(int count){
  int updates = 20;
  int counterWait = 0;
  while (count/updates > counterWait){
    counterWait++;
    delay(updates);
    //put functions here that require constant clock updates
    rainbowLine();
  }
  return;
}

void loop() {
  int currentLine = random(0,8);
  //reset
  removeAll();
  turnOnLine(lines[currentLine], currentLine, 1);
  showTransferStops();
  counterDelay(20);  

  FastLED.show();

  for(int trainStop = 0; trainStop < findLength(currentLine); trainStop++){
    currentTransferStop = checkTransferStop(lines[currentLine][trainStop]);
    //it doesn't make sense that the train tavels to the stop is starts on, because it leaves there. it needs to start off red and then just move on
    if(trainStop == 0){
      if (currentTransferStop == -1){
        leds[lines[currentLine][trainStop]] = CRGB::Red;
        leds[lines[currentLine][trainStop]].fadeToBlackBy(LOWER_BRIGHTNESS_OF_LINES_PERCENT);
      } else {
        leds[lines[currentLine][trainStop]] = COL_TRANSFER;
      }
      continue;
    }

    //turn red when train leaves then start flashing
    if (currentTransferStop == -1){
        leds[lines[currentLine][trainStop]] = CRGB::Red;
        leds[lines[currentLine][trainStop]].fadeToBlackBy(LOWER_BRIGHTNESS_OF_LINES_PERCENT);
      } else {
        leds[lines[currentLine][trainStop]] = COL_TRANSFER;
      }
    FastLED.show();

    //flash while train moving
    for(int trainTravelTime = 0; trainTravelTime < TRAINTRAVEL; trainTravelTime++){
      leds[lines[currentLine][trainStop]] = CRGB::Black;
      counterDelay(500*SPEED);
      FastLED.show();
      if (currentTransferStop == -1){
        leds[lines[currentLine][trainStop]] = CRGB::Red;
        leds[lines[currentLine][trainStop]].fadeToBlackBy(LOWER_BRIGHTNESS_OF_LINES_PERCENT);
      } else {
        leds[lines[currentLine][trainStop]] = COL_TRANSFER;
        leds[lines[currentLine][trainStop]].fadeToBlackBy(LOWER_BRIGHTNESS_OF_LINES_PERCENT);
      }
      counterDelay(500*SPEED);
      FastLED.show();
      }
    //train arrived
    if (currentTransferStop == -1){
      counterDelay(1000*STATIONWAIT);
    } else {
      if(currentLine != 0 && currentLine != 4){
        for(int transferStop = 0; transferStop < sizeof(transferStationsGreen)/sizeof(transferStationsGreen[0]); transferStop++){
          if(currentTransferStop == transferStationsGreen[transferStop]){
            blinkLine(lines[0],0);
            showTransferStops();
          }
        }
      }
      if((currentLine !=1 && currentLine != 5) && currentTransferStop == transferStationsBlue){
        blinkLine(lines[1],1);
        showTransferStops();
      } else if((currentLine != 2 && currentLine != 6) && currentTransferStop == transferStationsPurple){
        blinkLine(lines[2],2);
        showTransferStops();
      }
      if(currentLine != 3 && currentLine != 7){
        for(int transferStop = 0; transferStop < sizeof(transferStationsYellow)/sizeof(transferStationsYellow[0]); transferStop++){
          if(currentTransferStop == transferStationsYellow[transferStop]){
              blinkLine(lines[3],3);
              showTransferStops();
          }
        }
      }
      
    }
  }
}
