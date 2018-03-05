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


const uint8_t Spritesun2Data[] = {
  B8_3BIT(11011101),
  B8_3BIT(10020001),
  B8_3BIT(13000301),
  B8_3BIT(00323000),
  B8_3BIT(20222020),
  B8_3BIT(00323000),
  B8_3BIT(03000304),
  B8_3BIT(44020044) };
const struct CRGB Spritesun2Cols[7] = { CRGB(0,152,239), CRGB(255,156,0), CRGB(255,246,8), CRGB(8,8,189), CRGB(0,0,0), CRGB(0,0,0), CRGB(0,0,0) };
cSprite Shape(8, 8, Spritesun2Data, 1, _3BIT, Spritesun2Cols);


cLEDSprites Sprites(&leds);

void setup()
{
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds[0], leds.Size());
  FastLED.setBrightness(64);
  FastLED.clear(true);
//  delay(500);
//  FastLED.showColor(CRGB::Red);
//  delay(1000);
//  FastLED.showColor(CRGB::Lime);
//  delay(1000);
//  FastLED.showColor(CRGB::Blue);
//  delay(1000);
//  FastLED.showColor(CRGB::White);
//  delay(1000);
//  FastLED.show();

  Sprites.AddSprite(&Shape);
}


void loop()
{
  FastLED.clear();
  Sprites.UpdateSprites();
  Sprites.RenderSprites();
  FastLED.show();
  delay(50);
}
