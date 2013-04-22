all:
	nvcc RaytraceMain.cpp Raytracer.cu ParsingUtility.cpp Image.cpp -o raytrace
