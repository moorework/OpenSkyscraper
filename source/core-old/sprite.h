#ifndef OSS_SPRITE_H
#define OSS_SPRITE_H

#include "../general.h"
#include "../base/base.h"
#include "../resources/texture.h"
#include "coreobject.h"


namespace OSS {
	class Sprite : public CoreObject {
	public:
		//Initialization
		Sprite();
		~Sprite();
		
		/**
		 * Basic
		 */
		
		//TODO: Make rect and color private
		rectd rect;
		color4d color;
		bool hidden;
		
	public:
		const rectd & getRect();
		void setRect(const rectd & rect);
		
		const color4d & getColor();
		void setColor(const color4d & color);
		
		bool isHidden();
		void setHidden(bool hidden);
		
		
		//Texturing
		enum {
			kRepeatTextureMode,
			kRectTextureMode
		};
		Pointer<Texture> texture;
		rectd textureRect;
		unsigned int textureMode; //TODO: Make of type TextureMode
		double textureScale;
		
		//Autogenerating Texture Rect
		bool autoTexRectX;
		bool autoTexRectY;
		bool autoTexRelativeX;	//whether the texture coordinates should be relative to the sprite
		bool autoTexRelativeY;
		
		//Drawing
		void draw(rectd visibleRect);
		void autogenerateTextureRect();
	};
}


#endif