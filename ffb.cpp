#include "ffb.h"
#include "effect.h"

using namespace std;


int test_haptic( SDL_Joystick * joystick, FFDEffect effect_data) {
 SDL_Haptic *haptic;
 SDL_HapticEffect effect;
 int effect_id;

 // Open the device
 haptic = SDL_HapticOpenFromJoystick( joystick );
 if (haptic == NULL) { cout << "Joystick isn't haptic" << endl; return -1; } // Most likely joystick isn't haptic
  cout << "Joystick can do force feedback!" << endl;

 // See if it can do sine waves
 if ((SDL_HapticQuery(haptic) & SDL_HAPTIC_SINE)==0) {
  cout << "joystick can't do sine waves" << endl;
  SDL_HapticClose(haptic); // No sine effect
  return -1;
 }

 // See if it can do gain adjustment
 if ((SDL_HapticQuery(haptic) & SDL_HAPTIC_GAIN)==0) {
  cout << "joystick can't adjust gain" << endl;
  SDL_HapticClose(haptic); // No sine effect
  return -1;
 }

 //set joystick to full strength if it supports it
 SDL_HapticSetGain( haptic, 100);

 // Create the effect
 SDL_memset( &effect, 0, sizeof(SDL_HapticEffect) ); // 0 is safe default

//enum hap { leftright, sawtoothup, sawtoothdown, sine, triangle };

 enum hap_type { condition, constant, leftright, periodic, ramp, custom};
 hap_type haptic_effect = static_cast<hap_type>(effect_data.get_effect_type());
 cout << "Heffect: " << haptic_effect << " var cont: " << effect_data.get_effect_type() << endl;
 cout << "data length: " <<  effect_data.get_length() << endl;
 int effect_length = 1000;
 //cout << "Trying Effects" << endl;
 switch (haptic_effect)
 {
 	case periodic:
		cout << "Periodic" << endl;
		cout << "Effect Type: " << effect_data.get_effect_type() << endl;
		cout << "Direction: " << effect_data.get_direction() << endl;
		cout << "Length: " << effect_data.get_length() << endl;
		cout << "Delay: " << effect_data.get_delay() << endl;
		cout << "Period: " << effect_data.get_period() << endl;
		cout << "Phase: " << effect_data.get_phase() << endl;
		cout << "Magnitude: " << effect_data.get_magnitude() << endl;
		cout << "Attack Length: " << effect_data.get_attack_length() << endl;
		cout << "Attack Strength: " << effect_data.get_attack_level() << endl;
		cout << "Fade Length: " << effect_data.get_fade_length() << endl;
		cout << "Fade Level: " << effect_data.get_fade_level() << endl;
	 	effect_length = effect_data.get_length(); // 3 seconds long
		effect.periodic.type = effect_data.get_type();
 		effect.periodic.direction.type = SDL_HAPTIC_POLAR; // Polar coordinates
 		effect.periodic.direction.dir[0] = effect_data.get_direction(); // Force comes from north at 180 degrees
	 	effect.periodic.length = effect_data.get_length(); // 3 seconds long
//	 	effect.periodic.delay = effect_data.get_delay(); // 3 seconds long
 		effect.periodic.period = effect_data.get_period(); // 1500 ms
 		effect.periodic.phase = effect_data.get_phase(); // 18000 ms
	 	effect.periodic.magnitude = effect_data.get_magnitude(); // 32767 strength
 		effect.periodic.attack_length = effect_data.get_attack_length(); // 1000 = Takes 1 second to get max strength
 		effect.periodic.attack_level = effect_data.get_attack_level(); // 1000 = Takes 1 second to get max strength
		effect.periodic.fade_length = effect_data.get_fade_length(); // 1000 = Takes 1 second to fade away
//		effect.periodic.fade_level = effect_data.get_fade_level(); // 1000 = Takes 1 second to fade away
	 break;
 	case ramp: cout << "Ramp"  << endl;
	 	effect_length = 3000; // 3 seconds long
		effect.type = SDL_HAPTIC_RAMP;
 		effect.ramp.direction.type = SDL_HAPTIC_POLAR; // Polar coordinates
 		effect.ramp.direction.dir[0] = 18000; // Force comes from north at 180 degrees
	 	effect.ramp.length = 3000; // 3 seconds long
 		effect.ramp.attack_length = 125; // 1000 = Takes 1 second to get max strength
		effect.ramp.fade_length = 250; // 1000 = Takes 1 second to fade away
	 break;
 	case leftright:
		cout << "Left/Right" << endl;
	 	effect_length = effect_data.get_length(); // 3 seconds long
	 	effect.leftright.length = effect_data.get_length(); // 3 seconds long
	 	effect.leftright.large_magnitude = effect_data.get_large_magnitude(); // 3 seconds long
	 	effect.leftright.small_magnitude = effect_data.get_small_magnitude(); // 3 seconds long
	 break;
 	case condition:
		 cout << "Condition" << endl;
	 	effect_length = 3000; // 3 seconds long
 		effect.condition.direction.type = SDL_HAPTIC_POLAR; // Polar coordinates
 		effect.condition.direction.dir[0] = 18000; // Force comes from north at 180 degrees
	 	effect.condition.length = 3000; // 3 seconds long
	 break;
 	case custom:
		 cout << "Custom" << endl;
	 	effect_length = 3000; // 3 seconds long
 		effect.custom.direction.type = SDL_HAPTIC_POLAR; // Polar coordinates
 		effect.custom.direction.dir[0] = 18000; // Force comes from north at 180 degrees
 		effect.custom.period = 1500; // 1500 ms
	 	effect.custom.length = 3000; // 3 seconds long
 		effect.custom.attack_length = 125; // 1000 = Takes 1 second to get max strength
		effect.custom.fade_length = 250; // 1000 = Takes 1 second to fade away
	 break;
 	case constant: cout << "Constant" << endl; 
	 	effect_length = effect_data.get_length(); // 3 seconds long
		effect.constant.direction.type = SDL_HAPTIC_POLAR; // Polar coordinates
 		effect.constant.direction.dir[0] = 18000; // Force comes from north at 180 
	 	effect.constant.length = effect_data.get_length(); // 3 seconds long
	 	effect.constant.delay = effect_data.get_delay(); // delay before starting 1 second
 		effect.constant.attack_length = effect_data.get_attack_length(); // 1000 = Takes 1 second to get max strength
 		effect.constant.attack_level = effect_data.get_attack_level(); // 1000 = Takes 1 second to get max strength
		effect.constant.fade_length = effect_data.get_fade_length(); // 1000 = Takes 1 second to fade away
		effect.constant.fade_level = effect_data.get_fade_level(); // 1000 = Takes 1 second to fade away
	 break;
 }


 // Upload the effect
 effect_id = SDL_HapticNewEffect( haptic, &effect );

 // Test the effect
 SDL_HapticRunEffect( haptic, effect_id, 1 );
 SDL_Delay(effect_length); // Wait for the effect to finish

 // We destroy the effect, although closing the device also does this
 SDL_HapticDestroyEffect( haptic, effect_id );

 // Close the device
 SDL_HapticClose(haptic);
 return 0; // Success
}

