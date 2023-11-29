/*
  PluginMain.cpp
  ==============
  Implements registration and deregistration of custom node
*/
#include "PluginMain.hpp"

MStatus initializePlugin(MObject obj)
{

	MStatus status;
	MFnPlugin plugin(obj, PLUGIN_VENDOR, PLUGIN_VERSION, "Any");

	return status;

}

MStatus uninitializePlugin(MObject obj)
{

	MStatus status;
	MFnPlugin plugin(obj);

	return status;

}