#include"Sprite.h"
#include"Camera.h"
Sprite::Sprite(int id, int left, int top, int right, int bottom, LPTEXTURE tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
	if (right < left)
		this->flip = -1;
	sprite.pTexture = tex->getShaderResourceView();

	sprite.TexCoord.x = this->left / (float)tex->getWidth();
	sprite.TexCoord.y = this->top / (float)tex->getHeight();

	int spriteWidth = (this->right - this->left+1 );
	int spriteHeight = (this->bottom - this->top+1);

	sprite.TexSize.x = spriteWidth / (float)tex->getWidth();
	sprite.TexSize.y = spriteHeight / (float)tex->getHeight();

	sprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	sprite.TextureIndex = 0;

	D3DXMatrixScaling(&this->matScaling, this->flip*(FLOAT)spriteWidth, (FLOAT)spriteHeight, 1.0f);
}

void Sprite::Draw(float x, float y)
{
	Game* g = Game::GetInstance();


	D3DXMATRIX matTranslation;
	D3DXMatrixTranslation(&matTranslation, x, (g->GetBackBufferHeight() - y), 0.1f);
	this->sprite.matWorld = (this->matScaling * matTranslation);

	g->GetSpriteHandler()->DrawSpritesImmediate(&sprite, 1, 0, 0);
}