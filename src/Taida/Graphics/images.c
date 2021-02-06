#define STB_IMAGE_IMPLEMENTATION

#include <stdbool.h>
#include "stb_image.h"
#include "Taida/Core/log.h"
#include "Taida/Graphics/images.h"

taidaImage_t *taidaLoadNewImage(const char *filePath)
{
	taidaImage_t *image = malloc(sizeof(taidaImage_t));

	if (image == NULL) {
		taidaLogError("Image Cannot Be Loaded");
		return NULL;
	}

	stbi_set_flip_vertically_on_load(true);

	image->data = stbi_load(filePath, &image->width, &image->height, &image->nrChannels, 0);
	if (!image->data) {
		taidaLogError("Cannot Load Data For Image");

		taidaDestroyImage(image);
		return NULL;
	}

	image->colorType = image->nrChannels;

	return image;
}

void taidaDestroyImage(taidaImage_t *image)
{
	if (image) {
		if (image->data)
			stbi_image_free(image->data);

		free(image);	
	}
}
