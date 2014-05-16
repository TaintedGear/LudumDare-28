#ifndef PICKUP_OBJECT_H
#define PICKUP_OBJECT_H

#include "GameObject.h"

//enum{ PISTOL = 0, SHOTGUN = 1, ROCKET_LAUNCER = 2, RAILGUN = 3, TBC = 4};

class PickupObject : public GameObject
{
public:
	PickupObject();
	~PickupObject();

	bool LoadContent(ResourceManager& resources);
	void UnloadContent();

	void Update(float dt, Camera cam);
	void Render(SDL_Renderer* renderer, Camera cam);

	int GetType();
	void SetType( int type );
	void SetPicked( bool picked);

private:
	int m_typeId;
	bool m_pickedUp;
};

#endif