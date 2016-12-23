#include <IRremote.h>

const int speakerPin = 19;
const int green_1 = 17;
const int green_2 = 16;
const int white_1 = 15;
const int white_2 = 14;

const int RECV_PIN = 12;
IRrecv irrecv(RECV_PIN);
decode_results results;


volatile int track = 0; // track no
volatile int n;
 
const int length[8] = {73,69,71,29,51,77,64,63}; // no of musical notes from each track

const char * notes[8] = {"ggagsed deggsgg ggagsed deggsgg DCbCDbCbabCabagabgagsgasgsesgeseddeggsgg ", \
                     "ddaagfedcdefga ddaagfedcdefga avgavCDagfdefgfgavaagfedfedgfgavCDagfed" , \
                     "cfffgagavCavafggfcfffgagavCavafggffaCDCvagfgavCcfagfccfffgagavCavafggf " , \
                     "faagfvvagaCCbCaDCvagfeagffef ", \
                     "aavCagfgagdgavCaggfgagff vavCDDaaCagfecavCagfgagff ", \
                     "cffefaagCCCvagacffefaagCffeedcCCCfvaagCCCfvaagDDDCvavgavCffgaDDDCvavgavCffgf ", \
                     "ggdgadbabCbaggsesgabsedd DCbCbabgasedggsgagdbbabCbabCbagsgCbagg ", \
                     "egbbbaCbagabgegasedeaaeesgsedgabbbaCbag DD bb baCdagabgegasede " } ;
const byte beats[8][77] = { { 2,2,1,1,1,1,4,2,2,2,2,2,2,4,2,2,2,2,1,1,1,1,4,2,2,2,2,2,2,4,2,2,3,1,1,1,1,1,3,1,1,1,1,1,3,1,1,1,1,1,3,1,1,1,1,1,3,1,1,1,1,1,3,1,2,2,2,2,2,2,4,2,2 }, \
                 { 2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,2,4,2,2,2,2,2,2,4,1,1,2,4,2,2,2,2,2,2,2,2,2,2,8 } , \
                 { 2,2,2,2,2,1,1,1,1,2,2,2,1,1,2,2,6,2,2,2,2,2,1,1,1,1,2,2,2,1,1,2,2,6,1,1,3,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,4,4,2,2,2,2,1,1,1,1,2,2,2,1,1,2,2,6,2 } , \
                 { 2,3,1,2,2,2,2,2,2,2,2,2,2,6,2,3,1,2,2,2,2,2,2,2,2,2,2,6,2 }, \
                 { 2,3,1,2,2,4,4,3,1,2,2,8,3,1,2,2,3,1,4,2,2,3,1,6,2,3,1,2,2,2,2,2,2,2,2,2,2,6,2,2,2,2,2,4,4,2,2,3,1,8,8}, \
                 { 2,2,3,1,2,2,2,2,2,2,3,1,2,2,4,2,2,3,1,2,2,2,2,2,2,3,1,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,1,1,3,1,2,2,4,3,1,2,2,2,2,4,2,1,1,3,1,2,2,4,8} ,\
                 { 2,4,2,2,4,4,2,2,2,2,4,2,2,4,2,2,2,2,2,2,4,3,1,6,2,4,2,2,4,4,2,2,2,2,3,1,2,2,2,2,2,2,4,2,2,2,2,2,2,4,2,2,2,2,2,2,4,2,2,4,3,1,6,8 }, \
                 { 2,2,2,2,2,2,2,2,2,6,2,2,2,2,2,2,2,2,2,6,2,2,2,2,2,4,2,2,6,2,2,2,2,2,2,2,2,2,4,2,2,4,2,2,4,2,2,2,2,2,2,6,2,2,2,2,2,2,2,2,2,8,8 }};
 
const int tempo[8] = {150,150,150,150,150,150,150,150};
            

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {

	const char names[] = { 'c', 'd', 'e', 'f', 's', 'g', 'a', 'v', 'b', 'C', 'D', 'E' }; // note
	const int tones[] = { 1915, 1700, 1519, 1432, 1352, 1275, 1136, 1073, 1014, 956, 852, 758 }; // frequences

    for (int i = 0; i < 12; i++) 
    	if (names[i] == note) playTone(tones[i], duration);
}

void setup(){
  pinMode(speakerPin, OUTPUT);
  pinMode(green_1, OUTPUT);
  pinMode(green_2, OUTPUT);
  pinMode(white_1, OUTPUT);
  pinMode(white_2, OUTPUT);
  
  irrecv.enableIRIn(); // Start the receiver 
}

void loop(){

	 for (n = 0; n < length[track]; n++) {
	    
	    if (notes[track][n] == ' ') {
	      delay(beats[track][n] * tempo[track]); // break
	      digitalWrite(green_1, HIGH);
	      digitalWrite(green_2, LOW);
	      digitalWrite(white_1, LOW);
	      digitalWrite(white_2, LOW);
	    }
	    else{ 
	      playNote(notes[track][n], beats[track][n] * tempo[track]);
	      digitalWrite(green_1, LOW);
	      digitalWrite(green_2, LOW); 
	      digitalWrite(white_1, HIGH);
	      digitalWrite(white_2, HIGH);
	    }

	    if (irrecv.decode(&results)) {
	       
	        switch(results.value){
	          case 0xE0E020DF: track = 0; n = 0; delay(1000); break; 	// 1
	          case 0xE0E0A05F: track = 1; n = 0; delay(1000); break;	// 2
	          case 0xE0E0609F: track = 2; n = 0; delay(1000); break;	// 3
	          case 0xE0E010EF: track = 3; n = 0; delay(1000); break;	// 4
	          case 0xE0E0906F: track = 4; n = 0; delay(1000); break;	// 5
	          case 0xE0E050AF: track = 5; n = 0; delay(1000); break;	// 6
	          case 0xE0E030CF: track = 6; n = 0; delay(1000); break;	// 7
	          case 0xE0E0B04F: track = 7; n = 0; delay(1000); break;	// 8
	        }

	        irrecv.resume(); // Receive the next value
	        
	    }
	    
	    delay(tempo[track] / 2); // break between musical notes
	    digitalWrite(green_1, LOW);
	    digitalWrite(green_2, HIGH);
	    digitalWrite(white_1, LOW);
	    digitalWrite(white_2, LOW);
	}
	
	delay(1000);
}



