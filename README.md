# Nick's Ray Tracing in One Weekend
Note: I'm doing a more series attempt of this book series [here](https://github.com/nsdigirolamo/nicks-ray-tracer).

A ray tracer written in C following the [Ray Tracing in One Weekend](https://raytracing.github.io/) 
book series. This project only follows the first book, and if I end up following
the next two books I'll probably re-write it in a language that I'm a bit better
in.

![An image of a sphere with colored normals.](https://i.imgur.com/Pig4R4y.png)

![An image of a sphere with diffusion.](https://i.imgur.com/mTFym81.png)

![An image of multiple colored spheres with diffusion.](https://i.imgur.com/YT7XtXP.png)

![An image of multiple colored spheres with diffusion and reflection.](https://i.imgur.com/GKoVSVC.png)

![An image of multiple colored spheres. The sphere on the left is made of glass](https://i.imgur.com/IPKOMcH.png)

![A zoomed-in image of multiple colored spheres. The sphere on the left is made of glass](https://i.imgur.com/FMt7cMx.png)

This final image took an embarassing 20 hours and 13 minutes to render. In this scene 
I used a higher pixel sample rate than the other images and included more objects. 
It's also all done on the CPU and is not parallelized, so that could be another factor
in why it took so long.

![An image of three large spheres surrounded by many smaller spheres.](https://i.imgur.com/9rPgdEo.png)
