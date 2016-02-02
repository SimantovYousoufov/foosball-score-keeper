#include "Adafruit_mfGFX/Adafruit_mfGFX.h"   // Core graphics library
#include "RGBmatrixPanel/RGBmatrixPanel.h" // Hardware-specific library
#include "math.h"

// Matrix pin setup
#define CLK D6
#define OE  D7
#define LAT A4
#define A   A0
#define B   A1
#define C   A2
/****************************************/
int RIGHT_SENSOR = A5;
int LEFT_SENSOR  = A3;
int RESET_BUTTON = A7;
/****************************************/
int leftScore  = 0;
int rightScore = 0;
/****************************************/
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);
/****************************************/

void setup() {
    pinMode(RIGHT_SENSOR, INPUT_PULLUP);
    pinMode(LEFT_SENSOR, INPUT_PULLUP);
    pinMode(RESET_BUTTON, INPUT_PULLDOWN);

    matrix.begin();

    renderSplashScreen();

    // All black
    resetScreen(true);

    // All black with color border
    resetScreen(false);

    // Render a 0:0 score
    renderScore(leftScore, rightScore);
}

void loop() {
    matrix.setTextSize(1);

    // Score flag, used to set a delay before another score event can occur.
    bool scoreHasOccured = false;

    if (digitalRead(RIGHT_SENSOR) == LOW) {
        ++rightScore;

        scoreHasOccured = true;

        // Clear screen (with color border)
        resetScreen(false);

        // Render new score
        renderScore(leftScore, rightScore);
    }

    if (digitalRead(LEFT_SENSOR) == LOW) {
        ++leftScore;

        scoreHasOccured = true;
        resetScreen(false);
        renderScore(leftScore, rightScore);
    }

    if (digitalRead(RESET_BUTTON) == HIGH) {
        // Reset scores
        rightScore = 0;
        leftScore  = 0;

        resetScreen(false);
        renderScore(leftScore, rightScore);
        delay(5000);
    }

    if (scoreHasOccured == true) {
        // A score event has occurrent, prevent any scoring for 2000ms to prevent double scoring
        // due to ball bouncing, etc
        delay(2000);
    }
}

// Reset the LED matrix with 1) a full black screen or 2) A black screen with colored border
void resetScreen(bool allBlack) {
    if (allBlack == true) {
        matrix.fillScreen(matrix.Color333(0, 0, 0));
    } else {
        matrix.fillScreen(matrix.Color333(0, 0, 0));
        matrix.drawRect(0, 0, 32, 16, matrix.Color333(0, 4, 7));
    }
}

// Render a pair of scores
void renderScore(int leftScore, int rightScore) {
    renderDigit(leftScore, "left");

    printDivider();

    renderDigit(rightScore, "right");
}

// Render the score divider
void printDivider() {
    matrix.setCursor(13, 4);
    matrix.setTextColor(matrix.Color333(7,7,0));
    matrix.print(':');
    matrix.setCursor(14, 4);
    matrix.print(':');
}

// Determine how to render a digit (ex: how to handle double digits)
void renderDigit(int score, char team[]) {
    // @todo handle 3 or more digit cases
    int offset = 0;

    if (team == "right") {
        matrix.setTextColor(matrix.Color333(4,0,7)); // Blue

        // Cursor offset for the rightmost score
        offset = 17;
    } else {
        matrix.setTextColor(matrix.Color333(7,0,0)); // Red
    }

    String textScore = String(score);

    if (textScore.length() > 1) {
        matrix.setCursor(offset + 2, 4); // when 2 digits

        matrix.print(textScore.charAt(0));
        matrix.print(textScore.charAt(1));
    } else {
        matrix.setCursor(offset + 5, 4); // when 1 digit

        matrix.print(textScore.charAt(0));
    }
}

// The Fuzz Productions splash screen
void renderSplashScreen() {
    matrix.setCursor(1, 0);
    matrix.setTextSize(1); // size 1 == 8 pixels high

    // print each letter with a rainbow color
    matrix.setTextColor(matrix.Color333(7,0,0));
    matrix.print('F');
    matrix.setTextColor(matrix.Color333(7,4,0));
    matrix.print('U');
    matrix.setTextColor(matrix.Color333(7,7,0));
    matrix.print('Z');
    matrix.setTextColor(matrix.Color333(4,7,0));
    matrix.print('Z');
    matrix.setTextColor(matrix.Color333(0,7,0));
    matrix.print('!');

    matrix.setCursor(1, 9);   // next line
    matrix.setTextColor(matrix.Color333(0,7,7));
    matrix.print(' ');
    matrix.setTextColor(matrix.Color333(0,4,7));
    matrix.print('P');
    matrix.setTextColor(matrix.Color333(0,0,7));
    matrix.print('R');
    matrix.setTextColor(matrix.Color333(4,0,7));
    matrix.print('O');
    matrix.setTextColor(matrix.Color333(7,0,4));
    matrix.print(' ');

    delay(3000);
}

// Matix/Graphics libraries:
// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

