#include"Camera.h"


Camera* Camera::__instance = NULL;

Camera* Camera::GetInstace()
{
	if (__instance == NULL)
		__instance = new Camera();
	return __instance;
}
void Camera::SetMap(LPSPRITE map)
{
	this->map = map;
}
float Camera::ConvertWorldX(float x)
{
	return x - this->x;
}
float Camera::ConvertWorldY(float y)
{
	return this->y - y;
}
void Camera::Update(DWORD dt,Player* player)
{
	if(player->GetX() >= width / 2&&player->GetX()<=WORLD_WIDTH-width/2)
		this->x += player->Getvx() * dt;
	float right_edge = WORLD_WIDTH - width;
	if (this->x <=0 || this->x >= right_edge)
	{
		if (this->x<=0)
			this->x = 0;
		else
			this->x = right_edge;
	}

		
	this->Render();
}
void Camera::Render()
{
	float Cx = ConvertWorldX(WORLD_WIDTH/2);
	float Cy = ConvertWorldY(WORLD_HEIGHT/2);
	this->map->Draw(Cx, Cy);
}