#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	// course
	int n = 1;
	for (int i = 0; i < n; i++) {
		float posX = 0;
		float posY = 0;
		float posZ = -5;
		CreateObjectCourse(posX, posY, posZ);

	}
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	return UPDATE_CONTINUE;
}

bool ModuleSceneIntro::CreateObjectCourse(float posX, float posY, float posZ) {
	bool ret = true;
	
	float massCube = 1;
	float sizeX = 1;
	float sizeY = 3;
	float sizeZ = 1;
	Cube c(sizeX, sizeY, sizeZ);
	c.SetPos(posX, posY, posZ);
	App->physics->AddBody(c, massCube);


	////float massSphere = 1;
	////float radius = 1;
	////Sphere s(radius);
	////s.SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);
	////App->physics->AddBody(s, massSphere);
	////App->physics->AddBody(s)->Push(-(0), -(100), -(0));
	//float massCube = 1;
	//float sizeX = 1;
	//float sizeY = 3;
	//float sizeZ = 1;
	//Cube c(sizeX, sizeY, sizeZ);
	////c.SetPos(App->camera->Position.x + 2, App->camera->Position.y + 2, App->camera->Position.z + 2);
	//App->physics->AddBody(c, massCube);
	////App->physics->AddBody(c)->Push(-(0), -(100), -(0));

	return ret;
}


void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

