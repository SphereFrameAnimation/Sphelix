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

	//Register node
	plugin.registerNode("Sphelix_TwistReader", TwistReaderNode::id, TwistReaderNode::creator, TwistReaderNode::init, MPxNode::kDependNode);

	return status;

}

MStatus uninitializePlugin(MObject obj)
{

	MStatus status;
	MFnPlugin plugin(obj);

	//Deregister node
	plugin.deregisterNode(TwistReaderNode::id);

	return status;

}