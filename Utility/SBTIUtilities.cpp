#include "SBTIUtilities.h"
#define STB_IMAGE_IMPLEMENTATION // Both of these must only exist
#include "stb_image/stb_image.h" // in a single file (per source doc)

void SBTIUtilities::free_image(void* image_data){
	stbi_image_free(image_data);
}
