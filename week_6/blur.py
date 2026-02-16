# Blurs an image

from PIL import Image, ImageFilter

# Blur image
before = Image.open("courtyard.bmp")
after = before.filter(ImageFilter.BoxBlur(1))
after.save("out_blur.bmp")