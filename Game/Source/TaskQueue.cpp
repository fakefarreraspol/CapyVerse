#include "App.h"
#include "Entity.h"
#include "Input.h"
#include "TaskQueue.h"




bool TaskQueue::Update(float dt)
{
	bool ret = false;
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{

		if (Temp_Task == nullptr && TaskQu.size() != 0)
		{
			//TODO 4: Assign the first element of the queue to the auxiliar_task, call InitTask function for auxiliar_task and make a pop of the queue.
			Temp_Task = TaskQu.front();
			Temp_Task->InitTask();
			TaskQu.pop();
		}
	}

	ret = Do_Tasks();

	return ret;
}

bool TaskQueue::CleanUp()
{
	
		//TODO 3: Pop queue tasks if task queue if the queue still has tasks
	TaskQu.pop();
	return true;
}

bool TaskQueue::Enqueue(Task* task)
{
	//TODO 1 Add task to the queue
	TaskQu.push(task);

	return true;
}

bool TaskQueue::Do_Tasks()
{
	if (Temp_Task != nullptr)
	{

		if (Temp_Task->Action())
		{
			if (TaskQu.size() != 0)
			{
				//TODO 2: Assign the first element of the queue to the auxiliar_task, call InitTask function for auxiliar_task and make a pop of the queue.
				Temp_Task = TaskQu.front();
				Temp_Task->InitTask();
				TaskQu.pop();


			}
			else
				Temp_Task = nullptr;

		}
	}
	return true;
}

//Movement methods already done
bool Go_Right::Action()
{
	bool ret = true;

	if (entity->position.x >= Final_Position.x) {
		entity->position.x = Final_Position.x;
		ret = true;
	}
	else {
		entity->position.x += entity->speed.x;
	}
	return ret;
}

bool Go_Left::Action()
{
	bool ret = false;
	if (entity->position.x <= Final_Position.x) {
		entity->position.x = Final_Position.x;
		ret = true;
	}
	else {
		entity->position.x -= entity->speed.x;
	}

	return ret;
}
bool Go_Up::Action()
{
	bool ret = false;
	if (entity->position.y <= Final_Position.y) {
		entity->position.y = Final_Position.y;
		ret = true;
	}
	else {
		entity->position.y -= entity->speed.y;
	}
	return ret;
}
bool Go_Down::Action()
{
	bool ret = false;
	if (entity->position.y >= Final_Position.y) {
		entity->position.y = Final_Position.y;
		ret = true;
	}
	else {
		entity->position.y += entity->speed.y;
	}
	return ret;
}