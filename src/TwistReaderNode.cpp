/*
  TwistReaderNode.cpp
  ===================
  Implements the TwistReaderNode class
*/
#include "TwistReaderNode.hpp"

MTypeId TwistReaderNode::id(0x00000); //ID 0 [TEST ONLY]
MObject TwistReaderNode::object;
MObject TwistReaderNode::matrix;
MObject TwistReaderNode::twist;

MStatus TwistReaderNode::compute(const MPlug& plug, MDataBlock& data)
{

	MStatus status;

	//COMPUTE

	return status;

}

MStatus TwistReaderNode::init()
{

	MStatus status;
	MFnTypedAttribute tAttr;
	MFnNumericAttribute nAttr;

	//Object input attribute
	object = tAttr.create("Object", "obj", MFnData::kString, &status);
	status = tAttr.setKeyable(false);
	status = tAttr.setConnectable(false);
	status = addAttribute(object);

	//Matrix input attribute
	matrix = tAttr.create("m", "m", MFnData::kMatrix, &status);
	status = tAttr.setKeyable(false);
	status = addAttribute(matrix);

	//Twist output attribute
	twist = nAttr.create("Twist", "tw", MFnNumericData::kFloat, 0, &status);
	status = nAttr.setKeyable(false);
	status = nAttr.setWritable(false);
	status = addAttribute(twist);

	//Affects
	attributeAffects(object, twist);
	attributeAffects(matrix, twist);

	return status;

}

void* TwistReaderNode::creator()
{

	return new TwistReaderNode();

}