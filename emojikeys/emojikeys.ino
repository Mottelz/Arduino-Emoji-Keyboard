/* Emoji Keyboard - Linux only.

   Functions as a simple usb keyboard device, outputting a variety of unicode symbols of interest.
   relies on the unix input method: ctrl-shift-u <codepoint> <space>
   You must select Keyboard from the "Tools > USB Type" menu
   This example code is in the public domain.
*/

#include "keycodes.h"
#include "config.h"
#include <Keyboard.h>

int buttonState = HIGH;

/* The process for entering unicode key codes varies by OS.
 * This implementation is linux-specific, and relies on the code being ctrl+shift+u <keycode> <space>
 * the delay calls are present to prevent overwhelming the host with input.
 */
void sendSequenceLinux(String seq){
  Serial.println(seq);
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('u');
  delay(40);
  Keyboard.releaseAll();
  delay(20);
  Keyboard.print(seq);
  Keyboard.print(" ");
  delay(50);
}

// entirely untested.
// based on advice from: fileformat.info/tip/microsoft/enter_unicode.htm
void sendSequenceWindows(String seq){
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.print('+');
  Keyboard.print(seq);
  delay(20);
  Keyboard.releaseAll();
  delay(20);
}

// A Mac equivalent requires the "Unicode Hex Input" to be enabled,
// then hold Option, enter the keycode, release Option.

void sendSequenceMac(String seq){
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.print(seq);
  delay(20);
  Keyboard.releaseAll();
  delay(100);
  }



void setup() {
  Serial.begin(9600);
  Keyboard.begin();
  for(int i=0;i<KEYMAP_SIZE;i++){
    pinMode(i, INPUT_PULLUP);
  }
}

void loop() {
  for(int i=0;i<KEYMAP_SIZE;i++){
    buttonState = digitalRead(i);
    if(buttonState == LOW){
      sendSequenceMac(A_KEYMAP[i]);
//      sendSequenceWindows(KEYMAP[i]);
//      sendSequenceLinux(KEYMAP[i]);
    }
  }
}