void open_joysticks(FFDEffect effect_data){
	SDL_Joystick *joy;

	// Initialize the joystick subsystem
	SDL_InitSubSystem(SDL_INIT_JOYSTICK);

	// Check for joystick
	if (SDL_NumJoysticks() > 0) {
	    // Open joystick
	    joy = SDL_JoystickOpen(0);

	    if (joy) {
	        cout << "\nOpened Joystick 0" << endl;
	        cout << "Name: " << SDL_JoystickNameForIndex(0) << endl;
	        cout << "Number of Axes: " << SDL_JoystickNumAxes(joy) << endl;
	        cout << "Number of Buttons: " <<  SDL_JoystickNumButtons(joy) << endl;
	        cout << "Number of Balls: " <<  SDL_JoystickNumBalls(joy) << endl;
		int result = test_haptic(joy, effect_data);
		if (result == -1){
			cout << "error, not a Force Feedback Device" << endl;
		}
	    	} else {
	        cout << "Couldn't open Joystick 0" << endl;
	    }

	    // Close if opened
	    if (SDL_JoystickGetAttached(joy)) {	
	        SDL_JoystickClose(joy);
	    }
	}
}

void open_joys(FFDEffect effect_data){
	open_joysticks(effect_data);
}

void init_sdl(void){
        	cout << "Starting SDL\n this will take a while" << SDL_GetError( ) << endl;
	if (SDL_Init( SDL_INIT_HAPTIC|SDL_INIT_GAMECONTROLLER||SDL_INIT_JOYSTICK ) < 0 )
	{
        	cout << " error starting SDL " <<SDL_GetError( ) << endl;
	} else {
		cout << "SDL Started!" << endl;
	}
}
