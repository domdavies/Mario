#include "Collisions.h"
#include "Character.h"

Collisions* Collisions::mInstance = NULL;

Collisions::Collisions() {

}

Collisions* Collisions::Instance() {
	//check if there is an instance of collision, if not set one up
	if (!mInstance)
	{
		mInstance = new Collisions;
	}
	return mInstance;
}

Collisions::~Collisions() {
	mInstance = NULL;
}

bool Collisions::Circle(Character* character1, Character* character2) {
	//calculate the vector that seperates two objects
	Vector2D vec = Vector2D((character1->GetPosition().x - character2->GetPosition().x),
							 (character1->GetPosition().y - character2->GetPosition().y));

	//calculate the distance between the two
	double distance = sqrt((vec.x * vec.x) + (vec.y, vec.y));

	//get the collision radius of each character
	double combinedDistance = (character1->GetCollisionRadius() + character2->GetCollisionRadius());

	//check to see whether the distnce is shorter
	return distance < combinedDistance;
}

bool Collisions::Box(Rect2D rect1, Rect2D rect2) {
	//if eith one overlaps
	if (rect1.x + (rect1.w/2) > rect2.x && rect1.x + (rect1.w/2) < rect2.x + rect2.w &&
		rect1.y + (rect1.h/2) > rect2.y && rect1.y + (rect1.h/2) < rect2.y + rect2.h)
	{
		return true;
	}
	return false;
}
