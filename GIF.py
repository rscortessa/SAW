#!/usr/bin/env python
# coding: utf-8

# In[ ]:


from PIL import Image
import glob
# Create the frames
frames = []
imgs = glob.glob("*[0-9]")
for i in range(0,len(imgs)):
    imgs[i]=int(imgs[i])
imgs.sort()
for i in imgs:
    new_frame = Image.open(str(i))
    frames.append(new_frame)
# Save into a GIF file that loops forever
frames[0].save('png_to_gif.gif', format='GIF',
               append_images=frames[1:],
               save_all=True,
               duration=500, loop=1)
 

