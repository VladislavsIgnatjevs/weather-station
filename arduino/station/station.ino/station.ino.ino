#include <FastLED.h>
#include <LEDMatrix.h>
#include <LEDSprites.h>

#define LED_PIN        2
#define COLOR_ORDER    GRB
#define CHIPSET        WS2812B
#define MATRIX_TYPE    HORIZONTAL_ZIGZAG_MATRIX
#define SHAPE_WIDTH    8
#define SHAPE_HEIGHT   8
cLEDMatrix<8, 8, MATRIX_TYPE> leds;

String incomingByte = "";


/*sun*/

const uint8_t Spritesun2Data[] = {
  B8_3BIT(11011101),
  B8_3BIT(10020001),
  B8_3BIT(13000301),
  B8_3BIT(00323000),
  B8_3BIT(20222020),
  B8_3BIT(00323000),
  B8_3BIT(03000304),
  B8_3BIT(44020044)
};
const struct CRGB Spritesun2Cols[7] = { CRGB(0, 152, 239), CRGB(255, 156, 0), CRGB(255, 246, 8), CRGB(8, 8, 189), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0) };
cSprite Sun(8, 8, Spritesun2Data, 1, _3BIT, Spritesun2Cols);


/*cloud*/

const uint8_t SpritecloudData[] = {
  B8_3BIT(00000001),
  B8_3BIT(00220011),
  B8_3BIT(02222011),
  B8_3BIT(02222000),
  B8_3BIT(00000030),
  B8_3BIT(03033030),
  B8_3BIT(03033030),
  B8_3BIT(44444444) };
const struct CRGB SpritecloudCols[7] = { CRGB(107,104,104), CRGB(255,255,255), CRGB(246,8,41), CRGB(9,255,32), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0) };
cSprite Cloud(8, 8, SpritecloudData, 1, _3BIT, SpritecloudCols);



/*rain*/
const uint8_t SpriterainData[] = {
  B8_3BIT(00100020),
  B8_3BIT(30404040),
  B8_3BIT(45004000),
  B8_3BIT(00400040),
  B8_3BIT(40404040),
  B8_3BIT(65004540),
  B8_3BIT(00400000),
  B8_3BIT(40404740)
};
const struct CRGB SpriterainCols[7] = { CRGB(25, 113, 220), CRGB(25, 111, 217), CRGB(25, 111, 216), CRGB(25, 112, 219), CRGB(0, 1, 1), CRGB(25, 112, 220), CRGB(0, 2, 3) };
cSprite Rain(8, 8, SpriterainData, 1, _3BIT, SpriterainCols);


/*snow*/
const uint8_t SpritesnowData[] = {
  B8_1BIT(00000000),
  B8_1BIT(01010101),
  B8_1BIT(00000000),
  B8_1BIT(10101010),
  B8_1BIT(00000000),
  B8_1BIT(01010101),
  B8_1BIT(00000000),
  B8_1BIT(10100101)
};
const struct CRGB SpritesnowCols[1] = { CRGB(239, 237, 230) };
cSprite Snow(8, 8, SpritesnowData, 1, _1BIT, SpritesnowCols);

const uint8_t SpritesnowrainData[] = {
  B8_2BIT(00000000),
  B8_2BIT(01020102),
  B8_2BIT(00000000),
  B8_2BIT(20102010),
  B8_2BIT(00000000),
  B8_2BIT(02010102),
  B8_2BIT(00000000),
  B8_2BIT(10100201)
};
const struct CRGB SpritesnowrainCols[3] = { CRGB(239, 237, 230), CRGB(0, 152, 239), CRGB(0, 0, 0) };
cSprite SnowRain(8, 8, SpritesnowrainData, 1, _2BIT, SpritesnowrainCols);



const uint8_t SpritesadfaceData[] = {
  B8_1BIT(00000000),
  B8_1BIT(01100110),
  B8_1BIT(01100110),
  B8_1BIT(00000000),
  B8_1BIT(00111100),
  B8_1BIT(01000010),
  B8_1BIT(10000001),
  B8_1BIT(10000001)
};
const struct CRGB SpritesadfaceCols[1] = { CRGB(255, 22, 22) };
cSprite SadFace(8, 8, SpritesadfaceData, 1, _1BIT, SpritesadfaceCols);

/* Mist */
const uint8_t SpritemistData[] = {
  B8_2BIT(00011000),
  B8_2BIT(00111100),
  B8_2BIT(01111110),
  B8_2BIT(01111110),
  B8_2BIT(00000000),
  B8_2BIT(22222222),
  B8_2BIT(00000000),
  B8_2BIT(22222222) };
const struct CRGB SpritemistCols[3] = { CRGB(255,255,255), CRGB(66,61,61), CRGB(0,0,0) };
cSprite Mist(8, 8, SpritemistData, 1, _2BIT, SpritemistCols);


