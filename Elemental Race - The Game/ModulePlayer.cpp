#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"
#include "Primitive.h"


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


	VehicleInfo bus;

	// Car properties ----------------------------------------
	bus.chassis_size.Set(3, 9, 12);
	bus.chassis_offset.Set(0, 4.5, 0);
	bus.mass = 500.0f;
	bus.suspensionStiffness = 15.88f;
	bus.suspensionCompression = 0.83f;
	bus.suspensionDamping = 0.88f;
	bus.maxSuspensionTravelCm = 1000.0f;
	bus.frictionSlip = 50.5;
	bus.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float bus_connection_height = 1.2f;
	float bus_wheel_radius = 0.8f;
	float bus_wheel_width = 0.5f;
	float bus_suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float bus_half_width = bus.chassis_size.x * 0.5f;
	float bus_half_length = bus.chassis_size.z * 0.5f;
	
	vec3 bus_direction(0,-1,0);
	vec3 bus_axis(-1,0,0);
	
	bus.num_wheels = 8;
	bus.wheels = new Wheel[8];

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
	bus.wheels[2].connection.Set(bus_half_width - 0.3f * bus_wheel_width, bus_connection_height, -bus_half_length * 0.95f + bus_wheel_radius);
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
	bus.wheels[3].connection.Set(-bus_half_width + 0.3f * bus_wheel_width, bus_connection_height, -bus_half_length * 0.95f + bus_wheel_radius);
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

	// MID-FRONT-LEFT ------------------------
	bus.wheels[4].connection.Set(bus_half_width - 0.3f * bus_wheel_width, bus_connection_height, bus_half_length * 0.5f - bus_wheel_radius);
	bus.wheels[4].direction = bus_direction;
	bus.wheels[4].axis = bus_axis;
	bus.wheels[4].suspensionRestLength = bus_suspensionRestLength;
	bus.wheels[4].radius = bus_wheel_radius;
	bus.wheels[4].width = bus_wheel_width;
	bus.wheels[4].front = false;
	bus.wheels[4].drive = false;
	bus.wheels[4].brake = false;
	bus.wheels[4].steering = true;
	bus.wheels[4].color = Black;

	// MID-FORNT-RIGHT ------------------------
	bus.wheels[5].connection.Set(-bus_half_width + 0.3f * bus_wheel_width, bus_connection_height, bus_half_length * 0.5f - bus_wheel_radius);
	bus.wheels[5].direction = bus_direction;
	bus.wheels[5].axis = bus_axis;
	bus.wheels[5].suspensionRestLength = bus_suspensionRestLength;
	bus.wheels[5].radius = bus_wheel_radius;
	bus.wheels[5].width = bus_wheel_width;
	bus.wheels[5].front = false;
	bus.wheels[5].drive = false;
	bus.wheels[5].brake = false;
	bus.wheels[5].steering = true;
	bus.wheels[5].color = Black;

	// MID-BACK-LEFT ------------------------
	bus.wheels[6].connection.Set(bus_half_width - 0.3f * bus_wheel_width, bus_connection_height, -bus_half_length * 0.5f + bus_wheel_radius);
	bus.wheels[6].direction = bus_direction;
	bus.wheels[6].axis = bus_axis;
	bus.wheels[6].suspensionRestLength = bus_suspensionRestLength;
	bus.wheels[6].radius = bus_wheel_radius;
	bus.wheels[6].width = bus_wheel_width;
	bus.wheels[6].front = false;
	bus.wheels[6].drive = false;
	bus.wheels[6].brake = false;
	bus.wheels[6].steering = false;
	bus.wheels[6].color = Black;

	// MID-BACK-RIGHT ------------------------
	bus.wheels[7].connection.Set(-bus_half_width + 0.3f * bus_wheel_width, bus_connection_height, -bus_half_length * 0.5f + bus_wheel_radius);
	bus.wheels[7].direction = bus_direction;
	bus.wheels[7].axis = bus_axis;
	bus.wheels[7].suspensionRestLength = bus_suspensionRestLength;
	bus.wheels[7].radius = bus_wheel_radius;
	bus.wheels[7].width = bus_wheel_width;
	bus.wheels[7].front = false;
	bus.wheels[7].drive = false;
	bus.wheels[7].brake = false;
	bus.wheels[7].steering = false;
	bus.wheels[7].color = Black;

	Bus = App->physics->AddVehicle(bus);
	Bus->SetPos(-72.5, 12, -5);

	// THIS CANNOT BE DONE IN THE UPDATE BECAUSE HEY ARE LOCAL VARIBLES! WE NEED A STRUCT




	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	VehicleInfo bike;

	bike.chassis_size.Set( 0.1f, 1.0f, 3);
	bike.chassis_offset.Set(0, 0.45f, 0);
	bike.mass = 30.0f;
	bike.suspensionStiffness = 1.5f;
	bike.suspensionCompression = 0.083f;
	bike.suspensionDamping = 0.088f;
	bike.maxSuspensionTravelCm = 100.0f;
	bike.frictionSlip = 5.0f;
	bike.maxSuspensionForce = 600.0f;

	/////////////////////////////////////////////////

	float bike_connection_height = 0.3f;
	float bike_wheel_radius = 0.4f;
	float bike_wheel_width = 0.1f;
	float bike_suspensionRestLength = 0.2f;

	/////////////////////////////////////////////////

	float bike_half_width = bike.chassis_size.x * 0.5f;
	float bike_half_length = bike.chassis_size.z * 0.5f;

	vec3 bike_direction(0, -1, 0);
	vec3 bike_axis(-1, 0, 0);

	bike.num_wheels = 2;
	bike.wheels = new Wheel[2];

	/////////////////////////////////////////////////

	bike.wheels[0].connection.Set(bike_half_width - bike_wheel_width * 0.5, bike_connection_height, bike_half_length * 0.95f - bike_wheel_radius);
	bike.wheels[0].direction = bike_direction;
	bike.wheels[0].axis = bike_axis;
	bike.wheels[0].suspensionRestLength = bike_suspensionRestLength;
	bike.wheels[0].radius = bike_wheel_radius;
	bike.wheels[0].width = bike_wheel_width;
	bike.wheels[0].front = true;
	bike.wheels[0].drive = true;
	bike.wheels[0].brake = false;
	bike.wheels[0].steering = true;
	
	bike.wheels[1].connection.Set(bike_half_width - bike_wheel_width * 0.5, bike_connection_height, -bike_half_length * 0.95f + bike_wheel_radius);
	bike.wheels[1].direction = bike_direction;
	bike.wheels[1].axis = bike_axis;
	bike.wheels[1].suspensionRestLength = bike_suspensionRestLength;
	bike.wheels[1].radius = bike_wheel_radius;
	bike.wheels[1].width = bike_wheel_width;
	bike.wheels[1].front = false;
	bike.wheels[1].drive = false;
	bike.wheels[1].brake = true;
	bike.wheels[1].steering = false;

	/////////////////////////////////////////////////

	//Bike = App->physics->AddVehicle(bike);
	//Bike->SetPos(0, 12, -10);

	////////////////////////////////////////////////////////////////////////////////////////////

	//VehicleInfo truck;

	//// Car properties ----------------------------------------
	//truck.chassis_size.Set(3, 9, 12);
	//truck.chassis_offset.Set(0, 4.5, 0);
	//truck.mass = 500.0f;
	//truck.suspensionStiffness = 15.88f;
	//truck.suspensionCompression = 0.83f;
	//truck.suspensionDamping = 0.88f;
	//truck.maxSuspensionTravelCm = 1000.0f;
	//truck.frictionSlip = 50.5;
	//truck.maxSuspensionForce = 6000.0f;

	//// Wheel properties ---------------------------------------
	//float truck_connection_height = 1.2f;
	//float truck_wheel_radius = 0.8f;
	//float truck_wheel_width = 0.5f;
	//float truck_suspensionRestLength = 1.2f;

	//// Don't change anything below this line ------------------

	//float truck_half_width = truck.chassis_size.x * 0.5f;
	//float truck_half_length = truck.chassis_size.z * 0.5f;

	//vec3 truck_direction(0, -1, 0);
	//vec3 truck_axis(-1, 0, 0);

	//truck.num_wheels = 8;
	//truck.wheels = new Wheel[8];

	//// FRONT-LEFT ------------------------
	//truck.wheels[0].connection.Set(truck_half_width - 0.3f * truck_wheel_width, truck_connection_height, truck_half_length * 0.95f - truck_wheel_radius);
	//truck.wheels[0].direction = truck_direction;
	//truck.wheels[0].axis = truck_axis;
	//truck.wheels[0].suspensionRestLength = truck_suspensionRestLength;
	//truck.wheels[0].radius = truck_wheel_radius;
	//truck.wheels[0].width = truck_wheel_width;
	//truck.wheels[0].front = true;
	//truck.wheels[0].drive = true;
	//truck.wheels[0].brake = false;
	//truck.wheels[0].steering = true;
	//truck.wheels[0].color = Black;

	//// FRONT-RIGHT ------------------------
	//truck.wheels[1].connection.Set(-truck_half_width + 0.3f * truck_wheel_width, truck_connection_height, truck_half_length * 0.95f - truck_wheel_radius);
	//truck.wheels[1].direction = truck_direction;
	//truck.wheels[1].axis = truck_axis;
	//truck.wheels[1].suspensionRestLength = truck_suspensionRestLength;
	//truck.wheels[1].radius = truck_wheel_radius;
	//truck.wheels[1].width = truck_wheel_width;
	//truck.wheels[1].front = true;
	//truck.wheels[1].drive = true;
	//truck.wheels[1].brake = false;
	//truck.wheels[1].steering = true;
	//truck.wheels[1].color = Black;

	//// REAR-LEFT ------------------------
	//truck.wheels[2].connection.Set(truck_half_width - 0.3f * truck_wheel_width, truck_connection_height, -truck_half_length * 0.95f + truck_wheel_radius);
	//truck.wheels[2].direction = truck_direction;
	//truck.wheels[2].axis = truck_axis;
	//truck.wheels[2].suspensionRestLength = truck_suspensionRestLength;
	//truck.wheels[2].radius = truck_wheel_radius;
	//truck.wheels[2].width = truck_wheel_width;
	//truck.wheels[2].front = false;
	//truck.wheels[2].drive = false;
	//truck.wheels[2].brake = true;
	//truck.wheels[2].steering = false;
	//truck.wheels[2].color = Black;

	//// REAR-RIGHT ------------------------
	//truck.wheels[3].connection.Set(-truck_half_width + 0.3f * truck_wheel_width, truck_connection_height, -truck_half_length * 0.95f + truck_wheel_radius);
	//truck.wheels[3].direction = truck_direction;
	//truck.wheels[3].axis = truck_axis;
	//truck.wheels[3].suspensionRestLength = truck_suspensionRestLength;
	//truck.wheels[3].radius = truck_wheel_radius;
	//truck.wheels[3].width = truck_wheel_width;
	//truck.wheels[3].front = false;
	//truck.wheels[3].drive = false;
	//truck.wheels[3].brake = true;
	//truck.wheels[3].steering = false;
	//truck.wheels[3].color = Black;

	//// MID-FRONT-LEFT ------------------------
	//truck.wheels[4].connection.Set(truck_half_width - 0.3f * truck_wheel_width, truck_connection_height, truck_half_length * 0.5f - truck_wheel_radius);
	//truck.wheels[4].direction = truck_direction;
	//truck.wheels[4].axis = truck_axis;
	//truck.wheels[4].suspensionRestLength = truck_suspensionRestLength;
	//truck.wheels[4].radius = truck_wheel_radius;
	//truck.wheels[4].width = truck_wheel_width;
	//truck.wheels[4].front = false;
	//truck.wheels[4].drive = false;
	//truck.wheels[4].brake = false;
	//truck.wheels[4].steering = true;
	//truck.wheels[4].color = Black;

	//// MID-FORNT-RIGHT ------------------------
	//truck.wheels[5].connection.Set(-truck_half_width + 0.3f * truck_wheel_width, truck_connection_height, truck_half_length * 0.5f - truck_wheel_radius);
	//truck.wheels[5].direction = truck_direction;
	//truck.wheels[5].axis = truck_axis;
	//truck.wheels[5].suspensionRestLength = truck_suspensionRestLength;
	//truck.wheels[5].radius = truck_wheel_radius;
	//truck.wheels[5].width = truck_wheel_width;
	//truck.wheels[5].front = false;
	//truck.wheels[5].drive = false;
	//truck.wheels[5].brake = false;
	//truck.wheels[5].steering = true;
	//truck.wheels[5].color = Black;

	//// MID-BACK-LEFT ------------------------
	//truck.wheels[6].connection.Set(truck_half_width - 0.3f * truck_wheel_width, truck_connection_height, -truck_half_length * 0.5f + truck_wheel_radius);
	//truck.wheels[6].direction = truck_direction;
	//truck.wheels[6].axis = truck_axis;
	//truck.wheels[6].suspensionRestLength = truck_suspensionRestLength;
	//truck.wheels[6].radius = truck_wheel_radius;
	//truck.wheels[6].width = truck_wheel_width;
	//truck.wheels[6].front = false;
	//truck.wheels[6].drive = false;
	//truck.wheels[6].brake = false;
	//truck.wheels[6].steering = false;
	//truck.wheels[6].color = Black;

	//// MID-BACK-RIGHT ------------------------
	//truck.wheels[7].connection.Set(-truck_half_width + 0.3f * truck_wheel_width, truck_connection_height, -truck_half_length * 0.5f + truck_wheel_radius);
	//truck.wheels[7].direction = truck_direction;
	//truck.wheels[7].axis = truck_axis;
	//truck.wheels[7].suspensionRestLength = truck_suspensionRestLength;
	//truck.wheels[7].radius = truck_wheel_radius;
	//truck.wheels[7].width = truck_wheel_width;
	//truck.wheels[7].front = false;
	//truck.wheels[7].drive = false;
	//truck.wheels[7].brake = false;
	//truck.wheels[7].steering = false;
	//truck.wheels[7].color = Black;

	//Truck = App->physics->AddVehicle(truck);
	//Truck->SetPos(0, 12, 10);

	VehicleInfo racingCar;//Next Vehicle (should be flatter)

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
	turn = acceleration = brake = 0.0f;

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		if (Bus->GetKmh() < 0) brake = BRAKE_POWER / 3;
		else {
			if (Bus->GetKmh() < MAX_SPEED / 3)
			acceleration = MAX_ACCELERATION / 3;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if(turn < TURN_DEGREES * 0.8)
			turn +=  TURN_DEGREES * 0.8;
	}

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if(turn > -TURN_DEGREES * 0.8)
			turn -= TURN_DEGREES * 0.8;
	}

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		if(Bus->GetKmh() > 0) brake = BRAKE_POWER / 3;
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
	sprintf_s(title, "%.1f Km/h", Bus->GetKmh());
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}