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
	int num = 1;

	for (int i = 0; i < n; i++) {
		float posX = 0;
		float posY = 0;
		float posZ = -5;
		CreateObject_BorderCourse(posX, posY, posZ, num);
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

Cube ModuleSceneIntro::CreateObject_BorderCourse(float posX, float posY, float posZ, int course) {
	Cube* ret;
	
	float massCube = 100000;
	float sizeX = 1;
	float sizeY = 3;
	float sizeZ = 1;
	ret = new Cube(sizeX, sizeY, sizeZ);
	ret->SetPos(posX, posY, posZ);
	App->physics->AddBody(*ret, massCube);
	if (course == 1) { ret->color = Blue; }
	else if (course == 2) { ret->color = Black; }
	else if (course == 3) { ret->color = White; }
	else { ret->color = Red; }

	return *ret;
}


void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

