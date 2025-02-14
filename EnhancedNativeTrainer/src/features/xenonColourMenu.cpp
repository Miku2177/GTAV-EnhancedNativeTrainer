#include "vehicles.h"
#include "..\ui_support\menu_functions.h"
#include "..\io\config_io.h"

void apply_xenon_colors(int colorIndex) {
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()); // Get current vehicle
	XenonColour whichcolor = XENON_COLOURS[colorIndex];
	VEHICLE::SET_VEHICLE_XENON_COLOUR(veh, whichcolor.colour);
	VEHICLE::TOGGLE_VEHICLE_MOD(veh, 22, 1);
}

void onhighlight_xenon_selection(MenuItem<int> choice) {
	onconfirm_xenon_selection(choice);
}

bool onconfirm_xenon_selection(MenuItem<int> choice) {
	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!bPlayerExists) 
		return true;

	if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
		set_status_text("Player isn't in a vehicle");
		return true;
	}

	apply_xenon_colors(choice.value);

	return true;
}

bool process_xenon_colour_menu() {
	std::vector<MenuItem<int>*> menuItems;

	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	
	for (int i = 0; i < XENON_COLOURS.size(); i++) {
		XenonColour thisCol = XENON_COLOURS[i];
		
		MenuItem<int> *item = new MenuItem<int>();
		item->caption = XENON_COLOURS[i].colorString;
		item->isLeaf = true;
		item->value = i;
		menuItems.push_back(item);
	}
	return draw_generic_menu<int>(menuItems, 0, "Choose Xenon Color", onconfirm_xenon_selection, onhighlight_xenon_selection, NULL, vehicle_menu_interrupt);
}