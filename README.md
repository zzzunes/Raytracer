# Raytracer

To build the project, run the following commands:

``$ git clone https://github.com/Jragoon/Raytracer``

``$ cd Raytracer``

``$ mkdir build``

``$ cmake ..``

``$ make``

Then, run the Raytracer to generate the image:
``./Raytracer``

The result will be a file called ``output.ppm`` in the same directory.

# Reflections

![Alt text](/screenshots/Reflections.png?raw=true "First use of reflections and mirror material")

Spheres with a fully reflective mirror material.

# Shadowing

![Alt text](/screenshots/FirstShadows.png?raw=true "Shadows completed!")

To darken the areas where we want to create shadows, we have to imagine another line- this time originiating from our hit point. From the hit point, we need to draw a line to the light source. If we run into another object, then we know that we are in the shadow of another object. Therefore, we can skip the normal illumination sequence for this point in the framebuffer.

# Specular Lighting

![Alt text](/screenshots/SpecularLighting.png?raw=true "First instance of specular lighting")

Specular lighting is responsible for creating the effect of a shiny surface. Essentially, the brighter the spot on our object, the more aligned the reflected light direction and surface normal. The formula used for determining the reflection direction is derived from the [law of reflection](https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel). 

# Diffused Lighting

![Alt text](/screenshots/DiffusedLighting.png?raw=true "First instance of diffused lighting")

When we shoot our rays from the origin out into our scene and we make contact with an object- how do we determine the color of the pixel at this location? First, we get the sphere's raw color (for us, we store that in a 3D Vector representing RGB). Then, to illuminate the point, we need to figure out two things: the direction of our light source and the surface normal. The total brightness of this spot can be determined by finding the dot product between the normalized direction of the light and the surface normal of our object. The more aligned these two vectors are, the more this point is directly facing the light. 

Once we have the dot product of these two vectors, we scale it by the intensity of our light source. Then, once we have our scaled value, we use it to scale the original color of the object at this point. Doing this will scale the color values of our object to a higher number. When discussing RGB color values, higher numbers represent brighter colors. For example, (0, 0, 0) would represent black while (1, 1, 1) would represent white.

Credit for describing Ray Tracer behavior, knowledge: https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-ray-tracing
