# Finds edges in an image

from PIL import Image, ImageFilter

# Find edges
before = Image.open("courtyard.bmp")
after = before.filter(ImageFilter.FIND_EDGES)
after.save("out_edges.bmp")