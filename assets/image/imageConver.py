from PIL import Image
import os

current_folder = os.getcwd()

all_files = os.listdir(current_folder)

png_files = [file for file in all_files if file.endswith('.png')]

for png_file in png_files:
    
    image = Image.open(png_file)
     
    width, height = image.size
    pixel_list=list()
    png_file = png_file.replace(".png","")
    for x in range(width):
        for y in range(height):
            pixel_list.append(image.getpixel((x, y)))
    pixel_list_str = str(pixel_list)
    pixel_list_str = pixel_list_str.replace('(255, 201, 14, 255)', 'YELLOW')
    pixel_list_str = pixel_list_str.replace('(61, 18, 14, 255)', 'BROWN')
    pixel_list_str = pixel_list_str.replace('(103, 164, 224, 255)', 'CYAN')
    pixel_list_str = pixel_list_str.replace('(230, 7, 248, 255)', 'LIGHTMAGENTA')
    pixel_list_str = pixel_list_str.replace('(0, 0, 0, 255)', 'BLACK')
    pixel_list_str = pixel_list_str.replace('(255, 255, 255, 0)', '255')
    pixel_list_str = pixel_list_str.replace('(0, 0, 0, 0)', '255')
    pixel_list_str = pixel_list_str.replace("[","{")
    pixel_list_str = pixel_list_str.replace("]","}")
    pixel_list_str = pixel_list_str.replace("(","{")
    pixel_list_str = pixel_list_str.replace(")","}")
    with open(png_file+".cpp","w") as f:
        f.write("const int "+png_file+"["+str(len(pixel_list))+"] = \n"+pixel_list_str+";")