/*thunder*/
const uint8_t SpritethunderData[] = {
  B8_2BIT(00000100),
  B8_2BIT(00001020),
  B8_2BIT(00210222),
  B8_2BIT(02120000),
  B8_2BIT(00111110),
  B8_2BIT(02000120),
  B8_2BIT(22201222),
  B8_2BIT(00013000) };
const struct CRGB SpritethunderCols[3] = { CRGB(234,255,0), CRGB(0,12,255), CRGB(18,1,1) };
cSprite Thunder(8, 8, SpritethunderData, 1, _2BIT, SpritethunderCols);


/*breeze*/

const uint8_t SpritebreezeData[] = {
  B8_2BIT(00000000),
  B8_2BIT(00000010),
  B8_2BIT(00100111),
  B8_2BIT(01110000),
  B8_2BIT(00000000),
  B8_2BIT(01000010),
  B8_2BIT(11100111),
  B8_2BIT(00022000) };
const struct CRGB SpritebreezeCols[3] = { CRGB(255,255,255), CRGB(18,1,1), CRGB(0,0,0) };
cSprite Breeze(8, 8, SpritebreezeData, 1, _2BIT, SpritebreezeCols);


/*extreme*/
const uint8_t SpriteextremeData[] = {
  B8_2BIT(01012122),
  B8_2BIT(01112122),
  B8_2BIT(01012222),
  B8_2BIT(02222111),
  B8_2BIT(01122100),
  B8_2BIT(01012111),
  B8_2BIT(01012100),
  B8_2BIT(01122111)
};
const struct CRGB SpriteextremeCols[3] = { CRGB(255, 0, 0), CRGB(18, 1, 1), CRGB(0, 0, 0) };
cSprite Extreme(8, 8, SpriteextremeData, 1, _2BIT, SpriteextremeCols);



/* Clear */
const uint8_t SpriteclearData[] = {
  B8_3BIT(11111111),
  B8_3BIT(11111111),
  B8_3BIT(11111111),
  B8_3BIT(11111111),
  B8_3BIT(11121111),
  B8_3BIT(12131221),
  B8_3BIT(12131221),
  B8_3BIT(44444444)
};
const struct CRGB SpriteclearCols[7] = { CRGB(3, 50, 255), CRGB(244, 13, 30), CRGB(255, 3, 3), CRGB(67, 236, 34), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0) };
cSprite Clear(8, 8, SpriteclearData, 1, _3BIT, SpriteclearCols);



const uint8_t SpritevData[] = {
  B8_2BIT(10000001),
  B8_2BIT(12000021),
  B8_2BIT(01000010),
  B8_2BIT(01200210),
  B8_2BIT(00100100),
  B8_2BIT(00122100),
  B8_2BIT(00011000),
  B8_2BIT(00011000)
};
const struct CRGB SpritevCols[3] = { CRGB(243, 23, 44), CRGB(66, 6, 11), CRGB(0, 0, 0) };
cSprite IntroV(8, 8, SpritevData, 1, _2BIT, SpritevCols);

const uint8_t SpriteiData[] = {
  B8_1BIT(00011000),
  B8_1BIT(00011000),
  B8_1BIT(00000000),
  B8_1BIT(00011000),
  B8_1BIT(00011000),
  B8_1BIT(00011000),
  B8_1BIT(00011000),
  B8_1BIT(00011000)
};
const struct CRGB SpriteiCols[1] = { CRGB(243, 13, 13) };
cSprite IntroI(8, 8, SpriteiData, 1, _1BIT, SpriteiCols);


const uint8_t SpritesmileData[] = {
  B8_2BIT(01111110),
  B8_2BIT(10000001),
  B8_2BIT(10200201),
  B8_2BIT(10000001),
  B8_2BIT(10200201),
  B8_2BIT(10222201),
  B8_2BIT(10000001),
  B8_2BIT(01111110)
};
const struct CRGB SpritesmileCols[3] = { CRGB(255, 120, 0), CRGB(255, 0, 222), CRGB(0, 0, 0) };
cSprite IntroSmiley(8, 8, SpritesmileData, 1, _2BIT, SpritesmileCols);


cLEDSprites Sprites(&leds);

void clearUpdate() {
  FastLED.clear();
  Sprites.UpdateSprites();
  Sprites.RenderSprites();
  FastLED.show();
  delay(50);
}


String current = "";

void setup()
{
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds[0], leds.Size());
  FastLED.setBrightness(22);
  FastLED.clear(true);
  delay(500);
  Sprites.RemoveAllSprites();
  Sprites.AddSprite(&IntroV);
  clearUpdate();
  delay(1000);

  Sprites.RemoveAllSprites();
  Sprites.AddSprite(&IntroI);
  clearUpdate();
  delay(1000);


  Sprites.RemoveAllSprites();
  Sprites.AddSprite(&IntroSmiley);
  clearUpdate();
  delay(2000);

  FastLED.show();


  Serial.begin(9600);
  Serial.print("\r\nStart");

}


