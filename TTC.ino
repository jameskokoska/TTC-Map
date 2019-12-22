#include <FastLED.h>
#define NUM_LEDS 120
#define DATA_PIN 6
#define BRIGHTNESS 1
#define TRAINTRAVEL 15 //10 or 1
#define STATIONWAIT 15 //10 or 0.5
#define SPEED 2 //1 or 0.5
#define COL_TRANSFER CRGB::White

CRGB leds[NUM_LEDS];
int currentTransferStop = -1;
int lines[8][45] ={{0,2,4,6,8,10,12,14,16,18,20,22,24,26,89,87,27,75,28,30,32,34,36,38,40,42,44,46,49,51,53,-1},
                  {53,54,55,57,59,60,-1},
                  {61,62,63,64,67,-1},
                  {65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,90,92,93,94,95,96,97,98,99,101,103,105,108,109,1,1,1,-1},
                  {53,51,49,46,44,42,40,38,36,34,32,30,28,75,27,87,89,26,24,22,20,18,16,14,12,10,8,6,4,2,0,-1},
                  {60,59,57,55,54,53,-1},
                  {67,64,63,62,61,-1},
                  {109,108,105,103,101,99,98,97,96,95,94,93,92,90,88,87,86,85,84,83,82,81,80,79,78,77,76,75,74,73,73,71,70,69,68,67,66,65,-1}};

int transferStations[] = {53,67,75,87,88,89};
//{14,15,17,30,42,61};
int transferStationsYellow[] = {67,75,87,89};
//{14,15,17,42};
int transferStationsPurple = 67;
int transferStationsBlue = 53;
int transferStationsGreen[] = {87,75,53,88};
int lineSize[] = {31,6,4,38};//36


void setup() { 
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  randomSeed(analogRead(0));

  for(int trainStop = 0; trainStop < findLength(0); trainStop++){
    leds[lines[0][trainStop]] = CRGB::Green;
    delay(10);
    FastLED.show();
  }
  delay(1000);
  for(int trainStop = 0; trainStop < findLength(1); trainStop++){
    leds[lines[1][trainStop]] = CRGB::Blue;
    delay(10);
    FastLED.show();
  }
  delay(1000);
  for(int trainStop = 0; trainStop < findLength(2); trainStop++){
    leds[lines[2][trainStop]] = CRGB::Purple;
    delay(10);
    FastLED.show();
  }
  delay(1000);
  for(int trainStop = 0; trainStop < findLength(3); trainStop++){
    leds[lines[3][trainStop]] = CRGB::Yellow;
    delay(10);
    FastLED.show();
  }
  delay(1000);
/*while (true){
  for(int i=0; i< 120; i++){
    leds[i] = CRGB::Yellow;
    delay(20);
    FastLED.show();
  }
    delay(5000);

  for(int i=0; i< 120; i++){
    leds[i] = CRGB::Black;
    delay(20);
    FastLED.show();
  }
  }
  delay(10000);*/
}

void turnOnColour(int led, int lineID){
  if (lineID == 0){
    leds[led] = CRGB::Green;
  } else if (lineID == 1){
    leds[led] = CRGB::Blue;  
  } else if (lineID == 2){
    leds[led] = CRGB::Purple;
  } else if (lineID == 3){
    leds[led] = CRGB::Yellow;
  } else {
    leds[led] = CRGB::Black;
  }
}

int findLength(int lineID){
  for(int i = 0; i < sizeof(lines[lineID])/sizeof(lines[lineID][0]); i++){
    if(lines[lineID][i]==-1){
      if (lineID == 1){
        return i; //number of transfer stops not inlcuded in the line , need to subtract
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
        delay(500*SPEED);
        FastLED.show();
        turnOnLine(line, lineID, 0);
        delay(500*SPEED);
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
  }
  FastLED.show();
}

void removeAll(){
  for(int led = 0; led < NUM_LEDS; led++){
    leds[led] = CRGB::Black;
    delay(0);
    FastLED.show();
  }
}

void loop() {
  int currentLine = random(0,8);
  //Reset
  removeAll();
  turnOnLine(lines[currentLine], currentLine, 1);
  showTransferStops();
  delay(500);

  FastLED.show();
  for(int trainStop = 0; trainStop < findLength(currentLine); trainStop++){
    currentTransferStop = checkTransferStop(lines[currentLine][trainStop]);
    //it doesnt make snese that the train tavels to the stop is starts on, because it leaves there. it needs to start off red and then just move on
    if(trainStop == 0){
      if (currentTransferStop == -1){
        leds[lines[currentLine][trainStop]] = CRGB::Red;
      } else {
        leds[lines[currentLine][trainStop]] = COL_TRANSFER;
      }
      continue;
    }

    //turn red when train leaves then start flashing
    if (currentTransferStop == -1){
        leds[lines[currentLine][trainStop]] = CRGB::Red;
      } else {
        leds[lines[currentLine][trainStop]] = COL_TRANSFER;
      }
      //MAKE INTO FUNCTION, USE 3 TIMES!
    FastLED.show();

    //Flash while train moving
    for(int trainTravelTime = 0; trainTravelTime < TRAINTRAVEL; trainTravelTime++){
      leds[lines[currentLine][trainStop]] = CRGB::Black;
      delay(500*SPEED);
      FastLED.show();
      if (currentTransferStop == -1){
        leds[lines[currentLine][trainStop]] = CRGB::Red;
      } else {
        leds[lines[currentLine][trainStop]] = COL_TRANSFER;
      }
      delay(500*SPEED);
      FastLED.show();
      }
    //Train arrived
    if (currentTransferStop == -1){
      delay(1000*STATIONWAIT);
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
