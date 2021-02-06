#ifndef _IMAGES_H_
#define _IMAGES_H_

enum {
	TAIDA_DEFAULT,
	TAIDA_IMG_GREY,
	TAIDA_IMG_GREYA, /* GREY ALPHA */
	TAIDA_IMG_RGB,
	TAIDA_IMG_RGBA, /* RGB ALPHA*/
} taidaImageType;

typedef struct {
	int width, height, nrChannels, colorType;
	
	unsigned char *data;
} taidaImage_t;

taidaImage_t *taidaLoadNewImage(const char *filePath);
void taidaDestroyImage(taidaImage_t *image);

#endif /* _IMAGES_H_ */
