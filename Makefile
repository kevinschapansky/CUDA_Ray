all:
	nvcc RaytraceMain.cpp Raytracer.cu ParsingUtility.cpp Transformations.cpp Box.cpp Cone.cpp Triangle.cpp Image.cpp -o raytrace
