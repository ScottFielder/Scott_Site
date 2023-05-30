#include "LightActor.h"


LightActor::LightActor(Component* parent_, LightStyle lightStyle_, Vec3 position_, Vec4 color_, float intensity_, Vec3 fallOff_) :
	Actor(parent_), lightStyle(lightStyle_), position(position_), color(color_), intensity(intensity_), fallOff(fallOff_) {


}

LightActor::~LightActor() {}