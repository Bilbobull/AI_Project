For this project I used my own Graphics Engine, so there are some things that work kind of different.
Instructions:

Use in Debug Mode, couldnt find some dll

Can't move object with GUI, instead, I implemented a Camera that you can move with keyboard input
 - W forward
 - S backwards
 - A left
 - D right
 - E up
 - Q down
 
 You can also rotate the first object with P
 
 The Load Model works a little different:
 - You can load the following objects:
   - Cube
   - Drone
   - Ironman
   - Pyro
   
 Debug Mode easy, select the option you want
 
 Camera position is not really camera movement, is more kind of an offset from where u are. So you can ]
 move with WASDQE and offset the camera lookat vector or position
 
 Material easy
 
 Shininess easy
 
 Global ambient easy
 
 Lights works as its supposed to, create makes one, remove pops back. Is set so you can move lights around
 but it will "reset" positions if you create another one in order for them to create a circle
 
 Distance and atmospheric attenuation works just as its supposed to. You can Enable and Disable them inside
 their tabs
 
 Rotate lights, sets lights in a circle and starts rotating them. You can stop movement by clicking again.
 
 Particles, you can start a compute shader particle system thats controlled with the mouse by  clicking and
 desactivate it clicking again. You can do this as many times as wanted.
 
 Textures activates textures in object. Some objects may not have one and they'll just draw as debug draw instead
 Also, this features makes fog not work, so dont text fog with texturing enabled