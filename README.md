# demo64KB
This is a graphics demo generating and rendering procedural landscape on the fly using the GPU. The executable size is below 64KB and actually just 28KB (a single 500x500 JPG image file is larger than that). No textures or other files are loaded by the executable.

## Results
To see a video, take a look [here](https://vimeo.com/257886445).
![](https://github.com/ddrevicky/demo64KB/blob/master/imgs/result1.png)
![](https://github.com/ddrevicky/demo64KB/blob/master/imgs/result2.png)
![](https://github.com/ddrevicky/demo64KB/blob/master/imgs/result3.png)

## Details
* To keep the executable self-contained and its size small the landscape and environment textures have to be generated procedurally in the shader running on the GPU instead of being loaded from the hard drive. 
* Since I use OpenGL to access the GPU's rendering capabilities it is necessary to load the OpenGL function addresses from the opengl dynamic library. This usually accomplished using helper libraries like GLAD or GLEW but since they load all of the functions, the executable size would bloat beyond 64KB. I therefore only manually load the ones I actually use with WINAPI's `GetProcAddress` call.
* To keep the size small I also couldn't use a multi platform windowing library (like SDL) so I've just implemented the platform layer for Windows. All of the platform dependent stuff is in `main.cpp` file so to port this to Linux it would be enough to reimplement this file there.
* The shader files are stored as strings in `shaders.h` file but I've also placed a txt copy of them in the shaders subdirectory since those are a bit easier to read (but the txt versions are not actually used by the program).

## How it works
### Heightmap generation
* The terrain is described by a heightmap which is simply a function of 2 coordinates x, z returning the height y of the terrain in the given location, so that y = f(x, z). If we defined this function in such a way that the resulting heightmap looks random (though it is only pseudorandom and deterministic) we would start getting someplace interesting. Such a function is called a noise function, a popular example which has been used heavily in movies and games is called the [Perlin noise](https://en.wikipedia.org/wiki/Perlin_noise). 
* To get something that looks really natural though, the terrain needs to have variation on different scales (think mountains, hills, stones, pebbles etc.) so it might be a good idea to add several such noise functions together but with different amplitudes and frequency. This is called fractional Brownian motion or fBm for short and you can find an equivalent function in the fragment shader (by tweaking the parameters in the function you can get to the terrain that looks satisfactory for you).
* In the images below, starting from the top left and progressing along the rows each image is a sum of noises of different amplitudes and frequencies. The first image is a pure noise function with the largest amplitude amongst the summands and the lowest frequency. It models the mountains in the terrain. In the next image we've added noise of roughly half the amplitude and double the frequency. This is repeated several times until we end up with something that looks more or less like natural terrain in the bottom right picture.

![](https://github.com/ddrevicky/demo64KB/blob/master/imgs/fbms.png)

### Shading
Once we have generated the heightmap, we can give the environment color based on height and some smooth interpolation (image b), add some random patches of grass, exponential distance fog and clouds (c) and finally water with wavy surface reflecting the sky. Simulating water was quite interesting and I've added a Fresnel effect so that when the camera is parallel with the surface of the water it is perfectly reflective but if the camera looks straight bellow the surface becomes transparent and you can see the terrain underneath.
![](https://github.com/ddrevicky/demo64KB/blob/master/imgs/terrain.png)

### Rendering
The height map is rendered using ray marching which is a technique similar to ray casting. The difference is that when using ray marching we usually have analytical models of the objects so we can calculate ray-object intersection exactly but with a height map defined by a noise function this is not possible so we just send rays into the environment and step along them until we intersect the terrain (the tip of the ray goes into the terrain) and at that point we can calculate the surface normal and proceed with shading as described above.

## How to run
* If you are on Windows (which is required, see above) you can just download one of the precompiled executables (different resolutions are provided) from demo64KB/executables folder and double click to run. The performance will depend on your GPU and the resolution of the executable.
