#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

/*
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
	float connection_height = 1.2f;
	float wheel_radius = 0.8f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = bus.chassis_size.x * 0.5f;
	float half_length = bus.chassis_size.z * 0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	bus.num_wheels = 8;
	bus.wheels = new Wheel[8];

	// FRONT-LEFT ------------------------
	bus.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length * 0.95f - wheel_radius);
	bus.wheels[0].direction = direction;
	bus.wheels[0].axis = axis;
	bus.wheels[0].suspensionRestLength = suspensionRestLength;
	bus.wheels[0].radius = wheel_radius;
	bus.wheels[0].width = wheel_width;
	bus.wheels[0].front = true;
	bus.wheels[0].drive = true;
	bus.wheels[0].brake = false;
	bus.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	bus.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length * 0.95f - wheel_radius);
	bus.wheels[1].direction = direction;
	bus.wheels[1].axis = axis;
	bus.wheels[1].suspensionRestLength = suspensionRestLength;
	bus.wheels[1].radius = wheel_radius;
	bus.wheels[1].width = wheel_width;
	bus.wheels[1].front = true;
	bus.wheels[1].drive = true;
	bus.wheels[1].brake = false;
	bus.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	bus.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length * 0.95f + wheel_radius);
	bus.wheels[2].direction = direction;
	bus.wheels[2].axis = axis;
	bus.wheels[2].suspensionRestLength = suspensionRestLength;
	bus.wheels[2].radius = wheel_radius;
	bus.wheels[2].width = wheel_width;
	bus.wheels[2].front = false;
	bus.wheels[2].drive = false;
	bus.wheels[2].brake = true;
	bus.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	bus.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length * 0.95f + wheel_radius);
	bus.wheels[3].direction = direction;
	bus.wheels[3].axis = axis;
	bus.wheels[3].suspensionRestLength = suspensionRestLength;
	bus.wheels[3].radius = wheel_radius;
	bus.wheels[3].width = wheel_width;
	bus.wheels[3].front = false;
	bus.wheels[3].drive = false;
	bus.wheels[3].brake = true;
	bus.wheels[3].steering = false;

	// MID-FRONT-LEFT ------------------------
	bus.wheels[4].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length * 0.5f - wheel_radius);
	bus.wheels[4].direction = direction;
	bus.wheels[4].axis = axis;
	bus.wheels[4].suspensionRestLength = suspensionRestLength;
	bus.wheels[4].radius = wheel_radius;
	bus.wheels[4].width = wheel_width;
	bus.wheels[4].front = false;
	bus.wheels[4].drive = false;
	bus.wheels[4].brake = false;
	bus.wheels[4].steering = true;

	// MID-FORNT-RIGHT ------------------------
	bus.wheels[5].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length * 0.5f - wheel_radius);
	bus.wheels[5].direction = direction;
	bus.wheels[5].axis = axis;
	bus.wheels[5].suspensionRestLength = suspensionRestLength;
	bus.wheels[5].radius = wheel_radius;
	bus.wheels[5].width = wheel_width;
	bus.wheels[5].front = false;
	bus.wheels[5].drive = false;
	bus.wheels[5].brake = false;
	bus.wheels[5].steering = true;

	// MID-BACK-LEFT ------------------------
	bus.wheels[6].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length * 0.5f + wheel_radius);
	bus.wheels[6].direction = direction;
	bus.wheels[6].axis = axis;
	bus.wheels[6].suspensionRestLength = suspensionRestLength;
	bus.wheels[6].radius = wheel_radius;
	bus.wheels[6].width = wheel_width;
	bus.wheels[6].front = false;
	bus.wheels[6].drive = false;
	bus.wheels[6].brake = false;
	bus.wheels[6].steering = false;

	// MID-BACK-RIGHT ------------------------
	bus.wheels[7].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length * 0.5f + wheel_radius);
	bus.wheels[7].direction = direction;
	bus.wheels[7].axis = axis;
	bus.wheels[7].suspensionRestLength = suspensionRestLength;
	bus.wheels[7].radius = wheel_radius;
	bus.wheels[7].width = wheel_width;
	bus.wheels[7].front = false;
	bus.wheels[7].drive = false;
	bus.wheels[7].brake = false;
	bus.wheels[7].steering = false;

	vehicle = App->physics->AddVehicle(bus);
	vehicle->SetPos(0, 12, 10);
*/
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

	/*bus.chassis_size.Set(3, 9, 12);
	bus.chassis_offset.Set(0, 4.5, 0);
	bus.mass = 500.0f;
	bus.suspensionStiffness = 15.88f;
	bus.suspensionCompression = 0.83f;
	bus.suspensionDamping = 0.88f;
	bus.maxSuspensionTravelCm = 1000.0f;
	bus.frictionSlip = 50.5f;
	bus.maxSuspensionForce = 6000.0f;*/

	/////////////////////////////////////////////////

	float connection_height = 0.3f;
	float wheel_radius = 0.4f;
	float wheel_width = 0.1f;
	float suspensionRestLength = 0.2f;

	/////////////////////////////////////////////////

	float half_width = bike.chassis_size.x * 0.5f;
	float half_length = bike.chassis_size.z * 0.5f;

	vec3 direction(0, -1, 0);
	vec3 axis(-1, 0, 0);

	bike.num_wheels = 2;
	bike.wheels = new Wheel[2];

	/////////////////////////////////////////////////

	bike.wheels[0].connection.Set(half_width - wheel_width * 0.5, connection_height, half_length * 0.95f - wheel_radius);
	bike.wheels[0].direction = direction;
	bike.wheels[0].axis = axis;
	bike.wheels[0].suspensionRestLength = suspensionRestLength;
	bike.wheels[0].radius = wheel_radius;
	bike.wheels[0].width = wheel_width;
	bike.wheels[0].front = true;
	bike.wheels[0].drive = true;
	bike.wheels[0].brake = false;
	bike.wheels[0].steering = true;
	
	bike.wheels[1].connection.Set(half_width - wheel_width * 0.5, connection_height, -half_length * 0.95f + wheel_radius);
	bike.wheels[1].direction = direction;
	bike.wheels[1].axis = axis;
	bike.wheels[1].suspensionRestLength = suspensionRestLength;
	bike.wheels[1].radius = wheel_radius;
	bike.wheels[1].width = wheel_width;
	bike.wheels[1].front = false;
	bike.wheels[1].drive = false;
	bike.wheels[1].brake = true;
	bike.wheels[1].steering = false;

	/////////////////////////////////////////////////

	vehicle = App->physics->AddVehicle(bike);
	vehicle->SetPos(0, 12, 10);

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
		acceleration = MAX_ACCELERATION;
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
		brake = BRAKE_POWER;
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();

	char title[80];
	sprintf_s(title, "%.1f Km/h", vehicle->GetKmh());
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}