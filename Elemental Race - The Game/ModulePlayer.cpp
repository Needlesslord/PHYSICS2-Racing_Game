#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"
#include "Primitive.h"
#include "Color.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), Bus(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	// Bus properties ----------------------------------------
	bus.chassis_size.Set(5, 9, 12);
	bus.chassis_offset.Set(0, 4.5, 0);
	bus.mass = 500.0f;
	bus.suspensionStiffness = 15.88f;
	bus.suspensionCompression = 0.83f;
	bus.suspensionDamping = 0.88f;
	bus.maxSuspensionTravelCm = 1000.0f;
	bus.frictionSlip = 50.5;
	bus.maxSuspensionForce = 6000.0f;
	bus.chasisColor = Purple;
	
	// Wheel properties ---------------------------------------
	float bus_connection_height = 0.6f;
	float bus_wheel_radius = 1.2f;
	float bus_wheel_width = 0.8f;
	float bus_suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float bus_half_width = bus.chassis_size.x * 0.5f;
	float bus_half_length = bus.chassis_size.z * 0.5f;
	
	vec3 bus_direction(0,-1,0);
	vec3 bus_axis(-1,0,0);
	
	bus.num_wheels = 6;
	bus.wheels = new Wheel[6];

	// FRONT-LEFT ------------------------
	bus.wheels[0].connection.Set(bus_half_width - 0.3f * bus_wheel_width, bus_connection_height, bus_half_length * 0.95f - bus_wheel_radius);
	bus.wheels[0].direction = bus_direction;
	bus.wheels[0].axis = bus_axis;
	bus.wheels[0].suspensionRestLength = bus_suspensionRestLength;
	bus.wheels[0].radius = bus_wheel_radius;
	bus.wheels[0].width = bus_wheel_width;
	bus.wheels[0].front = true;
	bus.wheels[0].drive = true;
	bus.wheels[0].brake = false;
	bus.wheels[0].steering = true;
	bus.wheels[0].color = Black;

	// FRONT-RIGHT ------------------------
	bus.wheels[1].connection.Set(-bus_half_width + 0.3f * bus_wheel_width, bus_connection_height, bus_half_length * 0.95f - bus_wheel_radius);
	bus.wheels[1].direction = bus_direction;
	bus.wheels[1].axis = bus_axis;
	bus.wheels[1].suspensionRestLength = bus_suspensionRestLength;
	bus.wheels[1].radius = bus_wheel_radius;
	bus.wheels[1].width = bus_wheel_width;
	bus.wheels[1].front = true;
	bus.wheels[1].drive = true;
	bus.wheels[1].brake = false;
	bus.wheels[1].steering = true;
	bus.wheels[1].color = Black;

	// REAR-LEFT ------------------------
	bus.wheels[2].connection.Set(bus_half_width - 0.3f * bus_wheel_width - bus_wheel_width, bus_connection_height, -bus_half_length * 0.80f + bus_wheel_radius);
	bus.wheels[2].direction = bus_direction;
	bus.wheels[2].axis = bus_axis;
	bus.wheels[2].suspensionRestLength = bus_suspensionRestLength;
	bus.wheels[2].radius = bus_wheel_radius;
	bus.wheels[2].width = bus_wheel_width;
	bus.wheels[2].front = false;
	bus.wheels[2].drive = false;
	bus.wheels[2].brake = true;
	bus.wheels[2].steering = false;
	bus.wheels[2].color = Black;

	// REAR-RIGHT ------------------------
	bus.wheels[3].connection.Set(-bus_half_width + 0.3f * bus_wheel_width + bus_wheel_width, bus_connection_height, -bus_half_length * 0.80f + bus_wheel_radius);
	bus.wheels[3].direction = bus_direction;
	bus.wheels[3].axis = bus_axis;
	bus.wheels[3].suspensionRestLength = bus_suspensionRestLength;
	bus.wheels[3].radius = bus_wheel_radius;
	bus.wheels[3].width = bus_wheel_width;
	bus.wheels[3].front = false;
	bus.wheels[3].drive = false;
	bus.wheels[3].brake = true;
	bus.wheels[3].steering = false;
	bus.wheels[3].color = Black;

	// BACK-MID-LEFT ------------------------
	bus.wheels[4].connection.Set(bus_half_width, bus_connection_height, -bus_half_length * 0.80f + bus_wheel_radius);
	bus.wheels[4].direction = bus_direction;
	bus.wheels[4].axis = bus_axis;
	bus.wheels[4].suspensionRestLength = bus_suspensionRestLength;
	bus.wheels[4].radius = bus_wheel_radius;
	bus.wheels[4].width = bus_wheel_width;
	bus.wheels[4].front = false;
	bus.wheels[4].drive = false;
	bus.wheels[4].brake = true;
	bus.wheels[4].steering = false;
	bus.wheels[4].color = Black;

	// BACK-MID-RIGHT ------------------------
	bus.wheels[5].connection.Set(-bus_half_width, bus_connection_height, -bus_half_length * 0.80f + bus_wheel_radius);
	bus.wheels[5].direction = bus_direction;
	bus.wheels[5].axis = bus_axis;
	bus.wheels[5].suspensionRestLength = bus_suspensionRestLength;
	bus.wheels[5].radius = bus_wheel_radius;
	bus.wheels[5].width = bus_wheel_width;
	bus.wheels[5].front = false;
	bus.wheels[5].drive = false;
	bus.wheels[5].brake = true;
	bus.wheels[5].steering = false;
	bus.wheels[5].color = Black;
	

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Truck properties ----------------------------------------

	truck.chassis_size.Set(6, 8, 24);
	truck.chassis_offset.Set(0, 4.5, 0);
	truck.mass = 1000.0f;
	truck.suspensionStiffness = 15.88f;
	truck.suspensionCompression = 0.83f;
	truck.suspensionDamping = 0.88f;
	truck.maxSuspensionTravelCm = 1000.0f;
	truck.frictionSlip = 50.5;
	truck.maxSuspensionForce = 6000.0f;
	truck.chasisColor = White;

	// Wheel properties ---------------------------------------
	float truck_connection_height = 0.8f;
	float truck_wheel_radius = 1.2f;
	float truck_wheel_width = 1.2f;
	float truck_suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float truck_half_width = truck.chassis_size.x * 0.5f;
	float truck_half_length = truck.chassis_size.z * 0.5f;

	vec3 truck_direction(0, -1, 0);
	vec3 truck_axis(-1, 0, 0);

	truck.num_wheels = 12;
	truck.wheels = new Wheel[12];

	// FRONT-LEFT ------------------------
	truck.wheels[0].connection.Set(truck_half_width - 0.6f * truck_wheel_width, truck_connection_height, truck_half_length * 0.95f - truck_wheel_radius);
	truck.wheels[0].direction = truck_direction;
	truck.wheels[0].axis = truck_axis;
	truck.wheels[0].suspensionRestLength = truck_suspensionRestLength;
	truck.wheels[0].radius = truck_wheel_radius;
	truck.wheels[0].width = truck_wheel_width;
	truck.wheels[0].front = true;
	truck.wheels[0].drive = true;
	truck.wheels[0].brake = false;
	truck.wheels[0].steering = true;
	truck.wheels[0].color = Black;

	// FRONT-RIGHT ------------------------
	truck.wheels[1].connection.Set(-truck_half_width + 0.6f * truck_wheel_width, truck_connection_height, truck_half_length * 0.95f - truck_wheel_radius);
	truck.wheels[1].direction = truck_direction;
	truck.wheels[1].axis = truck_axis;
	truck.wheels[1].suspensionRestLength = truck_suspensionRestLength;
	truck.wheels[1].radius = truck_wheel_radius;
	truck.wheels[1].width = truck_wheel_width;
	truck.wheels[1].front = true;
	truck.wheels[1].drive = true;
	truck.wheels[1].brake = false;
	truck.wheels[1].steering = true;
	truck.wheels[1].color = Black;



	// FRONT-BACK-LEFT ------------------------
	truck.wheels[2].connection.Set(truck_half_width - 0.6f * truck_wheel_width, truck_connection_height, truck_half_length * 0.20f + truck_wheel_radius);
	truck.wheels[2].direction = truck_direction;
	truck.wheels[2].axis = truck_axis;
	truck.wheels[2].suspensionRestLength = truck_suspensionRestLength;
	truck.wheels[2].radius = truck_wheel_radius;
	truck.wheels[2].width = truck_wheel_width;
	truck.wheels[2].front = false;
	truck.wheels[2].drive = false;
	truck.wheels[2].brake = true;
	truck.wheels[2].steering = false;
	truck.wheels[2].color = Black;

	// FRONT-BACK-RIGHT ------------------------
	truck.wheels[3].connection.Set(-truck_half_width + 0.6f * truck_wheel_width, truck_connection_height, truck_half_length * 0.20f + truck_wheel_radius);
	truck.wheels[3].direction = truck_direction;
	truck.wheels[3].axis = truck_axis;
	truck.wheels[3].suspensionRestLength = truck_suspensionRestLength;
	truck.wheels[3].radius = truck_wheel_radius;
	truck.wheels[3].width = truck_wheel_width;
	truck.wheels[3].front = false;
	truck.wheels[3].drive = false;
	truck.wheels[3].brake = true;
	truck.wheels[3].steering = false;
	truck.wheels[3].color = Black;

