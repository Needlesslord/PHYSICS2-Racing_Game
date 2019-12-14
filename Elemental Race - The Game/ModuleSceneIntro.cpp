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
	
	Mario_size = 1248;
	CreateCourse(Mario, Mario_size);

	checkpoints_list_size = 12;
	CreateCheckpoints(checkpoints_list, checkpoints_list_size);


	////NUR
	//createRamp({ 75.0f, 0, -156.6f }, { 90, 4.0f, -146.0f });

	//START LINE
	float start_line_size[3] = { 4, 2, 20 };
	float start_line_position[3] = { 0, 1, 0 };
	Cube* start_line = new Cube(4, 2, 20);
	start_line->SetPos(300, 300, 300);
	start_line->color = White;

	

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

Cube ModuleSceneIntro::CreateObject_BorderCourse(float posX, float posY, float posZ) {
	float mass = 0;
	float sizeX = 3;
	float sizeY = 3;
	float sizeZ = 3;
	Course[course_index] = new Cube(sizeX, sizeY, sizeZ);
	Course[course_index]->SetPos(posX, posY + sizeY / 2, posZ);
	App->physics->AddBody(*Course[course_index], this, mass);
	Course[course_index]->color = Blue;
	
	course_index++;
	return *Course[course_index - 1];
}

bool ModuleSceneIntro::CreateCourse(float list[], uint size) {
	for (int i = 0; i < size; i += 3) {
		float x = list[i] * 300;
		float y = list[i + 1] * 300;
		float z = list[i + 2] * 300 - 75;
		CreateObject_BorderCourse(x, y, z);
	}
	
	return true;
}

void ModuleSceneIntro::AddCheckpoint(float posX, float posY, float posZ) {
	float sizeX = 5;
	float sizeY = 5;
	float sizeZ = 5;
	Cube checkpoint_cube(sizeX, sizeY, sizeZ);
	checkpoint_cube.SetPos(posX, posY + sizeY / 2, posZ);
	PhysBody3D*	Checkpoint = App->physics->AddBody(checkpoint_cube, this, 0.0f, false);
	Checkpoints.PushBack(Checkpoint);
}

bool ModuleSceneIntro::CreateCheckpoints(float list[], uint size) {
	for (int i = 0; i < size; i += 3) {
		float x = list[i];
		float y = list[i + 1];
		float z = list[i + 2];
		AddCheckpoint(x, y, z);
	}
	return true;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2) {
	if (body1 == Checkpoints[0] && !checkpointActivated[0]) {
		checkpointActivated[0] = true;
	}
}

////NUR
//void ModuleSceneIntro::createRamp(const vec3 i_pos, const vec3 f_pos)
//{
//	vec3 final_projection = { f_pos.x, 0, f_pos.z };
//	vec3 direction = normalize(f_pos - i_pos);
//	vec3 planar_direction = normalize(final_projection - i_pos);
//	float distance = length(f_pos - i_pos);
//	float planar_distance = length(final_projection - i_pos);
//
//	float heading = 0.0f;
//	if (f_pos.z >= i_pos.z && f_pos.x < i_pos.x)
//		heading = acos(dot(planar_direction, { 1, 0, 0 }));
//	else if (f_pos.z >= i_pos.z && f_pos.x >= i_pos.x)
//		heading = acos(dot(planar_direction, { 1, 0, 0 }));
//	else if (f_pos.z < i_pos.z && f_pos.x >= i_pos.x)
//		heading = 2 * M_PI - acos(dot(planar_direction, { 1, 0, 0 }));
//	else if (f_pos.z < i_pos.z && f_pos.x < i_pos.x)
//		heading = 2 * M_PI - acos(dot(planar_direction, { 1, 0, 0 }));
//
//	float slope = asin(f_pos.y / distance);
//
//	Cube c;
//	c.size = { distance, 0.25f, 15 - 2 };
//	c.color = White;
//
//	c.SetPos(i_pos.x + (direction.x * distance / 2.0f), i_pos.y + (sin(slope)* (c.size.x / 2.0f)), i_pos.z + (direction.z * distance / 2.0f));
//
//	c.SetRotation(slope * 180.0f / M_PI, { 0, 0, 1 });
//	mat4x4 R1;
//	for (uint i = 0; i < 16; i++)
//		R1[i] = c.transform.M[i];
//	c.SetRotation(-heading * 180.0f / M_PI, { 0, 1, 0 });
//	mat4x4 R2;
//	for (uint i = 0; i < 16; i++)
//		R2[i] = c.transform.M[i];
//	mat4x4 R3 = R2 * R1;
//
//	float angle;
//	vec3 axis;
//	angleAndAxisFromRotMat(R3, angle, axis);
//	c.SetRotation(-angle * 180.0f / M_PI, { axis.x, axis.y, axis.z });
//
//	//cube_circuit_pieces.prim_bodies.PushBack(c);
//	//cube_circuit_pieces.phys_bodies.PushBack(App->physics->AddBody(c, this, 0.0f));
//}
//
////NUR
//void ModuleSceneIntro::angleAndAxisFromRotMat(mat4x4 m, float &angle, vec3 &axis)
//{
//	angle = acos((m[0] + m[5] + m[10] - 1) / 2.0f);
//
//	axis.x = (m[9] - m[6]) / (2 * sin(angle));
//	axis.y = (m[2] - m[8]) / (2 * sin(angle));
//	axis.z = (m[4] - m[1]) / (2 * sin(angle));
//
//	axis = normalize(axis);
//}

