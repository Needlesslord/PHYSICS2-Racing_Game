#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "DataForTheCourses.h"

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
	
	size = 1248;
	numCourse = 1;
	CreateCourse(Mario, size, numCourse);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	for (uint i = 0; i < course_index; i++) {
		delete Course[i];
	}
	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	for (uint i = 0; i < course_index; i++) {
		Course[i]->Render();
	}
	return UPDATE_CONTINUE;
}

Cube ModuleSceneIntro::CreateObject_BorderCourse(float posX, float posY, float posZ, int course) {
	float mass = 100000;
	float sizeX = 3;
	float sizeY = 5;
	float sizeZ = 3;
	Course[course_index] = new Cube(sizeX, sizeY, sizeZ);
	Course[course_index]->SetPos(posX, posY, posZ);
	App->physics->AddBody(*Course[course_index], mass);
	if      (course == 1) { Course[course_index]->color = Blue; }		// The water course
	else if (course == 2) { Course[course_index]->color = Black; }		// The earth course
	else if (course == 3) { Course[course_index]->color = White; }		// The   air course
	else { Course[course_index]->color = Red; }							// The  fire course
	
	course_index++;
	return *Course[course_index - 1];
}

bool ModuleSceneIntro::CreateCourse(float list[], uint size, uint numCourse) {
	for (int i = 0; i < size; i += 3) {
		float x = list[i] * 300;
		float y = list[i + 1] * 300;
		float z = list[i + 2] * 300 - 75;
		CreateObject_BorderCourse(x, y, z, numCourse);
	}
	
	return true;
}


void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2) {}