void loop()
{
  if (Serial.available() > 0) {
    // If there is, read the incoming byte.
    incomingByte = Serial.readString();

    //   Serial.print("\r\n" + incomingByte );
    if (incomingByte == "sun") {
      Sprites.RemoveAllSprites();
      Sprites.AddSprite(&Sun);
      current = "sun";

      clearUpdate();

    } else if (incomingByte == "rain") {
      Sprites.RemoveAllSprites();


      Rain.SetPositionFrameMotionOptions(0/*X*/, 0/*Y*/, 0/*Frame*/, 0/*FrameRate*/, 0/*XChange*/, 0/*XRate*/, -1/*YChange*/, 12/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_X_KEEPIN | SPRITE_Y_KEEPIN);


      Sprites.AddSprite(&Rain);
      current = "rain";

      clearUpdate();
    }

    else if (incomingByte == "snow") {
      Sprites.RemoveAllSprites();

      Snow.SetPositionFrameMotionOptions(0/*X*/, 0/*Y*/, 0/*Frame*/, 0/*FrameRate*/, +1/*XChange*/, 3/*XRate*/, -1/*YChange*/, 2/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_X_KEEPIN | SPRITE_Y_KEEPIN);

      Sprites.AddSprite(&Snow);
      current = "snow";

      clearUpdate();
    }

    else if (incomingByte == "extreme") {
      Sprites.RemoveAllSprites();

      Sprites.AddSprite(&Extreme);
      current = "extreme";

      clearUpdate();
    }

    else if (incomingByte == "thunder") {
      Sprites.RemoveAllSprites();


      Sprites.AddSprite(&Thunder);
      current = "thunder";

      clearUpdate();
    }

   else if (incomingByte == "breeze") {
      Sprites.RemoveAllSprites();


      Breeze.SetPositionFrameMotionOptions(0/*X*/, 0/*Y*/, 0/*Frame*/, 0/*FrameRate*/, +1/*XChange*/, 40/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_X_KEEPIN | SPRITE_Y_KEEPIN);

      Sprites.AddSprite(&Breeze);
      current = "breeze";
      

      clearUpdate();
    }

    else if (incomingByte == "gale") {
      Sprites.RemoveAllSprites();


      Breeze.SetPositionFrameMotionOptions(0/*X*/, 0/*Y*/, 0/*Frame*/, 0/*FrameRate*/, +1/*XChange*/, 20/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_X_KEEPIN | SPRITE_Y_KEEPIN);

      Sprites.AddSprite(&Breeze);
      current = "gale";
      

      clearUpdate();
    }

    else if (incomingByte == "storm") {
      Sprites.RemoveAllSprites();


      Breeze.SetPositionFrameMotionOptions(0/*X*/, 0/*Y*/, 0/*Frame*/, 0/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_X_KEEPIN | SPRITE_Y_KEEPIN);

      Sprites.AddSprite(&Breeze);
      current = "storm";
      

      clearUpdate();
    }
    

    else if (incomingByte == "cloud") {
      Sprites.RemoveAllSprites();
      Sprites.AddSprite(&Cloud);
      current = "cloud";

      clearUpdate();
    }

  }

  else if (incomingByte == "mist") {
    Sprites.RemoveAllSprites();


    Sprites.AddSprite(&Mist);
    current = "mist";

    clearUpdate();
  }

  else if (incomingByte == "clear") {
    Sprites.RemoveAllSprites();


    Sprites.AddSprite(&Clear);
    current = "clear";

    clearUpdate();
  }
  else if (current == "sun") {
    Sprites.RemoveAllSprites();
    Sprites.AddSprite(&Sun);

    clearUpdate();

  } else if (current == "snow") {
    Sprites.RemoveAllSprites();
    Sprites.AddSprite(&Snow);

    clearUpdate();

  } else if (current == "rain") {
    Sprites.RemoveAllSprites();
    Sprites.AddSprite(&Rain);

    clearUpdate();

  }

  else if (current == "extreme") {
    Sprites.RemoveAllSprites();
    Sprites.AddSprite(&Extreme);

    clearUpdate();

  }

  else if (current == "thunder") {
    Sprites.RemoveAllSprites();
    Sprites.AddSprite(&Thunder);

    clearUpdate();

  } else if (current == "cloud") {
    Sprites.RemoveAllSprites();
    Sprites.AddSprite(&Cloud);

    clearUpdate();

  } else if (current == "") {
    Sprites.RemoveAllSprites();
    Sprites.AddSprite(&SadFace);
    current = "";

    clearUpdate();

  }
  else if (current == "mist") {
    Sprites.RemoveAllSprites();
    Sprites.AddSprite(&Mist);

    clearUpdate();

  } else if (current == "clear") {
    Sprites.RemoveAllSprites();
    Sprites.AddSprite(&Clear);

    clearUpdate();

  }


 else if (current == "storm" || current == "gale" || current == "breeze" ) {
    Sprites.RemoveAllSprites();
    Sprites.AddSprite(&Breeze);

    clearUpdate();

  }

  


}
