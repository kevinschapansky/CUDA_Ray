all:
	nvcc RaytraceMain.cpp Raytracer.cu Camera.cpp ParsingUtility.cpp LightSource.cpp Sphere.cpp Transformations.cpp Pigment.cpp Finish.cpp Box.cpp Cone.cpp Triangle.cpp Plane.cpp Image.cpp -o raytrace
