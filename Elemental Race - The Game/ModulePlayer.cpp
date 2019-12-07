#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

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

	Bus = App->physics->AddVehicle(bus);
	Bus->SetPos(0, 12, 10);

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

	Bike = App->physics->AddVehicle(bike);
	Bike->SetPos(0, 12, -10);
	

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
		if (Bus->GetKmh() < 0) brake = BRAKE_POWER;
		else {
			if (Bus->GetKmh() < MAX_SPEED)
			acceleration = MAX_ACCELERATION;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if(turn < TURN_DEGREES)
			turn +=  TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if(turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		if(Bus->GetKmh() > 0) brake = BRAKE_POWER;
		else {
			if (Bus->GetKmh() > MIN_SPEED)
			acceleration = -BRAKE_POWER;
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