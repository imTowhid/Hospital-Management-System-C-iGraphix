#include "texture.h"

texture textures[10];
texture home, top, infop, coutp, cinp, sch1, sch2, upda, pats, patsr, patr1, DOCL, rmst, style2;

//texture textureVariable;

void textureInit()
{
    coutp.Create("cout.bmp");
    textures[0].Create("Hospital2.bmp");
	textures[1].Create("roomp.bmp");
	textures[2].Create("style1.bmp");
	home.Create("home.bmp");
	top.Create("top1.bmp");
	infop.Create("info.bmp");
	cinp.Create("cin.bmp");
	sch1.Create("sch1.bmp");
	sch2.Create("sch2.bmp");
	upda.Create("upda.bmp");
	pats.Create("pse.bmp");
	patsr.Create("PSER.bmp");
	patr1.Create("pser1.bmp");
	DOCL.Create("DOCL.bmp");
	rmst.Create("rmst.bmp");
	style2.Create("style2.bmp");
}



/**
How to use texture image:

1. in TextureList.h: declare texture type variables as needed. For every image, you need to declare one texture type variable.

Example:

texture textureVariable;


2. in TextureList.h: in the function textureInit(): initialize the texture variable that you declared in step 1 with the name
of the image file.

Example: suppose you have an image file named: "google.bmp"
then, you initialize as follows:

textureVariable.Create("google.bmp");


3. in the main cpp file in iDraw function: use drawTexture function to draw the image. drawTexture takes three arguments.

-> first argument   : lower left x-coordinate of the image
-> second argument  : lower left y-coordinate of the image
-> third argument   : name of the textureVariable declared in step 1


Example:

drawTexture(100, 200, textureVariable);
**/