//

	// REAR-LEFT ------------------------
	truck.wheels[4].connection.Set(truck_half_width - 0.3f * truck_wheel_width - truck_wheel_width, truck_connection_height, -truck_half_length * 0.65f + truck_wheel_radius);
	truck.wheels[4].direction = truck_direction;
	truck.wheels[4].axis = truck_axis;
	truck.wheels[4].suspensionRestLength = truck_suspensionRestLength;
	truck.wheels[4].radius = truck_wheel_radius;
	truck.wheels[4].width = truck_wheel_width;
	truck.wheels[4].front = false;
	truck.wheels[4].drive = false;
	truck.wheels[4].brake = true;
	truck.wheels[4].steering = false;
	truck.wheels[4].color = Black;

	// REAR-RIGHT ------------------------
	truck.wheels[5].connection.Set(-truck_half_width + 0.3f * truck_wheel_width + truck_wheel_width, truck_connection_height, -truck_half_length * 0.65f + truck_wheel_radius);
	truck.wheels[5].direction = truck_direction;
	truck.wheels[5].axis = truck_axis;
	truck.wheels[5].suspensionRestLength = truck_suspensionRestLength;
	truck.wheels[5].radius = truck_wheel_radius;
	truck.wheels[5].width = truck_wheel_width;
	truck.wheels[5].front = false;
	truck.wheels[5].drive = false;
	truck.wheels[5].brake = true;
	truck.wheels[5].steering = false;
	truck.wheels[5].color = Black;



	// BACK-FRONT-MID-LEFT ------------------------
	truck.wheels[6].connection.Set(truck_half_width, truck_connection_height, -truck_half_length * 0.65f + truck_wheel_radius);
	truck.wheels[6].direction = truck_direction;
	truck.wheels[6].axis = truck_axis;
	truck.wheels[6].suspensionRestLength = truck_suspensionRestLength;
	truck.wheels[6].radius = truck_wheel_radius;
	truck.wheels[6].width = truck_wheel_width;
	truck.wheels[6].front = false;
	truck.wheels[6].drive = false;
	truck.wheels[6].brake = true;
	truck.wheels[6].steering = false;
	truck.wheels[6].color = Black;

	// BACK-FRONT-MID-RIGHT ------------------------
	truck.wheels[7].connection.Set(-truck_half_width, truck_connection_height, -truck_half_length * 0.65f + truck_wheel_radius);
	truck.wheels[7].direction = truck_direction;
	truck.wheels[7].axis = truck_axis;
	truck.wheels[7].suspensionRestLength = truck_suspensionRestLength;
	truck.wheels[7].radius = truck_wheel_radius;
	truck.wheels[7].width = truck_wheel_width;
	truck.wheels[7].front = false;
	truck.wheels[7].drive = false;
	truck.wheels[7].brake = true;
	truck.wheels[7].steering = false;
	truck.wheels[7].color = Black;



	// BACK-BACK-LEFT ------------------------
	truck.wheels[8].connection.Set(truck_half_width - 0.3f * truck_wheel_width - truck_wheel_width, truck_connection_height, -truck_half_length * 0.90f + truck_wheel_radius);
	truck.wheels[8].direction = truck_direction;
	truck.wheels[8].axis = truck_axis;
	truck.wheels[8].suspensionRestLength = truck_suspensionRestLength;
	truck.wheels[8].radius = truck_wheel_radius;
	truck.wheels[8].width = truck_wheel_width;
	truck.wheels[8].front = false;
	truck.wheels[8].drive = false;
	truck.wheels[8].brake = true;
	truck.wheels[8].steering = false;
	truck.wheels[8].color = Black;

	// BACK-BACK-RIGHT ------------------------
	truck.wheels[9].connection.Set(-truck_half_width + 0.3f * truck_wheel_width + truck_wheel_width, truck_connection_height, -truck_half_length * 0.90f + truck_wheel_radius);
	truck.wheels[9].direction = truck_direction;
	truck.wheels[9].axis = truck_axis;
	truck.wheels[9].suspensionRestLength = truck_suspensionRestLength;
	truck.wheels[9].radius = truck_wheel_radius;
	truck.wheels[9].width = truck_wheel_width;
	truck.wheels[9].front = false;
	truck.wheels[9].drive = false;
	truck.wheels[9].brake = true;
	truck.wheels[9].steering = false;
	truck.wheels[9].color = Black;



	// BACK-BACK-MID-LEFT ------------------------
	truck.wheels[10].connection.Set(truck_half_width, truck_connection_height, -truck_half_length * 0.90f + truck_wheel_radius);
	truck.wheels[10].direction = truck_direction;
	truck.wheels[10].axis = truck_axis;
	truck.wheels[10].suspensionRestLength = truck_suspensionRestLength;
	truck.wheels[10].radius = truck_wheel_radius;
	truck.wheels[10].width = truck_wheel_width;
	truck.wheels[10].front = false;
	truck.wheels[10].drive = false;
	truck.wheels[10].brake = true;
	truck.wheels[10].steering = false;
	truck.wheels[10].color = Black;

	// BACK-BACK-MID-RIGHT ------------------------
	truck.wheels[11].connection.Set(-truck_half_width, truck_connection_height, -truck_half_length * 0.90f + truck_wheel_radius);
	truck.wheels[11].direction = truck_direction;
	truck.wheels[11].axis = truck_axis;
	truck.wheels[11].suspensionRestLength = truck_suspensionRestLength;
	truck.wheels[11].radius = truck_wheel_radius;
	truck.wheels[11].width = truck_wheel_width;
	truck.wheels[11].front = false;
	truck.wheels[11].drive = false;
	truck.wheels[11].brake = true;
	truck.wheels[11].steering = false;
	truck.wheels[11].color = Black;


	// Trailer properties ----------------------------------------
	trailer.chassis_size.Set(5, 3, 7);
	trailer.chassis_offset.Set(0, 2.25f, 0);
	trailer.mass = 200.0f;
	trailer.suspensionStiffness = 5.80f;
	trailer.suspensionCompression = 0.63f;
	trailer.suspensionDamping = 0.68f;
	trailer.maxSuspensionTravelCm = 800.0f;
	trailer.frictionSlip = 30.5;
	trailer.maxSuspensionForce = 4000.0f;
	trailer.chasisColor = Green;

	// Wheel properties ---------------------------------------
	float trailer_connection_height = 0.8f;
	float trailer_wheel_radius = 1.2f;
	float trailer_wheel_width = 0.5f;
	float trailer_suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float trailer_half_width = trailer.chassis_size.x * 0.5f;
	float trailer_half_length = trailer.chassis_size.z * 0.5f;

	vec3 trailer_direction(0, -1, 0);
	vec3 trailer_axis(-1, 0, 0);

	trailer.num_wheels = 4;
	trailer.wheels = new Wheel[4];
	
	// FRONT-LEFT ------------------------
	trailer.wheels[0].connection.Set(trailer_half_width - 0.3f * trailer_wheel_width, trailer_connection_height, trailer_half_length * 0.95f - trailer_wheel_radius);
	trailer.wheels[0].direction = trailer_direction;
	trailer.wheels[0].axis = trailer_axis;
	trailer.wheels[0].suspensionRestLength = trailer_suspensionRestLength;
	trailer.wheels[0].radius = trailer_wheel_radius;
	trailer.wheels[0].width = trailer_wheel_width;
	trailer.wheels[0].front = true;
	trailer.wheels[0].drive = false;
	trailer.wheels[0].brake = false;
	trailer.wheels[0].steering = false;
	trailer.wheels[0].color = Black;

	// FRONT-RIGHT ------------------------
	trailer.wheels[1].connection.Set(-trailer_half_width + 0.3f * trailer_wheel_width, trailer_connection_height, trailer_half_length * 0.95f - trailer_wheel_radius);
	trailer.wheels[1].direction = trailer_direction;
	trailer.wheels[1].axis = trailer_axis;
	trailer.wheels[1].suspensionRestLength = trailer_suspensionRestLength;
	trailer.wheels[1].radius = trailer_wheel_radius;
	trailer.wheels[1].width = trailer_wheel_width;
	trailer.wheels[1].front = true;
	trailer.wheels[1].drive = false;
	trailer.wheels[1].brake = false;
	trailer.wheels[1].steering = false;
	trailer.wheels[1].color = Black;

	// REAR-LEFT ------------------------
	trailer.wheels[2].connection.Set(trailer_half_width - 0.3f * trailer_wheel_width, trailer_connection_height, -trailer_half_length * 0.95f + trailer_wheel_radius);
	trailer.wheels[2].direction = trailer_direction;
	trailer.wheels[2].axis = trailer_axis;
	trailer.wheels[2].suspensionRestLength = trailer_suspensionRestLength;
	trailer.wheels[2].radius = trailer_wheel_radius;
	trailer.wheels[2].width = trailer_wheel_width;
	trailer.wheels[2].front = false;
	trailer.wheels[2].drive = false;
	trailer.wheels[2].brake = false;
	trailer.wheels[2].steering = false;
	trailer.wheels[2].color = Black;

	// REAR-RIGHT ------------------------
	trailer.wheels[3].connection.Set(-trailer_half_width + 0.3f * trailer_wheel_width, trailer_connection_height, -trailer_half_length * 0.95f + trailer_wheel_radius);
	trailer.wheels[3].direction = trailer_direction;
	trailer.wheels[3].axis = trailer_axis;
	trailer.wheels[3].suspensionRestLength = trailer_suspensionRestLength;
	trailer.wheels[3].radius = trailer_wheel_radius;
	trailer.wheels[3].width = trailer_wheel_width;
	trailer.wheels[3].front = false;
	trailer.wheels[3].drive = false;
	trailer.wheels[3].brake = false;
	trailer.wheels[3].steering = false;
	trailer.wheels[3].color = Black;

	vehicleSelected = false;
	vehicleSelectedNum == 0;
	trailerAdded = false;
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN && vehicleSelectedNum == 2 && !trailerAdded) { //TRAILER
		Trailer = App->physics->AddVehicle(trailer);
		Trailer->SetPos(-72.5, 2, -25);
		App->physics->AddConstraintP2P(*Truck, *Trailer, { 0, 0, 0 }, { 0, 0, 17.5f });
		trailerAdded = true;
	}

	if (!vehicleSelected) {
		if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) { //BUS
			Bus = App->physics->AddVehicle(bus);
			Bus->SetPos(-72.5, 2, -5);
			vehicleSelected = true;
			vehicleSelectedNum = 1;
		}
		else if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) { //
			Truck = App->physics->AddVehicle(truck);
			Truck->SetPos(-72.5, 1, -5);
			vehicleSelected = true;
			vehicleSelectedNum = 2;
		}
	}
	else if (vehicleSelectedNum == 1) {	//BUS
		turn = acceleration = brake = 0.0f;

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) {
				if (Bus->GetKmh() < MAX_SPEED)
					acceleration = MAX_ACCELERATION / 3;
		}

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
			if (turn < TURN_DEGREES * 0.8)
				turn += TURN_DEGREES * 0.8;
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
			if (turn > -TURN_DEGREES * 0.8)
				turn -= TURN_DEGREES * 0.8;
		}

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {
			if (Bus->GetKmh() > 0) brake = BRAKE_POWER / 3;
			else {
				if (Bus->GetKmh() > MIN_SPEED / 3)
					acceleration = -BRAKE_POWER / 3;
			}
		}

		Bus->ApplyEngineForce(acceleration);
		Bus->Turn(turn);
		Bus->Brake(brake);
		Bus->Render();

		char title[80];
		if (vehicleSelectedNum == 1)
			sprintf_s(title, "%.1f Km/h", Bus->GetKmh());

		App->window->SetTitle(title);
	}


	else if (vehicleSelectedNum == 2) {	//TRUCK
		turn = acceleration = brake = 0.0f;

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) {
			if (Truck->GetKmh() < MAX_SPEED)
			acceleration = MAX_ACCELERATION;
		}
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {
			if (Truck->GetKmh() > 3) brake = BRAKE_POWER;
			else {
				if (Truck->GetKmh() > MIN_SPEED)
					acceleration = -BRAKE_POWER / 2;
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
			if (turn < TURN_DEGREES * 2.5) {
				turn += TURN_DEGREES * 2.5;
				acceleration *= 9;
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
			if (turn > -TURN_DEGREES * 2.5) {
				turn -= TURN_DEGREES * 2.5;
				acceleration *= 9;
			}
		}

		Truck->ApplyEngineForce(acceleration);
		Truck->Turn(turn);
		Truck->Brake(brake);
		Truck->Render();

		char title[80];
		if (vehicleSelectedNum == 1)
			sprintf_s(title, "%.1f Km/h", Truck->GetKmh());

		App->window->SetTitle(title);
	}
	return UPDATE_CONTINUE;
}